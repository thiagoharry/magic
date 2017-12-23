/*392:*/
#line 8708 "cweb/weaver.w"

#include "interface.h"
#include <stdarg.h>  
#if W_TARGET == W_WEB
#include <sys/stat.h>  
#include <sys/types.h>  
#endif
/*666:*/
#line 14733 "cweb/weaver.w"

#ifndef W_DISABLE_PNG
#include <png.h> 
#endif
/*:666*/
#line 8715 "cweb/weaver.w"

/*648:*/
#line 14292 "cweb/weaver.w"

#if W_TARGET == W_WEB
static void onerror_texture(unsigned undocumented,void*interface,
int error_code){
fprintf(stderr,"WARNING (0): Couldn't load a texture file. Code %d.\n",
error_code);
#ifdef W_MULTITHREAD
pthread_mutex_lock(&(W._pending_files_mutex));
#endif
W.pending_files--;
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&(W._pending_files_mutex));
#endif
}
#endif
/*:648*//*649:*/
#line 14312 "cweb/weaver.w"

#if W_TARGET == W_WEB
static void onload_texture(unsigned undocumented,
void*inter,const char*filename){
char*ext;
bool ret= true;
struct interface*my_interface= (struct interface*)inter;

ext= strrchr(filename,'.');
if(!ext){
onerror_texture(0,inter,0);
return;
}
if(!strcmp(ext,".gif")||!strcmp(ext,".GIF")){
my_interface->_texture= 
_extract_gif((char*)filename,
&(my_interface->number_of_frames),
&(my_interface->frame_duration),
&(my_interface->max_repetition),&ret);
}
if(ret){
my_interface->type= W_NONE;
return;
}

if(my_interface->number_of_frames> 1)
my_interface->animate= true;
_finalize_after(my_interface,_finalize_interface_texture);

my_interface->_loaded_texture= true;
#ifdef W_MULTITHREAD
pthread_mutex_lock(&(W._pending_files_mutex));
#endif
W.pending_files--;
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&(W._pending_files_mutex));
#endif
}
#endif
/*:649*//*650:*/
#line 14356 "cweb/weaver.w"

#if W_TARGET == W_WEB
static void onprogress_texture(unsigned int undocumented,void*snd,
int percent){
return;
}
#endif
/*:650*/
#line 8716 "cweb/weaver.w"

/*399:*/
#line 8812 "cweb/weaver.w"

void _flush_interfaces(void){
int i;
for(i= 0;i<W_MAX_INTERFACES;i++){
switch(_interfaces[_number_of_loops][i].type){




default:
_interfaces[_number_of_loops][i].type= W_NONE;
}
#ifdef W_MULTITHREAD
if(pthread_mutex_destroy(&(_interfaces[_number_of_loops][i]._mutex))!=
0)
perror("Finalizing interface mutex:");
#endif
}
}
/*:399*//*407:*/
#line 8942 "cweb/weaver.w"

