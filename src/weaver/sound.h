/*517:*/
#line 11329 "cweb/weaver.w"

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
#line 11338 "cweb/weaver.w"

/*522:*/
#line 11389 "cweb/weaver.w"

void _initialize_sound(void);
/*:522*//*524:*/
#line 11408 "cweb/weaver.w"

void _finalize_sound(void);
/*:524*//*534:*/
#line 11535 "cweb/weaver.w"

bool _select_sound_device(int position);
/*:534*//*538:*/
#line 11568 "cweb/weaver.w"

int _current_sound_device(void);
/*:538*//*566:*/
#line 12157 "cweb/weaver.w"

struct sound{
unsigned long size;
int channels,freq,bitrate;
ALuint _data;
bool loaded;
};
/*:566*//*567:*/
#line 12174 "cweb/weaver.w"

struct sound*_new_sound(char*filename);
/*:567*//*575:*/
#line 12372 "cweb/weaver.w"

void _play_sound(struct sound*snd);
/*:575*//*579:*/
#line 12407 "cweb/weaver.w"

void _destroy_sound(struct sound*snd);
/*:579*//*730:*/
#line 15948 "cweb/weaver.w"

#if W_TARGET == W_ELF
#include <semaphore.h> 
#ifndef W_DISABLE_MP3
#include <mpg123.h> 
#endif
#endif
/*:730*//*732:*/
#line 15976 "cweb/weaver.w"

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
/*:732*//*733:*/
#line 16000 "cweb/weaver.w"

extern struct _music_data _music[W_MAX_MUSIC];
#ifdef W_MULTITHREAD


extern pthread_mutex_t _music_mutex;
#endif
/*:733*//*735:*/
#line 16020 "cweb/weaver.w"

#define _NOT_LOADED 0
#define _PLAYING    1
#define _PAUSED     2
/*:735*//*740:*/
#line 16132 "cweb/weaver.w"

bool _play_music(char*,bool);
/*:740*//*744:*/
#line 16211 "cweb/weaver.w"

bool _pause_music(char*);
/*:744*//*748:*/
#line 16272 "cweb/weaver.w"

bool _resume_music(char*);
/*:748*//*750:*/
#line 16317 "cweb/weaver.w"

bool _stop_music(char*);
/*:750*//*754:*/
#line 16376 "cweb/weaver.w"

float _get_volume(char*);
/*:754*//*758:*/
#line 16409 "cweb/weaver.w"

float _increase_volume(char*,float);
/*:758*//*768:*/
#line 16643 "cweb/weaver.w"

#if W_TARGET == W_ELF && !defined(W_DISABLE_MP3)
void*_music_thread(void*);
#endif
/*:768*/
#line 11339 "cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:517*/
