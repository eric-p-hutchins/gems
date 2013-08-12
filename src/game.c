#include <stdlib.h>

#include "game.h"
#include "splash.h"
#include "menu.h"

int N_KEYS = 512;

game_t *
game_create ()
{
  SDL_InitSubSystem (SDL_INIT_VIDEO);
  SDL_Surface *screen = SDL_SetVideoMode (320, 240, 32, 0);
  game_t *game = (game_t*)malloc (sizeof (game_t));
  game->frame = 0;
  game->screen = screen;
  game->state = SPLASH_STATE;
  game->key_states = (bool*)malloc (sizeof (bool) * N_KEYS);
  game->prev_key_states = (bool*)malloc (sizeof (bool) * N_KEYS);
  return game;
}

void
game_destroy (game_t *game)
{
  free (game->key_states);
  free (game->prev_key_states);
  free (game);
  SDL_QuitSubSystem (SDL_INIT_VIDEO);
}

void
game_loop (game_t *game)
{
  switch (game->state)
    {
    case SPLASH_STATE:
      splash_loop (game);
      break;
    case MENU_STATE:
      menu_loop (game);
      break;
    }
  int i;
  for (i = 0; i < N_KEYS; ++i)
    {
      game->prev_key_states[i] = game->key_states[i];
    }
  ++game->frame;
}

bool
game_key_pressed (game_t *game, SDLKey key)
{
  return !game->prev_key_states[key] && game->key_states[key];
}

bool
game_key_released (game_t *game, SDLKey key)
{
  return game->prev_key_states[key] && !game->key_states[key];
}
