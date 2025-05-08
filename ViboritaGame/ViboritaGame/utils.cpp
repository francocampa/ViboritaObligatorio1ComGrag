
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

void loadTextTexture(GLuint& textureId, const char* text,TTF_Font* font) {
	SDL_Surface* surfaceText = TTF_RenderText_Blended(font, text, {255,255,255});

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

GLfloat baseCubeColors[] = {
	0,0,0,

	0.05,0.05,0.05,

	0.10,0.10,0.10,

	0.15,0.15,0.15,

	0.20,0.20,0.20,

	0.25,0.25,0.25,

	0.25,0.25,0.30,

	0.25,0.25,0.35,

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