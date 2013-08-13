#include "splash.h"
#include "game.h"

void
splash_loop (game_t *game)
{
  if (game->frame >= 250)
    {
      game->state = MENU_STATE;
      game->menu_cursor = 0;
      game->n_menu_items = 2;
      game->menu_functions = (void(**)(game_t*))malloc (sizeof (void(*)(game_t*)) * 2);
      game->menu_functions[0] = game_start;
      game->menu_functions[1] = game_quit;
    }
}
