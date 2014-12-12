varying vec3 normal;
uniform float counter;


void main() {
  vec3 color = vec3(0.2, 0.8, 0.3);
  color += (normal / 32.0);

  gl_FragColor = vec4(color, (sin(counter * 0.1) + 1.0) * 0.25);
}