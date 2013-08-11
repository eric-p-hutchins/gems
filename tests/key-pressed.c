#include <stdlib.h>

#include "game.h"

int
main ()
{
  game_t *game = game_create ();
  game->prev_key_states[SDLK_a] = false;
  game->prev_key_states[SDLK_b] = false;
  game->prev_key_states[SDLK_c] = true;
  game->prev_key_states[SDLK_d] = true;
  game->key_states[SDLK_a] = false;
  game->key_states[SDLK_b] = true;
  game->key_states[SDLK_c] = false;
  game->key_states[SDLK_d] = true;
  if (game_key_pressed (game, SDLK_a))
    {
      exit (1);
    }
  if (!game_key_pressed (game, SDLK_b))
    {
      exit (1);
    }
  if (game_key_pressed (game, SDLK_c))
    {
      exit (1);
    }
  if (game_key_pressed (game, SDLK_d))
    {
      exit (1);
    }
  game_destroy (game);
  return 0;
}
