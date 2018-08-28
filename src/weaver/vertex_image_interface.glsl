/*678:*/
#line 15089 "cweb/weaver.w"


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

/*467:*/
#line 10112 "cweb/weaver.w"

attribute vec3 vertex_position;
/*:467*/
#line 15103 "cweb/weaver.w"



/*468:*/
#line 10119 "cweb/weaver.w"

uniform vec4 object_color;
uniform mat4 model_view_matrix;
uniform vec2 object_size;
uniform float time;
uniform sampler2D texture1;
uniform int integer;
/*:468*/
#line 15106 "cweb/weaver.w"


varying mediump vec2 coordinate;

void main(){
gl_Position= model_view_matrix*vec4(vertex_position,1.0);

coordinate= vec2(vertex_position[0]+0.5,vertex_position[1]+0.5);
}
/*:678*/
