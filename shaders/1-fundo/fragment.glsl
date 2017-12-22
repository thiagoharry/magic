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
  vec4 texture = texture2D(texture1, texture_coordinate);
  float final_alpha = texture.a + object_color.a * (1.0 - texture.a);
  gl_FragData[0] = vec4((texture.a * texture.rgb +
                         object_color.rgb * object_color.a *
                         (1.0 - texture.a)) /                        final_alpha, final_alpha);
}
