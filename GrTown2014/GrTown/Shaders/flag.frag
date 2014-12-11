varying vec3 fPosition;
varying vec3 fNormal;
varying vec3 uPos;

void main()
{
  float ys = uPos.y*5.0 - floor(uPos.y*5.0);
  float xs = uPos.z*5.0 - floor(uPos.z*5.0);

  float xc = smoothstep(.45,.55,xs);
  float yc = step(.45, ys);
  
  //vec3 n = normalize(fNormal);
  //float dl = max(0.0, dot(n, vec3(.5,.707,0)));
  
  gl_FragColor = vec4(xc, xc, 0.0, 5)  ;
}