/*
 *  Multi2Sim
 *  Copyright (C) 2012  Rafael Ubal (ubal@ece.neu.edu)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "debug.h"
#include "mhandle.h"
#include "opengl.h"
#include "string.h"


/*
 * Global Variables
 */

char *opengl_err_not_impl =
	"\tThis error message is reported by the Multi2Sim OpenGL Runtime library\n"
	"\tlinked to your OpenGL application. The runtime only supports partial\n"
	"\timplementation of OpenGL. To request support for this feature, please\n"
	"\temail 'development@multi2sim.org'.\n";

char *opengl_err_note =
	"\tThis error message is generated by the Multi2Sim OpenGL Runtime library linked\n"
	"\twith your OpenGL host application.\n"
	"\tThis implementation only provides a subset of the OpenGL specification. Please\n"
	"\temail 'development@multi2sim.org' for further support.\n";

char *opengl_err_param_note =
	"\tThis error message is generated by the Multi2Sim OpenGL Runtime library\n"
	"\tlinked with your OpenGL host application.\n"
	"\tWhile a complete OpenGL implementation would return an error code to\n"
	"\tyour application, the Multi2Sim OpenGL library will make your program\n"
	"\tfail with an error code.\n";


/*
 * Debug
 *
 * If environment variable 'opengl_DEBUG' is set, the Multi2Sim OpenGL Runtime
 * library will dump debug information about OpenGL calls, argument values,
 * intermeidate actions, and return values.
 */

static int opengl_debug_initialized;
static int opengl_debugging;

void opengl_debug(char *fmt, ...)
{
	va_list va;
	char *value;
	char str[MAX_LONG_STRING_SIZE];

	/* Initialize debug */
	if (!opengl_debug_initialized)
	{
		opengl_debug_initialized = 1;
		value = getenv("M2S_OPENGL_DEBUG");
		if (value && !strcmp(value, "1"))
			opengl_debugging = 1;
	}

	/* Exit if not debugging */
	if (!opengl_debugging)
		return;
	
	/* Reconstruct message in 'str' first. This is done to avoid multiple
	 * calls to 'printf', that can have race conditions among threads. */
	va_start(va, fmt);
	vsnprintf(str, sizeof str, fmt, va);
	fprintf(stderr, "[libm2s-opengl] %s\n", str);
}
