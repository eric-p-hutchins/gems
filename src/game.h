#ifndef GAME_T
#define GAME_T

#include <stdbool.h>

#include "SDL.h"

typedef enum { SPLASH_STATE, MENU_STATE, SESSION_STATE, QUIT_STATE } state_t;

typedef struct gem_s gem_t;

struct gem_s {
  int x;
  int y;
  int dy;
  int type;
  int level;
};

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
  bool menu_held_down;
  int n_cols;
  int n_rows;
  int board_cursor_x;
  int board_cursor_y;
  bool cursor_locked;
  int n_gem_types;
  int **board;
  int fps;
  int n_gems;
  gem_t **gems;
  bool *column_settled;
  SDL_Surface *sprite;
  SDL_Surface *frame_sprite;
  SDL_Surface *button_sprite;
};

game_t *game_create ();
bool game_key_pressed (game_t *game, SDLKey key);
bool game_key_released (game_t *game, SDLKey key);
void game_loop (game_t *game);
void game_destroy ();

gem_t *gem_create (int x, int y, int type, int level);

void game_add_gem (game_t *game, gem_t *gem);
void game_move_gem (game_t *game, int x, int y, int gem_x, int gem_y);
void game_remove_gem (game_t *game, int x, int y);
void game_swap_gems (game_t *game, int x1, int y1, int x2, int y2);

void game_start (game_t *game);
void game_quit (game_t *game);

#endif
