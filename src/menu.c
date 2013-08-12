#include "menu.h"
#include "game.h"

void
menu_loop (game_t *game)
{
  if (game_key_pressed (game, SDLK_ESCAPE))
    {
      game->state = QUIT_STATE;
    }
}
