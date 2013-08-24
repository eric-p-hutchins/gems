#include <stdlib.h>

#include "game.h"

#include "session.h"

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
          gem_t *gem = (gem_t*)malloc (sizeof (gem_t));
          gem->x = j * 24;
          gem->y = i * 24;
          gem->type = rand () % game->n_gem_types;
          gem->level = 0;
          game_add_gem (game, gem);
          while (game->board[j][i] == match_list[0]
                 || game->board[j][i] == match_list[1])
            {
              ++(game->board[j][i]);
              ++gem->type;
            }
        }
    }
}

void
session_handle_keys (game_t *game)
{
  int x = game->board_cursor_x;
  int y = game->board_cursor_y;
  if (game_key_pressed (game, SDLK_LEFT))
    {
      if (!game->cursor_locked)
        {
          if (game->board_cursor_x > 0)
            {
              --game->board_cursor_x;
            }
        }
      else
        {
          if (game->board_cursor_x > 0)
            {
              if (session_legal_move (game, x, y, x - 1, y))
                {
                  game_swap_gems (game, x, y, x-1, y);
                  --game->board_cursor_x;
                  game->cursor_locked = false;
                }
            }
        }
    }
  else if (game_key_pressed (game, SDLK_RIGHT))
    {
      if (!game->cursor_locked)
        {
          if (game->board_cursor_x < game->n_cols - 1)
            {
              ++game->board_cursor_x;
            }
        }
      else
        {
          if (game->board_cursor_x < game->n_cols - 1)
            {
              if (session_legal_move (game, x, y, x + 1, y))
                {
                  game_swap_gems (game, x, y, x+1, y);
                  ++game->board_cursor_x;
                  game->cursor_locked = false;
                }
            }
        }
    }
  else if (game_key_pressed (game, SDLK_UP))
    {
      if (!game->cursor_locked)
        {
          if (game->board_cursor_y > 0)
            {
              --game->board_cursor_y;
            }
        }
      else
        {
          if (game->board_cursor_y > 0)
            {
              if (session_legal_move (game, x, y, x, y - 1))
                {
                  game_swap_gems (game, x, y, x, y-1);
                  --game->board_cursor_y;
                  game->cursor_locked = false;
                }
            }
        }
    }
  else if (game_key_pressed (game, SDLK_DOWN))
    {
      if (!game->cursor_locked)
        {
          if (game->board_cursor_y < game->n_rows - 1)
            {
              ++game->board_cursor_y;
            }
        }
      else
        {
          if (game->board_cursor_y < game->n_rows - 1)
            {
              if (session_legal_move (game, x, y, x, y + 1))
                {
                  game_swap_gems (game, x, y, x, y+1);
                  ++game->board_cursor_y;
                  game->cursor_locked = false;
                }
            }
        }
    }
  else if (game_key_pressed (game, SDLK_SPACE))
    {
      if (game->cursor_locked)
        {
          game->cursor_locked = false;
        }
      else
        {
          game->cursor_locked = true;
        }
    }
}

int
gem_level (game_t *game, int x, int y)
{
  return game->board[x][y] / game->n_gem_types;
}

