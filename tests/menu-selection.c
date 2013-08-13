#include <stdlib.h>

#include "game.h"

int
main ()
{
  game_t *game = game_create ();
  game->state = MENU_STATE;
  game->n_menu_items = 3;
  game->menu_cursor = 0;
  game->key_states[SDLK_DOWN] = true;
  game_loop (game);
  if (game->menu_cursor != 1)
    {
      exit (1);
    }
  game->key_states[SDLK_DOWN] = false;
  game_loop (game);
  game->key_states[SDLK_DOWN] = true;
  game_loop (game);
  if (game->menu_cursor != 2)
    {
      exit (1);
    }
  game->key_states[SDLK_DOWN] = false;
  game_loop (game);
  game->key_states[SDLK_DOWN] = true;
  game_loop (game);
  if (game->menu_cursor != 0)
    {
      exit (1);
    }
  game->key_states[SDLK_UP] = false;
  game_loop (game);
  game->key_states[SDLK_UP] = true;
  game_loop (game);
  if (game->menu_cursor != 2)
    {
      exit (1);
    }
  game->key_states[SDLK_UP] = false;
  game_loop (game);
  game->key_states[SDLK_UP] = true;
  game_loop (game);
  if (game->menu_cursor != 1)
    {
      exit (1);
    }
  game->key_states[SDLK_UP] = false;
  game_loop (game);
  game->key_states[SDLK_UP] = true;
  game_loop (game);
  if (game->menu_cursor != 0)
    {
      exit (1);
    }
  game_destroy (game);
  return 0;
}
