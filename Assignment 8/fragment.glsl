precision highp float;
uniform float time;
uniform vec2 resolution;
varying vec3 fPosition;
varying vec3 fNormal;

void main()
{
  vec3 color = vec3(0.1, 0.7, 0.15) * time/12.0;
  gl_FragColor = vec4(color * fNormal, 0.5);

}
