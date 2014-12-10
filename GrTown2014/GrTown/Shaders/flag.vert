attribute vec3 vertex;
attribute vec3 normal;
attribute vec2 uv1;
//attribute vec4 tangent;

//uniform mat4 _mv; // model-view matrix
uniform mat4 _mvProj; // model-view-projection matrix
uniform mat3 _norm; // normal matrix
uniform float _time; // time in seconds

varying vec2 uv;
varying vec3 n;

void main(void) {
	
	vec4 v = vec4(vertex, 1.0);
	 mat4 modelView = gl_ModelViewMatrix;
	//v.z = cos(-5.0*v.z + _time*0.01)*0.25;
	// compute position
	gl_Position = modelView* vec4(v);
	
	uv = uv1;
	// compute light info
	n = normalize(_norm * normal);
}