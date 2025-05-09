/*#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

int main(int argc, char* argv[]){
	//INICIALIZACION
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
		exit(1);
	}

	SDL_Window* win = SDL_CreateWindow("Apple Warm 3D",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDL_GLContext context = SDL_GL_CreateContext(win);

	glMatrixMode(GL_PROJECTION);

	//Proyeccion en perspectiva
	gluPerspective(45, 640 / 480.f, 0.1, 100);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);

	bool fin = false;
	SDL_Event evento;

	//Vertex arrays

	GLfloat colores[] = {
		0.20, 0.20, 0.20,
		0.30, 0.30, 0.30,
		0.50, 0.50, 0.50,
		0.70, 0.70, 0.70,
		0.90, 0.90, 0.90,
		0.110, 0.110, 0.110
	};	

	GLfloat vertices[] = {
		-1.0, -1.0, 1,
		1.0, -1.0, 1,
		1.0, 1.0, 1,
		-1.0, 1.0, 1,
		-1.0, -1.0, 3,
		1.0, -1.0, 3,
		1.0, 1.0, 3,
		-1.0, 1.0, 3
	};

	GLubyte indices[] = {
		0, 1, 2, 3,
		4, 5, 6, 7,
		0, 1, 5, 4,
		2, 3, 7, 6,
		0, 3, 7, 4,
		1, 2, 6, 5
	};

	//Variables de movimiento (awsd)
	bool translate_w = false;
	bool translate_s = false;
	bool translate_a = false;
	bool translate_d = false;

	GLdouble eyeX = 0;
	GLdouble eyeY = 0;
	GLdouble eyeZ = 20;

	do {

		//Movimiento de camara
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(eyeX, eyeY, eyeZ,    // Cámara en (0, 0, 20)
			0.0, 0.0, 0.0,    // Cámara mirando hacia (0, 0, 0)
			0.0, 1.0, 0.0);

		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, colores);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);

		if (translate_w) {
			eyeZ -= 1;
			translate_w = false;
		}
		else if (translate_s) {
			eyeZ += 1;
			translate_s = false;
		}
		else if (translate_a) {
			eyeX -= 1;
			translate_a = false;
		}
		else if (translate_d) {
			eyeX += 1;
			translate_d = false;
		}

		glBegin(GL_QUADS);
		//atras del bloque
		glColor3f(0.20, 0.20, 0.20);
		glVertex3f(-1.0, -1.0, 1);
		glVertex3f(1.0, -1.0, 1);
		glVertex3f(1.0, 1.0, 1);
		glVertex3f(-1.0, 1.0, 1);
		//Base del bloque
		glColor3f(0.30, 0.30, 0.30);
		glVertex3f(-1.0, -1.0, 1);
		glVertex3f(1.0, -1.0, 1);
		glVertex3f(1.0, -1, 3);
		glVertex3f(-1.0, -1, 3);
		//Frente del bloque
		glColor3f(0.50, 0.50, 0.50);
		glVertex3f(-1.0, -1.0, 3);
		glVertex3f(1.0, -1.0, 3);
		glVertex3f(1.0, 1.0, 3);
		glVertex3f(-1.0, 1.0, 3);
		//Techo del bloque
		glColor3f(0.70, 0.70, 0.70);
		glVertex3f(-1.0, 1.0, 1);
		glVertex3f(1.0, 1.0, 1);
		glVertex3f(1.0, 1, 3);
		glVertex3f(-1.0, 1, 3);
		//Lateral izquierdo del bloque
		glColor3f(0.90, 0.90, 0.90);
		glVertex3f(-1.0, -1.0, 1);
		glVertex3f(-1.0, 1.0, 1);
		glVertex3f(-1.0, 1.0, 3);
		glVertex3f(-1.0, -1.0, 3);
		//Lateral derecho del bloque
		glColor3f(0.110, 0.110, 0.110);
		glVertex3f(1.0, -1.0, 1);
		glVertex3f(1.0, 1.0, 1);
		glVertex3f(1.0, 1.0, 3);
		glVertex3f(1.0, -1.0, 3);
		glEnd();

		//MANEJO DE EVENTOS
		while (SDL_PollEvent(&evento)) {
			switch (evento.type) {
			case SDL_QUIT:
				fin = true;
				break;
			case SDL_KEYUP:
				switch (evento.key.keysym.sym) {
				case SDLK_ESCAPE:
					fin = true;
					break;
				case SDLK_RIGHT:
					break;
				}
			case SDL_KEYDOWN:
				switch (evento.key.keysym.sym) {
				case SDLK_w:
					translate_w = true;
					break;
				case SDLK_s:
					translate_s = true;
					break;
				case SDLK_a:
					translate_a = true;
					break;
				case SDLK_d:
					translate_d = true;
					break;
				}
			}
		}
		//FIN MANEJO DE EVENTOS
		SDL_GL_SwapWindow(win);
	} while (!fin);
	//FIN LOOP PRINCIPAL
	// LIMPIEZA
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	SDL_Quit();
    return 0;
}*/
#include <GL/glew.h>
#include "SDL.h"
#include "SDL_opengl.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>	
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <fstream>
#include <string>
#include <sstream>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


