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
  int n = game->n_rows;
  int m = game->n_cols;
  int i, j;
  for (i = 0; i < m; ++i)
    {
      for (j = 0; j < n; ++j)
        {
          game_remove_gem (game, i, j);
        }
    }
  for (i = 0; i < m; ++i)
    {
      for (j = 0; j < n; ++j)
        {
          gem_t *gem = (gem_t*)malloc (sizeof (gem_t));
          gem->x = i * 24;
          gem->y = j * 24;
          gem->type = j * m + i;
          gem->level = 0;
          game_add_gem (game, gem);
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

void
replace_gem (game_t *game, int x, int y, int val)
{
  game_remove_gem (game, x, y);
  gem_t *gem = (gem_t*)malloc (sizeof (gem_t));
  gem->x = x * 24;
  gem->y = y * 24;
  gem->type = val % game->n_gem_types;
  gem->level = val / game->n_gem_types;
  game_add_gem (game, gem);
}

void
replace_gems (game_t *game, char *pattern)
{
  if (pattern[0] == '\n')
    {
      pattern = pattern + 1;
    }
  int row = 0;
  int col = 0;
  int i;
  for (i = 0; i < strlen (pattern) + 1; ++i)
    {
      switch (pattern[i])
        {
        case ' ':
          break;
        case 'O':
          game_remove_gem (game, col, row);
          game->board[col][row] = -1;
          break;
        case '@':
          replace_gem (game, col, row, TESTGEM_AT);
          break;
        case '=':
          replace_gem (game, col, row, TESTGEM_EQUALS);
          break;
        case '$':
          replace_gem (game, col, row, TESTGEM_DOLLAR);
          break;
        case '%':
          replace_gem (game, col, row, TESTGEM_PERCENT);
          break;
        case '&':
          replace_gem (game, col, row, TESTGEM_AMP);
          break;
        case '!':
          replace_gem (game, col, row, TESTGEM_BANG);
          break;
        case '?':
          replace_gem (game, col, row, TESTGEM_QUESTION);
          break;
        case '+':
          replace_gem (game, col, row, TESTGEM_PLUS);
          break;
        case '.':
          replace_gem (game, col, row, TESTGEM_DOT);
          break;
        case '*':
          replace_gem (game, col, row, TESTGEM_ASTERISK);
          break;
        case '#':
          replace_gem (game, col, row, TESTGEM_HASH);
          break;
        }
      if (pattern[i] == '\n' || pattern[i] == '\0')
        {
          ++row;
          col = 0;
        }
      else
        {
          ++col;
        }
    }
}
