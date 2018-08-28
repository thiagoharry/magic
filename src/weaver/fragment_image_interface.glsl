/*679:*/
#line 15119 "cweb/weaver.w"


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


/*468:*/
#line 10119 "cweb/weaver.w"

uniform vec4 object_color;
uniform mat4 model_view_matrix;
uniform vec2 object_size;
uniform float time;
uniform sampler2D texture1;
uniform int integer;
/*:468*/
#line 15134 "cweb/weaver.w"


varying mediump vec2 coordinate;

void main(){
gl_FragData[0]= texture2D(texture1,coordinate);
}
/*:679*/
