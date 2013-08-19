#include <stdlib.h>

#include "game.h"

void
session_start (game_t *game)
{
  srand (time (NULL));
  game->state = SESSION_STATE;
  game->n_rows = 8;
  game->n_cols = 8;
  game->n_gem_types = 4;
  game->board = (int**)malloc (sizeof (int*) * game->n_cols);
  int i;
  for (i = 0; i < game->n_cols; ++i)
    {
      game->board[i] = (int*)malloc (sizeof (int) * game->n_rows);
    }
  int match_list[2];
  int j;
  for (i = 0; i < game->n_rows; ++i)
    {
      for (j = 0; j < game->n_cols; ++j)
        {
          match_list[0] = match_list[1] = -1;
          if (j >= 2 && game->board[j-2][i] == game->board[j-1][i])
            {
              match_list[0] = game->board[j-2][i];
            }
          if (i >= 2 && game->board[j][i-2] == game->board[j][i-1])
            {
              match_list[1] = game->board[j][i-2];
            }
          game->board[j][i] = rand () % game->n_gem_types;
          while (game->board[j][i] == match_list[0]
                 || game->board[j][i] == match_list[1])
            {
              ++(game->board[j][i]);
            }
        }
    }
}

void
handle_keys (game_t *game)
{
  if (game_key_pressed (game, SDLK_LEFT))
    {
      if (game->board_cursor_x > 0)
        {
          --game->board_cursor_x;
        }
    }
  else if (game_key_pressed (game, SDLK_RIGHT))
    {
      if (game->board_cursor_x < game->n_cols - 1)
        {
          ++game->board_cursor_x;
        }
    }
  else if (game_key_pressed (game, SDLK_UP))
    {
      if (game->board_cursor_y > 0)
        {
          --game->board_cursor_y;
        }
    }
  else if (game_key_pressed (game, SDLK_DOWN))
    {
      if (game->board_cursor_y < game->n_rows - 1)
        {
          ++game->board_cursor_y;
        }
    }
}

void
handle_t_shape (game_t *game)
{
  int i, j;
  for (i = 0; i < game->n_rows; ++i)
    {
      for (j = 0; j < game->n_cols; ++j)
        {
          if (j >= 1 && j < game->n_cols - 1
              && i < game->n_rows - 2
              && game->board[j][i] == game->board[j-1][i]
              && game->board[j][i] == game->board[j+1][i]
              && game->board[j][i] == game->board[j][i+1]
              && game->board[j][i] == game->board[j][i+2])
            {
              game->board[j][i] = game->board[j][i] + game->n_gem_types * 2;
              game->board[j-1][i] = -1;
              game->board[j+1][i] = -1;
              game->board[j][i+1] = -1;
              game->board[j][i+2] = -1;
            }
          else if (i >= 1 && i < game->n_rows - 1
                   && j < game->n_cols - 2
                   && game->board[j][i] == game->board[j][i-1]
                   && game->board[j][i] == game->board[j][i+1]
                   && game->board[j][i] == game->board[j+1][i]
                   && game->board[j][i] == game->board[j+2][i])
            {
              game->board[j][i] = game->board[j][i] + game->n_gem_types * 2;
              game->board[j][i-1] = -1;
              game->board[j][i+1] = -1;
              game->board[j+1][i] = -1;
              game->board[j+2][i] = -1;
            }
          else if (j >= 1 && j < game->n_cols - 1
                   && i > 1
                   && game->board[j][i] == game->board[j-1][i]
                   && game->board[j][i] == game->board[j+1][i]
                   && game->board[j][i] == game->board[j][i-1]
                   && game->board[j][i] == game->board[j][i-2])
            {
              game->board[j][i] = game->board[j][i] + game->n_gem_types * 2;
              game->board[j-1][i] = -1;
              game->board[j+1][i] = -1;
              game->board[j][i-1] = -1;
              game->board[j][i-2] = -1;
            }
          else if (i >= 1 && i < game->n_rows - 1
                   && j > 1
                   && game->board[j][i] == game->board[j][i-1]
                   && game->board[j][i] == game->board[j][i+1]
                   && game->board[j][i] == game->board[j-1][i]
                   && game->board[j][i] == game->board[j-2][i])
            {
              game->board[j][i] = game->board[j][i] + game->n_gem_types * 2;
              game->board[j][i-1] = -1;
              game->board[j][i+1] = -1;
              game->board[j-1][i] = -1;
              game->board[j-2][i] = -1;
            }
        }
    }
}

