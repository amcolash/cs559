varying vec3 normal;

void main()
{
	//	gl_FragColor = vec4(1,0,0,1);
	vec3 mycolor = -normal * .5 + vec3(.5,.5,.5);
	gl_FragColor = vec4(mycolor.x,mycolor.y,mycolor.z,1);
}