ion highp float;
uniform float time;
uniform vec2 resolution;
varying vec3 fPosition;
varying vec3 fNormal;

float seed = 0.123456789;

float rand()
{
  seed = seed + 0.987654321;
  return mod(seed, 1.0);

}

void main()
{
  vec3 color = vec3(rand(), rand(), rand());
  color = cos(color);
  gl_FragColor = vec4(color * fNormal, 0.5) * cos(time);

}
