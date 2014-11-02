precision highp float;
uniform float time;
uniform vec2 resolution;
varying vec3 fPosition;
varying vec3 fNormal;
varying vec3 uPos;

void main()
{
  //float ys = uPos.y*100.0 - floor(uPos.y*100.0);
  //float xs = uPos.x*100.0 - floor(uPos.x*100.0);

  //float xc = smoothstep(0.45,.55,xs*0.6);
  //float yc = smoothstep(0.45,.55,ys*0.6);

  vec3 n = normalize(fNormal);
  float dl = max(0.0, dot(n, vec3(.707,.707,0)));

  //gl_FragColor = vec4(xc, yc*0.7, 0.1, 0.7) * (.3+10.0*dl);


  gl_FragColor = vec4(uPos.x, uPos.y, uPos.z, 1.0) * (1.0 + 4.0 * dl);

}
