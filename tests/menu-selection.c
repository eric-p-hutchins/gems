#include <stdlib.h>

#include "game.h"

#include "test.h"

int
main (int argc, char *argv[])
{
  game_t *game = game_create ();
  game->state = MENU_STATE;
  game->n_menu_items = 3;
  game->menu_cursor = 0;

  press_key_and_loop (game, SDLK_DOWN);
  fail_if (game->menu_cursor != 1);
  release_key_and_loop (game, SDLK_DOWN);

  press_key_and_loop (game, SDLK_DOWN);
  fail_if (game->menu_cursor != 2);
  release_key_and_loop (game, SDLK_DOWN);

  press_key_and_loop (game, SDLK_DOWN);
  fail_if (game->menu_cursor != 0);
  release_key_and_loop (game, SDLK_DOWN);

  press_key_and_loop (game, SDLK_UP);
  fail_if (game->menu_cursor != 2);
  release_key_and_loop (game, SDLK_UP);

  press_key_and_loop (game, SDLK_UP);
  fail_if (game->menu_cursor != 1);
  release_key_and_loop (game, SDLK_UP);

  press_key_and_loop (game, SDLK_UP);
  fail_if (game->menu_cursor != 0);

  game_destroy (game);
  return 0;
}
