#version 100
uniform mediump float uTime;
attribute mediump vec2 aPos;
attribute mediump vec3 aColor;
varying mediump vec3 vColor;
void main() { gl_Position = vec4(aPos * ((sin(uTime) + 1.5) * 0.75), 0.0, 1.0); vColor = aColor; }

