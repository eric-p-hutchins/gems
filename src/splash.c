#include "splash.h"
#include "game.h"

void
splash_loop (game_t *game)
{
  if (game->frame >= 250)
    {
      game->state = MENU_STATE;
    }
}