struct interface*_new_interface(int type,int x,int y,int width,
int height,...){
int i;
va_list valist;
struct interface*new_interface= (struct interface*)1;
#ifdef W_MULTITHREAD
pthread_mutex_lock(&_interface_mutex);
#endif

for(i= 0;i<W_MAX_INTERFACES;i++)
if(_interfaces[_number_of_loops][i].type==W_NONE)
break;
if(i==W_MAX_INTERFACES){
#if W_DEBUG_LEVEL >  0
fprintf(stderr,"WARNING (1): Unable to create new interfaces. Please, "
"define W_MAX_INTERFACES as a value greater than %d at "
"conf/conf.h.\n",W_MAX_INTERFACES);
#endif
new_interface= NULL;
}
else{
_interfaces[_number_of_loops][i].type= type;
_interfaces[_number_of_loops][i].visible= true;
_interfaces[_number_of_loops][i].integer= 0;

_interfaces[_number_of_loops][i].r= 1.0;
_interfaces[_number_of_loops][i].g= 1.0;
_interfaces[_number_of_loops][i].b= 1.0;
_interfaces[_number_of_loops][i].a= 1.0;

_interfaces[_number_of_loops][i].x= (float)x;
_interfaces[_number_of_loops][i].y= (float)y;
_interfaces[_number_of_loops][i].rotation= 0.0;
_interfaces[_number_of_loops][i].width= (float)width;
_interfaces[_number_of_loops][i].height= (float)height;

_interfaces[_number_of_loops][i]._mode= GL_TRIANGLE_FAN;
/*645:*/
#line 14177 "cweb/weaver.w"

{
_interfaces[_number_of_loops][i]._texture= &_empty_texture;




_interfaces[_number_of_loops][i]._loaded_texture= true;
_interfaces[_number_of_loops][i].animate= false;
_interfaces[_number_of_loops][i].number_of_frames= 1;
_interfaces[_number_of_loops][i].current_frame= 0;
_interfaces[_number_of_loops][i].frame_duration= NULL;
_interfaces[_number_of_loops][i]._t= W.t;
_interfaces[_number_of_loops][i].max_repetition= -1;
}
/*:645*/
#line 8980 "cweb/weaver.w"

#ifdef W_MULTITHREAD
if(pthread_mutex_init(&(_interfaces[_number_of_loops][i]._mutex),
NULL)!=0){
_interfaces[_number_of_loops][i].type= W_NONE;
perror("Initializing interface mutex:");
new_interface= NULL;
}
#endif
if(new_interface!=NULL){
switch(type){
case W_INTERFACE_PERIMETER:
_interfaces[_number_of_loops][i]._mode= GL_LINE_LOOP;

case W_INTERFACE_SQUARE:
va_start(valist,height);
_interfaces[_number_of_loops][i].r= va_arg(valist,double);
_interfaces[_number_of_loops][i].g= va_arg(valist,double);
_interfaces[_number_of_loops][i].b= va_arg(valist,double);
_interfaces[_number_of_loops][i].a= va_arg(valist,double);
va_end(valist);
break;
/*647:*/
#line 14208 "cweb/weaver.w"

case W_INTERFACE_IMAGE:
_interfaces[_number_of_loops][i]._loaded_texture= false;
{
#if W_TARGET == W_WEB
char dir[]= "image/";
#elif W_DEBUG_LEVEL >= 1
char dir[]= "./image/";
#elif W_TARGET == W_ELF
char dir[]= W_INSTALL_DATA"/image/";
#endif
#if W_TARGET == W_ELF
char*ext;
bool ret= true;
#endif
char*filename,complete_path[256];
va_start(valist,height);
filename= va_arg(valist,char*);
va_end(valist);

strncpy(complete_path,dir,256);
complete_path[255]= '\0';
strncat(complete_path,filename,256-strlen(complete_path));
#if W_TARGET == W_WEB

if(mkdir("image/",0777)==-1)
perror(NULL);
W.pending_files++;

emscripten_async_wget2(complete_path,complete_path,
"GET","",
(void*)&(_interfaces[_number_of_loops][i]),
&onload_texture,&onerror_texture,
&onprogress_texture);
#else

ext= strrchr(filename,'.');
if(!ext){
fprintf(stderr,"WARNING (0): No file extension in %s.\n",
filename);
_interfaces[_number_of_loops][i].type= W_NONE;
return NULL;
}
if(!strcmp(ext,".gif")||!strcmp(ext,".GIF")){
_interfaces[_number_of_loops][i]._texture= 
_extract_gif(complete_path,
&(_interfaces[_number_of_loops][i].number_of_frames),
&(_interfaces[_number_of_loops][i].frame_duration),
&(_interfaces[_number_of_loops][i].max_repetition),
&ret);
if(ret){
_interfaces[_number_of_loops][i].type= W_NONE;
return NULL;
}

if(_interfaces[_number_of_loops][i].number_of_frames> 1)
_interfaces[_number_of_loops][i].animate= true;
_interfaces[_number_of_loops][i]._loaded_texture= true;



_finalize_after(&(_interfaces[_number_of_loops][i]),
_finalize_interface_texture);
}
#endif
}
break;
/*:647*/
#line 9002 "cweb/weaver.w"

default:
/*662:*/
#line 14561 "cweb/weaver.w"

{
#if W_TARGET == W_WEB
char dir[]= "image/";
#elif W_DEBUG_LEVEL >= 1
char dir[]= "./image/";
#elif W_TARGET == W_ELF
char dir[]= W_INSTALL_DATA"/image/";
#endif
#if W_TARGET == W_ELF
char*ext;
bool ret= true;
#endif
char*filename,complete_path[256];
va_start(valist,height);
filename= va_arg(valist,char*);
if(filename!=NULL&&filename[0]!='\0'){
_interfaces[_number_of_loops][i]._loaded_texture= false;

strncpy(complete_path,dir,256);
complete_path[255]= '\0';
strncat(complete_path,filename,256-strlen(complete_path));

#if W_TARGET == W_WEB
mkdir("images/",0777);
W.pending_files++;

emscripten_async_wget2(complete_path,complete_path,
"GET","",
(void*)&(_interfaces[_number_of_loops][i]),
&onload_texture,&onerror_texture,
&onprogress_texture);
#else

ext= strrchr(filename,'.');
if(!ext){
fprintf(stderr,"WARNING (0): No file extension in %s.\n",
filename);
_interfaces[_number_of_loops][i].type= W_NONE;
return NULL;
}
if(!strcmp(ext,".gif")||!strcmp(ext,".GIF")){
_interfaces[_number_of_loops][i]._texture= 
_extract_gif(complete_path,
&(_interfaces[_number_of_loops][i].number_of_frames),
&(_interfaces[_number_of_loops][i].frame_duration),
&(_interfaces[_number_of_loops][i].max_repetition),
&ret);
if(ret){
_interfaces[_number_of_loops][i].type= W_NONE;
return NULL;
}

if(_interfaces[_number_of_loops][i].number_of_frames> 1)
_interfaces[_number_of_loops][i].animate= true;
_interfaces[_number_of_loops][i]._loaded_texture= true;



_finalize_after(&(_interfaces[_number_of_loops][i]),
_finalize_interface_texture);
}
#endif
}
va_end(valist);
}
/*:662*/
#line 9004 "cweb/weaver.w"

;
}
/*431:*/
#line 9478 "cweb/weaver.w"

{
float nx,ny,cosine,sine,x1,y1;
nx= 2.0*((float)_interfaces[_number_of_loops][i].width);
ny= 2.0*((float)_interfaces[_number_of_loops][i].height);
cosine= cosf(_interfaces[_number_of_loops][i].rotation);
sine= sinf(_interfaces[_number_of_loops][i].rotation);
x1= (2.0*((float)_interfaces[_number_of_loops][i].x/
(float)W.width))-1.0;
y1= (2.0*((float)_interfaces[_number_of_loops][i].y/
(float)W.height))-1.0;
_interfaces[_number_of_loops][i]._transform_matrix[0]= nx*cosine/
(float)W.width;
_interfaces[_number_of_loops][i]._transform_matrix[4]= -(ny*sine)/
(float)W.width;
_interfaces[_number_of_loops][i]._transform_matrix[8]= 0.0;
_interfaces[_number_of_loops][i]._transform_matrix[12]= x1;
_interfaces[_number_of_loops][i]._transform_matrix[1]= nx*sine/
(float)W.height;
_interfaces[_number_of_loops][i]._transform_matrix[5]= ny*cosine/
(float)W.height;
_interfaces[_number_of_loops][i]._transform_matrix[9]= 0.0;
_interfaces[_number_of_loops][i]._transform_matrix[13]= y1;
_interfaces[_number_of_loops][i]._transform_matrix[2]= 0.0;
_interfaces[_number_of_loops][i]._transform_matrix[3]= 0.0;
_interfaces[_number_of_loops][i]._transform_matrix[10]= 1.0;
_interfaces[_number_of_loops][i]._transform_matrix[14]= 0.0;
_interfaces[_number_of_loops][i]._transform_matrix[3]= 0.0;
_interfaces[_number_of_loops][i]._transform_matrix[7]= 0.0;
_interfaces[_number_of_loops][i]._transform_matrix[11]= 0.0;
_interfaces[_number_of_loops][i]._transform_matrix[15]= 1.0;
}
/*:431*/
#line 9007 "cweb/weaver.w"

/*474:*/
#line 10538 "cweb/weaver.w"


_insert_interface_queue(&(_interfaces[_number_of_loops][i]));
/*:474*/
#line 9008 "cweb/weaver.w"

new_interface= &(_interfaces[_number_of_loops][i]);
}
}
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&_interface_mutex);
#endif
return new_interface;
}
/*:407*//*411:*/
#line 9039 "cweb/weaver.w"

