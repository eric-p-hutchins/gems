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
  game->n_gem_types = 6;
  game->column_settled = (bool*)malloc (sizeof (bool) * game->n_cols);
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
          gem->dy = 0;
          gem->type = rand () % game->n_gem_types;
          gem->level = 0;
          game_add_gem (game, gem);
          while (game->board[j][i] == match_list[0]
                 || game->board[j][i] == match_list[1])
            {
              ++(game->board[j][i]);
              if (game->board[j][i] >= game->n_gem_types)
                {
                  game->board[j][i] = 0;
                }
              gem->type = game->board[j][i];
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

int
gem_type (game_t *game, int x, int y)
{
  return game->board[x][y] % game->n_gem_types;
}

void
replace_with_hole (game_t *game, int x, int y)
{
  int hole_type = -1 - gem_level (game, x, y);
  game_remove_gem (game, x, y);
  game->board[x][y] = hole_type;
}

void
for_each_board_position_holes (game_t *game, void (*func)(game_t*, int, int),
                               bool holes)
{
  int i, j;
  for (i = 0; i < game->n_rows; ++i)
    {
      for (j = 0; j < game->n_cols; ++j)
        {
          if (!holes && game->board[j][i] < 0)
            {
              continue;
            }
          func (game, j, i);
        }
    }
}

void
for_each_board_position (game_t *game, void (*func)(game_t*, int, int))
{
  for_each_board_position_holes (game, func, true);
}

void
for_each_non_hole_board_position (game_t *game, void (*func)(game_t*, int, int))
{
  for_each_board_position_holes (game, func, false);
}

bool
column_settled (game_t *game, int x)
{
  int i;
  for (i = 0; i < game->n_rows; ++i)
    {
      if (game->board[x][i] < 0)
        {
          return false;
        }
    }
  return true;
}

void
handle_t_shape_x_y (game_t *game, int x, int y)
{
  if (x >= 1 && x < game->n_cols - 1
      && y < game->n_rows - 2
      && game->column_settled[x-1]
      && game->column_settled[x]
      && game->column_settled[x+1]
      && game->board[x][y] == game->board[x-1][y]
      && game->board[x][y] == game->board[x+1][y]
      && game->board[x][y] == game->board[x][y+1]
      && game->board[x][y] == game->board[x][y+2])
    {
      int type = game->board[x][y] % game->n_gem_types;
      game_remove_gem (game, x, y);
      game_add_gem (game, gem_create (x * 24, y * 24, type, 2));
      replace_with_hole (game, x-1, y);
      replace_with_hole (game, x+1, y);
      replace_with_hole (game, x, y+1);
      replace_with_hole (game, x, y+2);
    }
  else if (y >= 1 && y < game->n_rows - 1
           && x < game->n_cols - 2
           && game->column_settled[x]
           && game->column_settled[x+1]
           && game->column_settled[x+2]
           && game->board[x][y] == game->board[x][y-1]
           && game->board[x][y] == game->board[x][y+1]
           && game->board[x][y] == game->board[x+1][y]
           && game->board[x][y] == game->board[x+2][y])
    {
      int type = game->board[x][y] % game->n_gem_types;
      game_remove_gem (game, x, y);
      game_add_gem (game, gem_create (x * 24, y * 24, type, 2));
      replace_with_hole (game, x, y-1);
      replace_with_hole (game, x, y+1);
      replace_with_hole (game, x+1, y);
      replace_with_hole (game, x+2, y);
    }
  else if (x >= 1 && x < game->n_cols - 1
           && y > 1
           && game->column_settled[x-1]
           && game->column_settled[x]
           && game->column_settled[x+1]
           && game->board[x][y] == game->board[x-1][y]
           && game->board[x][y] == game->board[x+1][y]
           && game->board[x][y] == game->board[x][y-1]
           && game->board[x][y] == game->board[x][y-2])
    {
      int type = game->board[x][y] % game->n_gem_types;
      game_remove_gem (game, x, y);
      game_add_gem (game, gem_create (x * 24, y * 24, type, 2));
      replace_with_hole (game, x-1, y);
      replace_with_hole (game, x+1, y);
      replace_with_hole (game, x, y-1);
      replace_with_hole (game, x, y-2);
    }
  else if (y >= 1 && y < game->n_rows - 1
           && x > 1
           && game->column_settled[x]
           && game->column_settled[x-1]
           && game->column_settled[x-2]
           && game->board[x][y] == game->board[x][y-1]
           && game->board[x][y] == game->board[x][y+1]
           && game->board[x][y] == game->board[x-1][y]
           && game->board[x][y] == game->board[x-2][y])
    {
      int type = game->board[x][y] % game->n_gem_types;
      game_remove_gem (game, x, y);
      game_add_gem (game, gem_create (x * 24, y * 24, type, 2));
      replace_with_hole (game, x, y-1);
      replace_with_hole (game, x, y+1);
      replace_with_hole (game, x-1, y);
      replace_with_hole (game, x-2, y);
    }
}

void
handle_l_shape_x_y (game_t *game, int x, int y)
{
  if (x < game->n_cols - 2 && y < game->n_rows - 2
      && game->column_settled[x]
      && game->column_settled[x+1]
      && game->column_settled[x+2]
      && game->board[x][y] == game->board[x+1][y]
      && game->board[x][y] == game->board[x+2][y]
      && game->board[x][y] == game->board[x][y+1]
      && game->board[x][y] == game->board[x][y+2])
    {
      int type = game->board[x][y] % game->n_gem_types;
      game_remove_gem (game, x, y);
      game_add_gem (game, gem_create (x * 24, y * 24, type, 2));
      replace_with_hole (game, x+1, y);
      replace_with_hole (game, x+2, y);
      replace_with_hole (game, x, y+1);
      replace_with_hole (game, x, y+2);
    }
  else if (y >= 2 && x < game->n_cols - 2
           && game->column_settled[x]
           && game->column_settled[x+1]
           && game->column_settled[x+2]
           && game->board[x][y] == game->board[x][y-1]
           && game->board[x][y] == game->board[x][y-2]
           && game->board[x][y] == game->board[x+1][y]
           && game->board[x][y] == game->board[x+2][y])
    {
      int type = game->board[x][y] % game->n_gem_types;
      game_remove_gem (game, x, y);
      game_add_gem (game, gem_create (x * 24, y * 24, type, 2));
      replace_with_hole (game, x, y-1);
      replace_with_hole (game, x, y-2);
      replace_with_hole (game, x+1, y);
      replace_with_hole (game, x+2, y);
    }
  else if (x >= 2 && y >= 2
           && game->column_settled[x]
           && game->column_settled[x-1]
           && game->column_settled[x-2]
           && game->board[x][y] == game->board[x-1][y]
           && game->board[x][y] == game->board[x-2][y]
           && game->board[x][y] == game->board[x][y-1]
           && game->board[x][y] == game->board[x][y-2])
    {
      int type = game->board[x][y] % game->n_gem_types;
      game_remove_gem (game, x, y);
      game_add_gem (game, gem_create (x * 24, y * 24, type, 2));
      replace_with_hole (game, x-1, y);
      replace_with_hole (game, x-2, y);
      replace_with_hole (game, x, y-1);
      replace_with_hole (game, x, y-2);
    }
  else if (x >= 2 && y < game->n_rows - 2
           && game->column_settled[x]
           && game->column_settled[x-1]
           && game->column_settled[x-2]
           && game->board[x][y] == game->board[x][y+1]
           && game->board[x][y] == game->board[x][y+2]
           && game->board[x][y] == game->board[x-1][y]
           && game->board[x][y] == game->board[x-2][y])
    {
      int type = game->board[x][y] % game->n_gem_types;
      game_remove_gem (game, x, y);
      game_add_gem (game, gem_create (x * 24, y * 24, type, 2));
      replace_with_hole (game, x, y+1);
      replace_with_hole (game, x, y+2);
      replace_with_hole (game, x-1, y);
      replace_with_hole (game, x-2, y);
    }
}

void
handle_three_in_row_or_column_x_y (game_t *game, int x, int y)
{
  if (y >= 2
      && game->column_settled[x]
      && gem_type (game, x, y) == gem_type (game, x, y - 1)
      && gem_type (game, x, y) == gem_type (game, x, y - 2))
    {
      replace_with_hole (game, x, y);
      replace_with_hole (game, x, y-1);
      replace_with_hole (game, x, y-2);
    }
  else if (x < game->n_cols - 2
           && game->column_settled[x]
           && game->column_settled[x+1]
           && game->column_settled[x+2]
           && gem_type (game, x, y) == gem_type (game, x + 1, y)
           && gem_type (game, x, y) == gem_type (game, x + 2, y))
    {
      replace_with_hole (game, x, y);
      replace_with_hole (game, x+1, y);
      replace_with_hole (game, x+2, y);
    }
}

void
handle_four_in_row_or_column_x_y (game_t *game, int x, int y)
{
  if (y >= 3
      && game->column_settled[x]
      && game->board[x][y] == game->board[x][y-1]
      && game->board[x][y] == game->board[x][y-2]
      && game->board[x][y] == game->board[x][y-3])
    {
      int type = game->board[x][y] % game->n_gem_types;
      replace_with_hole (game, x, y);
      game_remove_gem (game, x, y-1);
      game_add_gem (game, gem_create (x * 24, (y-1) * 24, type, 1));
      replace_with_hole (game, x, y-2);
      replace_with_hole (game, x, y-3);
    }
  else if (x < game->n_cols - 3
           && game->column_settled[x]
           && game->column_settled[x+1]
           && game->column_settled[x+2]
           && game->column_settled[x+3]
           && game->board[x][y] == game->board[x+1][y]
           && game->board[x][y] == game->board[x+2][y]
           && game->board[x][y] == game->board[x+3][y])
    {
      int type = game->board[x][y] % game->n_gem_types;
      game_remove_gem (game, x+1, y);
      game_add_gem (game, gem_create ((x+1) * 24, y * 24, type, 1));
      replace_with_hole (game, x, y);
      replace_with_hole (game, x+2, y);
      replace_with_hole (game, x+3, y);
    }
}

void
handle_five_in_row_or_column_x_y (game_t *game, int x, int y)
{
  if (y >= 4
      && game->column_settled[x]
      && game->board[x][y] == game->board[x][y-1]
      && game->board[x][y] == game->board[x][y-2]
      && game->board[x][y] == game->board[x][y-3]
      && game->board[x][y] == game->board[x][y-4])
    {
      int type = game->board[x][y] % game->n_gem_types;
      game_remove_gem (game, x, y-2);
      game_add_gem (game, gem_create (x * 24, (y-2) * 24, type, 3));
      replace_with_hole (game, x, y);
      replace_with_hole (game, x, y-1);
      replace_with_hole (game, x, y-3);
      replace_with_hole (game, x, y-4);
    }
  else if (x < game->n_cols - 4
           && game->column_settled[x]
           && game->column_settled[x+1]
           && game->column_settled[x+2]
           && game->column_settled[x+3]
           && game->column_settled[x+4]
           && game->board[x][y] == game->board[x+1][y]
           && game->board[x][y] == game->board[x+2][y]
           && game->board[x][y] == game->board[x+3][y]
           && game->board[x][y] == game->board[x+4][y])
    {
      int type = game->board[x][y] % game->n_gem_types;
      game_remove_gem (game, x+2, y);
      game_add_gem (game, gem_create ((x+2) * 24, y * 24, type, 3));
      replace_with_hole (game, x, y);
      replace_with_hole (game, x+1, y);
      replace_with_hole (game, x+3, y);
      replace_with_hole (game, x+4, y);
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
                  int x, y;
                  int m;
                  gem_t *gem = NULL;
                  for (m = 0; m < game->n_gems; ++m)
                    {
                      gem_t *gem_m = game->gems[m];
                      if (gem_m->x / 24 == i && gem_m->y / 24 == k - 1)
                        {
                          gem = gem_m;
                        }
                    }
                  if (gem != NULL)
                    {
                      ++gem->dy;
                      game_move_gem (game, i, k - 1, gem->x, gem->y + gem->dy);
                      if (gem->y >= k * 24)
                        {
                          game_move_gem (game, i, k, i * 24, k * 24);
                          bool gem_under_it = k+1 < game->n_rows
                            && game->board[i][k+1] >= 0;
                          bool at_bottom = k == game->n_rows - 1;
                          if (gem_under_it || at_bottom)
                            {
                              gem->dy = 0;
                            }
                        }
                    }
                }
              if (game->board[i][0] < 0)
                {
                  int type = rand () % game->n_gem_types;
                  game_add_gem (game, gem_create (i * 24, 0, type, 0));
                }
              break;
            }
        }
    }
}

