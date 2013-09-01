#include <stdlib.h>

#include "game.h"
#include "splash.h"
#include "menu.h"
#include "session.h"

#include "SDL_image.h"

int N_KEYS = 512;

SDL_Surface *
game_load_image (const char *filename)
{
  char *sprite_path = (char*)malloc (1 + strlen (filename) + strlen (BUILD_DIR) + 1);
  strcpy (sprite_path, BUILD_DIR);
  strcat (sprite_path, "/");
  strcat (sprite_path, filename);
  SDL_Surface *img = IMG_Load (sprite_path);
  if (img == NULL)
    {
      free (sprite_path);
      sprite_path = (char*)malloc (1 + strlen (filename) + strlen (PKG_DATA_DIR) + 1);
      strcpy (sprite_path, PKG_DATA_DIR);
      strcat (sprite_path, "/");
      strcat (sprite_path, filename);
      img = IMG_Load (sprite_path);
    }
  return img;
}

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
  game->sprite = game_load_image ("gems.png");
  game->frame_sprite = game_load_image ("slot.png");
  game->button_sprite = game_load_image ("buttons.png");
  game->menu_held_down = false;
  game->menu_cursor = 0;
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
  Uint32 frame_begin = SDL_GetTicks ();
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
      Uint32 frame_end = SDL_GetTicks ();
      Uint32 elapsed = frame_end - frame_begin;
      if (elapsed < 1000 / game->fps)
        {
          Uint32 wait_time = 1000 / game->fps - elapsed;
          SDL_Delay (wait_time);
        }
    }
  ++game->frame;
}

gem_t *
gem_create (int x, int y, int type, int level)
{
  gem_t *gem = (gem_t*)malloc (sizeof (gem_t));
  gem->x = x;
  gem->y = y;
  gem->dy = 0;
  gem->type = type;
  gem->level = level;
  return gem;
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

void
game_remove_gem (game_t *game, int x, int y)
{
  int i;
  for (i = 0; i < game->n_gems; ++i)
    {
      gem_t *gem = game->gems[i];
      if (gem->x / 24 == x && gem->y / 24 == y)
        {
          game->board[x][y] = -1;
          free (game->gems[i]);
          game->gems[i] = game->gems[game->n_gems - 1];
          --game->n_gems;
          game->gems = (gem_t**)realloc (game->gems, sizeof (gem_t*) * game->n_gems);
          break;
        }
    }
}

void
game_swap_gems (game_t *game, int x1, int y1, int x2, int y2)
{
  gem_t *gem1 = NULL;
  gem_t *gem2 = NULL;
  int i;
  for (i = 0; i < game->n_gems; ++i)
    {
      gem_t *gem = game->gems[i];
      if (gem->x / 24 == x1 && gem->y / 24 == y1)
        {
          gem1 = gem;
        }
      else if (gem->x / 24 == x2 && gem->y / 24 == y2)
        {
          gem2 = gem;
        }
    }
  int val1 = game->board[x1][y1];
  int gemx1 = gem1->x;
  int gemy1 = gem1->y;
  gem1->x = gem2->x;
  gem1->y = gem2->y;
  gem2->x = gemx1;
  gem2->y = gemy1;
  game->board[x1][y1] = game->board[x2][y2];
  game->board[x2][y2] = val1;
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
