/*517:*/
#line 11345 "cweb/weaver.w"

#ifndef _sound_h_
#define _sound_h_
#ifdef __cplusplus
extern"C"{
#endif
#include <AL/al.h> 
#include <AL/alc.h> 
#include "weaver.h"
/*66:*/
#line 1927 "cweb/weaver.w"

#include "conf_begin.h"
#include "../../conf/conf.h"
#include "conf_end.h"
/*:66*/
#line 11354 "cweb/weaver.w"

/*522:*/
#line 11405 "cweb/weaver.w"

void _initialize_sound(void);
/*:522*//*524:*/
#line 11424 "cweb/weaver.w"

void _finalize_sound(void);
/*:524*//*534:*/
#line 11551 "cweb/weaver.w"

bool _select_sound_device(int position);
/*:534*//*538:*/
#line 11584 "cweb/weaver.w"

int _current_sound_device(void);
/*:538*//*568:*/
#line 12207 "cweb/weaver.w"

struct sound{
unsigned long size;
int channels,freq,bitrate;
ALuint _data;
bool loaded;
};
/*:568*//*569:*/
#line 12224 "cweb/weaver.w"

struct sound*_new_sound(char*filename);
/*:569*//*577:*/
#line 12433 "cweb/weaver.w"

void _play_sound(struct sound*snd);
/*:577*//*581:*/
#line 12468 "cweb/weaver.w"

void _destroy_sound(struct sound*snd);
/*:581*//*586:*/
#line 12530 "cweb/weaver.w"

#if defined(W_MULTITHREAD) && W_TARGET == W_ELF
struct _thread_file_info{
char filename[256];
void*target;
void*(*onload)(void*);


void*(*onerror)(void*);




void*(*process)(void*);
bool valid_info;
#if W_THREAD_POOL >  0
pthread_mutex_t mutex;


pthread_mutex_t struct_mutex;
pthread_cond_t condition;
bool _kill_switch;
#endif
};
#endif
/*:586*//*587:*/
#line 12568 "cweb/weaver.w"

#if defined(W_MULTITHREAD) && W_TARGET == W_ELF && W_THREAD_POOL >  0
struct _thread_file_info _file_list[W_THREAD_POOL];
pthread_t _thread_list[W_THREAD_POOL];
int _file_list_count;
pthread_mutex_t _file_list_count_mutex;
#endif
/*:587*//*590:*/
#line 12639 "cweb/weaver.w"

#if defined(W_MULTITHREAD) && W_TARGET == W_ELF && W_THREAD_POOL >  0
void*_file_list_thread(void*p);
#endif
/*:590*//*593:*/
#line 12683 "cweb/weaver.w"

#if defined(W_MULTITHREAD) && W_TARGET == W_ELF
void _multithread_load_file(const char*filename,void*snd,
void*(*process)(void*),
void*(*onload)(void*),
void*(*onerror)(void*));

#endif
/*:593*//*748:*/
#line 16465 "cweb/weaver.w"

#if W_TARGET == W_ELF
#include <semaphore.h> 
#ifndef W_DISABLE_MP3
#include <mpg123.h> 
#endif
#endif
/*:748*//*750:*/
#line 16493 "cweb/weaver.w"

struct _music_data{
char filename[W_MAX_SUBLOOP][256];
int status[W_MAX_SUBLOOP];
float volume[W_MAX_SUBLOOP];
bool loop[W_MAX_SUBLOOP];
#if W_TARGET == W_ELF
unsigned char*buffer;
size_t buffer_size;

pthread_t thread;
sem_t semaphore;
#ifndef W_DISABLE_MP3

mpg123_handle*mpg_handle;
#endif

ALuint sound_source,openal_buffer[2];
#endif
};
/*:750*//*751:*/
#line 16517 "cweb/weaver.w"

extern struct _music_data _music[W_MAX_MUSIC];
/*:751*//*753:*/
#line 16532 "cweb/weaver.w"

#define _NOT_LOADED 0
#define _PLAYING    1
#define _PAUSED     2
/*:753*//*758:*/
#line 16644 "cweb/weaver.w"

bool _play_music(char*,bool);
/*:758*//*762:*/
#line 16723 "cweb/weaver.w"

bool _pause_music(char*);
/*:762*//*766:*/
#line 16784 "cweb/weaver.w"

bool _resume_music(char*);
/*:766*//*768:*/
#line 16829 "cweb/weaver.w"

bool _stop_music(char*);
/*:768*//*772:*/
#line 16888 "cweb/weaver.w"

float _get_volume(char*);
/*:772*//*776:*/
#line 16921 "cweb/weaver.w"

float _increase_volume(char*,float);
/*:776*//*786:*/
#line 17155 "cweb/weaver.w"

#if W_TARGET == W_ELF && !defined(W_DISABLE_MP3)
void*_music_thread(void*);
#endif
/*:786*/
#line 11355 "cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:517*/
