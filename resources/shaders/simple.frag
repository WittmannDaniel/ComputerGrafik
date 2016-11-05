#version 150

in  vec3 pass_Normal;
in	vec3 color_planet;
out vec4 out_Color;

void main() {
  out_Color = vec4(color_planet, 1.0f);
}
