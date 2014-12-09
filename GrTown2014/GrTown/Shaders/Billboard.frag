uniform sampler2D myTexture;

varying vec3 normal;
varying vec2 vTexCoord;

void main() {
	//vec3 mycolor = normal * 0.5 + vec3(.5,.5,.5);
  //gl_FragColor = vec4(mycolor.x,mycolor.y,mycolor.z,1);

  gl_FragColor = texture2D(myTexture, vTexCoord).rgba;
}