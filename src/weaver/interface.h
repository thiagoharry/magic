/*391:*/
#line 8695 "cweb/weaver.w"

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
#line 8702 "cweb/weaver.w"

/*394:*/
#line 8733 "cweb/weaver.w"

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
/*641:*/
#line 14132 "cweb/weaver.w"


GLuint*_texture;
bool _loaded_texture;
bool animate;
unsigned number_of_frames;
unsigned current_frame;
unsigned*frame_duration;
unsigned long _t;
int max_repetition;
/*:641*/
#line 8747 "cweb/weaver.w"


#ifdef W_MULTITHREAD
pthread_mutex_t _mutex;
#endif
}_interfaces[W_MAX_SUBLOOP][W_MAX_INTERFACES];
#ifdef W_MULTITHREAD


pthread_mutex_t _interface_mutex;
#endif
/*:394*//*395:*/
#line 8766 "cweb/weaver.w"

#define W_NONE                 0
#define W_INTERFACE_SQUARE    -1
#define W_INTERFACE_PERIMETER -2
/*:395*//*398:*/
#line 8810 "cweb/weaver.w"

void _flush_interfaces(void);
/*:398*//*403:*/
#line 8882 "cweb/weaver.w"

GLfloat _interface_vertices[12];

GLuint _interface_VBO;

GLuint _interface_VAO;
/*:403*//*406:*/
#line 8939 "cweb/weaver.w"

struct interface*_new_interface(int type,int x,int y,int width,
int height,...);
/*:406*//*410:*/
#line 9037 "cweb/weaver.w"

bool _destroy_interface(struct interface*inter);
/*:410*//*414:*/
#line 9091 "cweb/weaver.w"

struct interface*_copy_interface(struct interface*inter);
/*:414*//*419:*/
#line 9154 "cweb/weaver.w"

void _move_interface(struct interface*,float x,float y);
/*:419*//*423:*/
#line 9246 "cweb/weaver.w"

void _resize_interface(struct interface*inter,float size_x,float size_y);
/*:423*//*427:*/
#line 9325 "cweb/weaver.w"

void _rotate_interface(struct interface*inter,float rotation);
/*:427*//*434:*/
#line 9547 "cweb/weaver.w"

void _update_interface_screen_size(void);
/*:434*//*464:*/
#line 10365 "cweb/weaver.w"

struct interface*_interface_queue[W_MAX_SUBLOOP][W_MAX_INTERFACES];
/*:464*//*466:*/
#line 10392 "cweb/weaver.w"

void _insert_interface_queue(struct interface*inter);
/*:466*//*468:*/
#line 10440 "cweb/weaver.w"

void _remove_interface_queue(struct interface*inter);
/*:468*//*470:*/
#line 10509 "cweb/weaver.w"

void _clean_interface_queue(void);
/*:470*//*646:*/
#line 14201 "cweb/weaver.w"

#define W_INTERFACE_IMAGE -3
/*:646*//*651:*/
#line 14369 "cweb/weaver.w"

void _finalize_interface_texture(void*);
/*:651*//*667:*/
#line 14743 "cweb/weaver.w"

#ifndef W_DISABLE_PNG
GLuint*_extract_png(char*,unsigned*,unsigned**,int*,bool*);
#endif
/*:667*//*668:*/
#line 14757 "cweb/weaver.w"

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
/*669:*/
#line 14799 "cweb/weaver.w"

{
char header[8];






fread(header,1,8,fp);
if(png_sig_cmp(header,0,8)){
fprintf(stderr,"ERROR: %s don't have a PNG header.\n",filename);
goto error_png;
}
}
/*:669*//*670:*/
#line 14819 "cweb/weaver.w"

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
/*:670*//*671:*/
#line 14847 "cweb/weaver.w"

{
if(setjmp(png_jmpbuf(png_ptr))){
fprintf(stderr,"ERROR: %s initialization failed.\n",filename);
goto error_png;
}
}
/*:671*//*672:*/
#line 14860 "cweb/weaver.w"

{
png_init_io(png_ptr,fp);
}
/*:672*//*673:*/
#line 14871 "cweb/weaver.w"

{
png_set_sig_bytes(png_ptr,8);
}
/*:673*//*674:*/
#line 14882 "cweb/weaver.w"

{
png_read_info(png_ptr,info_ptr);
width= png_get_image_width(png_ptr,info_ptr);
height= png_get_image_height(png_ptr,info_ptr);
color_type= png_get_color_type(png_ptr,info_ptr);
bit_depth= png_get_bit_depth(png_ptr,info_ptr);
}
/*:674*//*675:*/
#line 14896 "cweb/weaver.w"

{
number_of_passes= png_set_interlace_handling(png_ptr);
}
/*:675*//*676:*/
#line 14907 "cweb/weaver.w"

{
png_read_update_info(png_ptr,info_ptr);
if(setjmp(png_jmpbuf(png_ptr))){
fprintf(stderr,"ERROR: Failed to interpret %s .\n",filename);
goto error_png;
}
}
/*:676*//*677:*/
#line 14923 "cweb/weaver.w"

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
/*:677*/
#line 14776 "cweb/weaver.w"

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
/*:668*/
#line 8703 "cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:391*/
