/* buggy.c - implement the moon buggy
 *
 * Copyright 1999  Jochen Voss  */

static const  char  rcsid[] = "$Id: buggy.c,v 1.20 2000/03/31 11:18:02 voss Rel $";

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <assert.h>

#include "moon-buggy.h"
#include "buggy.h"


int  car_x, car_y;


typedef  struct scene {
  enum car_state  n;		/* image number (index to array `image') */
  int  y;			/* vertical position */
  double  dt;			/* time to next state */
  int  has_ground;		/* flag, true iff we may crash or jump */
}  scenario [];

static  scenario  sz_empty = {
  { car_NORMAL, 5, -1, 1 }
};

static scenario sz_jump = {
  { car_START, 5, TICK(1), 0 },
  { car_UP1, 6, TICK(2.5), 0 },
  { car_UP2, 7, TICK(5), 0 },
  { car_UP1, 6, TICK(2.5), 0 },
  { car_LAND, 5, TICK(2.5), 1 },
  { car_NORMAL, 5, -1, 1 }
};

static  scenario  sz_crash = {
  { car_BROKEN, 5, -1, 0 }
};

static  scenario  sz_ram = {
  { car_RAM1, 5, TICK(1), 0 },
  { car_RAM2, 5, TICK(0.5), 0 },
  { car_RAM3, 5, -1, 0 }
};

static  scenario  sz_sit = {
  { car_SIT, 5, -1, 0 }
};

static  struct scene *state;


void
initialise_buggy (void)
/* Reset the buggy to its initial state.  */
{
  int  y;

  state = sz_empty;
  for (y=5; y<9; ++y)  mvwaddstr (moon, LINES-y, car_x, "       ");
  car_x = car_base;
  car_y = state->y;
  wnoutrefresh (moon);
}

void
print_buggy (void)
{
  enum car_state  n = state->n;
  int  y = state->y;

  if (y < car_y) {
    mvwaddstr (moon, LINES-car_y-1, car_x, "       ");
  } else if (y > car_y) {
    mvwaddstr (moon, LINES-car_y, car_x, "       ");
  }
  car_y = y;
  mvwaddstr (moon, LINES-y-1, car_x, image[n][0]);
  mvwaddstr (moon, LINES-y, car_x, image[n][1]);
  if (n == car_BROKEN) {
    if (ground2[car_x+1] == ' ')  mvwaddch (moon, LINES-4, car_x+1, 'o');
    if (ground2[car_x+5] == ' ')  mvwaddch (moon, LINES-4, car_x+5, 'o');
  }
  wnoutrefresh (moon);
}

static void
jump_handler (game_time t, void *client_data)
{
  state = client_data;
  if (car_y > 5 && state->y == 5) {
    if (meteor_car_hit (car_x, car_x+7)) {
      state = sz_sit;
      crash_detected = 1;
    }
  }
  print_buggy ();
  if (state->n == car_RAM2 || crash_check ())  crash_detected = 1;
  if (state->dt >= -0.5) {
    add_event (t+state->dt, jump_handler, state+1);
  }
}

void
jump (game_time t)
{
  assert (state->has_ground);
  remove_event (jump_handler);	/* only one jump at a time */
  add_event (t, jump_handler, sz_jump);
}

int
can_jump (void)
{
  return  state->has_ground;
}

int
crash_check (void)
/* Return true, if the car crashed.  */
{
  if (! state->has_ground)  return 0;
  if (ground2[car_x+1] == ' ' || ground2[car_x+5] == ' ') {
    remove_event (jump_handler);
    state = sz_crash;
    print_buggy ();
    return 1;
  }
  
  return  0;
}

void
shift_buggy (int dx)
/* Horizontally shift the buggy by the amount DX.
 * Positive values of dx indicate a shift to the right.  */
{
  mvwaddstr (moon, LINES-car_y-1, car_x, "       ");
  mvwaddstr (moon, LINES-car_y, car_x, "       ");
  car_x += dx;
  print_buggy ();
}

int
car_meteor_hit (game_time t, int x)
/* Return true, if the car is down a occupies position X.
 * Then the car crashes immediately.  */
{
  if (car_y == 5 && x >= car_x && x < car_x+7) {
    remove_event (jump_handler);
    add_event (t, jump_handler, sz_ram);
    print_buggy ();
    return 1;
  }

  return  0;
}
