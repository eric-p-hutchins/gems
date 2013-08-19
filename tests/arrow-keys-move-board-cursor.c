#include "game.h"

#include "test.h"

int
main (int argc, char *argv[])
{
  game_t *game = game_create ();
  game_start (game);

  // TOP LEFT CORNER

  game->board_cursor_x = 0;
  game->board_cursor_y = 0;

  press_key_and_loop (game, SDLK_LEFT);
  fail_if (game->board_cursor_x != 0
           || game->board_cursor_y != 0);
  release_key_and_loop (game, SDLK_LEFT);

  press_key_and_loop (game, SDLK_UP);
  fail_if (game->board_cursor_x != 0
           || game->board_cursor_y != 0);
  release_key_and_loop (game, SDLK_UP);

  press_key_and_loop (game, SDLK_RIGHT);
  fail_if (game->board_cursor_x != 1
           || game->board_cursor_y != 0);
  release_key_and_loop (game, SDLK_RIGHT);

  game->board_cursor_x = 0;
  game->board_cursor_y = 0;

  press_key_and_loop (game, SDLK_DOWN);
  fail_if (game->board_cursor_x != 0
           || game->board_cursor_y != 1);
  release_key_and_loop (game, SDLK_DOWN);

  // TOP RIGHT CORNER

  game->board_cursor_x = game->n_cols - 1;
  game->board_cursor_y = 0;

  press_key_and_loop (game, SDLK_RIGHT);
  fail_if (game->board_cursor_x != game->n_cols - 1
           || game->board_cursor_y != 0);
  release_key_and_loop (game, SDLK_RIGHT);

  press_key_and_loop (game, SDLK_UP);
  fail_if (game->board_cursor_x != game->n_cols - 1
           || game->board_cursor_y != 0);
  release_key_and_loop (game, SDLK_UP);

  press_key_and_loop (game, SDLK_LEFT);
  fail_if (game->board_cursor_x != game->n_cols - 2
           || game->board_cursor_y != 0);
  release_key_and_loop (game, SDLK_LEFT);

  game->board_cursor_x = game->n_cols - 1;
  game->board_cursor_y = 0;

  press_key_and_loop (game, SDLK_DOWN);
  fail_if (game->board_cursor_x != game->n_cols - 1
           || game->board_cursor_y != 1);
  release_key_and_loop (game, SDLK_DOWN);

  // BOTTOM LEFT CORNER

  game->board_cursor_x = 0;
  game->board_cursor_y = game->n_rows - 1;

  press_key_and_loop (game, SDLK_LEFT);
  fail_if (game->board_cursor_x != 0
           || game->board_cursor_y != game->n_rows - 1);
  release_key_and_loop (game, SDLK_LEFT);

  press_key_and_loop (game, SDLK_DOWN);
  fail_if (game->board_cursor_x != 0
           || game->board_cursor_y != game->n_rows - 1);
  release_key_and_loop (game, SDLK_DOWN);

  press_key_and_loop (game, SDLK_RIGHT);
  fail_if (game->board_cursor_x != 1
           || game->board_cursor_y != game->n_rows - 1);
  release_key_and_loop (game, SDLK_RIGHT);

  game->board_cursor_x = 0;
  game->board_cursor_y = game->n_rows - 1;

  press_key_and_loop (game, SDLK_UP);
  fail_if (game->board_cursor_x != 0
           || game->board_cursor_y != game->n_rows - 2);
  release_key_and_loop (game, SDLK_UP);

  // BOTTOM RIGHT CORNER

  game->board_cursor_x = game->n_cols - 1;
  game->board_cursor_y = game->n_rows - 1;

  press_key_and_loop (game, SDLK_RIGHT);
  fail_if (game->board_cursor_x != game->n_cols - 1
           || game->board_cursor_y != game->n_rows - 1);
  release_key_and_loop (game, SDLK_RIGHT);

  press_key_and_loop (game, SDLK_DOWN);
  fail_if (game->board_cursor_x != game->n_cols - 1
           || game->board_cursor_y != game->n_rows - 1);
  release_key_and_loop (game, SDLK_DOWN);

  press_key_and_loop (game, SDLK_LEFT);
  fail_if (game->board_cursor_x != game->n_cols - 2
           || game->board_cursor_y != game->n_rows - 1);
  release_key_and_loop (game, SDLK_LEFT);

  game->board_cursor_x = game->n_cols - 1;
  game->board_cursor_y = game->n_rows - 1;

  press_key_and_loop (game, SDLK_UP);
  fail_if (game->board_cursor_x != game->n_cols - 1
           || game->board_cursor_y != game->n_rows - 2);
  release_key_and_loop (game, SDLK_UP);

  game_destroy (game);
  return 0;
}
