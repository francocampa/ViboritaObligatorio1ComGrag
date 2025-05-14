#include "utils.h"

float distance(const Vec3& a, const Vec3& b) {
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	float dz = b.z - a.z;
	return std::sqrt(dx * dx + dy * dy + dz * dz);
}

void drawCube(GLfloat vertices[24], GLfloat colors[24], GLubyte indices[24]) {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);
	for (int i = 0; i < 6; ++i) {
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, &indices[i * 4]);
	}
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

Vec3* getVec3FromVec3(Vec3 vecPrev) {
	Vec3* vec = new Vec3;
	vec->x = vecPrev.x;
	vec->y = vecPrev.y;
	vec->z = vecPrev.z;
	return vec;
}

void loadTexture(GLuint& textureId, const char* path) {
	SDL_Surface* surface = IMG_Load(path);
	SDL_Surface* converted = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
	SDL_FreeSurface(surface);

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	GLenum format = (converted->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, converted->w, converted->h, 0,
		format, GL_UNSIGNED_BYTE, converted->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	SDL_FreeSurface(converted);
}

void loadTextTexture(GLuint& textureId, const char* text,TTF_Font* font, int &width, int &height) {
	SDL_Surface* surfaceText = TTF_RenderText_Blended(font, text, {255,255,255});
	width = surfaceText->w;
	height = surfaceText->h;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surfaceText->w, surfaceText->h, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, surfaceText->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	SDL_FreeSurface(surfaceText);
}

GLfloat baseCubeVertices[] = {
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,

	0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f
};
GLfloat baseKeyboardKeyVertices[] = {
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.5f, 0.0f,
	0.0f, 0.5f, 0.0f,

	0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f,
	1.0f, 0.5f, 1.0f,
	0.0f, 0.5f, 1.0f
};

GLfloat baseCubeColors[] = {
	0.3,0.3,0.3,
	0.3,0.3,0.3,
	0.3,0.3,0.3,
	0.3,0.3,0.3,
	0.3,0.3,0.3,
	0.3,0.3,0.3,
	0.3,0.3,0.3,
	0.3,0.3,0.3,

};

GLubyte baseCubeIndices[] = {
	0, 1, 2, 3, // Front face
	4, 5, 6, 7, // Back face
	0, 1, 5, 4, // Left face
	1, 2, 6, 5, // Right face
	2, 3, 7, 6, // Top face
	0, 3, 7, 4  // Bottom face
};


void drawPyramid(GLfloat vertices[12], GLfloat colors[12], GLuint indices[12]) {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);
	for (int i = 0; i < 4; ++i) {
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, &indices[i * 3]);
	}

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

GLfloat* basePyramidVertices = new GLfloat[12]{
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 
	0.5f, 0.0f, 0.866f,
	0.5f, 1.0f, 0.288f 
};

GLfloat* basePyramidColors = new GLfloat[12]{
	1.0f, 0.388f, 0.278f,
	1.0f, 0.288f, 0.278f,
	1.0f, 0.388f, 0.278f,
	1.0f, 0.288f, 0.278f,
};

GLuint basePyramydIndices[] = {
	0, 1, 2,  // Base triangle (ABC)

	0, 1, 3,  // Side triangle (AB + top)
	1, 2, 3,  // Side triangle (BC + top)
	2, 0, 3   // Side triangle (CA + top)
};

void drawArrowKeys(Vec3 position) {
	Vec3 color = { 0.82f, 0.80f, 0.72f };
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glScalef(1, 0.5, 1);
	glTranslatef(1.2f,0,0);
	drawCubeWithNormals(color); // ^
	
	glPopMatrix();

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glScalef(1, 0.5, 1);
	glTranslatef(0, 0, -1.2f);
	drawCubeWithNormals(color); // <
	
	glTranslatef(1.2f, 0, 0);
	drawCubeWithNormals(color); // \/

	glTranslatef(1.2f, 0, 0);
	drawCubeWithNormals(color); // >
	glPopMatrix();

}

