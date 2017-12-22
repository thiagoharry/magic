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
  float final_alpha = texture.a;
  vec3 final_color;
  int branco = 0;
  if(distance(texture.rgb, vec3(1.0, 1.0, 1.0)) < 0.3){
    if(integer == 5 || integer == 3)
      final_alpha = 0.6;
    branco = 1;
  }
  if(integer == 7){ // Tile
    if(object_color.a == 0.0){// Invisível
      if(object_color.rgb != vec3(1.0, 1.0, 1.0)){
        if(final_alpha == 0.0)
          gl_FragData[0] = vec4(1.0, 0.0, 0.0, 0.0);
        else
          gl_FragData[0] = vec4(object_color.rgb, 0.4);
      }
      else
        gl_FragData[0] = vec4(0.0, 0.0, 0.0, 0.0);
    }
    else if(object_color == vec4(0.0, 0.0, 0.0, 1.0)){ // Tile removido
      gl_FragData[0] = vec4(vec3(0.0, 0.0, 0.0), final_alpha);
    }
    else{ // Revelado
      if(branco == 1 && object_color.rgb != vec3(1.0, 1.0, 1.0)){
        final_color.r = clamp(0.0, object_color.r + 0.6, 1.0);
        final_color.g = clamp(0.0, object_color.g + 0.6, 1.0);
        final_color.b = clamp(0.0, object_color.b + 0.6, 1.0);
        gl_FragData[0] = vec4(final_color.rgb, final_alpha);
      }
      else
        gl_FragData[0] = vec4(texture.rgb, final_alpha);
    }
  }
  else{
    if(object_color == vec4(0.0, 0.0, 0.0, 1.0)){
      gl_FragData[0] = vec4(vec3(0.0, 0.0, 0.0), final_alpha);
    }
    else
      gl_FragData[0] = vec4(texture.rgb, final_alpha);
  }
}
