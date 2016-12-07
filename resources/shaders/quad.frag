#version 150

in vec2 pass_Texcoord;

uniform sampler2D BufferTex;

uniform bool greyscale;


out vec4 out_Color;

void main() {
  out_Color = texture(BufferTex, pass_Texcoord);
  

  
    if (luminance == true)
    {
        float greyscale = 0.2126 * out_Color.r + 0.7152 * out_Color.g + 0.0722 * out_Color.b;

        out_Color = vec4(greyscale,greyscale,greyscale,1.0f);
    }
}