Vec3 crossProduct(Vec3 a, Vec3 b) {
	return {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

Vec3 normalize(Vec3 v) {
	float length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length == 0.0f) return { 0, 0, 0 }; // avoid division by zero
	return { v.x / length, v.y / length, v.z / length };
}

GLfloat baseViboritaColors[24] = {
			0.0f, 0.25f, 0.0f,
			0.0f, 0.30f, 0.0f,
			0.0f, 0.35f, 0.0f,
			0.0f, 0.40f, 0.0f,
			0.0f, 0.45f, 0.0f,
			0.0f, 0.50f, 0.0f,
			0.0f, 0.55f, 0.0f,
			0.0f, 0.60f, 0.0f
};
GLfloat headColors[24] = {
			0.0f, 0.25f, 0.3f,
			0.0f, 0.30f, 0.3f,
			0.0f, 0.35f, 0.3f,
			0.0f, 0.40f, 0.3f,
			0.0f, 0.45f, 0.3f,
			0.0f, 0.50f, 0.3f,
			0.0f, 0.55f, 0.3f,
			0.0f, 0.60f, 0.3f
};

std::vector<modelInfo> modelsInfo;

void cargarModelo(std::string& filePath, std::string name,int pos) {
	// Implementación de cargarModelo
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath,
		aiProcess_Triangulate |
		aiProcess_GenNormals |
		aiProcess_FlipUVs | // Opcional: puede ser necesario para algunos formatos/texturas
		aiProcess_JoinIdenticalVertices);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cerr << "Error al cargar el archivo OBJ con Assimp: " << importer.GetErrorString() << std::endl;
		return ;
	}

	std::vector<VertexData> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> normals;

	// Procesar cada malla en la escena
	for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
		const aiMesh* mesh = scene->mMeshes[i];;
		unsigned int materialIndex = mesh->mMaterialIndex;

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

				normals.push_back(mesh->mNormals[j].x);
				normals.push_back(mesh->mNormals[j].y);
				normals.push_back(mesh->mNormals[j].z);
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
				vertex.color = glm::vec4(0.5f, 0.5f, 0.5f, 0.5f); // Color blanco por defecto
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

	if (modelsInfo.size() <= pos) {
		modelsInfo.resize(pos + 1);
	}

	// Guardar el VAO para usarlo en el bucle de renderizado
	modelsInfo[pos].name = name;
	modelsInfo[pos].vertices = vertices;
	modelsInfo[pos].indices = indices;
	modelsInfo[pos].normals = normals;
}

void drawModel(MODEL_TYPE modelType, bool textures) {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	const GLfloat* vertexData;
	const GLuint* indexData;
	const GLfloat* normalsData;
	int indexModel;
	switch (modelType)
	{
	case APPLE_MODEL:
		indexModel = 0;
		break;
	case WORM_HEAD_MODEL:
		indexModel = 1;
		break;
	case WORM_BODY_MODEL:
		indexModel = 2;
		break;
	case WORM_TAIL_MODEL:
		indexModel = 3;
		break;
	case GOAL_MODEL:
		indexModel = 4;
		break;
	default:
		break;
	}
	if (textures) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, modelsInfo[indexModel].textureId);
	}
	
	vertexData = reinterpret_cast<const GLfloat*>(modelsInfo[indexModel].vertices.data());
	indexData = modelsInfo[indexModel].indices.data();
	normalsData = modelsInfo[indexModel].normals.data();
	glVertexPointer(3, GL_FLOAT, sizeof(VertexData), &vertexData[0]);
	glNormalPointer(GL_FLOAT, 0, normalsData);
	glTexCoordPointer(2, GL_FLOAT, sizeof(VertexData), &vertexData[offsetof(VertexData, texCoord)]);
	for (size_t i = 0; i < modelsInfo[indexModel].indices.size() / 3; ++i) {
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, &indexData[i * 3]);
	}
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	if (textures)
		glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