bool _destroy_interface(struct interface*inter){
int i;

for(i= 0;i<W_MAX_INTERFACES;i++)
if(&(_interfaces[_number_of_loops][i])==inter&&inter->type!=W_NONE)
break;
if(i==W_MAX_INTERFACES)
return false;
/*475:*/
#line 10546 "cweb/weaver.w"


_remove_interface_queue(&(_interfaces[_number_of_loops][i]));
/*:475*//*653:*/
#line 14387 "cweb/weaver.w"

{
_finalize_this(&_interfaces[_number_of_loops][i],true);
if(_interfaces[_number_of_loops][i]._texture!=&_empty_texture)
Wfree(_interfaces[_number_of_loops][i]._texture);
_finalize_interface_texture((void*)&_interfaces[_number_of_loops][i]);
}
/*:653*/
#line 9048 "cweb/weaver.w"

switch(_interfaces[_number_of_loops][i].type){

case W_INTERFACE_SQUARE:
case W_INTERFACE_PERIMETER:
case W_NONE:
default:
_interfaces[_number_of_loops][i].type= W_NONE;
}
#ifdef W_MULTITHREAD
if(pthread_mutex_destroy(&(_interfaces[_number_of_loops][i]._mutex))!=0){
perror("Error destroying mutex from interface:");
Wexit();
}
#endif
return true;
}
/*:411*//*415:*/
#line 9093 "cweb/weaver.w"