void
replace_with_hole (game_t *game, int x, int y)
{
  int hole_type = -1 - gem_level (game, x, y);
  game_remove_gem (game, x, y);
  game->board[x][y] = hole_type;
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
              int type = game->board[j][i] % game->n_gem_types;
              game_remove_gem (game, j, i);
              game_add_gem (game, gem_create (j * 24, i * 24, type, 2));
              replace_with_hole (game, j-1, i);
              replace_with_hole (game, j+1, i);
              replace_with_hole (game, j, i+1);
              replace_with_hole (game, j, i+2);
            }
          else if (i >= 1 && i < game->n_rows - 1
                   && j < game->n_cols - 2
                   && game->board[j][i] == game->board[j][i-1]
                   && game->board[j][i] == game->board[j][i+1]
                   && game->board[j][i] == game->board[j+1][i]
                   && game->board[j][i] == game->board[j+2][i])
            {
              int type = game->board[j][i] % game->n_gem_types;
              game_remove_gem (game, j, i);
              game_add_gem (game, gem_create (j * 24, i * 24, type, 2));
              replace_with_hole (game, j, i-1);
              replace_with_hole (game, j, i+1);
              replace_with_hole (game, j+1, i);
              replace_with_hole (game, j+2, i);
            }
          else if (j >= 1 && j < game->n_cols - 1
                   && i > 1
                   && game->board[j][i] == game->board[j-1][i]
                   && game->board[j][i] == game->board[j+1][i]
                   && game->board[j][i] == game->board[j][i-1]
                   && game->board[j][i] == game->board[j][i-2])
            {
              int type = game->board[j][i] % game->n_gem_types;
              game_remove_gem (game, j, i);
              game_add_gem (game, gem_create (j * 24, i * 24, type, 2));
              replace_with_hole (game, j-1, i);
              replace_with_hole (game, j+1, i);
              replace_with_hole (game, j, i-1);
              replace_with_hole (game, j, i-2);
            }
          else if (i >= 1 && i < game->n_rows - 1
                   && j > 1
                   && game->board[j][i] == game->board[j][i-1]
                   && game->board[j][i] == game->board[j][i+1]
                   && game->board[j][i] == game->board[j-1][i]
                   && game->board[j][i] == game->board[j-2][i])
            {
              int type = game->board[j][i] % game->n_gem_types;
              game_remove_gem (game, j, i);
              game_add_gem (game, gem_create (j * 24, i * 24, type, 2));
              replace_with_hole (game, j, i-1);
              replace_with_hole (game, j, i+1);
              replace_with_hole (game, j-1, i);
              replace_with_hole (game, j-2, i);
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
              int type = game->board[j][i] % game->n_gem_types;
              game_remove_gem (game, j, i);
              game_add_gem (game, gem_create (j * 24, i * 24, type, 2));
              replace_with_hole (game, j+1, i);
              replace_with_hole (game, j+2, i);
              replace_with_hole (game, j, i+1);
              replace_with_hole (game, j, i+2);
            }
          else if (i >= 2 && j < game->n_cols - 2
                   && game->board[j][i] == game->board[j][i-1]
                   && game->board[j][i] == game->board[j][i-2]
                   && game->board[j][i] == game->board[j+1][i]
                   && game->board[j][i] == game->board[j+2][i])
            {
              int type = game->board[j][i] % game->n_gem_types;
              game_remove_gem (game, j, i);
              game_add_gem (game, gem_create (j * 24, i * 24, type, 2));
              replace_with_hole (game, j, i-1);
              replace_with_hole (game, j, i-2);
              replace_with_hole (game, j+1, i);
              replace_with_hole (game, j+2, i);
            }
          else if (j >= 2 && i >= 2
                   && game->board[j][i] == game->board[j-1][i]
                   && game->board[j][i] == game->board[j-2][i]
                   && game->board[j][i] == game->board[j][i-1]
                   && game->board[j][i] == game->board[j][i-2])
            {
              int type = game->board[j][i] % game->n_gem_types;
              game_remove_gem (game, j, i);
              game_add_gem (game, gem_create (j * 24, i * 24, type, 2));
              replace_with_hole (game, j-1, i);
              replace_with_hole (game, j-2, i);
              replace_with_hole (game, j, i-1);
              replace_with_hole (game, j, i-2);
            }
          else if (j >= 2 && i < game->n_rows - 2
                   && game->board[j][i] == game->board[j][i+1]
                   && game->board[j][i] == game->board[j][i+2]
                   && game->board[j][i] == game->board[j-1][i]
                   && game->board[j][i] == game->board[j-2][i])
            {
              int type = game->board[j][i] % game->n_gem_types;
              game_remove_gem (game, j, i);
              game_add_gem (game, gem_create (j * 24, i * 24, type, 2));
              replace_with_hole (game, j, i+1);
              replace_with_hole (game, j, i+2);
              replace_with_hole (game, j-1, i);
              replace_with_hole (game, j-2, i);
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
              replace_with_hole (game, j, i);
              replace_with_hole (game, j, i-1);
              replace_with_hole (game, j, i-2);
            }
          else if (j < game->n_cols - 2
                   && game->board[j][i] == game->board[j+1][i]
                   && game->board[j][i] == game->board[j+2][i])
            {
              replace_with_hole (game, j, i);
              replace_with_hole (game, j+1, i);
              replace_with_hole (game, j+2, i);
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
              int type = game->board[j][i] % game->n_gem_types;
              replace_with_hole (game, j, i);
              game_remove_gem (game, j, i-1);
              game_add_gem (game, gem_create (j * 24, (i-1) * 24, type, 1));
              replace_with_hole (game, j, i-2);
              replace_with_hole (game, j, i-3);
            }
          else if (j < game->n_cols - 3
                   && game->board[j][i] == game->board[j+1][i]
                   && game->board[j][i] == game->board[j+2][i]
                   && game->board[j][i] == game->board[j+3][i])
            {
              int type = game->board[j][i] % game->n_gem_types;
              game_remove_gem (game, j+1, i);
              game_add_gem (game, gem_create ((j+1) * 24, i * 24, type, 1));
              replace_with_hole (game, j, i);
              replace_with_hole (game, j+2, i);
              replace_with_hole (game, j+3, i);
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
              int type = game->board[j][i] % game->n_gem_types;
              game_remove_gem (game, j, i-2);
              game_add_gem (game, gem_create (j * 24, (i-2) * 24, type, 3));
              replace_with_hole (game, j, i);
              replace_with_hole (game, j, i-1);
              replace_with_hole (game, j, i-3);
              replace_with_hole (game, j, i-4);
            }
          else if (j < game->n_cols - 4
                   && game->board[j][i] == game->board[j+1][i]
                   && game->board[j][i] == game->board[j+2][i]
                   && game->board[j][i] == game->board[j+3][i]
                   && game->board[j][i] == game->board[j+4][i])
            {
              int type = game->board[j][i] % game->n_gem_types;
              game_remove_gem (game, j+2, i);
              game_add_gem (game, gem_create ((j+2) * 24, i * 24, type, 3));
              replace_with_hole (game, j, i);
              replace_with_hole (game, j+1, i);
              replace_with_hole (game, j+3, i);
              replace_with_hole (game, j+4, i);
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
          if (game->board[i][j] < 0)
            {
              for (k = j; k > 0; --k)
                {
                  game_move_gem (game, i, k - 1, i * 24, k * 24);
                }
              gem_t *gem = (gem_t*)malloc (sizeof (gem_t));
              gem->x = i * 24;
              gem->y = 0;
              gem->type = rand () % game->n_gem_types;
              gem->level = 0;
              game_add_gem (game, gem);
              break;
            }
        }
    }
}

