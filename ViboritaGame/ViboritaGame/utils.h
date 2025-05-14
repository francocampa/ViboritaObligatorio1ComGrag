#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <cmath>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vec3 {  
   float x, y, z;  

   // Sobrecarga del operador == 
   bool operator==(const Vec3& other) const {  
       return x == other.x && y == other.y && z == other.z;  
   }  
};  

struct VertexData {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
	glm::vec4 color;

};

struct ViboritaPart {  
   Vec3 gridIndex;  
   Vec3 position;
   ViboritaPart* next;  
};  

struct ViboritaBody {  
   int size;  
   ViboritaPart* head;  
   ViboritaPart* tail;  
};  

struct modelInfo {
	std::string name;
	std::vector<VertexData> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> normals;
	GLuint objectVAO;
	GLuint textureId;
};

enum BUTTON_TYPE { BUTTON, SLIDER, CHECKBOX, TEXTFIELD};
enum GAME_ENTITY_TYPE {BLOCK,VIBORITA,APPLE,GOAL};
enum TEX_SETTINGS {FACETADO, INTERPOLADO};
enum MODEL_TYPE {APPLE_MODEL, WORM_HEAD_MODEL, WORM_BODY_MODEL, WORM_TAIL_MODEL, GOAL_MODEL};

Vec3* getVec3FromVec3(Vec3 vecPrev);

extern std::vector<modelInfo> modelsInfo;//Arreglo que contiene la información de cada modelo

extern GLuint cubeTexture;//ID de la textura del cubo

struct Vec2 {
	int x, y;
};

void loadTexture(GLuint& textureId, const char* path);
void loadTextTexture(GLuint& textureId, const char* text, TTF_Font* font, int& width, int& height);

float distance(const Vec3& a, const Vec3& b);

extern GLfloat cubeTextureCoords[];

void drawCube(GLfloat vertices[24], GLfloat colors[24], GLubyte indices[24]);

extern GLfloat baseCubeVertices[];  

extern GLfloat baseCubeColors[];  

extern GLubyte baseCubeIndices[];  

void drawPyramid(GLfloat vertices[12], GLfloat colors[12], GLuint indices[12]);  

extern GLfloat* basePyramidVertices;  

extern GLfloat* basePyramidColors;  

extern GLuint basePyramydIndices[];

extern GLfloat baseKeyboardKeyVertices[];

void drawArrowKeys(Vec3 position);

Vec3 crossProduct(Vec3 a, Vec3 b);

Vec3 normalize(Vec3 v);

extern GLfloat baseViboritaColors[24];
extern GLfloat headColors[24];

void cargarModelo(std::string& filePath, std::string name, int pos);

void drawModel(MODEL_TYPE,bool textures);

extern GLfloat cubeNormals[];
extern GLfloat cubeNormalsColors[];
extern GLuint cubeNormalsIndices[];
void drawCubeWithNormals(Vec3 color, bool textures);

struct Light {
	GLfloat position[4];
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
};
extern Light defaultLight;
struct Material {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess[1];
};
extern Material defaultMaterial;

void applyMaterial(Material);