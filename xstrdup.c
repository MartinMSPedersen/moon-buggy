/* xstrdup.c - fail save strdup
 *
 * Copyright (C) 1998  Jochen Voss.  */

static const  char  rcsid[] = "$Id: xstrdup.c,v 1.3 1998/12/29 00:40:57 voss Rel $";

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string.h>

#include "moon.h"


char *
xstrdup (const char *str)
{
  char *tmp = xmalloc (strlen(str) + 1);
  if (tmp == NULL)  fatal ("Memory exhausted");
  strcpy (tmp, str);
  return  tmp;
}

static size_t
xstrnlen (const char *str, size_t size)
{
  size_t  n = 0;
  while (n<size && str[n])  ++n;
  return  n;
}

char *
xstrndup (const char *str, size_t size)
/* Like `strndup' from glibc, but never returns NULL.  */
{
  size_t  n = xstrnlen (str, size);
  char *tmp = xmalloc (n + 1);
  
  if (tmp == NULL)  fatal ("Memory exhausted");
  strncpy (tmp, str, n);
  tmp[n] = '\0';
  
  return  tmp;
}
