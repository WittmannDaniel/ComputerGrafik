#version 150

in  vec4 pass_Normal;
in	vec3 color_planet;

in vec3	pass_toLight;
in vec3	pass_toCamera;

out vec4 out_Color;


	// returns intensity of reflected ambient lighting
float ambientLighting(in float u_matAmbientReflectance, in float u_lightAmbientIntensity)
{
   return float(u_matAmbientReflectance * u_lightAmbientIntensity);
}

// returns intensity of diffuse reflection
float diffuseLighting(in vec4 N, in vec3 L, in float u_matDiffuseReflectance, in float u_lightDiffuseIntensity)
{
   // calculation as for Lambertian reflection
   float diffuseTerm = clamp(dot(N.xyz, L), 0, 1) ;
   return u_matDiffuseReflectance * u_lightDiffuseIntensity * diffuseTerm;
}

// returns intensity of specular reflection
float specularLighting(in vec4 N, in vec3 L, in vec3 V, in float u_matSpecularReflectance, in float u_lightSpecularIntensity, in float u_matShininess)
{
   float specularTerm = 0;

   // calculate specular reflection only if
   // the surface is oriented to the light source
   if(dot(N.xyz, L) > 0)
   {
      // half vector
      vec3 H = normalize(L + V);
      specularTerm = pow(dot(N.xyz, H), u_matShininess);
   }
   return u_matSpecularReflectance * u_lightSpecularIntensity * specularTerm;
}

void main(void)
{
	float u_lightAmbientIntensitys = 0.2;
	float u_lightDiffuseIntensitys = 1;
	float u_lightSpecularIntensitys = 1;

// parameters of the material and possible values
	float u_matAmbientReflectances = 1;
	float u_matDiffuseReflectances = 1;
	float u_matSpecularReflectances = 1;
	float u_matShininess = 64;

   // normalize vectors after interpolation
   vec3 L = normalize(pass_toLight);
   vec3 V = normalize(pass_toCamera);
   vec4 N = normalize(pass_Normal);

   // get Blinn-Phong reflectance components
   float Iamb = ambientLighting(u_matAmbientReflectances, u_lightAmbientIntensitys);
   float Idif = diffuseLighting(N, L, u_matDiffuseReflectances, u_lightDiffuseIntensitys);
   float Ispe = specularLighting(N, L, V, u_matSpecularReflectances, u_lightSpecularIntensitys, u_matShininess);

   // diffuse color of the object from texture
   //vec3 diffuseColor = texture(u_diffuseTexture, o_texcoords).rgb;

   // combination of all components and diffuse color of the object
   //resultingColor.xyz = diffuseColor * (Iamb + Idif + Ispe);
   //resultingColor.a = 1;
   out_Color.xyz = color_planet * (Iamb + Idif + Ispe);
   out_Color.a = 1;
}
