/* moon.h - global moon-buggy header file
 *
 * Copyright (C) 1998  Jochen Voss.
 *
 * $Id: moon.h,v 1.9 1998/12/30 20:30:50 voss Exp $ */

#ifndef FILE_MOON_H_SEEN
#define FILE_MOON_H_SEEN

#include <curses.h>

/* If key symbols are not defined move them out of the way.
 * Avoid duplicate case labels.  */

#ifndef KEY_BEG
#define KEY_BEG -1
#endif
#ifndef KEY_CANCEL
#define KEY_CANCEL -2
#endif
#ifndef KEY_CLOSE
#define KEY_CLOSE -3
#endif
#ifndef KEY_END
#define KEY_END -4
#endif
#ifndef KEY_EXIT
#define KEY_EXIT -5
#endif
#ifndef KEY_UNDO
#define KEY_UNDO -6
#endif

/* This defines the game's speed.  */
#define TICK(x) ((x)*0.08)

extern  long  score, bonus;

/* from "main.c" */
extern  const char *my_name;
extern  WINDOW *moon, *status, *message;

enum game_state { INIT, TITLE, PAGER, PLAYING, HIGHSCORE };
extern  enum game_state  game_state;

extern  void  print_message (const char *str);
extern  void  prepare_for_exit (void);
extern  void  block_winch (void);
extern  void  block_all (void);
extern  void  unblock (void);

/* from "title.c" */
extern  int  title_mode (void);
extern  void  resize_title (void);

/* from "pager.c" */
extern  void  pager_mode (int);
extern  void  resize_pager (void);

/* from "game.c" */
extern  int  game_mode (void);
extern  void  resize_game (void);
extern  void  score_bonus (int x);

/* from "moon.c" */
extern  char *ground1, *ground2;
extern  int  d_rnd (int limit);
extern  void  resize_ground (int clear_it);
extern  void  print_ground (void);
extern  void  scroll_ground (void);

/* from "buggy.c" */
extern  int  car_base, score_base;
extern  void  initialize_buggy (void);
extern  void  print_buggy (void);
extern  void  jump (double t);
extern  int  can_jump (void);
extern  int  crash_check (void);

/* from "highscore.c" */
extern  int  highscore_mode (void);
extern  void  resize_highscore (void);

/* from "realname.c" */
extern  void  get_real_user_name (char *buffer, size_t size);

/* from "queue.c" */
enum event_type { ev_KEY, ev_TIMEOUT, ev_MESSAGE, ev_SCROLL, ev_BUGGY, \
		  ev_SCORE };
extern  double  sleep_meter;
extern  struct circle_buffer *queuelag;

extern  void  clock_adjust_delay (double dt);
extern  void  clear_queue (void);
extern  void  add_event (double t, enum event_type type);
extern  enum event_type  get_event (double *t);
extern  int  remove_event (enum event_type type, double *t);

/* from "lag.c" */
struct circle_buffer;
extern  struct circle_buffer *new_circle_buffer (void);
extern  void  add_value (struct circle_buffer *lm, double x);
extern  double  get_mean (const struct circle_buffer *lm);

/* from "vclock.c" */
extern  double  vclock (void);

/* from "persona.c" */
extern  void  initialize_persona (void);
extern  void  set_game_persona (void);
extern  void  set_user_persona (void);

/* from "error.c" */
#ifdef __GNUC__
extern  void  fatal (const char *format, ...)
	__attribute__ ((noreturn)) __attribute__ ((format (printf, 1, 2)));
#else
extern  void  fatal (const char *format, ...);
#endif

/* from "xmalloc.c" */
extern  void *xmalloc (size_t size);
extern  void *xrealloc (void *ptr, size_t size);

/* from "xstrdup.c" */
extern  char *xstrdup (const char *str);
extern  char *xstrndup (const char *str, size_t size);

/* from "mbpaths.c" */
extern  const char *score_dir;

#endif /* FILE_MOON_H_SEEN */
