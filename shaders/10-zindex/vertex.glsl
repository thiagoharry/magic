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


attribute vec3 vertex_position;

uniform vec4 object_color;
uniform mat4 model_view_matrix;
uniform float time;
uniform vec2 object_size;
uniform int integer;

varying mediump vec2 texture_coordinate;

void main(){
  gl_Position = model_view_matrix * vec4(vertex_position, 1.0);
  //gl_Position = gl_Position + vec4(0.0, 0.0, 1.0 - 1.0/float(integer), 0.0);
  gl_Position.z = -1.0 + 1.0/float(integer+1);
  texture_coordinate = vec2(vertex_position[0] + 0.5, vertex_position[1] + 0.5);
}
