//attribute vec3 vertex;
//attribute vec2 uv1;
//attribute vec4 tangent;

//uniform mat4 _mv; // model-view matrix
//uniform mat4 _mvProj; // model-view-projection matrix
//uniform mat3 _norm; // normal matrix
uniform float count; // time in seconds

//varying vec2 uv;
//varying vec3 n;
//varying vec3 normal;
//varying vec3 fPosition;

uniform float waveTime;
uniform float waveWidth;
uniform float waveHeight;

void main()
{
	vec4 v = vec4(gl_Vertex);
	//v.z = cos(0.3 * v.x + count*0.01) * 2.0;
	//v.z = sin(waveWidth * v.x + waveTime) * cos(waveWidth * v.y + waveTime) * waveHeight;
	v.z = cos(waveHeight * v.x + waveTime) * waveWidth;
	gl_Position = gl_ModelViewProjectionMatrix*v;
	//gl_TexCoord[0] = gl_MultiTexCoord0;

	/*vec4 v = vec4(fPosition, 1.0);
	v.y = sin(_time);
	v.y += sin(fPosition.z + _time);
	v.y *= fPosition.x * 0.08;
	gl_Position = gl_ModelViewProjectionMatrix * v;
    normal = gl_Normal;
	vec4 v = vec4(vertex, 1.0);
	mat4 modelView = gl_ModelViewMatrix;
	v.z = cos(-5.0*v.x + _time*0.01)*0.25;
	// compute position
	gl_Position = modelView* vec4(v);
	fPosition = gl_Position;
	//uv = uv1;
	// compute light info
//	n = normalize(_norm * normal);*/
}