void
session_draw_gem (game_t *game, gem_t *gem)
{
  Uint32 black = SDL_MapRGB (game->screen->format, 0, 0, 0);
  Uint32 white = SDL_MapRGB (game->screen->format, 255, 255, 255);
  int board_w = 24 * game->n_cols;
  int board_h = 24 * game->n_rows;
  int board_x = (320 - board_w) / 2;
  int board_y = (240 - board_h) / 2;
  SDL_Rect s;
  s.x = board_x + gem->x;
  s.y = board_y + gem->y;
  s.w = 24;
  s.h = 24;
  int type = gem->type;
  int level = gem->level;
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

  SDL_Rect src = { gem->type * 24, gem->level * 24, 24, 24 };
  SDL_Rect d = { s.x, s.y, 0, 0 };
  SDL_BlitSurface (game->sprite, &src, game->screen, &d);
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
  Uint32 dark_gray = SDL_MapRGB (game->screen->format, 64, 64, 80);
  Uint32 black = SDL_MapRGB (game->screen->format, 0, 0, 0);
  Uint32 white = SDL_MapRGB (game->screen->format, 255, 255, 255);
  SDL_FillRect (game->screen, NULL, dark_gray);

  SDL_Rect framer = { 0, 0, 48, 12 };
  SDL_Rect framed = { board_x - 12, board_y - 12, 0, 0 };
  SDL_BlitSurface (game->frame_sprite, &framer, game->screen, &framed);
  framer.x = 33;
  framer.y = 0;
  framer.w = 12;
  framer.h = 12;
  framed.x = board_x + 36;
  framed.y = board_y - 12;
  SDL_BlitSurface (game->frame_sprite, &framer, game->screen, &framed);
  framer.x = 6;
  framer.y = 54;
  framer.w = 12;
  framer.h = 12;
  framed.x = board_x + board_w - 48;
  framed.y = board_y + board_h;
  SDL_BlitSurface (game->frame_sprite, &framer, game->screen, &framed);
  framer.x = 18;
  framer.y = 54;
  framer.w = 48;
  framer.h = 12;
  framed.x = board_x + board_w - 36;
  framed.y = board_y + board_h;
  SDL_BlitSurface (game->frame_sprite, &framer, game->screen, &framed);

  framer.x = 0;
  framer.y = 54;
  framer.w = 12;
  framer.h = 12;
  framed.x = board_x - 12;
  framed.y = board_y + board_h;
  SDL_BlitSurface (game->frame_sprite, &framer, game->screen, &framed);

  framer.x = 54;
  framer.y = 0;
  framer.w = 12;
  framer.h = 12;
  framed.x = board_x + board_w;
  framed.y = board_y - 12;
  SDL_BlitSurface (game->frame_sprite, &framer, game->screen, &framed);

  int i, j;
  for (i = 0; i < game->n_cols; ++i)
    {
      if (i > 1)
        {
          framer.x = 33;
          framer.y = 0;
          framer.w = 24;
          framer.h = 12;
          framed.x = board_x + 24 * i;
          framed.y = board_y - 12;
          SDL_BlitSurface (game->frame_sprite, &framer, game->screen, &framed);
        }
      if (i < game->n_cols - 2)
        {
          framer.x = 6;
          framer.y = 54;
          framer.w = 24;
          framer.h = 12;
          framed.x = board_x + 24 * i;
          framed.y = board_y + board_h;
          SDL_BlitSurface (game->frame_sprite, &framer, game->screen, &framed);
        }
      for (j = 0; j < game->n_rows; ++j)
        {
          framer.x = 12;
          framer.y = 12;
          framer.w = 24;
          framer.h = 24;
          framed.x = board_x + 24 * i;
          framed.y = board_y + 24 * j;
          SDL_BlitSurface (game->frame_sprite, &framer, game->screen, &framed);
        }
    }
  for (j = 0; j < game->n_rows; ++j)
    {
      framer.x = 0;
      framer.y = 12;
      framer.w = 12;
      framer.h = 24;
      framed.x = board_x - 12;
      framed.y = board_y + 24 * j;
      SDL_BlitSurface (game->frame_sprite, &framer, game->screen, &framed);
      framer.x = 54;
      framer.y = 12;
      framer.w = 12;
      framer.h = 24;
      framed.x = board_x + board_w;
      framed.y = board_y + 24 * j;
      SDL_BlitSurface (game->frame_sprite, &framer, game->screen, &framed);
    }
  int k;
  for (k = 0; k < game->n_gems; ++k)
    {
      session_draw_gem (game, game->gems[k]);
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
handle_special1_gem (game_t *game, int x, int y)
{
  int i;
  for (i = 0; i < game->n_cols; ++i)
    {
      replace_with_hole (game, i, y);
    }
  for (i = 0; i < game->n_rows; ++i)
    {
      replace_with_hole (game, x, i);
    }
}

void
handle_special2_gem (game_t *game, int x, int y)
{
  int i, j;
  for (i = x - 1; i <= x + 1; ++i)
    {
      if (i < 0 || i >= game->n_cols)
        {
          continue;
        }
      for (j = y - 1; j <= y + 1; ++j)
        {
          if (j < 0 || j >= game->n_rows)
            {
              continue;
            }
          replace_with_hole (game, i, j);
        }
    }
}

void
handle_special_gems_x_y (game_t *game, int x, int y)
{
  switch (game->board[x][y])
    {
    case -2:
      handle_special1_gem (game, x, y);
      break;
    case -3:
      handle_special2_gem (game, x, y);
      break;
    }
}

void
update_columns_settled (game_t *game)
{
  int i;
  for (i = 0; i < game->n_cols; ++i)
    {
      game->column_settled[i] = column_settled (game, i);
    }
}

void
session_loop (game_t *game)
{
  update_columns_settled (game);
  session_handle_keys (game);
  for_each_non_hole_board_position (game, handle_five_in_row_or_column_x_y);
  for_each_non_hole_board_position (game, handle_t_shape_x_y);
  for_each_non_hole_board_position (game, handle_l_shape_x_y);
  for_each_non_hole_board_position (game, handle_four_in_row_or_column_x_y);
  for_each_non_hole_board_position (game, handle_three_in_row_or_column_x_y);
  for_each_board_position (game, handle_special_gems_x_y);
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
