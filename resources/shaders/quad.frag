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
}