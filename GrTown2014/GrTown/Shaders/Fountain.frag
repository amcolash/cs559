varying vec3 normal;
uniform float timeOfDay;

void main()
{
	//gl_FragColor = vec4(1,0,0,1);
	//vec3 mycolor = normal * 0.5 + vec3(.5,.5,.5);
	vec3 mycolor = vec3(0.25, 0.25, 0.7);
  gl_FragColor = vec4(mycolor.x,mycolor.y,mycolor.z,1);
}