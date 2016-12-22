#version 150
#extension GL_ARB_explicit_attrib_location : require

// vertex attributes
layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Color;

//Matrix Uniforms 
layout (std140) uniform shader_data{
	mat4 view_matrix_struct;
	mat4 projection_matrix_struct;
};


out vec3 pass_Color;

void main()
{
	gl_Position = (view_matrix_struct  * projection_matrix_struct) * vec4(in_Position, 1.0f);
	pass_Color 	= in_Color;
}