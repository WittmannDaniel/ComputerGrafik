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
uniform sampler2D BumpTex;

uniform mat4 ModelMatrix;
uniform mat4 NormalMatrix;

uniform vec3 planet_rgb;

out vec4 pass_Normal;
out vec3 color_planet;

//out vec3 pass_normal;
out vec3 pass_toLight;
out vec3 pass_toCamera;

out vec2 pass_Texcoord;

out vec4 pass_position;
out mat4 pass_ViewMatrix;
out vec3 pass_worldPosition;

void main(void)
{
	mat4 ViewMatrix = view_matrix_struct;
	mat4 ProjectionMatrix = projection_matrix_struct;
	vec4 light_position = ViewMatrix * vec4(0.0f,0.0f,0.0f,1.0f);

	 // ------- displacement mapping ------------ //

	pass_Texcoord = in_Texcoord;
	vec4 dv = texture(BumpTex, in_Texcoord);
    float df = (0.30 * dv.x , 0.59 * dv.y , 0.11 * dv.z);

	vec4 newVertexPosition = vec4(in_Normal * df *100.0 , 0) + vec4(in_Position, 1.0f);

	gl_Position = (ProjectionMatrix  * ViewMatrix * ModelMatrix) * newVertexPosition;
	//pass_Normal = (NormalMatrix * vec4(in_Normal, 0.0)).xyz;
	color_planet = planet_rgb;

	vec4 worldPosition = vec4(ViewMatrix * ModelMatrix) * vec4(in_Position, 1.0f);
	
   // normal in world space
   pass_Normal	= (NormalMatrix * vec4 (in_Normal, 0.0f));

   // direction to light
   pass_toLight	= normalize(light_position.xyz - worldPosition.xyz);

   // direction to camera
   pass_toCamera	= normalize( - worldPosition.xyz);

   pass_position =  newVertexPosition;
   pass_ViewMatrix = ViewMatrix;
   pass_worldPosition = worldPosition.xyz;

  
}
