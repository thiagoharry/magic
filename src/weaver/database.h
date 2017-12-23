/*680:*/
#line 15012 "cweb/weaver.w"

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
#line 15019 "cweb/weaver.w"

/*685:*/
#line 15069 "cweb/weaver.w"

#if W_TARGET == W_ELF
void _initialize_database(void);
#endif
/*:685*//*688:*/
#line 15183 "cweb/weaver.w"

#if W_TARGET == W_ELF
void _finalize_database(void);
#endif
/*:688*//*692:*/
#line 15218 "cweb/weaver.w"

void _write_integer(char*name,int value);
/*:692*//*697:*/
#line 15290 "cweb/weaver.w"

void _write_float(char*name,float value);
/*:697*//*702:*/
#line 15358 "cweb/weaver.w"

void _write_string(char*name,char*value);
/*:702*//*708:*/
#line 15428 "cweb/weaver.w"

bool _read_integer(char*name,int*value);
bool _read_float(char*name,float*value);
bool _read_string(char*name,char*value,int n);
/*:708*//*718:*/
#line 15676 "cweb/weaver.w"

void _delete_integer(char*name);
void _delete_float(char*name);
void _delete_string(char*name);
void _delete_all(void);
/*:718*/
#line 15020 "cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:680*/
