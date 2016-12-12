#include <iostream>

struct QuadObj {
	GLuint vertex_AO = 0;
	GLuint vertex_BO = 0;
	GLuint element_BO = 0;
};

struct FBtexObj {
	GLenum context = GL_TEXTURE0;
	GLenum target = GL_TEXTURE_2D;
	GLuint obj_ptr = 0;
};