struct shader_data
{
	glm::fmat4 view_matrix_struct;
	glm::fmat4 projection_matrix_struct;
};

struct light_data
{
	float radius;
	glm::vec3 color;
	glm::vec2 position;
};