struct interface*_copy_interface(struct interface*inter){
int i;
struct interface*new_interface= (struct interface*)1;
#ifdef W_MULTITHREAD
pthread_mutex_lock(&_interface_mutex);
#endif

for(i= 0;i<W_MAX_INTERFACES;i++)
if(_interfaces[_number_of_loops][i].type==W_NONE)
break;
if(i==W_MAX_INTERFACES){
#if W_DEBUG_LEVEL >  0
fprintf(stderr,"WARNING (1): Not enough space for interfaces. Please, "
"increase the value of W_MAX_INTERFACES at conf/conf.h.\n");
#endif
new_interface= NULL;
}
else{

new_interface= &(_interfaces[_number_of_loops][i]);
memcpy(new_interface,inter,sizeof(struct interface));


#ifdef W_MULTITHREAD
if(pthread_mutex_init(&(_interfaces[_number_of_loops][i]._mutex),
NULL)!=0){
_interfaces[_number_of_loops][i].type= W_NONE;
perror("Initializing interface mutex:");
new_interface= NULL;
}
#endif
}
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&_interface_mutex);
#endif
return new_interface;
}
/*:415*//*420:*/
#line 9217 "cweb/weaver.w"

void _move_interface(struct interface*inter,float x,float y){
#ifdef W_MULTITHREAD
pthread_mutex_lock(&(inter->_mutex));
#endif
inter->x= x;
inter->y= y;
/*432:*/
#line 9515 "cweb/weaver.w"

{
float x1,y1;
x1= (2.0*((float)inter->x/(float)W.width))-1.0;
y1= (2.0*((float)inter->y/(float)W.height))-1.0;
inter->_transform_matrix[12]= x1;
inter->_transform_matrix[13]= y1;
}
/*:432*/
#line 9224 "cweb/weaver.w"

#ifdef W_MULTITHREAD
pthread_mutex_unlock(&(inter->_mutex));
#endif
}
/*:420*//*424:*/
#line 9296 "cweb/weaver.w"

