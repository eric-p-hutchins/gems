#include <stdlib.h>

#include "game.h"

#include "test.h"

int
main ()
{
  game_t *game = game_create ();
  fail_if (game->state != SPLASH_STATE);
  int i;
  for (i = 0; i < 50 * 30; ++i)
    {
      game_loop (game);
      if (game->state != SPLASH_STATE)
        {
          break;
        }
    }
  fail_if (game->state != MENU_STATE);
  fail_if (game->n_menu_items != 2);
  fail_if (game->menu_cursor != 0);

  press_key_and_loop (game, SDLK_RETURN);
  fail_if (game->state != SESSION_STATE);
  release_key_and_loop (game, SDLK_RETURN);

  game->state = MENU_STATE;
  game->n_menu_items = 2;
  game->menu_cursor = 0;

  press_key_and_loop (game, SDLK_DOWN);
  release_key_and_loop (game, SDLK_DOWN);

  press_key_and_loop (game, SDLK_RETURN);
  fail_if (game->state != QUIT_STATE);
  release_key_and_loop (game, SDLK_RETURN);

  game_destroy (game);
  return 0;
}
