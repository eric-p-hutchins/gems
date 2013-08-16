#include <stdlib.h>

#include "game.h"

#include "test.h"

int
main (int argc, char *argv[])
{
  game_t *game = game_create ();
  int frame = game->frame;
  game_loop (game);
  fail_if (game->frame != frame + 1);
  game_destroy (game);
  return 0;
}
