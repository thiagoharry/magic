/*680:*/
#line 15013 "cweb/weaver.w"

#ifndef _database_h_
#define _database_h_
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
#line 15020 "cweb/weaver.w"

/*685:*/
#line 15070 "cweb/weaver.w"

#if W_TARGET == W_ELF
void _initialize_database(void);
#endif
/*:685*//*688:*/
#line 15184 "cweb/weaver.w"

#if W_TARGET == W_ELF
void _finalize_database(void);
#endif
/*:688*//*692:*/
#line 15219 "cweb/weaver.w"

void _write_integer(char*name,int value);
/*:692*//*697:*/
#line 15291 "cweb/weaver.w"

void _write_float(char*name,float value);
/*:697*//*702:*/
#line 15359 "cweb/weaver.w"

void _write_string(char*name,char*value);
/*:702*//*708:*/
#line 15429 "cweb/weaver.w"

bool _read_integer(char*name,int*value);
bool _read_float(char*name,float*value);
bool _read_string(char*name,char*value,int n);
/*:708*//*718:*/
#line 15677 "cweb/weaver.w"

void _delete_integer(char*name);
void _delete_float(char*name);
void _delete_string(char*name);
void _delete_all(void);
/*:718*/
#line 15021 "cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:680*/
