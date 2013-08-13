#include <stdlib.h>

#include "game.h"

#include "test.h"

int
main ()
{
  game_t *game = game_create ();
  fail_if (game->state != SPLASH_STATE);
  bool gets_to_menu = false;
  int i;
  for (i = 0; i < 50 * 30; ++i)
    {
      game_loop (game);
      if (game->state == MENU_STATE)
        {
          gets_to_menu = true;
          break;
        }
    }
  fail_if (!gets_to_menu);
  game->key_states[SDLK_ESCAPE] = true;
  game_loop (game);
  fail_if (game->state != QUIT_STATE);
  game_destroy (game);
  return 0;
}
