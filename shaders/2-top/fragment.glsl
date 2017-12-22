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

// top
void main(){
  float alpha = 0.6;
  vec4 texture = texture2D(texture1, texture_coordinate);
  vec4 texture2;
  if(texture_coordinate.y > 0.96){
    if(distance(texture.rgb, vec3(1.0, 1.0, 1.0)) < 0.1 ||
       distance(texture.rgb, vec3(0.0, 0.0, 0.0)) < 0.1){
      alpha = 1.0;
    }
  }
  else if(texture_coordinate.y > 0.92){
    if(texture_coordinate.x < 0.2)
      alpha = 0.2;
    else
      alpha = 0.5;
  }
  else if(texture_coordinate.y < 0.1){
    if(distance(texture.rgb, vec3(1.0, 1.0, 1.0)) < 0.1 ||
       distance(texture.rgb, vec3(0.0, 0.0, 0.0)) < 0.1)
      alpha = 0.0;
    else
      alpha = 0.25;
  }
  else if(texture_coordinate.y < 0.2){
    texture2 = texture2D(texture1, texture_coordinate + vec2(0.0, -0.1));
    if(distance(texture2.rgb, vec3(1.0, 1.0, 1.0)) < 0.1 ||
       distance(texture2.rgb, vec3(0.0, 0.0, 0.0)) < 0.1){
      alpha = 1.0;
      texture = texture2;
    }
  }
  gl_FragData[0] = vec4(texture.rgb, alpha);
}
