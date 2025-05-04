
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

	glDisableClientState(GL_VERTEX_ARRAY);
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
