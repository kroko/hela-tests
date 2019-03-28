#version 100
precision mediump float;

uniform mediump sampler2D uTexture;
uniform mediump float uTime;

varying mediump vec3 vColor;
varying mediump vec2 vTexCoord;

void main() {
  // attribute color
  vec4 colorVertAttr = vec4(vColor, 1.0);

  // Texture data is in linear colorspace, so no converting
  vec4 colorVertUv = texture2D(uTexture, vTexCoord);

  gl_FragColor = colorVertUv;

  // Do gamma correction on final output ourselves
  float gamma = 2.2;
  gl_FragColor.rgb = pow(gl_FragColor.rgb, vec3(1.0/gamma));

}
