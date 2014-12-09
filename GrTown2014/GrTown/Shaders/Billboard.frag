uniform sampler2D texture;

void main() {
	//vec3 mycolor = normal * 0.5 + vec3(.5,.5,.5);
  //gl_FragColor = vec4(mycolor.x,mycolor.y,mycolor.z,1);
  //gl_FragColor = vec4(gl_TexCoord[0].y);

  vec4 color = texture2D(texture, gl_TexCoord[0]);

  if (color.rgb == vec3(1.0, 0.0, 0.0))
    discard;

  gl_FragColor = color;
}