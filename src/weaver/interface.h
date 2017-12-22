/*391:*/
#line 8694 "cweb/weaver.w"

#ifndef _interface_h_
#define _interface_h_
#ifdef __cplusplus
extern"C"{
#endif
#include "weaver.h"
/*66:*/
#line 1927 "cweb/weaver.w"

#include "conf_begin.h"
#include "../../conf/conf.h"
#include "conf_end.h"
/*:66*/
#line 8701 "cweb/weaver.w"

/*394:*/
#line 8732 "cweb/weaver.w"

struct interface{
int type;
int integer;

float x,y;
float rotation;
float r,g,b,a;
float height,width;
bool visible;

GLfloat _transform_matrix[16];

GLenum _mode;
/*656:*/
#line 14541 "cweb/weaver.w"


GLuint*_texture;
bool _loaded_texture;
bool animate;
unsigned number_of_frames;
unsigned current_frame;
unsigned*frame_duration;
unsigned long _t;
int max_repetition;
/*:656*/
#line 8746 "cweb/weaver.w"


#ifdef W_MULTITHREAD
pthread_mutex_t _mutex;
#endif
}_interfaces[W_MAX_SUBLOOP][W_MAX_INTERFACES];
#ifdef W_MULTITHREAD


pthread_mutex_t _interface_mutex;
#endif
/*:394*//*395:*/
#line 8765 "cweb/weaver.w"

#define W_NONE                 0
#define W_INTERFACE_SQUARE    -1
#define W_INTERFACE_PERIMETER -2
/*:395*//*398:*/
#line 8809 "cweb/weaver.w"

void _flush_interfaces(void);
/*:398*//*403:*/
#line 8881 "cweb/weaver.w"

GLfloat _interface_vertices[12];

GLuint _interface_VBO;

GLuint _interface_VAO;
/*:403*//*406:*/
#line 8938 "cweb/weaver.w"

struct interface*_new_interface(int type,int x,int y,int width,
int height,...);
/*:406*//*410:*/
#line 9036 "cweb/weaver.w"

bool _destroy_interface(struct interface*inter);
/*:410*//*414:*/
#line 9090 "cweb/weaver.w"

struct interface*_copy_interface(struct interface*inter);
/*:414*//*419:*/
#line 9153 "cweb/weaver.w"

void _move_interface(struct interface*,float x,float y);
/*:419*//*423:*/
#line 9245 "cweb/weaver.w"

void _resize_interface(struct interface*inter,float size_x,float size_y);
/*:423*//*427:*/
#line 9324 "cweb/weaver.w"

void _rotate_interface(struct interface*inter,float rotation);
/*:427*//*434:*/
#line 9546 "cweb/weaver.w"

void _update_interface_screen_size(void);
/*:434*//*464:*/
#line 10364 "cweb/weaver.w"

struct interface*_interface_queue[W_MAX_SUBLOOP][W_MAX_INTERFACES];
/*:464*//*466:*/
#line 10391 "cweb/weaver.w"

void _insert_interface_queue(struct interface*inter);
/*:466*//*468:*/
#line 10439 "cweb/weaver.w"

void _remove_interface_queue(struct interface*inter);
/*:468*//*470:*/
#line 10508 "cweb/weaver.w"

void _clean_interface_queue(void);
/*:470*//*661:*/
#line 14610 "cweb/weaver.w"

#define W_INTERFACE_IMAGE -3
/*:661*//*669:*/
#line 14872 "cweb/weaver.w"

void _finalize_interface_texture(void*);
/*:669*//*685:*/
#line 15260 "cweb/weaver.w"

#ifndef W_DISABLE_PNG
GLuint*_extract_png(char*,unsigned*,unsigned**,int*,bool*);
#endif
/*:685*//*686:*/
#line 15274 "cweb/weaver.w"

#ifndef W_DISABLE_PNG
GLuint*_extract_png(char*filename,unsigned*number_of_frames,
unsigned**frame_duration,int*max_repetition,
bool*error){
int width,height,number_of_passes;
unsigned char*pixel_array;
png_byte color_type,bit_depth;
png_structp png_ptr;
png_infop info_ptr;
png_bytep*row_pointers;
GLuint*returned_data= NULL;
FILE*fp= fopen(filename,"r");
*error= false;

if(fp==NULL){
fprintf(stderr,"ERROR: Can't open file %s.\n",filename);
goto error_png;
}
/*687:*/
#line 15316 "cweb/weaver.w"

{
char header[8];






fread(header,1,8,fp);
if(png_sig_cmp(header,0,8)){
fprintf(stderr,"ERROR: %s don't have a PNG header.\n",filename);
goto error_png;
}
}
/*:687*//*688:*/
#line 15336 "cweb/weaver.w"

{






png_ptr= png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
if(!png_ptr){
fprintf(stderr,"ERROR: Can't create structure to read PNG.\n");
goto error_png;
}
info_ptr= png_create_info_struct(png_ptr);
if(!info_ptr){
fprintf(stderr,"ERROR: Can't create structure to read PNG.\n");
goto error_png;
}
}
/*:688*//*689:*/
#line 15364 "cweb/weaver.w"

{
if(setjmp(png_jmpbuf(png_ptr))){
fprintf(stderr,"ERROR: %s initialization failed.\n",filename);
goto error_png;
}
}
/*:689*//*690:*/
#line 15377 "cweb/weaver.w"

{
png_init_io(png_ptr,fp);
}
/*:690*//*691:*/
#line 15388 "cweb/weaver.w"

{
png_set_sig_bytes(png_ptr,8);
}
/*:691*//*692:*/
#line 15399 "cweb/weaver.w"

{
png_read_info(png_ptr,info_ptr);
width= png_get_image_width(png_ptr,info_ptr);
height= png_get_image_height(png_ptr,info_ptr);
color_type= png_get_color_type(png_ptr,info_ptr);
bit_depth= png_get_bit_depth(png_ptr,info_ptr);
}
/*:692*//*693:*/
#line 15413 "cweb/weaver.w"

{
number_of_passes= png_set_interlace_handling(png_ptr);
}
/*:693*//*694:*/
#line 15424 "cweb/weaver.w"

{
png_read_update_info(png_ptr,info_ptr);
if(setjmp(png_jmpbuf(png_ptr))){
fprintf(stderr,"ERROR: Failed to interpret %s .\n",filename);
goto error_png;
}
}
/*:694*//*695:*/
#line 15440 "cweb/weaver.w"

{
int y,z;
pixel_array= (unsigned char*)Walloc(width*height*4);
if(pixel_array==NULL){
fprintf(stderr,"ERROR: No enough memory to load %s. "
"Please increase the value of W_MAX_MEMORY at conf/conf.h.\n",
filename);
goto error_png;
}
row_pointers= (png_bytep*)Walloc(sizeof(png_bytep)*height);
if(row_pointers==NULL){
Wfree(pixel_array);
fprintf(stderr,"ERROR: No enough memory to load %s. "
"Please increase the value of W_MAX_MEMORY at conf/conf.h.\n",
filename);
goto error_png;
}
for(y= 0;y<height;y++){
row_pointers[y]= (png_byte*)Walloc(png_get_rowbytes(png_ptr,info_ptr));
if(row_pointers[y]==NULL){
for(z= y-1;z>=0;x--)
Wfree(row_pointers[z]);
Wfree(pixel_array);
fprintf(stderr,"ERROR: No enough memory to load %s. "
"Please increase the value of W_MAX_MEMORY at conf/conf.h.\n",
filename);
goto error_png;
}
}

png_read_image(png_ptr,row_pointers);
fclose(fp);
}
/*:695*/
#line 15293 "cweb/weaver.w"

goto end_of_png;
error_png:

*error= true;
returned_data= NULL;
end_of_png:

#if W_TARGET == W_ELF && !defined(W_MULTITHREAD)
fclose(fp);
#else

#endif
return returned_data;
}
#endif
/*:686*/
#line 8702 "cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:391*/
