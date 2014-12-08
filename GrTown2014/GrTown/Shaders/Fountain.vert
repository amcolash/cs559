uniform float counter;
varying vec3 normal;

const float PI = 3.14159;

void main()
{
  vec4 v = gl_Vertex;
	
  v.y = 10 * sin(counter);

  gl_Position = gl_ModelViewProjectionMatrix * v;
	normal = gl_Normal;
}