void
handle_l_shape (game_t *game)
{
  int i, j;
  for (i = 0; i < game->n_rows; ++i)
    {
      for (j = 0; j < game->n_cols; ++j)
        {
          if (j < game->n_cols - 2 && i < game->n_rows - 2
              && game->board[j][i] == game->board[j+1][i]
              && game->board[j][i] == game->board[j+2][i]
              && game->board[j][i] == game->board[j][i+1]
              && game->board[j][i] == game->board[j][i+2])
            {
              game->board[j][i] = game->board[j][i] + game->n_gem_types * 2;
              game->board[j+1][i] = -1;
              game->board[j+2][i] = -1;
              game->board[j][i+1] = -1;
              game->board[j][i+2] = -1;
            }
          else if (i >= 2 && j < game->n_cols - 2
                   && game->board[j][i] == game->board[j][i-1]
                   && game->board[j][i] == game->board[j][i-2]
                   && game->board[j][i] == game->board[j+1][i]
                   && game->board[j][i] == game->board[j+2][i])
            {
              game->board[j][i] = game->board[j][i] + game->n_gem_types * 2;
              game->board[j][i-1] = -1;
              game->board[j][i-2] = -1;
              game->board[j+1][i] = -1;
              game->board[j+2][i] = -1;
            }
          else if (j >= 2 && i >= 2
                   && game->board[j][i] == game->board[j-1][i]
                   && game->board[j][i] == game->board[j-2][i]
                   && game->board[j][i] == game->board[j][i-1]
                   && game->board[j][i] == game->board[j][i-2])
            {
              game->board[j][i] = game->board[j][i] + game->n_gem_types * 2;
              game->board[j-1][i] = -1;
              game->board[j-2][i] = -1;
              game->board[j][i-1] = -1;
              game->board[j][i-2] = -1;
            }
          else if (j >= 2 && i < game->n_rows - 2
                   && game->board[j][i] == game->board[j][i+1]
                   && game->board[j][i] == game->board[j][i+2]
                   && game->board[j][i] == game->board[j-1][i]
                   && game->board[j][i] == game->board[j-2][i])
            {
              game->board[j][i] = game->board[j][i] + game->n_gem_types * 2;
              game->board[j][i+1] = -1;
              game->board[j][i+2] = -1;
              game->board[j-1][i] = -1;
              game->board[j-2][i] = -1;
            }
        }
    }
}

void
handle_three_in_row_or_column (game_t *game)
{
  int i, j;
  for (i = 0; i < game->n_rows; ++i)
    {
      for (j = 0; j < game->n_cols; ++j)
        {
          if (i >= 2
              && game->board[j][i] == game->board[j][i-1]
              && game->board[j][i] == game->board[j][i-2])
            {
              game->board[j][i] = -1;
              game->board[j][i-1] = -1;
              game->board[j][i-2] = -1;
            }
          else if (j < game->n_cols - 2
                   && game->board[j][i] == game->board[j+1][i]
                   && game->board[j][i] == game->board[j+2][i])
            {
              game->board[j][i] = -1;
              game->board[j+1][i] = -1;
              game->board[j+2][i] = -1;
            }
        }
    }
}

void
handle_four_in_row_or_column (game_t *game)
{
  int i, j;
  for (i = 0; i < game->n_rows; ++i)
    {
      for (j = 0; j < game->n_cols; ++j)
        {
          if (i >= 3
              && game->board[j][i] == game->board[j][i-1]
              && game->board[j][i] == game->board[j][i-2]
              && game->board[j][i] == game->board[j][i-3])
            {
              game->board[j][i-1] = game->board[j][i]
                + game->n_gem_types;
              game->board[j][i] = -1;
              game->board[j][i-2] = -1;
              game->board[j][i-3] = -1;
            }
          else if (j < game->n_cols - 3
                   && game->board[j][i] == game->board[j+1][i]
                   && game->board[j][i] == game->board[j+2][i]
                   && game->board[j][i] == game->board[j+3][i])
            {
              game->board[j+1][i] = game->board[j][i]
                + game->n_gem_types;
              game->board[j][i] = -1;
              game->board[j+2][i] = -1;
              game->board[j+3][i] = -1;
            }
        }
    }
}

void
handle_five_in_row_or_column (game_t *game)
{
  int i, j;
  for (i = 0; i < game->n_rows; ++i)
    {
      for (j = 0; j < game->n_cols; ++j)
        {
          if (i >= 4
              && game->board[j][i] == game->board[j][i-1]
              && game->board[j][i] == game->board[j][i-2]
              && game->board[j][i] == game->board[j][i-3]
              && game->board[j][i] == game->board[j][i-4])
            {
              game->board[j][i-2] = game->board[j][i]
                + 3 * game->n_gem_types;
              game->board[j][i] = -1;
              game->board[j][i-1] = -1;
              game->board[j][i-3] = -1;
              game->board[j][i-4] = -1;
            }
          else if (j < game->n_cols - 4
                   && game->board[j][i] == game->board[j+1][i]
                   && game->board[j][i] == game->board[j+2][i]
                   && game->board[j][i] == game->board[j+3][i]
                   && game->board[j][i] == game->board[j+4][i])
            {
              game->board[j+2][i] = game->board[j][i]
                + 3 * game->n_gem_types;
              game->board[j][i] = -1;
              game->board[j+1][i] = -1;
              game->board[j+3][i] = -1;
              game->board[j+4][i] = -1;
            }
        }
    }
}

void
drop_columns_to_fill_holes (game_t *game)
{
  int i, j, k;
  for (i = 0; i < game->n_cols; ++i)
    {
      for (j = game->n_rows - 1; j >= 0; --j)
        {
          if (game->board[i][j] == -1)
            {
              for (k = j; k > 0; --k)
                {
                  game->board[i][k] = game->board[i][k-1];
                }
              game->board[i][0] = rand () % game->n_gem_types;
              break;
            }
        }
    }
}

void
session_loop (game_t *game)
{
  handle_keys (game);
  handle_five_in_row_or_column (game);
  handle_t_shape (game);
  handle_l_shape (game);
  handle_four_in_row_or_column (game);
  handle_three_in_row_or_column (game);
  drop_columns_to_fill_holes (game);
}
