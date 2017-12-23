/*70:*/
#line 1976 "cweb/weaver.w"

#ifndef _weaver_h_
#define _weaver_h_
#ifdef __cplusplus
extern"C"{
#endif
/*66:*/
#line 1927 "cweb/weaver.w"

#include "conf_begin.h"
#include "../../conf/conf.h"
#include "conf_end.h"
/*:66*/
#line 1982 "cweb/weaver.w"

#include <stdlib.h> 
#include <stdbool.h> 
#if W_TARGET == W_WEB
#include <emscripten.h> 
#endif
/*71:*/
#line 2018 "cweb/weaver.w"

void _awake_the_weaver(void);
void _may_the_weaver_sleep(void)__attribute__((noreturn));
void _update(void);
void _render(void);
#define Winit() _awake_the_weaver()
#define Wexit() _may_the_weaver_sleep()
/*:71*//*79:*/
#line 2144 "cweb/weaver.w"

struct timeval _last_time;
/*:79*//*81:*/
#line 2161 "cweb/weaver.w"

unsigned long _update_time(void);
/*:81*//*84:*/
#line 2207 "cweb/weaver.w"

extern struct _game_struct _game;
/*:84*//*89:*/
#line 2369 "cweb/weaver.w"

#include "memory.h"
/*:89*//*162:*/
#line 3845 "cweb/weaver.w"

#include <stdio.h> 
#include <sys/time.h> 

#define W_TIMER_BEGIN() { struct timeval _begin, _end; \
gettimeofday(&_begin, NULL);
#define W_TIMER_END() gettimeofday(&_end, NULL); \
printf("%ld us\n", (1000000 * (_end.tv_sec - _begin.tv_sec) + \
_end.tv_usec - _begin.tv_usec)); \
}

/*:162*//*168:*/
#line 4161 "cweb/weaver.w"

typedef void MAIN_LOOP;







bool _loop_begin,_running_loop;
/*:168*//*169:*/
#line 4187 "cweb/weaver.w"

void _Wloop(MAIN_LOOP(*f)(void))__attribute__((noreturn));
void Wsubloop(MAIN_LOOP(*f)(void))__attribute__((noreturn));
#define Wloop(a) ((W.pending_files)?(false):(_Wloop(a)))
/*:169*//*170:*/
#line 4223 "cweb/weaver.w"

bool _first_loop;

int _number_of_loops;
MAIN_LOOP(*_loop_stack[W_MAX_SUBLOOP])(void);
/*:170*//*173:*/
#line 4276 "cweb/weaver.w"

void _exit_loop(void)__attribute__((noreturn));
/*:173*//*175:*/
#line 4316 "cweb/weaver.w"

#define Wexit_loop() (_running_loop =  false)
/*:175*//*178:*/
#line 4396 "cweb/weaver.w"

long _lag;
/*:178*//*181:*/
#line 4415 "cweb/weaver.w"

#define LOOP_INIT if(!_running_loop) _exit_loop(); if(!_running_loop)\
   goto _LOOP_FINALIZATION; if(!_loop_begin) goto _END_LOOP_INITIALIZATION;\
   _BEGIN_LOOP_INITIALIZATION
