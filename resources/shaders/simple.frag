#version 430

in  vec4 pass_Normal;
in	vec3 color_planet;

in vec3	pass_toLight;
in vec3	pass_toCamera;

in vec2 pass_Texcoord;

in vec4 pass_position;
in mat4 pass_ViewMatrix;
in vec3 pass_worldPosition;

struct light_data {
  float radius;
  vec4 color;
  vec4 position;
};

layout (std430) buffer light_array {
  light_data lights[];
};

uniform sampler2D u_diffuseTexture;

out vec4 out_Color;


void main() {


  //--------- SUN ---------
  vec4 diffuse_color = texture(u_diffuseTexture, pass_Texcoord);

  vec3 H = normalize(pass_toLight.xyz + pass_toCamera);
  vec4 N = normalize(pass_Normal);
 
  float ka = 0.3; 
  float kd = 0.3; 
  float ks = 0.3; 

  vec3 ia = vec3(0.3f, 0.3f, 0.3f);
  vec3 id = vec3(0.3f, 0.3f, 0.3f);
  vec3 is = vec3(0.3f, 0.3f, 0.3f);

  float reflectance = 2.0f; //0.5f;

  // The formula for the ambient light
  vec3 ambientlight = ka * ia + diffuse_color.rgb;
  vec3 diffuselight = kd * id + diffuse_color.rgb;
  vec3 specularlight = ks * is;
  
  out_Color = vec4(vec3(ambientlight + diffuselight * 
					   dot(pass_toLight.rgb, N.xyz) + specularlight * 
					   pow(dot(N.xyz,H),reflectance)),1.0f);



  for(int i = 0; i != lights.length(); ++i)
  {
	vec4 current_lightpos = pass_ViewMatrix * lights[i].position;
	vec3 current_passtolight = normalize(current_lightpos.xyz - pass_worldPosition.xyz);

	if(length(current_lightpos - pass_position) < lights[i].radius)
		{
			H = normalize(current_passtolight.xyz + pass_toCamera);

			diffuselight = kd * lights[i].color.xyz + diffuse_color.rgb;
			specularlight = ks * lights[i].color.xyz;
			
			out_Color -= vec4(vec3(diffuselight *  dot(current_passtolight.rgb, N.xyz) +
								specularlight * pow(dot(N.xyz,H),reflectance)),1.0f);
		}
  }
}
