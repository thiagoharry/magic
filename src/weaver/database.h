/*710:*/
#line 15863 "cweb/weaver.w"

#ifndef _database_h_
#define _database_h_
#ifdef __cplusplus
extern"C"{
#endif
#include "weaver.h"
/*66:*/
#line 1928 "cweb/weaver.w"

#include "conf_begin.h"
#include "../../conf/conf.h"
#include "conf_end.h"
/*:66*/
#line 15870 "cweb/weaver.w"

/*715:*/
#line 15920 "cweb/weaver.w"

#if W_TARGET == W_ELF
void _initialize_database(void);
#endif
/*:715*//*718:*/
#line 16034 "cweb/weaver.w"

#if W_TARGET == W_ELF
void _finalize_database(void);
#endif
/*:718*//*722:*/
#line 16069 "cweb/weaver.w"

void _write_integer(char*name,int value);
/*:722*//*727:*/
#line 16141 "cweb/weaver.w"

void _write_float(char*name,float value);
/*:727*//*732:*/
#line 16209 "cweb/weaver.w"

void _write_string(char*name,char*value);
/*:732*//*738:*/
#line 16279 "cweb/weaver.w"

bool _read_integer(char*name,int*value);
bool _read_float(char*name,float*value);
bool _read_string(char*name,char*value,int n);
/*:738*//*748:*/
#line 16527 "cweb/weaver.w"

void _delete_integer(char*name);
void _delete_float(char*name);
void _delete_string(char*name);
void _delete_all(void);
/*:748*/
#line 15871 "cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:710*/
