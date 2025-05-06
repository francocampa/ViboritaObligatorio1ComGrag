#pragma once  
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

struct Vec3 {  
   float x, y, z;  

   // Sobrecarga del operador == 
   bool operator==(const Vec3& other) const {  
       return x == other.x && y == other.y && z == other.z;  
   }  
};  

struct ViboritaPart {  
   Vec3 gridIndex;  
   Vec3 position;
   ViboritaPart* prePosition;
   ViboritaPart* next;  
};  

struct ViboritaBody {  
   int size;  
   ViboritaPart* head;  
   ViboritaPart* tail;  
};  

enum GAME_ENTITY_TYPE {BLOCK,VIBORITA,APPLE,GOAL};
enum TEX_SETTINGS {FACETADO, INTERPOLADO};
enum TEX_SETTINGS { FACETADO, INTERPOLADO };  

Vec3* getVec3FromVec3(Vec3 vecPrev);

float distance(const Vec3& a, const Vec3& b);

void drawCube(GLfloat vertices[], GLfloat colors[], GLubyte indices[]);  

extern GLfloat baseCubeVertices[];  

extern GLfloat baseCubeColors[];  

extern GLubyte baseCubeIndices[];  

void drawPyramid(GLfloat vertices[12], GLfloat colors[12], GLuint indices[12]);  

extern GLfloat* basePyramidVertices;  

extern GLfloat* basePyramidColors;  

extern GLuint basePyramydIndices[];