void _resize_interface(struct interface*inter,float size_x,float size_y){
#ifdef W_MULTITHREAD
pthread_mutex_lock(&(inter->_mutex));
#endif
inter->height= size_y;
inter->width= size_x;
/*433:*/
#line 9528 "cweb/weaver.w"

{
float nx,ny,cosine,sine;
nx= 2.0*((float)inter->width);
ny= 2.0*((float)inter->height);
cosine= cosf(inter->rotation);
sine= sinf(inter->rotation);
inter->_transform_matrix[0]= (nx*cosine)/(float)W.width;
inter->_transform_matrix[4]= -(ny*sine)/(float)W.width;
inter->_transform_matrix[1]= (nx*sine)/(float)W.height;
inter->_transform_matrix[5]= (ny*cosine)/(float)W.height;
}
/*:433*/
#line 9303 "cweb/weaver.w"

#ifdef W_MULTITHREAD
pthread_mutex_unlock(&(inter->_mutex));
#endif
}
/*:424*//*428:*/
#line 9377 "cweb/weaver.w"

void _rotate_interface(struct interface*inter,float rotation){
#ifdef W_MULTITHREAD
pthread_mutex_lock(&(inter->_mutex));
#endif
inter->rotation= rotation;
/*433:*/
#line 9528 "cweb/weaver.w"

{
float nx,ny,cosine,sine;
nx= 2.0*((float)inter->width);
ny= 2.0*((float)inter->height);
cosine= cosf(inter->rotation);
sine= sinf(inter->rotation);
inter->_transform_matrix[0]= (nx*cosine)/(float)W.width;
inter->_transform_matrix[4]= -(ny*sine)/(float)W.width;
inter->_transform_matrix[1]= (nx*sine)/(float)W.height;
inter->_transform_matrix[5]= (ny*cosine)/(float)W.height;
}
/*:433*/
#line 9383 "cweb/weaver.w"

#ifdef W_MULTITHREAD
pthread_mutex_unlock(&(inter->_mutex));
#endif
}
/*:428*//*435:*/
#line 9550 "cweb/weaver.w"

void _update_interface_screen_size(void){
int i,j;
float nx,ny,cosine,sine;
for(i= 0;i<_number_of_loops;i++)
for(j= 0;j<W_MAX_INTERFACES;j++){
if(_interfaces[i][j].type==W_NONE)continue;
#ifdef W_MULTITHREAD
pthread_mutex_lock(&_interfaces[i][j]._mutex);
#endif
nx= 2.0*_interfaces[i][j].width;
ny= 2.0*_interfaces[i][j].height;
cosine= cosf(_interfaces[i][j].rotation);
sine= sinf(_interfaces[i][j].rotation);
_interfaces[i][j]._transform_matrix[0]= (nx*cosine)/
(float)W.width;
_interfaces[i][j]._transform_matrix[4]= -(ny*sine)/
(float)W.width;
_interfaces[i][j]._transform_matrix[1]= (nx*sine)/
(float)W.height;
_interfaces[i][j]._transform_matrix[5]= (ny*cosine)/
(float)W.height;
#ifdef W_MULTITHREAD
pthread_mutex_unlock(&_interfaces[i][j]._mutex);
#endif
}
}
/*:435*//*467:*/
#line 10395 "cweb/weaver.w"

