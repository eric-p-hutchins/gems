#include "game.h"

#include "test.h"

#include "session.h"

int
main (int argc, char *argv[])
{
  game_t *game = game_create (game);
  game_start (game);

  // Moving the corners of a checkerboard pattern shouldn't be legal

  int w = game->n_cols;
  int h = game->n_rows;

  int i, j;
  for (i = 0; i < game->n_cols; ++i)
    {
      for (j = 0; j < game->n_rows; ++j)
        {
          game->board[i][j] = (i + j % 2) % 2;
        }
    }

  fail_if (session_legal_move (game, 0, 0, 1, 0));
  fail_if (session_legal_move (game, 1, 0, 0, 0));

  fail_if (session_legal_move (game, 0, 0, 0, 1));
  fail_if (session_legal_move (game, 0, 1, 0, 0));

  fail_if (session_legal_move (game, w-1, 0, w-2, 0));
  fail_if (session_legal_move (game, w-2, 0, w-1, 0));

  fail_if (session_legal_move (game, w-1, 0, w-1, 1));
  fail_if (session_legal_move (game, w-1, 1, w-1, 0));

  fail_if (session_legal_move (game, 0, h-1, 0, h-2));
  fail_if (session_legal_move (game, 0, h-2, 0, h-1));

  fail_if (session_legal_move (game, 0, h-1, 1, h-1));
  fail_if (session_legal_move (game, 1, h-1, 0, h-1));

  fail_if (session_legal_move (game, w-1, h-1, w-1, h-2));
  fail_if (session_legal_move (game, w-1, h-2, w-1, h-1));

  fail_if (session_legal_move (game, w-1, h-1, w-2, h-1));
  fail_if (session_legal_move (game, w-2, h-1, w-1, h-1));

  game_destroy (game);

  return 0;
}
