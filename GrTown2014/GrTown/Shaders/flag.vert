uniform float waveTime;
uniform float waveWidth;
uniform float waveHeight;
varying vec3 fPosition;

void main()
{

	vec4 v = vec4(gl_Vertex);
	v.z = cos(waveHeight * v.x + waveTime) * waveWidth;
	gl_Position = gl_ModelViewProjectionMatrix*v;
	fPosition = gl_Vertex;
}