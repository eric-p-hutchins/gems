#include <stdlib.h>

#include "game.h"
#include "splash.h"
#include "menu.h"
#include "session.h"

int N_KEYS = 512;

game_t *
game_create ()
{
  SDL_InitSubSystem (SDL_INIT_VIDEO);
  SDL_Surface *screen = SDL_SetVideoMode (320, 240, 32, 0);
  game_t *game = (game_t*)malloc (sizeof (game_t));
  game->board = NULL;
  game->n_gems = 0;
  game->gems = NULL;
  game->frame = 0;
  game->screen = screen;
  game->state = SPLASH_STATE;
  game->fps = 0;
  game->board_cursor_x = 0;
  game->board_cursor_y = 0;
  game->key_states = (bool*)malloc (sizeof (bool) * N_KEYS);
  memset (game->key_states, false, N_KEYS);
  game->prev_key_states = (bool*)malloc (sizeof (bool) * N_KEYS);
  memset (game->prev_key_states, false, N_KEYS);
  game->cursor_locked = false;
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
  SDL_Event event;
  while (SDL_PollEvent (&event))
    {
      int sym;
      switch (event.type)
        {
        case SDL_QUIT:
          game->state = QUIT_STATE;
          break;
        case SDL_KEYDOWN:
          sym = event.key.keysym.sym;
          if (sym >= 0 && sym < 512)
            {
              game->key_states[sym] = true;
            }
          break;
        case SDL_KEYUP:
          sym = event.key.keysym.sym;
          if (sym >= 0 && sym < 512)
            {
              game->key_states[sym] = false;
            }
          break;
        }
    }
  switch (game->state)
    {
    case SPLASH_STATE:
      splash_loop (game);
      break;
    case MENU_STATE:
      menu_loop (game);
      break;
    case SESSION_STATE:
      session_loop (game);
      break;
    }
  int i;
  for (i = 0; i < N_KEYS; ++i)
    {
      game->prev_key_states[i] = game->key_states[i];
    }
  if (game->fps > 0)
    {
      usleep (1000000 / game->fps);
    }
  ++game->frame;
}

void
game_add_gem (game_t *game, gem_t *gem)
{
  ++game->n_gems;
  game->gems = (gem_t**)realloc (game->gems, sizeof (gem_t*) * game->n_gems);
  game->gems[game->n_gems - 1] = gem;

  int x = gem->x / 24;
  int y = gem->y / 24;
  game->board[x][y] = game->n_gem_types * gem->level + gem->type;
}

void
game_move_gem (game_t *game, int x, int y, int gem_x, int gem_y)
{
  int bx = gem_x / 24;
  int by = gem_y / 24;
  int i;
  for (i = 0; i < game->n_gems; ++i)
    {
      gem_t *gem = game->gems[i];
      if (gem->x / 24 == x && gem->y / 24 == y)
        {
          game->board[x][y] = -1;
          gem->x = gem_x;
          gem->y = gem_y;
          game->board[bx][by] = game->n_gem_types * gem->level + gem->type;
          break;
        }
    }
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

void
game_start (game_t *game)
{
  session_start (game);
}

void
game_quit (game_t *game)
{
  game->state = QUIT_STATE;
}
