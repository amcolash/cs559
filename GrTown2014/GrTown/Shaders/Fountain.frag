varying vec3 normal;
uniform float ambient;
uniform vec4 light;

float randomNoise(vec2 p) {
  return max(fract(6791.*sin(47.*p.x + p.y*9973.)), 0.5);
}

void main() {

  vec3 mycolor = vec3(0.95t , 0.85, 0.85);

  vec2 p = gl_FragCoord.xz;

  float noise = randomNoise(p);
  mycolor =  vec3(vec3(noise) * mycolor);

  vec3 n = normalize(normal);

  float dl;

  if (light[0] != -1)
	dl = max(0.0, dot(n, vec3(light[0], light[1], light[2])));
  else
	dl = 0.0;

	 mycolor *= (ambient + .7*dl);

  gl_FragColor = vec4(mycolor[2], mycolor[1], mycolor[0], 1.0);
}