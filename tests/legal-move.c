#include "game.h"

#include "session.h"

#include "test.h"

int
main (int argc, char *argv[])
{
  game_t *game = game_create (game);
  game_start (game);

  // Swapping to or from outside of the board is illegal
  fail_if (session_legal_move (game, 0, 0, -1, 0));
  fail_if (session_legal_move (game, 0, 0, 0, -1));
  fail_if (session_legal_move (game, game->n_cols - 1, 0, game->n_cols, 0));
  fail_if (session_legal_move (game, game->n_cols - 1, 0, game->n_cols - 1, -1));
  fail_if (session_legal_move (game, 0, game->n_rows - 1, 0, game->n_rows));
  fail_if (session_legal_move (game, 0, game->n_rows - 1, -1, game->n_rows - 1));
  fail_if (session_legal_move (game, game->n_cols - 1, game->n_rows - 1,
                            game->n_cols - 1, game->n_rows));
  fail_if (session_legal_move (game, game->n_cols - 1, game->n_rows - 1,
                            game->n_cols, game->n_rows - 1));

  // Swapping non-adjacent locations is illegal
  fail_if (session_legal_move (game, 0, 0, 1, 1));
  fail_if (session_legal_move (game, 1, 1, 0, 0));
  fail_if (session_legal_move (game, 3, 2, 0, 1));
  fail_if (session_legal_move (game, 5, 4, 2, 2));

  // Swap and neither location is part of row or col of 3 or more
  game->n_gem_types = 1000000;
  setup_board_every_gem_different (game);

  // Since every location is different, there can be no legal moves
  int i, j;
  for (i = 0; i < game->n_cols; ++i)
    {
      for (j = 0; j < game->n_rows; ++j)
        {
          fail_if (session_legal_move (game, i, j, i - 1, j));
          fail_if (session_legal_move (game, i, j, i, j - 1));
          fail_if (session_legal_move (game, i, j, i + 1, j));
          fail_if (session_legal_move (game, i, j, i, j + 1));
        }
    }

  // Swap into a row of three

  // On bottom

  setup_board_every_gem_different (game);
  game->board[2][2] = 999999;
  game->board[2][3] = 999999;
  game->board[2][4] = 0;
  game->board[3][4] = 999999;
  fail_if (!session_legal_move (game, 2, 4, 3, 4));
  fail_if (!session_legal_move (game, 3, 4, 2, 4));

  // In middle

  setup_board_every_gem_different (game);
  game->board[2][2] = 999999;
  game->board[2][3] = 0;
  game->board[2][4] = 1999999;
  game->board[3][3] = 999999;
  fail_if (!session_legal_move (game, 2, 3, 3, 3));
  fail_if (!session_legal_move (game, 3, 3, 2, 3));

  // On top

  setup_board_every_gem_different (game);
  game->board[2][2] = 0;
  game->board[2][3] = 999999;
  game->board[2][4] = 2999999;
  game->board[3][2] = 999999;
  fail_if (!session_legal_move (game, 2, 2, 3, 2));
  fail_if (!session_legal_move (game, 3, 2, 2, 2));

  // Swap into a col of three

  // On right

  setup_board_every_gem_different (game);
  game->board[2][2] = 999999;
  game->board[3][2] = 3999999;
  game->board[4][2] = 0;
  game->board[4][3] = 999999;
  fail_if (!session_legal_move (game, 4, 2, 4, 3));
  fail_if (!session_legal_move (game, 4, 3, 4, 2));

  // In middle

  setup_board_every_gem_different (game);
  game->board[2][2] = 1999999;
  game->board[3][2] = 0;
  game->board[4][2] = 999999;
  game->board[3][3] = 999999;
  fail_if (!session_legal_move (game, 3, 2, 3, 3));
  fail_if (!session_legal_move (game, 3, 3, 3, 2));

  // On left

  setup_board_every_gem_different (game);
  game->board[2][2] = 0;
  game->board[3][2] = 999999;
  game->board[4][2] = 999999;
  game->board[2][3] = 2999999;
  fail_if (!session_legal_move (game, 2, 2, 2, 3));
  fail_if (!session_legal_move (game, 2, 3, 2, 2));

  // Swapping a special1 with a special1

  setup_board_every_gem_different (game);
  game->board[2][2] = 1999999;
  game->board[2][3] = 1999999;
  fail_if (!session_legal_move (game, 2, 2, 2, 3));
  fail_if (!session_legal_move (game, 2, 3, 2, 2));

  setup_board_every_gem_different (game);
  game->board[2][2] = 1999999;
  game->board[3][2] = 1999999;
  fail_if (!session_legal_move (game, 2, 2, 3, 2));
  fail_if (!session_legal_move (game, 3, 2, 2, 2));

  // Swapping a special1 with a special2

  setup_board_every_gem_different (game);
  game->board[2][2] = 1999999;
  game->board[2][3] = 2999999;
  fail_if (!session_legal_move (game, 2, 2, 2, 3));
  fail_if (!session_legal_move (game, 2, 3, 2, 2));

  setup_board_every_gem_different (game);
  game->board[2][2] = 1999999;
  game->board[3][2] = 2999999;
  fail_if (!session_legal_move (game, 2, 2, 3, 2));
  fail_if (!session_legal_move (game, 3, 2, 2, 2));

  // Swapping a special2 with a special2

  setup_board_every_gem_different (game);
  game->board[2][2] = 2999999;
  game->board[2][3] = 2999999;
  fail_if (!session_legal_move (game, 2, 2, 2, 3));
  fail_if (!session_legal_move (game, 2, 3, 2, 2));

  setup_board_every_gem_different (game);
  game->board[2][2] = 2999999;
  game->board[3][2] = 2999999;
  fail_if (!session_legal_move (game, 2, 2, 3, 2));
  fail_if (!session_legal_move (game, 3, 2, 2, 2));

  // Swapping a special1 with a special3

  setup_board_every_gem_different (game);
  game->board[2][2] = 1999999;
  game->board[2][3] = 3999999;
  fail_if (!session_legal_move (game, 2, 2, 2, 3));
  fail_if (!session_legal_move (game, 2, 3, 2, 2));

  setup_board_every_gem_different (game);
  game->board[2][2] = 1999999;
  game->board[3][2] = 3999999;
  fail_if (!session_legal_move (game, 2, 2, 3, 2));
  fail_if (!session_legal_move (game, 3, 2, 2, 2));

  // Swapping a special2 with a special3

  setup_board_every_gem_different (game);
  game->board[2][2] = 2999999;
  game->board[2][3] = 3999999;
  fail_if (!session_legal_move (game, 2, 2, 2, 3));
  fail_if (!session_legal_move (game, 2, 3, 2, 2));

  setup_board_every_gem_different (game);
  game->board[2][2] = 2999999;
  game->board[3][2] = 3999999;
  fail_if (!session_legal_move (game, 2, 2, 3, 2));
  fail_if (!session_legal_move (game, 3, 2, 2, 2));

  // Swapping a special3 with a special3

  setup_board_every_gem_different (game);
  game->board[2][2] = 3999999;
  game->board[2][3] = 3999999;
  fail_if (!session_legal_move (game, 2, 2, 2, 3));
  fail_if (!session_legal_move (game, 2, 3, 2, 2));

  setup_board_every_gem_different (game);
  game->board[2][2] = 3999999;
  game->board[3][2] = 3999999;
  fail_if (!session_legal_move (game, 2, 2, 3, 2));
  fail_if (!session_legal_move (game, 3, 2, 2, 2));

  game_destroy (game);
  return 0;
}
