/* xmalloc.c - memory allocation with error checking
 *
 * Copyright 1998  Jochen Voss  */

static const  char  rcsid[] = "$Id: xmalloc.c,v 1.6 1999/05/30 19:45:12 voss Rel $";

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include "mbuggy.h"


void *
xmalloc (size_t size)
/* Like `malloc', but check for shortage of memory.  `xmalloc' never
 * returns `NULL'.  */
{
  void *ptr = malloc (size);
  if (ptr == NULL)  fatal ("Memory exhausted");
  return  ptr;
}

void *
xrealloc (void *ptr, size_t size)
/* Like `realloc', but check for shortage of memory.  `xrealloc' never
 * returns `NULL'.  */
{
  void *tmp;

  if (ptr) {
    tmp = realloc (ptr, size);
  } else {
    tmp = malloc (size);
  }
  if (tmp == NULL)  fatal ("Memory exhausted");
  return  tmp;
}
