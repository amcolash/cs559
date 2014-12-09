varying vec3 normal;
varying vec2 position;

float randomNoise(vec2 p) {
  return max(fract(10000.*sin(128.*p.x + 1024.*p.y)), 0.5);
}

void main() {

  vec3 cLight = normalize(vec3(.5, .5, 1.0));
  float diffuse = max(0.0, dot(normal, cLight));

  float noise = randomNoise(gl_Position);
  vec3 color = vec3(noise * diffuse);

  gl_FragColor = vec4(color, diffuse);
}