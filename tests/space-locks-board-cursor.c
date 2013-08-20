#include "game.h"

#include "test.h"

#define fail_if_not_at(game,x,y)                                    \
  fail_if (game->board_cursor_x != x || game->board_cursor_y != y);

int
main (int argc, char *argv[])
{
  game_t *game = game_create ();
  game_start (game);

  setup_board_every_gem_different (game);

  game->board_cursor_x = 1;
  game->board_cursor_y = 1;

  press_key_and_loop (game, SDLK_SPACE);
  fail_if (!game->cursor_locked);
  release_key_and_loop (game, SDLK_SPACE);

  press_key_and_loop (game, SDLK_LEFT);
  fail_if_not_at (game, 1, 1);
  release_key_and_loop (game, SDLK_LEFT);

  press_key_and_loop (game, SDLK_RIGHT);
  fail_if_not_at (game, 1, 1);
  release_key_and_loop (game, SDLK_RIGHT);

  press_key_and_loop (game, SDLK_UP);
  fail_if_not_at (game, 1, 1);
  release_key_and_loop (game, SDLK_UP);

  press_key_and_loop (game, SDLK_DOWN);
  fail_if_not_at (game, 1, 1);
  release_key_and_loop (game, SDLK_DOWN);

  press_key_and_loop (game, SDLK_SPACE);
  fail_if (game->cursor_locked);
  release_key_and_loop (game, SDLK_SPACE);

  game_destroy (game);
  return 0;
}
