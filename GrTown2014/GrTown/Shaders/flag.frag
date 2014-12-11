uniform vec2 resolution;
varying vec3 fPosition;
varying vec3 fNormal;
varying vec3 uPos;

varying vec4 outputF;
varying vec3 n;

void main()
{
  vec2 position = fPosition.xy;
 
  float pi = 3.14159265359;
  float wave = sin(.25*pi*position.y);
  wave = (wave+1.)/4.;
 
  gl_FragColor = vec4(vec3(wave-.5, wave+.12, wave+.11), 1.);








	/*float x1 = n.x + pow(n.x,n.x);
	float y1 = n.y + pow(n.y,n.y);
	float x2 = step(x1, 0.0);
	float y2 = smoothstep(x2, x1, y1);
	
  //  vec3 eyeSpaceLightDirection = vec3(2.0,1.0,1.0);
  //  float diffuse = max(0.0,dot(n,eyeSpaceLightDirection));
	gl_FragColor = vec4(n.xz*di, x2, y2);*/
    
}

/*void main()
{
  /*float ys = uPos.y*5.0 - floor(uPos.y*5.0);
  float xs = uPos.x*5.0 - floor(uPos.x*5.0);

  //float xc = smoothstep(.45,.55,xs);
  float yc = smoothstep(.45,.55,ys);
  float xc = 0.5;
  vec3 n = normalize(fNormal);
  float dl = max(0.0, dot(n, vec3(.707,.707,0)));
  
  gl_FragColor = vec4(xc, yc, 0, 1.0);
}*/