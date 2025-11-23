#ifndef __MAUPLAY_H__
#define __MAUPLAY_H__

#include "config.h"

/* Milsko */
#include <MDE/Foundation.h>
#include <Mw/Milsko.h>

/* External */

/* Standard */
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/* main.c */
extern MwWidget	  window;
extern MwWidget	  album, info;
extern MwWidget	  bskipback, bplay, bpause, bstop, bskipfwd, brepeat, bshuffle;
extern MwWidget	  eltime, seekbar, rmtime;
extern MwWidget	  tree, list;
extern MwLLPixmap pxalbum;

/* db.c */
int  db_exec(const char* s);
int  db_init(void);
void db_add(const char* path);
void db_scan(void);

/* ui.c */
void ui_list_reset(void);
void ui_tree_reset(void);
void ui_init(void);
void ui_set_play_queue(int v);
void ui_set_all_music(int v);
void ui_set_albums(int v);
void ui_set_artists(int v);
void ui_set_genres(int v);
void ui_set_playlists(int v);

#endif
