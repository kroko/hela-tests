#version 100
precision mediump float;
varying mediump vec3 vColor;
void main() { gl_FragColor = vec4(vColor, 1.0); }
