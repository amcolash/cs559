precision highp float;
attribute vec3 position;
attribute vec3 normal;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
varying vec3 fNormal;

void main()
{
  fNormal = normalize(normalMatrix * normal);
  vec4 pos = modelViewMatrix * vec4(position, 1.0);

  pos.y =  -pos.y;
  pos.x = 1.5 * pos.x;
  pos.z = 0.75 * pos.z;
  gl_Position = projectionMatrix * pos;

}
