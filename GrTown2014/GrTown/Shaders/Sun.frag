uniform int timeOfDay;

void main() {

  vec3 color;

  if (timeOfDay <= 6 || timeOfDay > 16)
    color = vec3(0.9, 0.15, 0.1);
  else if ((timeOfDay >= 7 && timeOfDay < 9) || (timeOfDay > 14))
    color = vec3(0.8, 0.5, 0.4);
  else
    color = vec3(1.0, 0.95, 0.85);

  gl_FragColor = vec4(color, 1.0);
}