#include "menu.h"
#include "game.h"

void
menu_handle_keys (game_t *game)
{
  if (game_key_pressed (game, SDLK_ESCAPE))
    {
      game->state = QUIT_STATE;
    }
  else if (game_key_pressed (game, SDLK_DOWN))
    {
      ++game->menu_cursor;
      if (game->menu_cursor >= game->n_menu_items)
        {
          game->menu_cursor = 0;
        }
    }
  else if (game_key_pressed (game, SDLK_UP))
    {
      --game->menu_cursor;
      if (game->menu_cursor < 0)
        {
          game->menu_cursor = game->n_menu_items - 1;
        }
    }
  else if (game_key_pressed (game, SDLK_RETURN))
    {
      game->menu_held_down = true;
    }
  else if (game_key_released (game, SDLK_RETURN))
    {
      game->menu_held_down = false;
      game->menu_functions[game->menu_cursor](game);
    }
}

void
menu_draw (game_t *game)
{
  Uint32 black = SDL_MapRGB (game->screen->format, 0, 0, 0);
  Uint32 yellow = SDL_MapRGB (game->screen->format, 240, 240, 0);
  Uint32 gray = SDL_MapRGB (game->screen->format, 64, 64, 80);
  SDL_FillRect (game->screen, NULL, gray);

  int start = 240 - game->n_menu_items * 48;

  int i;
  for (i = 0; i < game->n_menu_items; ++i)
    {
      SDL_Rect s = { 7, 0, 129, 28 };
      if (game->menu_cursor == i)
        {
          s.y = game->menu_held_down?28:56;
        }
      SDL_Rect r = { 96, start + i * 48, 0, 0 };
      SDL_BlitSurface (game->button_sprite, &s, game->screen, &r);
    }
  SDL_Flip (game->screen);
}

void
menu_loop (game_t *game)
{
  menu_handle_keys (game);
  menu_draw (game);
}
