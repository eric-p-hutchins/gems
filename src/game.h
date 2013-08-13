#ifndef GAME_T
#define GAME_T

#include <stdbool.h>

#include "SDL.h"

typedef enum { SPLASH_STATE, MENU_STATE, SESSION_STATE, QUIT_STATE } state_t;

typedef struct game_s game_t;
struct game_s {
  state_t state;
  bool *key_states;
  bool *prev_key_states;
  SDL_Surface *screen;
  int frame;
  int n_menu_items;
  int menu_cursor;
  void (**menu_functions)(game_t*);
};

game_t *game_create ();
bool game_key_pressed (game_t *game, SDLKey key);
bool game_key_released (game_t *game, SDLKey key);
void game_loop (game_t *game);
void game_destroy ();

void game_start (game_t *game);
void game_quit (game_t *game);

#endif