using namespace std;
struct VertexData {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
	glm::vec4 color;

};

struct TextureData {
	unsigned char* data;
	int width;
	int height;
	int nrChannels;
};

struct LoadedMaterial {
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
	float shininess;
	std::string diffuseTexturePath;
	std::string specularTexturePath;
	TextureData diffuseTexture;
	GLuint textureID; // Nuevo miembro para el ID de la textura de OpenGL
};

// Función auxiliar para resolver la ruta de la textura (relativa al modelo)
std::string resolveTexturePath(const std::string& textureFile, const std::string& modelPath) {
	if (textureFile.empty()) {
		return "";
	}
	size_t lastSlash = modelPath.find_last_of("/\\");
	std::string directory = (lastSlash == std::string::npos) ? "." : modelPath.substr(0, lastSlash);
	return directory + "/" + textureFile;
}

LoadedMaterial loadMaterial(const aiScene* scene, unsigned int materialIndex, const std::string& modelPath) {
	LoadedMaterial materialData;
	materialData.diffuseColor = glm::vec3(1.0f); // Valores por defecto
	materialData.specularColor = glm::vec3(0.0f);
	materialData.shininess = 1.0f;
	materialData.diffuseTexturePath = "";
	materialData.specularTexturePath = "";
	materialData.diffuseTexture.data = nullptr;
	materialData.diffuseTexture.width = 0;
	materialData.diffuseTexture.height = 0;
	materialData.diffuseTexture.nrChannels = 0;

	if (materialIndex >= scene->mNumMaterials) {
		std::cerr << "Error: Índice de material fuera de rango." << std::endl;
		return materialData;
	}

	aiMaterial* material = scene->mMaterials[materialIndex];
	aiString texturePath;
	aiColor4D color;
	float shininessFactor;

	// 1. Color Difuso
	if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color)) {
		materialData.diffuseColor = glm::vec3(color.r, color.g, color.b);
	}

	// 2. Color Especular
	if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &color)) {
		materialData.specularColor = glm::vec3(color.r, color.g, color.b);
	}

	// 3. Brillo (Shininess)
	if (AI_SUCCESS == aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininessFactor)) {
		materialData.shininess = shininessFactor;
	}

	// 4. Textura Difusa
	if (AI_SUCCESS == aiGetMaterialString(material, AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), &texturePath)) {
		materialData.diffuseTexturePath = resolveTexturePath(texturePath.C_Str(), modelPath);
	}

	// 5. Textura Especular
	if (AI_SUCCESS == aiGetMaterialString(material, AI_MATKEY_TEXTURE(aiTextureType_SPECULAR, 0), &texturePath)) {
		materialData.specularTexturePath = resolveTexturePath(texturePath.C_Str(), modelPath);
	}

	return materialData;
}


