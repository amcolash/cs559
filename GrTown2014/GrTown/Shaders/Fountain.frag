varying vec3 normal;
uniform int timeOfDay;

void main() {
	//gl_FragColor = vec4(1,0,0,1);
	//vec3 mycolor = normal * 0.5 + vec3(.5,.5,.5);
  float time;

  if (timeOfDay < 5) {
    time = 0.25;
  } else if (timeOfDay < 8) {
    time = 0.5;
  } else if (timeOfDay < 16) {
    time = 0.85;
  } else if (timeOfDay < 19) {
    time = 0.5;
  } else {
    time = 0.25;
  }

	vec3 mycolor = time * vec3(0.25, 0.25, 0.7) + 0.1;
  gl_FragColor = vec4(mycolor.x,mycolor.y,mycolor.z,1);
}