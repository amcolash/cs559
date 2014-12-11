varying vec3 normal;
uniform float ambient;
uniform vec4 light;

void main() {

	vec3 mycolor = vec3(0.25, 0.25, 0.7);
  vec3 n = normalize(normal);
  float dl = max(0.0, dot(n, vec3(light[0], light[1], light[2])));

  mycolor *= (ambient + .7*dl);

  gl_FragColor = vec4(mycolor[2], mycolor[1], mycolor[0], 1.0);
}