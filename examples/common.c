/*
 *  common - common utility functions
 *
 *  Copyright (C) 2025 Tomasz Wolak
 *
 *  This file is part of adfinfo, an utility program showing low-level
 *  filesystem metadata of Amiga Disk Files (ADFs).
 *
 *  adflib is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  adflib is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool change_dir( struct AdfVolume * const  vol,
                 const char * const        dir_path )
{
    char * const dirpath_tmp = strdup( dir_path );

    char * dir = dirpath_tmp;
    char * dir_end;
    while ( *dir && ( dir_end = strchr( dir, '/' ) ) ) {
        *dir_end = '\0';     // replace '/' (setting end of the dirname to change to)

        if ( adfChangeDir( vol, dir ) != ADF_RC_OK ) {
            free( dirpath_tmp );
            return false;
        }

        dir = dir_end + 1;   // next subdir
    }

    if ( adfChangeDir( vol, dir ) != ADF_RC_OK ) {
        free( dirpath_tmp );
        return false;
    }

    free( dirpath_tmp );
    return true;
}
