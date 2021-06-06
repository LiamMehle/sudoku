#include "screen_ops.h"
#include "types.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <alloca.h>
#include "common.h"
inline
void clear_screen() {
	void* const buffer = alloca(term_height);
	memset(buffer, '\n', term_height);
	fwrite(buffer, term_height, 1, stdout);
	fflush(stdout);
}