void _insert_interface_queue(struct interface*inter){
int begin,end,middle,tmp;
int type= inter->type;
if(_interface_queue[_number_of_loops][W_MAX_INTERFACES-1]!=NULL){
fprintf(stderr,"WARNING (0): Couldn't create new interface. You "
"should increase the value of W_MAX_INTERFACES at cont/conf.h "
"or decrease the number of inerfaces created.\n");
return;
}
begin= 0;
end= W_MAX_INTERFACES-1;
middle= (begin+end)/2;
while((_interface_queue[_number_of_loops][middle]==NULL||
_interface_queue[_number_of_loops][middle]->type!=type)&&
begin!=end){
if(_interface_queue[_number_of_loops][middle]==NULL||
_interface_queue[_number_of_loops][middle]->type<type){
tmp= (middle+end)/2;
if(tmp==end)end--;
else end= tmp;
middle= (begin+end)/2;
}
else{
tmp= (middle+begin)/2;
if(tmp==begin)begin++;
else begin= tmp;
middle= (begin+end)/2;
}
}


for(tmp= W_MAX_INTERFACES-1;tmp>=middle;tmp--)
_interface_queue[_number_of_loops][tmp]= 
_interface_queue[_number_of_loops][tmp-1];

_interface_queue[_number_of_loops][middle]= inter;
}
/*:467*//*469:*/
#line 10443 "cweb/weaver.w"

void _remove_interface_queue(struct interface*inter){
int begin,end,middle,tmp;
int type= inter->type;
begin= 0;
end= W_MAX_INTERFACES-1;
middle= (begin+end)/2;
while((_interface_queue[_number_of_loops][middle]==NULL||
_interface_queue[_number_of_loops][middle]->type!=type)
&&begin!=end){
if(_interface_queue[_number_of_loops][middle]==NULL||
_interface_queue[_number_of_loops][middle]->type<type){
tmp= (middle+end)/2;
if(tmp==end)end--;
else end= tmp;
middle= (begin+end)/2;
}
else{
tmp= (middle+begin)/2;
if(tmp==begin)begin++;
else begin= tmp;
middle= (begin+end)/2;
}
}

while(middle> 0&&_interface_queue[_number_of_loops][middle]!=NULL&&
_interface_queue[_number_of_loops][middle]->type==
_interface_queue[_number_of_loops][middle-1]->type)
middle--;
if(_interface_queue[_number_of_loops][middle]->type!=type){
#if W_DEBUG_LEVEL >= 1
fprintf(stderr,
"WARNING (1): Tried to erase a non-existent interface.\n");
#endif
return;
}


while(_interface_queue[_number_of_loops][middle]!=NULL&&
_interface_queue[_number_of_loops][middle]->type==type&&
_interface_queue[_number_of_loops][middle]!=inter)
middle++;


if(_interface_queue[_number_of_loops][middle]==inter){
while(_interface_queue[_number_of_loops][middle]!=NULL&&
middle!=W_MAX_INTERFACES-1){
_interface_queue[_number_of_loops][middle]= 
_interface_queue[_number_of_loops][middle+1];
middle++;
}
_interface_queue[_number_of_loops][W_MAX_INTERFACES-1]= NULL;
}
else{
#if W_DEBUG_LEVEL >= 1
fprintf(stderr,
"WARNING (1): Tried to erase a non-existent interface.\n");
#endif
return;
}
}
/*:469*//*471:*/
#line 10512 "cweb/weaver.w"

void _clean_interface_queue(void){
int i;
for(i= 0;i<W_MAX_INTERFACES;i++)
_interface_queue[_number_of_loops][i]= NULL;
}
/*:471*//*652:*/
#line 14372 "cweb/weaver.w"



void _finalize_interface_texture(void*data){
struct interface*p= (struct interface*)data;
glDeleteTextures(p->number_of_frames,p->_texture);
}
/*:652*/
#line 8717 "cweb/weaver.w"

/*:392*/
