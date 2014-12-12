uniform float waveTime;
uniform float waveWidth;
uniform float waveHeight;
varying vec3 fPosition;
varying vec3 normal;

void main()
{
	vec4 v = vec4(gl_Vertex);
	v.z = cos(waveHeight * v.x + waveTime) * waveWidth;

  fPosition = vec3(gl_Vertex.xyz);
  normal = gl_Normal;

	gl_Position = gl_ModelViewProjectionMatrix*v;
}