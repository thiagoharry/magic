/*
Copyright (c) Thiago "Harry" Leucz Astrizi, 2017

This file is part of magic.

magic is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

magic is distributed in the hope that it will be useful,
but WITHOUT ANY  WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS  FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more  details.

You should have received a copy of the GNU Affero General Public License
along with magic. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _arquiinimigo_h_
#define _arquiinimigo_h_
#include "weaver/weaver.h"

#include "includes.h"

MAIN_LOOP arquiinimigo(void);
void compra_arquiinimigo(struct interface **, struct interface **,
                         struct interface **);
bool eh_plano_em_andamento(int);
void embaralha_arquiinimigo(void);

#endif
