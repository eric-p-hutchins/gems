#include "game.h"

int
main ()
{
  game_t *game = game_create ();
  game_loop (game);
  game_destroy (game);
  return 0;
}