std::vector<VertexData> loadOBJWithAssimp(const std::string& filePath, std::vector<unsigned int>& indices, std::vector<LoadedMaterial>& loadedMaterials) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath,
		aiProcess_Triangulate |
		aiProcess_GenNormals |
		aiProcess_FlipUVs | // Opcional: puede ser necesario para algunos formatos/texturas
		aiProcess_JoinIdenticalVertices);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cerr << "Error al cargar el archivo OBJ con Assimp: " << importer.GetErrorString() << std::endl;
		return {};
	}

	std::vector<VertexData> vertices;
	loadedMaterials.resize(scene->mNumMeshes);


	// Procesar cada malla en la escena
	for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
		const aiMesh* mesh = scene->mMeshes[i];;
		unsigned int materialIndex = mesh->mMaterialIndex;

		LoadedMaterial materialData = loadMaterial(scene, materialIndex, "C:/Users/Usuario/Desktop/3D_models/obj/eyeball.obj");

		// Cargar la textura difusa usando IMG_Load
        if (!materialData.diffuseTexturePath.empty()) {
            std::cout << "Intentando cargar textura con SDL_image desde: " << materialData.diffuseTexturePath << std::endl;
            SDL_Surface* loadedSurface = IMG_Load(materialData.diffuseTexturePath.c_str());
            if (!loadedSurface) {
                std::cerr << "Error al cargar la textura con SDL_image: " << materialData.diffuseTexturePath << std::endl;
                std::cerr << "Razón del error (SDL_image): " << IMG_GetError() << std::endl;
            }
            else {
                materialData.diffuseTexture.width = loadedSurface->w;
                materialData.diffuseTexture.height = loadedSurface->h;
                materialData.diffuseTexture.nrChannels = loadedSurface->format->BytesPerPixel;
                materialData.diffuseTexture.data = static_cast<unsigned char*>(loadedSurface->pixels);
                std::cout << "Textura difusa cargada con SDL_image: " << materialData.diffuseTexturePath << " ("
                    << materialData.diffuseTexture.width << "x" << materialData.diffuseTexture.height << " canales: " << materialData.diffuseTexture.nrChannels << ")" << std::endl;
                // Importante: No liberar la superficie aquí. La struct TextureData tiene su propio destructor.
            }
        }


		loadedMaterials[i] = materialData;

		// Procesar vértices
		for (unsigned int j = 0; j < mesh->mNumVertices; ++j) {
			VertexData vertex;

			// Posición
			vertex.position.x = mesh->mVertices[j].x;
			vertex.position.y = mesh->mVertices[j].y;
			vertex.position.z = mesh->mVertices[j].z;

			// Normales (asegurarse de que existan)
			if (mesh->HasNormals()) {
				vertex.normal.x = mesh->mNormals[j].x;
				vertex.normal.y = mesh->mNormals[j].y;
				vertex.normal.z = mesh->mNormals[j].z;
			}
			else {
				vertex.normal = glm::vec3(0.0f, 0.0f, 0.0f); // Si no hay normales, ponerlas a cero
			}

			// Coordenadas de Textura (UVs) - Tomamos el primer conjunto si existe
			if (mesh->HasTextureCoords(0)) {
				vertex.texCoord.x = mesh->mTextureCoords[0][j].x;
				vertex.texCoord.y = mesh->mTextureCoords[0][j].y;
			}
			else {
				vertex.texCoord = glm::vec2(0.0f, 0.0f);
			}

			// Colores de Vértice - Tomamos el primer conjunto si existe
			if (mesh->HasVertexColors(0)) {
				vertex.color.r = mesh->mColors[0][j].r;
				vertex.color.g = mesh->mColors[0][j].g;
				vertex.color.b = mesh->mColors[0][j].b;
				vertex.color.a = mesh->mColors[0][j].a;
			}
			else {
				vertex.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // Color blanco por defecto
			}

			vertices.push_back(vertex);
		}

		// Procesar caras (índices)
		for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {
			const aiFace& face = mesh->mFaces[j];
			for (unsigned int k = 0; k < face.mNumIndices; ++k) {
				indices.push_back(face.mIndices[k]);
			}
		}
	}

	return vertices;
}

