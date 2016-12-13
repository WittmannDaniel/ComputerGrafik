#version 150

uniform sampler2D ColorTex;
uniform bool greyscale;

in vec2 pass_Texcoord;
out vec4 out_Color;



void main() {


	vec2 texCoords = pass_Texcoord;
	vec4 color = vec4(0.0f);
	 color = texture(ColorTex, texCoords);

	if (greyscale)
    {
		color = vec4(vec3(dot(vec3(0.2126f, 0.7152f, 0.0722f), color.rgb)), color.a);
    }

    out_Color = color;

	//out_Color = vec4(0.0f);
  
    //if (greyscale == true)
    //{
       // float grey = 0.2126 * out_Color.r + 0.7152 * out_Color.g + 0.0722 * out_Color.b;

     //   out_Color = vec4(grey,grey,grey,1.0f);
    //}

}