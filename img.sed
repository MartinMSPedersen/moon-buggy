# img.sed - used by "Makefile.am" to create "buggy.h"
# Copyright 1999  Jochen Vo�
# $Id: img.sed,v 1.1 1999/04/23 22:20:35 voss Exp $

# initialisation
1 {
	i\
/* buggy.h - the image data for "buggy.c"\
 * Automatically created from file "car.img".\
 * DO NOT EDIT !!! */\
\
static char *image[][4] = {
	x
	s/^.*$/  /
	x
}

# closing brackets for the images
1, /^[A-Z0-9]*:/ b ishead
/^[A-Z0-9]*:/ i\
  },
: ishead

# headers
/^[A-Z0-9]*:/ {
	s/\([A-Z0-9]*\):/car_\1, /
	H
	x
	s/\n//
	x
	i\
  {
}

# images
/^|.*|/ s/|\(.*\)|/    "\1",/p

# end
$ {
	i\
  },\
};\
\
enum car_state { 
	x
	p
	i\
};
}