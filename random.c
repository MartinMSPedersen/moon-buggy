/* random.c - generate pseudo random numbers
 *
 * Copyright (C) 1999  Jochen Voss.  */

static const  char  rcsid[] = "$Id: random.c,v 1.1 1999/05/19 21:06:46 voss Exp $";

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>
#include <time.h>

void
init_rnd (void)
/* Initialise the random number generator with a random seed.
 * The seed is based on the current time.  */
{
  srand (time (0));
}

int
uniform_rnd (int limit)
/* Returns a pseudo random integer `x' with `0 <= x < limit'.
 * The numbers a uniformly distributed.  */
{
  return  (int)((double)limit*rand()/(RAND_MAX+1.0));
}
