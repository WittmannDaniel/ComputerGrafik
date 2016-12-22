#version 140
#extension GL_ARB_explicit_attrib_location : require
// vertex attributes of VAO
layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_Texcoord;

//struct light_data {
//  float radius;
//  vec3 color;
//  vec2 position;
//};

//layout (std430, binding = 3) buffer light_array {
//  light_data lights[];
//};

layout (std140) uniform shader_data{

	mat4 view_matrix_struct;
	mat4 projection_matrix_struct;
};

//Matrix Uniforms as specified with glUniformMatrix4fv
uniform mat4 ModelMatrix;
//uniform mat4 ViewMatrix;
//uniform mat4 ProjectionMatrix;
uniform mat4 NormalMatrix;

//Vector Unifrom glUniform3f
uniform vec3 planet_rgb;
//uniform vec3 light_position;

out vec4 pass_Normal;
out vec3 color_planet;

//out vec3 pass_normal;
out vec3 pass_toLight;
out vec3 pass_toCamera;

out vec2 pass_Texcoord;

void main(void)
{
	mat4 ViewMatrix = view_matrix_struct;
	mat4 ProjectionMatrix = projection_matrix_struct;
	//vec3 camera_position = vec3(0.0f,0.0f,0.0f);
	vec4 light_position = /*vec4(5.0f,0.0f,0.0f,4.0f);*/ViewMatrix * vec4(0.0f,0.0f,0.0f,1.0f);

	gl_Position = (ProjectionMatrix  * ViewMatrix * ModelMatrix) * vec4(in_Position, 1.0f);
	//pass_Normal = (NormalMatrix * vec4(in_Normal, 0.0)).xyz;
	color_planet = planet_rgb;

	vec3 worldPosition = vec3((ViewMatrix * ModelMatrix) * vec4(in_Position, 1.0f));
	
   // normal in world space
   pass_Normal	= (NormalMatrix * vec4 (in_Normal, 0.0f));

   // direction to light
   pass_toLight	= normalize(light_position.xyz - worldPosition.xyz);

   // direction to camera
   pass_toCamera	= normalize( - worldPosition.xyz);

   pass_Texcoord = in_Texcoord;

}
