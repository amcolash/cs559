precision highp float;

varying vec3 n;
varying vec2 uv;

//uniform sampler2D tex;

//#pragma include "noise2D.glsl // for snoise(vec2 v)
//#pragma include "noise3D.glsl" //  for snoise(vec3 v)
//#pragma include "noise4D.glsl" //  for snoise(vec4 v)
//#pragma include "cellular2D.glsl" //  for cellular(vec2 P)
//#pragma include "cellular2x2.glsl" //  for cellular2x2(vec2 P)
//#pragma include "cellular2x2x2.glsl" //  for cellular2x2x2(vec3 P)
//#pragma include "cellular3D.glsl" //  cellular(vec3 P)

void main(void)
{/*
	float ys = n.y*5.0 - floor(n.y*5.0);
	  float y = smoothstep(.45,.55,ys);
  float x = smoothstep(.55, .45, ys);
  float x1 = n.x + pow(n.x,n.x);
	float y1 = n.y + pow(n.y,n.y);
	float x2 = step(x1, 0.0);
	float y2 = smoothstep(x2, x1, y1);
	asdf
    vec3 eyeSpaceLightDirection = vec3(2.0,1.0,1.0);
    //float diffuse = max(0.0,dot(n,eyeSpaceLightDirection));
	//gl_FragColor = vec4(n.xz*diffuse, x2, y2);*/
	gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}