void loadTexture(GLuint& textureId, LoadedMaterial& material) {
	if (!material.diffuseTexture.data) {
		std::cerr << "Error: No data to load for texture." << std::endl;
		return;
	}

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	GLenum format = GL_RGB;
	if (material.diffuseTexture.nrChannels == 4) {
		format = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, format, material.diffuseTexture.width, material.diffuseTexture.height, 0,
		format, GL_UNSIGNED_BYTE, material.diffuseTexture.data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	material.textureID = textureId; // Guarda el ID de la textura en la estructura del material
}

void drawLoadedOBJ(const std::vector<VertexData>& vertices, const std::vector<unsigned int>& indices, GLuint objectVAO) {
	// Para dibujar el objeto en tu bucle de renderizado:
	glBindVertexArray(objectVAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


int main(int argc, char** argv) {
	//INICIALIZACION
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
		exit(1);
	}

	SDL_Window* win = SDL_CreateWindow("Apple Warm 3D",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDL_GLContext context = SDL_GL_CreateContext(win);
	if (glewInit() != GLEW_OK) {
		std::cerr << "Error al inicializar GLEW" << std::endl;
		return 1; // O algún otro código de error
	}

	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG; // Añade IMG_INIT_PNG si también vas a cargar PNGs
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cerr << "Error al inicializar SDL_image: " << IMG_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	glMatrixMode(GL_PROJECTION);
	vector<unsigned int> indices;
	vector<LoadedMaterial> loadedMaterials;
	vector<VertexData> vertices = loadOBJWithAssimp("C:/Users/Usuario/Desktop/3D_models/obj/eyeball.obj", indices, loadedMaterials);
	std::cout << "Primeros bytes de la textura: ";
	for (int i = 0; i < 100; ++i) {
		std::cout << static_cast<int>(loadedMaterials[0].diffuseTexture.data[i]) << " ";
	}
	std::cout << std::endl;
	loadedMaterials[0].textureID = 0; // Inicializar el ID de textura
		loadedMaterials[0].textureID = 0;
		loadTexture(loadedMaterials[0].textureID, loadedMaterials[0]);
	
	// Crear texturas de OpenGL para cada material cargado
	cout<<loadedMaterials.size();

	// Generar y enlazar el Vertex Array Object (VAO)
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Generar y llenar el Vertex Buffer Object (VBO) con los datos de los vértices
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData), &vertices[0], GL_STATIC_DRAW);

	// Generar y llenar el Element Buffer Object (EBO) con los índices
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// Configurar los atributos del vértice (posición) - layout(0) en el shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
	glEnableVertexAttribArray(0);

	// Configurar los atributos del vértice (normal) - layout(1) en el shader
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, normal));
	glEnableVertexAttribArray(1);

	// Desenlazar el VAO (puedes enlazarlo de nuevo cuando vayas a dibujar)
	glBindVertexArray(0);

	// Guardar el VAO para usarlo en el bucle de renderizado
	static GLuint objectVAO = 0;
	if (objectVAO == 0) {
		objectVAO = VAO;
	}

	//Proyeccion en perspectiva
	gluPerspective(45, 640 / 480.f, 0.1, 100);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);

	bool fin = false;
	SDL_Event evento;

	GLfloat moveX = 0;
	GLfloat moveY = 0;
	GLfloat moveZ = 0;


	//Vertex arrays

	GLfloat colores[] = {
		0.20, 0.20, 0.20,
		0.30, 0.30, 0.30,
		0.50, 0.50, 0.50,
		0.70, 0.70, 0.70,
		0.90, 0.90, 0.90,
		0.110, 0.110, 0.110
	};

	GLubyte indices1[] = {
		0, 1, 2, 3,
		4, 5, 6, 7,
		0, 1, 5, 4,
		2, 3, 7, 6,
		0, 3, 7, 4,
		1, 2, 6, 5
	};

	GLfloat luz_posicion[4] = { 0, 0, 1, 1 };
	GLfloat luz_posicion1[4] = { 0, 0, -1, 1 };
	GLfloat colorLuz[4] = { 1, 1, 1, 1 };

	//Variables de movimiento (awsd)
	bool translate_w = false;
	bool translate_s = false;
	bool translate_a = false;
	bool translate_d = false;
	bool translate_right = false;
	bool translate_left = false;
	bool translate_up = false;
	bool translate_down = false;


	GLdouble eyeX = 0;
	GLdouble eyeY = 0;
	GLdouble eyeZ = 20;
	
	do {
		//Movimiento de camara
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(eyeX, eyeY, eyeZ,    // Cámara en (0, 0, 20)
			0.0, 0.0, 0.0,    // Cámara mirando hacia (0, 0, 0)
			0.0, 1.0, 0.0);

			glEnable(GL_LIGHT0); // habilita la luz 0
		glLightfv(GL_LIGHT0, GL_POSITION, luz_posicion);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, colorLuz);

		glEnable(GL_LIGHT1); // habilita la luz 1
		glLightfv(GL_LIGHT1, GL_POSITION, luz_posicion1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, colorLuz);
		glTranslatef(0, 0, 0);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		drawLoadedOBJ(vertices, indices, objectVAO);

		GLfloat vertices1[] = {
		-1.0 + moveX, -1.0 + moveY, 1 + moveZ,
		1.0 + moveX, -1.0 + moveY, 1 + moveZ,
		1.0 + moveX, 1.0 + moveY, 1 + moveZ,
		-1.0 + moveX, 1.0 + moveY, 1 + moveZ,
		-1.0 + moveX, -1.0 + moveY, 3 + moveZ,
		1.0 + moveX, -1.0 + moveY, 3 + moveZ,
		1.0 + moveX, 1.0 + moveY, 3 + moveZ,
		-1.0 + moveX, 1.0 + moveY, 3 + moveZ
		};

		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glColorPointer(3, GL_FLOAT, 0, colores);
		glVertexPointer(3, GL_FLOAT, 0, vertices1);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices1);
		

		if (translate_w) {
			eyeZ -= 1;
			translate_w = false;
		}
		else if (translate_s) {
			eyeZ += 1;
			translate_s = false;
		}
		else if (translate_a) {
			eyeX -= 1;
			translate_a = false;
		}
		else if (translate_d) {
			eyeX += 1;
			translate_d = false;
		}
		else if (translate_right) {
			moveX += 1;
			translate_right = false;
		}
		else if (translate_left) {
			moveX -= 1;
			translate_left = false;
		}
		else if (translate_up) {
			moveY += 1;
			translate_up = false;
		}
		else if (translate_down) {
			moveY -= 1;
			translate_down = false;
		}	

		//MANEJO DE EVENTOS
		while (SDL_PollEvent(&evento)) {
			switch (evento.type) {
			case SDL_QUIT:
				fin = true;
				break;
			case SDL_KEYUP:
				switch (evento.key.keysym.sym) {
				case SDLK_ESCAPE:
					fin = true;
					break;
				case SDLK_RIGHT:
					break;
				}
			case SDL_KEYDOWN:
				switch (evento.key.keysym.sym) {
				case SDLK_w:
					translate_w = true;
					break;
				case SDLK_s:
					translate_s = true;
					break;
				case SDLK_a:
					translate_a = true;
					break;
				case SDLK_d:
					translate_d = true;
					break;
				case SDLK_RIGHT:
					translate_right = true;
					break;
				case SDLK_LEFT:
					translate_left = true;
					break;
				case SDLK_UP:
					translate_up = true;
					break;
				case SDLK_DOWN:
					translate_down = true;
					break;
				}
			}
		}
		//FIN MANEJO DE EVENTOS
		SDL_GL_SwapWindow(win);
	} while (!fin);
	//FIN LOOP PRINCIPAL
	// LIMPIEZA
	IMG_Quit();
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
