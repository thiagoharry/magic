/*698:*/
#line 15530 "cweb/weaver.w"

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
#line 15537 "cweb/weaver.w"

/*703:*/
#line 15587 "cweb/weaver.w"

#if W_TARGET == W_ELF
void _initialize_database(void);
#endif
/*:703*//*706:*/
#line 15701 "cweb/weaver.w"

#if W_TARGET == W_ELF
void _finalize_database(void);
#endif
/*:706*//*710:*/
#line 15736 "cweb/weaver.w"

void _write_integer(char*name,int value);
/*:710*//*715:*/
#line 15808 "cweb/weaver.w"

void _write_float(char*name,float value);
/*:715*//*720:*/
#line 15876 "cweb/weaver.w"

void _write_string(char*name,char*value);
/*:720*//*726:*/
#line 15946 "cweb/weaver.w"

bool _read_integer(char*name,int*value);
bool _read_float(char*name,float*value);
bool _read_string(char*name,char*value,int n);
/*:726*//*736:*/
#line 16194 "cweb/weaver.w"

void _delete_integer(char*name);
void _delete_float(char*name);
void _delete_string(char*name);
void _delete_all(void);
/*:736*/
#line 15538 "cweb/weaver.w"

#ifdef __cplusplus
}
#endif
#endif
/*:698*/
