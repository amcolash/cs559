uniform float timeOfDay;

void main() {
  float myTime = timeOfDay - 12.0;

  float intensity = cos(myTime / 4.0) * 1.5;
  vec3 color = vec3(0.7 + intensity, intensity, intensity);

  gl_FragColor = vec4(color, 1.0);
}