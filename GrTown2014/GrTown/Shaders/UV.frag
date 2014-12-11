varying vec3 normal;

void main() {
  gl_FragColor = vec4(gl_TexCoord[0].xy, 1.0, 1.0);
}