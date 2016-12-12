#version 150

in vec2 pass_Texcoord;

//uniform sampler2D BufferTex;

uniform bool greyscale;


out vec4 out_Color;

void main() {
  //out_Color = texture(BufferTex, pass_Texcoord);
  
	out_Color = vec4(0.0f);
  
    if (greyscale == true)
    {
        float grey = 0.2126 * out_Color.r + 0.7152 * out_Color.g + 0.0722 * out_Color.b;

        out_Color = vec4(grey,grey,grey,1.0f);
    }

}