#version 100

#if GL_FRAGMENT_PRECISION_HIGH == 1
  precision highp float;
  precision highp int;
#else
  precision mediump float;
  precision mediump int;
#endif
  precision lowp sampler2D;
  precision lowp samplerCube;

uniform vec4 object_color;

uniform float time;
uniform vec2 object_size;
uniform int integer;

uniform sampler2D texture1;
varying mediump vec2 texture_coordinate;

void main(){
  float r, g, b;
  vec4 texture = texture2D(texture1, texture_coordinate);
  if(object_color.r < texture.r)
    r = object_color.r;
  else
    r = texture.r;
  if(object_color.g < texture.g)
    g = object_color.g;
  else
    g = texture.g;
  if(object_color.b < texture.b)
    b = object_color.b;
  else
    b = texture.b;
  if(texture.a != 0.0)
    gl_FragData[0] = vec4(r, g, b, texture.a);
  else
    gl_FragData[0] = texture;
}
