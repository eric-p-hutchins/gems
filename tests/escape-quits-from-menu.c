#include <stdlib.h>

#include "game.h"

int
main ()
{
  game_t *game = game_create ();
  if (game->state != SPLASH_STATE)
    {
      exit (1);
    }
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
  if (!gets_to_menu)
    {
      exit (1);
    }
  game->key_states[SDLK_ESCAPE] = true;
  game_loop (game);
  if (game->state != QUIT_STATE)
    {
      exit (1);
    }
  game_destroy (game);
  return 0;
}
