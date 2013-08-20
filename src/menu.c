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
      game->menu_functions[game->menu_cursor](game);
    }
}

void
menu_draw (game_t *game)
{
  Uint32 gray = SDL_MapRGB (game->screen->format, 192, 192, 192);
  SDL_FillRect (game->screen, NULL, gray);
  SDL_Flip (game->screen);
}

void
menu_loop (game_t *game)
{
  menu_handle_keys (game);
  menu_draw (game);
}
