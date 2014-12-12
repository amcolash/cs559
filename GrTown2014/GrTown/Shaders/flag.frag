varying vec3 normal;
varying vec3 fPosition;
uniform float ambient;
uniform vec4 light;

void main()
{
  vec2 position = fPosition.xy;

  vec3 n = normalize(normal);
  
  float dl;

  if (light[0] != -1)
	dl = max(0.0, dot(n, vec3(light[0], light[1], light[2])));
  else
	dl = 0.0;

  float pi = 3.14159265359;
  float wave = sin(.25*pi*position.y);
  wave = (wave+1.)/4.;

  wave*= (ambient + .7*dl);
 
  gl_FragColor = vec4(vec3(wave-.5, wave+.12, wave+.11), 1.);







}

