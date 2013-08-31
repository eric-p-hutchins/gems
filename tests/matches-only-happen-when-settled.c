#include "game.h"

#include "test.h"

int
main (int argc, char *argv[])
{
  game_t *game = game_create ();
  game_start (game);

  setup_board_every_gem_different (game);
  replace_gems (game, "\n\
      \n\
  .   \n\
 .*.  \n\
  *   \n\
  *   \n\
      ");

  int i;
  for (i = 0; i < 50 * 2; ++i)
    {
      game_loop (game);
    }

  // ######
  // ######
  // #.#.##
  // ######
  // ##.###
  // ######

  fail_if (game->board[1][2] != 999999);
  fail_if (game->board[3][2] != 999999);
  fail_if (game->board[2][4] != 999999);

  setup_board_every_gem_different (game);
  replace_gems (game, "\
  *   \n\
 *.*  \n\
  .   \n\
  .   \n\
  O   \n\
      ");
  for (i = 0; i < 50 * 2; ++i)
    {
      game_loop (game);
    }

  fail_if (game->board[1][1] == 999996);
  fail_if (game->board[3][1] == 999996);

  setup_board_every_gem_different (game);
  replace_gems (game, "\n\
      \n\
  .   \n\
 .*.. \n\
  *   \n\
  *   \n\
      ");

  for (i = 0; i < 50 * 2; ++i)
    {
      game_loop (game);
    }

  fail_if (game->board[1][2] != 999999);
  fail_if (game->board[2][4] != 999999);
  fail_if (game->board[3][2] != 999999);
  fail_if (game->board[4][2] != 999999);

  setup_board_every_gem_different (game);
  replace_gems (game, "\
  *   \n\
 *.*  \n\
  .   \n\
  .   \n\
  .   \n\
  O   ");
  for (i = 0; i < 50 * 2; ++i)
    {
      game_loop (game);
    }

  fail_if (game->board[1][1] == 999996);
  fail_if (game->board[3][1] == 999996);

  setup_board_every_gem_different (game);
  replace_gems (game, "\n\
      \n\
  . . \n\
 .*.*.\n\
  * * \n\
  * * \n\
      ");

  for (i = 0; i < 50 * 2; ++i)
    {
      game_loop (game);
    }

  fail_if (game->board[1][2] != 999999);
  fail_if (game->board[2][4] != 999999);
  fail_if (game->board[3][2] != 999999);
  fail_if (game->board[4][4] != 999999);
  fail_if (game->board[5][2] != 999999);

  setup_board_every_gem_different (game);
  replace_gems (game, "\n\
  *   \n\
 *.*  \n\
  .   \n\
  .   \n\
  .   \n\
  .   \n\
  O   ");
  for (i = 0; i < 50 * 2; ++i)
    {
      game_loop (game);
    }

  fail_if (game->board[1][1] == 999996);
  fail_if (game->board[3][1] == 999996);

  setup_board_every_gem_different (game);
  replace_gems (game, "\
  *   \n\
 *.*  \n\
  .   \n\
  .   \n\
  .   \n\
  .   \n\
  O   ");
  for (i = 0; i < 50 * 2; ++i)
    {
      game_loop (game);
    }

  fail_if (game->board[1][1] == 999996);
  fail_if (game->board[3][1] == 999996);

  // This tests for both up and down facing T shapes

  setup_board_every_gem_different (game);
  replace_gems (game, "\
  *   \n\
  *   \n\
 ***  \n\
  O   \n\
  O   \n\
  O   \n\
  O   ");
  for (i = 0; i < 50 * 2; ++i)
    {
      game_loop (game);
    }

  fail_if (game->board[1][2] != 999996);
  fail_if (game->board[3][2] != 999996);

  // This tests for two L shapes as well as a T shape

  setup_board_every_gem_different (game);
  replace_gems (game, "\
  *   \n\
  *   \n\
  *   \n\
  O** \n\
  O   \n\
  O   \n\
  O   ");
  for (i = 0; i < 50 * 2; ++i)
    {
      game_loop (game);
    }

  fail_if (game->board[3][3] != 999996);
  fail_if (game->board[4][3] != 999996);

  // This tests for two L shapes as well as a T shape

  setup_board_every_gem_different (game);
  replace_gems (game, "\
  *   \n\
  *   \n\
  *   \n\
**O   \n\
  O   \n\
  O   \n\
  O   ");
  for (i = 0; i < 50 * 2; ++i)
    {
      game_loop (game);
    }

  fail_if (game->board[0][3] != 999996);
  fail_if (game->board[1][3] != 999996);

  game_destroy (game);
  return 0;
}
