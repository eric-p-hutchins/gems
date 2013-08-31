#ifndef TEST_H
#define TEST_H

#include "game.h"

#define press_key_and_loop(game, key)  \
  game->key_states[key] = true;        \
  game_loop (game);

#define release_key_and_loop(game, key)         \
  game->key_states[key] = false;                \
  game_loop (game);

#define fail_if(condition)                      \
  if (condition)                                \
    {                                           \
      exit (1);                                 \
    }

int **copy_board (game_t *game);
void setup_board_every_gem_different (game_t *game);
void wait (game_t *game, int frames);
void replace_gem (game_t *game, int x, int y, int val);
void replace_gems (game_t *game, char *pattern);

#endif
