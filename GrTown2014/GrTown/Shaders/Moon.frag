uniform vec2 resolution;
varying vec3 normal;
varying vec3 fPosition;

float randomNoise(vec2 p) {
  return max(fract(6791.*sin(47.*p.x + p.y*9973.)), 0.5);
}

float interpolatedNoise(vec2 p) {
  float q11 = randomNoise(vec2(floor(p.x), floor(p.y)));
  float q12 = randomNoise(vec2(floor(p.x), ceil(p.y)));
  float q21 = randomNoise(vec2(ceil(p.x), floor(p.y)));
  float q22 = randomNoise(vec2(ceil(p.x), ceil(p.y)));

  float r1 = mix(q11, q21, fract(p.x));
  float r2 = mix(q12, q22, fract(p.x));

  return mix(r1, r2, fract(p.y));
}

void main() {
  vec2 position = gl_FragCoord.xy / resolution.xx;
  float tiles = 8.0;
  position *= tiles;

  float noise = interpolatedNoise(position.xy);
  vec3 color = vec3(noise);

  gl_FragColor = vec4(color, 1.0);
}