GLfloat cubeNormalsColors[] = {
	0.3,0.3,0.3,
	0.3,0.3,0.3,
	0.3,0.3,0.3,
	0.3,0.3,0.3,

	0.3,0.3,0.3,
	0.3,0.3,0.3,
	0.3,0.3,0.3,
	0.3,0.3,0.3,

	0.3,0.3,0.3,
	0.3,0.3,0.3,
	0.3,0.3,0.3,
	0.3,0.3,0.3,

	0.3,0.3,0.3,
	0.3,0.3,0.3,
	0.3,0.3,0.3,
	0.3,0.3,0.3,

	0.3,0.3,0.3,
	0.3,0.3,0.3,
	0.3,0.3,0.3,
	0.3,0.3,0.3,

	0.3,0.3,0.3,
	0.3,0.3,0.3,
	0.3,0.3,0.3,
	0.3,0.3,0.3,

};


GLfloat normalCubeVertices[] = {
	// Front face
	0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f,

	// Back face
	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,

	// Left face
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 0.0f,

	// Right face
	1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f,

	// Top face
	0.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,

	// Bottom face
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
};

GLfloat cubeNormals[] = {
	// Front face normals
	 0.0f,  0.0f,  1.0f,
	 0.0f,  0.0f,  1.0f,
	 0.0f,  0.0f,  1.0f,
	 0.0f,  0.0f,  1.0f,

	 // Back face normals
	  0.0f,  0.0f, -1.0f,
	  0.0f,  0.0f, -1.0f,
	  0.0f,  0.0f, -1.0f,
	  0.0f,  0.0f, -1.0f,

	  // Left face normals
	  -1.0f,  0.0f,  0.0f,
	  -1.0f,  0.0f,  0.0f,
	  -1.0f,  0.0f,  0.0f,
	  -1.0f,  0.0f,  0.0f,

	  // Right face normals
	   1.0f,  0.0f,  0.0f,
	   1.0f,  0.0f,  0.0f,
	   1.0f,  0.0f,  0.0f,
	   1.0f,  0.0f,  0.0f,

	   // Top face normals
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,

		// Bottom face normals
		 0.0f, -1.0f,  0.0f,
		 0.0f, -1.0f,  0.0f,
		 0.0f, -1.0f,  0.0f,
		 0.0f, -1.0f,  0.0f,
};

GLuint cubeNormalsIndices[] = {
	0, 1, 2, 3,     // Front face
	4, 5, 6, 7,     // Back face
	8, 9,10,11,     // Left face
   12,13,14,15,     // Right face
   16,17,18,19,     // Top face
   20,21,22,23      // Bottom face
};


void drawCubeWithNormals(Vec3 color) {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glColor3f(color.x,color.y,color.z);
	glVertexPointer(3, GL_FLOAT, 0, normalCubeVertices);
	glNormalPointer(GL_FLOAT, 0, cubeNormals);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, &cubeNormalsIndices);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glColor3f(1, 1, 1);
}

Light defaultLight = { { 0.0f, 10.0f, 0.0f, 1.0f } ,{ 0.2f, 0.2f, 0.2f, 1.0f },{ 0.8f, 0.8f, 0.8f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
Material defaultMaterial = { {0.2f, 0.2f, 0.2f, 1.0f} , {0.8f, 0.8f, 0.8f, 1.0f} ,  {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f} };

void applyMaterial(Material m) {
	glMaterialfv(GL_FRONT, GL_AMBIENT, m.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m.specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, m.shininess);
}


//glLightfv(GL_LIGHT0, GL_POSITION, defaultLight.position);
//glLightfv(GL_LIGHT0, GL_AMBIENT, defaultLight.ambient);
//glLightfv(GL_LIGHT0, GL_DIFFUSE, defaultLight.diffuse);
//glLightfv(GL_LIGHT0, GL_SPECULAR, defaultLight.specular);