void
session_draw (game_t *game)
{
  int board_w = 24 * game->n_cols;
  int board_h = 24 * game->n_rows;
  int board_x = (320 - board_w) / 2;
  int board_y = (240 - board_h) / 2;

  SDL_Rect rect;
  rect.w = board_w + 2;
  rect.h = board_h + 2;
  rect.x = board_x - 1;
  rect.y = board_y - 1;
  Uint32 gray = SDL_MapRGB (game->screen->format, 192, 192, 192);
  Uint32 black = SDL_MapRGB (game->screen->format, 0, 0, 0);
  Uint32 white = SDL_MapRGB (game->screen->format, 255, 255, 255);
  SDL_FillRect (game->screen, NULL, white);
  SDL_FillRect (game->screen, &rect, black);
  int i, j;
  for (i = 0; i < game->n_rows; ++i)
    {
      for (j = 0; j < game->n_cols; ++j)
        {
          if (game->board[j][i] < 0)
            {
              continue;
            }
          SDL_Rect s;
          s.x = board_x + 24 * j;
          s.y = board_y + 24 * i;
          s.w = 24;
          s.h = 24;
          int type = game->board[j][i] % game->n_gem_types;
          int level = game->board[j][i] / game->n_gem_types;
          int v = 256 * type / game->n_gem_types;
          int r, g, b;
          switch (type)
            {
            case 0:
              r = 255; g = 0; b = 0;
              break;
            case 1:
              r = 0; g = 255; b = 0;
              break;
            case 2:
              r = 0; g = 0; b = 255;
              break;
            case 3:
              r = 255; g = 255; b = 0;
              break;
            }
          Uint32 color = SDL_MapRGB (game->screen->format, r, g, b);
          SDL_FillRect (game->screen, &s, color);
          int k;
          for (k = 0; k < level + 1; ++k)
            {
              SDL_Rect outline_rect;
              outline_rect.x = s.x + k * 2;
              outline_rect.y = s.y + k * 2;
              outline_rect.w = s.w - k * 4;
              outline_rect.h = 1;
              SDL_FillRect (game->screen, &outline_rect, white);
              outline_rect.x = s.x + k * 2;
              outline_rect.y = s.y + s.h - 1 - k * 2;
              outline_rect.w = s.w - k * 4;
              outline_rect.h = 1;
              SDL_FillRect (game->screen, &outline_rect, black);
              outline_rect.x = s.x + k * 2;
              outline_rect.y = s.y + k * 2;
              outline_rect.w = 1;
              outline_rect.h = s.h - k * 4;
              SDL_FillRect (game->screen, &outline_rect, white);
              outline_rect.x = s.x + s.w - 1 - k * 2;
              outline_rect.y = s.y + k * 2;
              outline_rect.w = 1;
              outline_rect.h = s.h - k * 4;
              SDL_FillRect (game->screen, &outline_rect, black);
            }
        }
    }
  Uint32 yellow = SDL_MapRGB (game->screen->format, 240, 240, 64);
  Uint32 cursor_color = game->cursor_locked?yellow:white;
  SDL_Rect cursor;
  cursor.x = board_x + game->board_cursor_x * 24;
  cursor.y = board_y + game->board_cursor_y * 24;
  cursor.w = 24;
  cursor.h = 2;
  SDL_FillRect (game->screen, &cursor, cursor_color);
  cursor.x = board_x + game->board_cursor_x * 24;
  cursor.y = board_y + game->board_cursor_y * 24 + 22;
  cursor.w = 24;
  cursor.h = 2;
  SDL_FillRect (game->screen, &cursor, cursor_color);
  cursor.x = board_x + game->board_cursor_x * 24;
  cursor.y = board_y + game->board_cursor_y * 24;
  cursor.w = 2;
  cursor.h = 24;
  SDL_FillRect (game->screen, &cursor, cursor_color);
  cursor.x = board_x + game->board_cursor_x * 24 + 22;
  cursor.y = board_y + game->board_cursor_y * 24;
  cursor.w = 2;
  cursor.h = 24;
  SDL_FillRect (game->screen, &cursor, cursor_color);
  SDL_Flip (game->screen);
}

