struct shader_data
{
	glm::fmat4 view_matrix_struct;
	glm::fmat4 projection_matrix_struct;
};

struct light_data
{
	float radius;
	glm::vec4 color;
	glm::vec4 position;
};