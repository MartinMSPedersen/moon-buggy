/* error.c - functions to signal error conditions
 *
 * Copyright (C) 1998  Jochen Voss.  */

static const  char  rcsid[] = "$Id: error.c,v 1.2 1998/12/20 00:46:54 voss Exp $";

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <unistd.h>

#include "moon.h"


void
fatal (const char *format, ...)
/* Signal a fatal error and quit immediately.  The arguments have the
 * same meaning, as in the function `printf'.  */
{
  va_list  ap;

  prepare_for_exit ();
  
  va_start (ap, format);
  fflush (NULL);
  fputs ("Fatal error: ", stderr);
  vfprintf (stderr, format, ap);
  fputc ('\n', stderr);
  va_end (ap);

  exit (EXIT_FAILURE);
}

void
warning (const char *format, ...)
/* Emit a warning message.  The arguments have the same meaning, as in
 * the function `printf'. */
{
  va_list  ap;

  va_start (ap, format);
  fflush (NULL);
  fputs ("Warning: ", stderr);
  vfprintf (stderr, format, ap);
  fputc ('\n', stderr);
  va_end (ap);
}
