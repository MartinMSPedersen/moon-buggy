/* game.c - play the game
 *
 * Copyright 1999  Jochen Voss  */

static const  char  rcsid[] = "$Id: game.c,v 1.26 1999/07/17 13:00:11 voss Exp $";

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "mbuggy.h"


int  crash_detected;		/* a crash is in progress */
int  stakes;			/* points to get, when we reach the ground */
static  int  score;		/* points we already got */
static  int  lives;		/* cars left (including the current one) */


void
adjust_score (int val)
/* Add VAL to the score.  */
{
  if (crash_detected)  return;
  score += val;
  mvwprintw (status, 0, car_base-7, "score: %-8d", score);
  wnoutrefresh (status);
}

static void
print_lives (void)
{
  mvwprintw (status, 0, car_base-20, "lives: %d", lives);
  wnoutrefresh (status);
}

static void
life_key_handler (game_time t)
{
  int  meaning = read_key ();
  if (meaning & mbk_jump) {
    if (! crash_detected && can_jump())  jump (t);
  } else if (meaning & mbk_fire) {
    if (! crash_detected)  fire_laser (t);
  } else if (meaning & mbk_end) {
    quit_main_loop ();
    lives = 1;
    print_message ("aborted at user's request");
  } else {
    beep ();
  }
}

static void
spend_life ()
{
  crash_detected = 0;
  stakes = 0;
  print_ground ();
  print_lives ();

  clear_queue ();

  initialise_buggy ();
  print_buggy ();

  start_scrolling (1);
  main_loop (1, life_key_handler);

  extinguish_laser ();
}

static void
setup_screen (void)
{
  werase (moon);
  werase (status);
  resize_ground (1);
}

static void
game_key_handler (game_time t)
{
  int  meaning = read_key ();
  if (meaning & mbk_end) {
    quit_main_loop ();
    lives = 0;
  } else if (meaning & mbk_start) {
    quit_main_loop ();
  } else {
    beep ();
  }
}

int
game_mode (void)
{
  int  level = 0;
  
  game_state = PLAYING;
  setup_screen ();
  
  score = 0;
  lives = 3;
  do {
    resize_ground (1);
    level_start (level);
    spend_life ();
    level = current_level ();

    --lives;
    print_lives ();

    xsleep (0.5);
    add_event (1.5, quit_main_loop_h, NULL);
    main_loop (1.5, game_key_handler);
    remove_meteors ();
  } while (lives > 0);
  remove_meteors ();

  wattron (moon, A_BLINK);
  mvwaddstr (moon, LINES-11, car_base-1, "GAME OVER");
  wattroff (moon, A_BLINK);

  return  highscore_mode (score, level+1);
}

void
resize_game (void)
{
  werase (moon);
  werase (status);
  werase (message);
  resize_meteors ();
  resize_laser ();
  resize_ground (0);
  print_ground ();
  adjust_score (0);
  print_lives ();
  print_buggy ();
}

void
quit_game (void)
{
  lives = 1;
  crash_detected = 1;
}
