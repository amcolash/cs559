varying vec3 normal;

void main()
{
  normal = gl_Normal;
  gl_TexCoord[0] = gl_MultiTexCoord0;
  
  mat4 modelView = gl_ModelViewMatrix;
  int spherical = 1;

  // First colunm.
  modelView[0][0] = 0.0;
  modelView[0][1] = 0.0;
  modelView[0][2] = 1.0;

  if (spherical == 1) {
    // Second colunm.
    modelView[1][0] = 0.0;
    modelView[1][1] = 1.0;
    modelView[1][2] = 0.0;
  }

  // Thrid colunm.
  modelView[2][0] = 1.0;
  modelView[2][1] = 0.0;
  modelView[2][2] = 0.0;

  gl_Position = gl_ProjectionMatrix * modelView * gl_Vertex;
}