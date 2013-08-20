#include "game.h"

int
main (int argc, char *argv[])
{
  game_t *game = game_create ();

  while (game->state != QUIT_STATE)
    {
      game_loop (game);
    }

  game_destroy (game);

  return 0;
}
