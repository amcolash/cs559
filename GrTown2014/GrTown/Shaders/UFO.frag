varying vec3 normal;
uniform int timeOfDay;

void main() {
  float alpha = 0.0;

  if (timeOfDay < 5 || timeOfDay >= 19) {
    alpha = 1.0;
  }

  vec3 mycolor = normal * 0.5 + vec3(.5, .5, .5);
  gl_FragColor = vec4(mycolor.x, mycolor.y, mycolor.z, alpha);
}