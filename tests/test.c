#include "game.h"

#include "test.h"

int **
copy_board (game_t *game)
{
  int **board = (int**)malloc (sizeof (int*) * game->n_cols);
  int i, j;
  for (i = 0; i < game->n_cols; ++i)
    {
      board[i] = (int*)malloc (sizeof (int) * game->n_rows);
      for (j = 0; j < game->n_rows; ++j)
        {
          board[i][j] = game->board[i][j];
        }
    }
  return board;
}

void
setup_board_every_gem_different (game_t *game)
{
  game->n_gem_types = 1000000;
  int i, j;
  for (i = 0; i < game->n_cols; ++i)
    {
      for (j = 0; j < game->n_rows; ++j)
        {
          game->board[i][j] = j * game->n_cols + i;
        }
    }
}

void
wait (game_t *game, int frames)
{
  int i;
  for (i = 0; i < frames; ++i)
    {
      game_loop (game);
    }
}
