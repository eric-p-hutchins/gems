#include <stdlib.h>

#include "game.h"

#include "test.h"

int a = 0;

void
increment_value (game_t *game)
{
  ++a;
}

void
start (game_t *game)
{
  game_start (game);
}

void
quit (game_t *game)
{
  game->state = QUIT_STATE;
}

int
main (int argc, char *argv[])
{
  game_t *game = game_create ();
  game->state = MENU_STATE;
  game->n_menu_items = 3;
  game->menu_functions = (void(**)(game_t*))malloc (sizeof (void(*)(game_t*)) * 3);
  game->menu_functions[0] = start;
  game->menu_functions[1] = increment_value;
  game->menu_functions[2] = quit;
  game->menu_cursor = 0;

  press_key_and_loop (game, SDLK_DOWN);
  fail_if (game->menu_cursor != 1);
  release_key_and_loop (game, SDLK_DOWN);

  press_key_and_loop (game, SDLK_RETURN);
  release_key_and_loop (game, SDLK_RETURN);
  fail_if (a != 1);

  press_key_and_loop (game, SDLK_UP);
  release_key_and_loop (game, SDLK_UP);
  fail_if (game->menu_cursor != 0);

  press_key_and_loop (game, SDLK_RETURN);
  release_key_and_loop (game, SDLK_RETURN);
  fail_if (game->state != SESSION_STATE);

  game->state = MENU_STATE;

  press_key_and_loop (game, SDLK_DOWN);
  release_key_and_loop (game, SDLK_DOWN);
  fail_if (game->menu_cursor != 1);

  press_key_and_loop (game, SDLK_DOWN);
  release_key_and_loop (game, SDLK_DOWN);
  fail_if (game->menu_cursor != 2);

  press_key_and_loop (game, SDLK_RETURN);
  release_key_and_loop (game, SDLK_RETURN);
  fail_if (game->state != QUIT_STATE);

  game_destroy (game);
  return 0;
}