#define LOOP_BODY _loop_begin =   false; if(_loop_begin)\
   goto _BEGIN_LOOP_INITIALIZATION; _END_LOOP_INITIALIZATION:\
   _lag +=   _update_time(); while(_lag >= 40000){ _update(); _LABEL_0
#define LOOP_END _lag -=   40000; W.t +=   40000; } \
   _render(); if(_running_loop || W.pending_files) return; \
   if(W.t == 0) goto _LABEL_0;\
   _LOOP_FINALIZATION
/*:181*//*187:*/
#line 4563 "cweb/weaver.w"

#include "numeric.h"
/*:187*//*207:*/
#line 5001 "cweb/weaver.w"

#include <GL/glew.h> 
/*:207*//*211:*/
#line 5082 "cweb/weaver.w"

#ifdef W_MULTITHREAD
extern pthread_mutex_t _window_mutex;
#endif
/*:211*//*213:*/
#line 5099 "cweb/weaver.w"

#if W_TARGET == W_ELF
#include "window.h"
#endif
/*:213*//*219:*/
#line 5208 "cweb/weaver.w"

#if W_TARGET == W_ELF
#include <X11/Xlib.h> 
extern Display*_dpy;
#endif
/*:219*//*222:*/
#line 5244 "cweb/weaver.w"

#if W_TARGET == W_ELF
extern int _screen;
#endif
/*:222*//*227:*/
#line 5286 "cweb/weaver.w"

#if W_TARGET == W_ELF
#include <X11/Xlib.h> 
extern Window _window;
#endif
/*:227*//*235:*/
#line 5465 "cweb/weaver.w"

#if W_TARGET == W_ELF
#include <GL/glx.h> 
extern GLXContext _context;
#endif
/*:235*//*242:*/
#line 5580 "cweb/weaver.w"

#if W_TARGET == W_WEB
#include "canvas.h"
#endif
/*:242*//*272:*/
#line 6094 "cweb/weaver.w"

#ifdef W_MULTITHREAD
pthread_mutex_t _input_mutex;
#endif

/*:272*//*275:*/
#line 6155 "cweb/weaver.w"

#define W_SHIFT 2 
#define W_CTRL  3 
#define W_ALT   4 
#define W_ANY   6 
/*:275*//*277:*/
#line 6192 "cweb/weaver.w"

int _Wkey_translate(unsigned old_value,unsigned new_value);
void _Werase_key_translations(void);
/*:277*//*285:*/
#line 6416 "cweb/weaver.w"

#if W_TARGET == W_ELF
#define W_UP          XK_Up
#define W_RIGHT       XK_Right
#define W_DOWN        XK_Down
#define W_LEFT        XK_Left
#define W_PLUS        XK_KP_Add
#define W_MINUS       XK_KP_Subtract
#define W_ESC         XK_Escape
#define W_A           XK_a
#define W_S           XK_s
#define W_D           XK_d
#define W_W           XK_w
#define W_ENTER       XK_Return
#define W_SPACEBAR    XK_space
#define W_LEFT_CTRL   XK_Control_L
#define W_RIGHT_CTRL  XK_Control_R
#define W_F1          XK_F1
#define W_F2          XK_F2
#define W_F3          XK_F3
#define W_F4          XK_F4
#define W_F5          XK_F5
#define W_F6          XK_F6
#define W_F7          XK_F7
#define W_F8          XK_F8
#define W_F9          XK_F9
#define W_F10         XK_F10
#define W_F11         XK_F11
#define W_F12         XK_F12
#define W_BACKSPACE   XK_BackSpace
#define W_TAB         XK_Tab
#define W_PAUSE       XK_Pause
#define W_DELETE      XK_Delete
#define W_SCROLL_LOCK XK_Scroll_Lock
#define W_HOME        XK_Home
#define W_PAGE_UP     XK_Page_Up
#define W_PAGE_DOWN   XK_Page_Down
#define W_END         XK_End
#define W_INSERT      XK_Insert
#define W_NUM_LOCK    XK_Num_Lock
#define W_0           XK_0
#define W_1           XK_1
#define W_2           XK_2
#define W_3           XK_3
#define W_4           XK_4
#define W_5           XK_5
#define W_6           XK_6
#define W_7           XK_7
#define W_8           XK_8
#define W_9           XK_9
#define W_LEFT_SHIFT  XK_Shift_L
#define W_RIGHT_SHIFT XK_Shift_R
#define W_CAPS_LOCK   XK_Caps_Lock
#define W_LEFT_ALT    XK_Alt_L
#define W_RIGHT_ALT   XK_Alt_R
#define W_Q           XK_q
#define W_E           XK_e
#define W_R           XK_r
#define W_T           XK_t
#define W_Y           XK_y
#define W_U           XK_u
#define W_I           XK_i
#define W_O           XK_o
#define W_P           XK_p
#define W_F           XK_f
#define W_G           XK_g
#define W_H           XK_h
#define W_J           XK_j
#define W_K           XK_k
#define W_L           XK_l
#define W_Z           XK_z
#define W_X           XK_x
#define W_C           XK_c
#define W_V           XK_v
#define W_B           XK_b
#define W_N           XK_n
#define W_M           XK_m
#endif
/*:285*//*286:*/
#line 6508 "cweb/weaver.w"

void _Wflush_input(void);
/*:286*//*291:*/
#line 6561 "cweb/weaver.w"

#if W_TARGET == W_WEB
#include <SDL/SDL.h> 
#endif
/*:291*//*294:*/
#line 6629 "cweb/weaver.w"

#if W_TARGET == W_WEB
#define W_UP          SDLK_UP
#define W_RIGHT       SDLK_RIGHT
#define W_DOWN        SDLK_DOWN
#define W_LEFT        SDLK_LEFT
#define W_PLUS        SDLK_PLUS
#define W_MINUS       SDLK_MINUS
#define W_ESC         SDLK_ESCAPE
#define W_A           SDLK_a
#define W_S           SDLK_s
#define W_D           SDLK_d
#define W_W           SDLK_w
#define W_ENTER       SDLK_RETURN
#define W_SPACEBAR    SDLK_SPACE
#define W_LEFT_CTRL   SDLK_LCTRL
#define W_RIGHT_CTRL  SDLK_RCTRL
#define W_F1          SDLK_F1
#define W_F2          SDLK_F2
#define W_F3          SDLK_F3
#define W_F4          SDLK_F4
#define W_F5          SDLK_F5
#define W_F6          SDLK_F6
#define W_F7          SDLK_F7
#define W_F8          SDLK_F8
#define W_F9          SDLK_F9
#define W_F10         SDLK_F10
#define W_F11         SDLK_F11
#define W_F12         SDLK_F12
#define W_BACKSPACE   SDLK_BACKSPACE
#define W_TAB         SDLK_TAB
#define W_PAUSE       SDLK_PAUSE
#define W_DELETE      SDLK_DELETE
#define W_SCROLL_LOCK SDLK_SCROLLOCK
#define W_HOME        SDLK_HOME
#define W_PAGE_UP     SDLK_PAGEUP
#define W_PAGE_DOWN   SDLK_PAGEDOWN
#define W_END         SDLK_END
#define W_INSERT      SDLK_INSERT
#define W_NUM_LOCK    SDLK_NUMLOCK
#define W_0           SDLK_0
#define W_1           SDLK_1
#define W_2           SDLK_2
#define W_3           SDLK_3
#define W_4           SDLK_4
#define W_5           SDLK_5
#define W_6           SDLK_6
#define W_7           SDLK_7
#define W_8           SDLK_8
#define W_9           SDLK_9
#define W_LEFT_SHIFT  SDLK_LSHIFT
#define W_RIGHT_SHIFT SDLK_RSHIFT
#define W_CAPS_LOCK   SDLK_CAPSLOCK
#define W_LEFT_ALT    SDLK_LALT
#define W_RIGHT_ALT   SDLK_RALT
#define W_Q           SDLK_q
#define W_E           SDLK_e
#define W_R           SDLK_r
#define W_T           SDLK_t
#define W_Y           SDLK_y
#define W_U           SDLK_u
#define W_I           SDLK_i
#define W_O           SDLK_o
#define W_P           SDLK_p
#define W_F           SDLK_f
#define W_G           SDLK_g
#define W_H           SDLK_h
#define W_J           SDLK_j
#define W_K           SDLK_k
#define W_L           SDLK_l
#define W_Z           SDLK_z
#define W_X           SDLK_x
#define W_C           SDLK_c
#define W_V           SDLK_v
#define W_B           SDLK_b
#define W_N           SDLK_n
#define W_M           SDLK_m
#endif
/*:294*//*298:*/
#line 6745 "cweb/weaver.w"

struct _mouse{


long buttons[7];
int x,y,dx,dy,ddx,ddy;
};
/*:298*//*300:*/
#line 6763 "cweb/weaver.w"

#if W_TARGET == W_ELF
#define W_MOUSE_LEFT   Button1
#define W_MOUSE_MIDDLE Button2
#define W_MOUSE_RIGHT  Button3
#define W_MOUSE_B1     Button4
#define W_MOUSE_B2     Button5
#endif
#if W_TARGET == W_WEB
#define W_MOUSE_LEFT   SDL_BUTTON_LEFT
#define W_MOUSE_MIDDLE SDL_BUTTON_MIDDLE
#define W_MOUSE_RIGHT  SDL_BUTTON_RIGHT
#define W_MOUSE_B1     4
#define W_MOUSE_B2     5
#endif
/*:300*//*318:*/
#line 7085 "cweb/weaver.w"

bool _using_original_cursor;
void _Whide_cursor(void);
/*:318*//*366:*/
#line 8199 "cweb/weaver.w"

#ifdef W_MULTITHREAD
pthread_mutex_t _scheduler_mutex;
#endif
struct{
bool periodic;
unsigned long last_execution;
unsigned long period;
void(*f)(void);
}_scheduled_functions[W_MAX_SUBLOOP][W_MAX_SCHEDULING];
/*:366*//*372:*/
#line 8320 "cweb/weaver.w"

void _run_periodically(void(*f)(void),float t);
void _run_futurelly(void(*f)(void),float t);
void _cancel(void(*f)(void));
float _period(void(*f)(void));
/*:372*//*393:*/
#line 8719 "cweb/weaver.w"

#include "interface.h"
/*:393*//*441:*/
#line 9653 "cweb/weaver.w"

#include <ctype.h>  
#include "shaders.h"
/*:441*//*481:*/
#line 10768 "cweb/weaver.w"

#define W_NONE            0
#define W_DEFAULT_SHADER -1
/*:481*//*482:*/
#line 10773 "cweb/weaver.w"










int _final_shader[W_MAX_SUBLOOP];


bool _changed_resolution;


GLuint _framebuffer;
/*:482*//*485:*/
#line 10819 "cweb/weaver.w"



GLuint _texture;
/*:485*//*487:*/
#line 10858 "cweb/weaver.w"


GLuint _depth_stencil;
/*:487*//*511:*/
#line 11259 "cweb/weaver.w"

int _final_shader_integer[W_MAX_SUBLOOP];
/*:511*//*519:*/
#line 11364 "cweb/weaver.w"

#include "sound.h"
/*:519*//*584:*/
#line 12467 "cweb/weaver.w"

#ifdef W_MULTITHREAD
pthread_mutex_t _finalizing_mutex;
#endif
struct _finalize_element{
void*data;
void(*finalize)(void*);
struct _finalize_element*prev,*next;
};
struct _finalize_element*_finalize_list[W_MAX_SUBLOOP];
/*:584*//*587:*/
#line 12511 "cweb/weaver.w"

void _finalize_after(void*,void(*f)(void*));
/*:587*//*589:*/
#line 12553 "cweb/weaver.w"

void _finalize_all(void);
/*:589*//*593:*/
#line 12591 "cweb/weaver.w"

void _finalize_this(void*,bool);
/*:593*//*599:*/
#line 12730 "cweb/weaver.w"

#include "gif.h"
/*:599*//*642:*/
#line 14151 "cweb/weaver.w"

GLuint _empty_texture;
char _empty_image[4];
/*:642*//*682:*/
#line 15033 "cweb/weaver.w"

#include "database.h"
/*:682*/
#line 1988 "cweb/weaver.w"


/*75:*/
#line 2088 "cweb/weaver.w"



extern struct _weaver_struct{
/*78:*/
#line 2138 "cweb/weaver.w"


unsigned long long t;
unsigned long dt;
/*:78*//*85:*/
#line 2211 "cweb/weaver.w"


struct _game_struct*game;
/*:85*//*208:*/
#line 5010 "cweb/weaver.w"


int resolution_x,resolution_y,framerate;
/*:208*//*210:*/
#line 5073 "cweb/weaver.w"


int width,height,x,y;
/*:210*//*270:*/
#line 6074 "cweb/weaver.w"


long keyboard[0xffff];
/*:270*//*299:*/
#line 6754 "cweb/weaver.w"


struct _mouse mouse;
/*:299*//*506:*/
#line 11211 "cweb/weaver.w"


int final_shader_integer;
/*:506*//*529:*/
#line 11445 "cweb/weaver.w"


int number_of_sound_devices;
char**sound_device_name;
/*:529*//*549:*/
#line 11757 "cweb/weaver.w"

unsigned pending_files;
#ifdef W_MULTITHREAD
pthread_mutex_t _pending_files_mutex;
#endif
/*:549*/
#line 2092 "cweb/weaver.w"

/*116:*/
#line 3075 "cweb/weaver.w"


#if W_DEBUG_LEVEL >= 1
void*(*create_arena)(size_t,char*,unsigned long);
#else
void*(*create_arena)(size_t);
#endif
/*:116*//*124:*/
#line 3201 "cweb/weaver.w"


int(*destroy_arena)(void*);
/*:124*//*129:*/
#line 3326 "cweb/weaver.w"


#if W_DEBUG_LEVEL >= 1
void*(*alloc_arena)(void*,size_t,char*,unsigned long);
#else
void*(*alloc_arena)(void*,size_t);
#endif
/*:129*//*133:*/
#line 3438 "cweb/weaver.w"


#if W_DEBUG_LEVEL >= 2 && !defined(W_MULTITHREAD)
void(*free)(void*,char*,unsigned long);
#else
void(*free)(void*);
#endif
/*:133*//*139:*/
#line 3548 "cweb/weaver.w"


#if W_DEBUG_LEVEL >= 1
int(*breakpoint_arena)(void*,char*,unsigned long);
#else
int(*breakpoint_arena)(void*);
#endif
/*:139*//*143:*/
#line 3614 "cweb/weaver.w"


void(*trash_arena)(void*);
/*:143*//*153:*/
#line 3742 "cweb/weaver.w"


#if W_DEBUG_LEVEL >= 1
void*(*alloc)(size_t,char*,unsigned long);
#else
void*(*alloc)(size_t);
#endif
/*:153*//*158:*/
#line 3810 "cweb/weaver.w"


#if W_DEBUG_LEVEL >= 1
int(*breakpoint)(char*,unsigned long);
#else
int(*breakpoint)(void);
#endif
void(*trash)(void);
/*:158*//*202:*/
#line 4897 "cweb/weaver.w"


unsigned long(*random)(void);
/*:202*//*254:*/
#line 5828 "cweb/weaver.w"

void(*resize_window)(int,int);
/*:254*//*260:*/
#line 5874 "cweb/weaver.w"

void(*move_window)(int,int);
/*:260*//*279:*/
#line 6248 "cweb/weaver.w"

int(*key_translate)(unsigned,unsigned);
void(*erase_key_translations)(void);
/*:279*//*288:*/
#line 6538 "cweb/weaver.w"

void(*flush_input)(void);
/*:288*//*322:*/
#line 7152 "cweb/weaver.w"

void(*hide_cursor)(void);
/*:322*//*340:*/
#line 7733 "cweb/weaver.w"

bool(*reload_plugin)(int);
/*:340*//*351:*/
#line 7960 "cweb/weaver.w"

int(*get_plugin)(char*);
/*:351*//*355:*/
#line 8069 "cweb/weaver.w"

void(*reload_all_plugins)(void);
/*:355*//*377:*/
#line 8459 "cweb/weaver.w"


void(*run_periodically)(void(*f)(void),float);
void(*run_futurelly)(void(*f)(void),float);
void(*cancel)(void(*f)(void));
float(*period)(void(*f)(void));
/*:377*//*382:*/
#line 8548 "cweb/weaver.w"

bool(*enable_plugin)(int);
bool(*disable_plugin)(int);
bool(*is_plugin_enabled)(int);
/*:382*//*386:*/
#line 8598 "cweb/weaver.w"

void*(*get_plugin_data)(int);
bool(*set_plugin_data)(int,void*);
/*:386*//*408:*/
#line 9021 "cweb/weaver.w"

struct interface*(*new_interface)(int,int,int,int,int,...);
/*:408*//*412:*/
#line 9069 "cweb/weaver.w"

bool(*destroy_interface)(struct interface*);
/*:412*//*416:*/
#line 9135 "cweb/weaver.w"

struct interface*(*copy_interface)(struct interface*);
/*:416*//*421:*/
#line 9233 "cweb/weaver.w"

void(*move_interface)(struct interface*,float,float);
/*:421*//*425:*/
#line 9312 "cweb/weaver.w"

void(*resize_interface)(struct interface*,float,float);
/*:425*//*429:*/
#line 9392 "cweb/weaver.w"

void(*rotate_interface)(struct interface*,float);
/*:429*//*499:*/
#line 11167 "cweb/weaver.w"

void(*change_resolution)(int,int);
/*:499*//*504:*/
#line 11200 "cweb/weaver.w"

void(*change_final_shader)(int);
/*:504*//*536:*/
#line 11554 "cweb/weaver.w"

bool(*select_sound_device)(int);
/*:536*//*540:*/
#line 11587 "cweb/weaver.w"

int(*current_sound_device)(void);
/*:540*//*573:*/
#line 12361 "cweb/weaver.w"

struct sound*(*new_sound)(char*);
/*:573*//*577:*/
#line 12393 "cweb/weaver.w"

void(*play_sound)(struct sound*);
/*:577*//*581:*/
#line 12442 "cweb/weaver.w"

void(*destroy_sound)(struct sound*);
/*:581*//*693:*/
#line 15224 "cweb/weaver.w"

void(*write_integer)(char*,int);
/*:693*//*698:*/
#line 15296 "cweb/weaver.w"

void(*write_float)(char*,float);
/*:698*//*703:*/
#line 15364 "cweb/weaver.w"

void(*write_string)(char*,char*);
/*:703*//*709:*/
#line 15436 "cweb/weaver.w"

bool(*read_integer)(char*,int*);
bool(*read_float)(char*,float*);
bool(*read_string)(char*,char*,int);
/*:709*//*719:*/
#line 15685 "cweb/weaver.w"

void(*delete_integer)(char*);
void(*delete_float)(char*);
void(*delete_string)(char*);
void(*delete_all)(void);
/*:719*//*742:*/
#line 16200 "cweb/weaver.w"

bool(*play_music)(char*,bool);
/*:742*//*746:*/
#line 16261 "cweb/weaver.w"

bool(*pause_music)(char*);
/*:746*//*752:*/
#line 16366 "cweb/weaver.w"

bool(*stop_music)(char*);
/*:752*//*756:*/
#line 16397 "cweb/weaver.w"

float(*get_volume)(char*);
/*:756*//*760:*/
#line 16457 "cweb/weaver.w"

float(*increase_volume)(char*,float);
/*:760*/
#line 2093 "cweb/weaver.w"

}W;
/*:75*/
#line 1990 "cweb/weaver.w"

/*330:*/
#line 7349 "cweb/weaver.w"

#include "plugins.h"
/*:330*//*363:*/
#line 8159 "cweb/weaver.w"

#if W_TARGET == W_WEB
#include "../../.hidden_code/header.h"
#endif
/*:363*/
#line 1991 "cweb/weaver.w"

/*327:*/
#line 7293 "cweb/weaver.w"


#define W_PLUGIN struct _weaver_struct *_W
#ifdef W_PLUGIN_CODE
#define W (*_W)
#endif
/*:327*/
#line 1992 "cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:70*/
