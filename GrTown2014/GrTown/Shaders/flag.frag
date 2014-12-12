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







}

