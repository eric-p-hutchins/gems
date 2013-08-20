#include "game.h"

#include "test.h"

bool
success (int **old_board, game_t *game, int newx, int newy, int oldx, int oldy)
{
  // #*#
  // #&#
  // #%#
  // #@$
  // ###

  int i;
  for (i = 0; i < 50 * 2; ++i)
    {
      game_loop (game);
    }

  if (newx != 2 || newy != 4)
    {
      if (game->board[newx][newy] != old_board[oldx][oldy])
        {
          return false;
        }
    }
  if (oldx != 2 || oldy != 4)
    {
      if (game->board[oldx][oldy] != old_board[newx][newy])
        {
          return false;
        }
    }
  if (game->board[2][4] != old_board[2][1])
    {
      return false;
    }
  if (game->board_cursor_x != newx)
    {
      return false;
    }
  if (game->board_cursor_y != newy)
    {
      return false;
    }
  if (game->cursor_locked)
    {
      return false;
    }
  return true;
}

int **
setup_board (game_t *game)
{
  setup_board_every_gem_different (game);

  // #@#
  // #.#
  // #.#
  // ###
  // ###

  game->n_gem_types = 1000000;
  game->board[2][2] = 999999;
  game->board[2][3] = 999999;

  return copy_board (game);
}

int
main (int argc, char *argv[])
{
  game_t *game = game_create ();
  game_start (game);

  int **old_board = NULL;

  old_board = setup_board (game);

  game->board_cursor_x = 2;
  game->board_cursor_y = 4;
  game->board[3][4] = 999999;

  press_key_and_loop (game, SDLK_SPACE);
  fail_if (!game->cursor_locked);
  release_key_and_loop (game, SDLK_SPACE);

  press_key_and_loop (game, SDLK_RIGHT);
  release_key_and_loop (game, SDLK_RIGHT);

  wait (game, 50 * 2);

  fail_if (!success (old_board, game, 3, 4, 2, 4));

  old_board = setup_board (game);

  game->board_cursor_x = 3;
  game->board_cursor_y = 4;
  game->board[3][4] = 999999;

  press_key_and_loop (game, SDLK_SPACE);
  fail_if (!game->cursor_locked);
  release_key_and_loop (game, SDLK_SPACE);

  press_key_and_loop (game, SDLK_LEFT);
  release_key_and_loop (game, SDLK_LEFT);

  wait (game, 50 * 2);

  fail_if (!success (old_board, game, 2, 4, 3, 4));

  old_board = setup_board (game);

  game->board_cursor_x = 2;
  game->board_cursor_y = 4;
  game->board[2][5] = 999999;

  press_key_and_loop (game, SDLK_SPACE);
  fail_if (!game->cursor_locked);
  release_key_and_loop (game, SDLK_SPACE);

  press_key_and_loop (game, SDLK_DOWN);
  release_key_and_loop (game, SDLK_DOWN);

  wait (game, 50 * 2);

  fail_if (!success (old_board, game, 2, 5, 2, 4));

  old_board = setup_board (game);

  game->board_cursor_x = 2;
  game->board_cursor_y = 5;
  game->board[2][5] = 999999;

  press_key_and_loop (game, SDLK_SPACE);
  fail_if (!game->cursor_locked);
  release_key_and_loop (game, SDLK_SPACE);

  press_key_and_loop (game, SDLK_UP);
  release_key_and_loop (game, SDLK_UP);

  wait (game, 50 * 2);

  fail_if (!success (old_board, game, 2, 4, 2, 5));

  game_destroy (game);
  return 0;
}
