varying vec3 normal;
uniform int timeOfDay;
uniform float ambient;
uniform vec4 light;

uniform float rotation;


void main() {
  float alpha = 0.0;

  if (timeOfDay < 5 || timeOfDay >= 19) {
    alpha = 1.0;
  }

  vec3 mycolor = vec3(0.2, 0.9, 0.7);
  vec3 n = normalize(normal);
  float dl = max(0.0, dot(n, vec3(light[0], light[1], light[2])));

  mycolor *= (ambient + .7*dl);

  gl_FragColor = vec4(mycolor[0], mycolor[1], mycolor[2], alpha);
}