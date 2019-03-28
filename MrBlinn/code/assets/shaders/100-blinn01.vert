#version 100

uniform mediump mat4 model;
uniform mediump mat4 view;
uniform mediump mat4 projection;
uniform mediump mat4 MVP;

attribute mediump vec4 aPos;
attribute mediump vec3 aColor;
attribute mediump vec2 aTexCoord;

varying mediump vec3 vColor;
varying mediump vec2 vTexCoord;

void main() {
  gl_Position = projection * view * model * aPos;
  // gl_Position = MVP * aPos;
  vColor = aColor;
  vTexCoord = aTexCoord;
}