void
session_loop (game_t *game)
{
  session_handle_keys (game);
  handle_five_in_row_or_column (game);
  handle_t_shape (game);
  handle_l_shape (game);
  handle_four_in_row_or_column (game);
  handle_three_in_row_or_column (game);
  drop_columns_to_fill_holes (game);
  session_draw (game);
}

bool
session_matches_row_at_point (game_t *game, int type, int x, int y)
{
  if (x < game->n_cols - 2
      && game->board[x+1][y] % game->n_gem_types == type
      && game->board[x+2][y] % game->n_gem_types == type)
    {
      return true;
    }
  if (x > 0
      && x < game->n_cols - 1
      && game->board[x-1][y] % game->n_gem_types == type
      && game->board[x+1][y] % game->n_gem_types == type)
    {
      return true;
    }
  if (x > 1
      && game->board[x-1][y] % game->n_gem_types == type
      && game->board[x-2][y] % game->n_gem_types == type)
    {
      return true;
    }
  return false;
}

bool
session_matches_column_at_point (game_t *game, int type, int x, int y)
{
  if (y < game->n_rows - 2
      && game->board[x][y+1] % game->n_gem_types == type
      && game->board[x][y+2] % game->n_gem_types == type)
    {
      return true;
    }
  if (y > 0
      && y < game->n_rows - 1
      && game->board[x][y-1] % game->n_gem_types == type
      && game->board[x][y+1] % game->n_gem_types == type)
    {
      return true;
    }
  if (y > 1
      && game->board[x][y-1] % game->n_gem_types == type
      && game->board[x][y-2] % game->n_gem_types == type)
    {
      return true;
    }
  return false;
}

bool
session_matches_at_point (game_t *game, int type, int x, int y)
{
  return session_matches_row_at_point (game, type, x, y)
    || session_matches_column_at_point (game, type, x, y);
}

bool
session_legal_move (game_t *game, int x1, int y1, int x2, int y2)
{
  if (x1 < 0 || x1 > game->n_cols - 1 || y1 < 0 || y1 > game->n_rows - 1
      || x2 < 0 || x2 > game->n_cols - 1 || y2 < 0 || y2 > game->n_rows - 1)
    {
      return false;
    }
  if (x1 - x2 < -1 || x1 - x2 > 1)
    {
      return false;
    }
  if (y1 - y2 < -1 || y1 - y2 > 1)
    {
      return false;
    }
  if ((x1 != x2 && y1 != y2)
      || (x1 == x2 && y1 == y2))
    {
      return false;
    }

  if (game->board[x1][y1] / game->n_gem_types > 0
      && game->board[x2][y2] / game->n_gem_types > 0)
    {
      return true;
    }

  int p1 = game->board[x1][y1];
  int p2 = game->board[x2][y2];

  int type1 = game->board[x1][y1] % game->n_gem_types;
  int type2 = game->board[x2][y2] % game->n_gem_types;

  // Temporarily swap position 1 and 2 to test for a match

  game->board[x2][y2] = p1;
  game->board[x1][y1] = p2;

  bool match1 = session_matches_at_point (game, type1, x2, y2);
  bool match2 = session_matches_at_point (game, type2, x1, y1);

  // Swap them back now that we know if they would have matched

  game->board[x1][y1] = p1;
  game->board[x2][y2] = p2;

  return match1 || match2;
}
