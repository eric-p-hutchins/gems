#include "game.h"

#include "test.h"

int
main (int argc, char *argv[])
{
  game_t *game = game_create ();

  game->board = (int**)malloc (sizeof (int*) * 8);
  int i, j;
  for (i = 0; i < 8; ++i)
    {
      game->board[i] = (int*)malloc (sizeof (int) * 8);
      for (j = 0; j < 8; ++j)
        {
          game->board[i][j] = 0;
        }
    }

  game->n_gem_types = 4;

  gem_t *gem = (gem_t*)malloc (sizeof (gem_t));
  gem->x = 0;
  gem->y = 0;
  gem->type = 0;
  gem->level = 0;
  game_add_gem (game, gem);
  game_move_gem (game, 0, 0, 0, 12);
  fail_if (game->board[0][0] != 0);
  fail_if (game->n_gems != 1);
  fail_if (game->gems[0]->x != 0);
  fail_if (game->gems[0]->y != 12);
  fail_if (game->gems[0]->type != 0);
  fail_if (game->gems[0]->level != 0);
  game_move_gem (game, 0, 0, 0, 24);
  fail_if (game->board[0][0] != -1);
  fail_if (game->board[0][1] != 0);
  fail_if (game->n_gems != 1);
  fail_if (game->gems[0]->x != 0);
  fail_if (game->gems[0]->y != 24);
  fail_if (game->gems[0]->type != 0);
  fail_if (game->gems[0]->level != 0);

  gem = (gem_t*)malloc (sizeof (gem_t));
  gem->x = 24;
  gem->y = 48;
  gem->type = 2;
  gem->level = 3;
  game_add_gem (game, gem);
  game_move_gem (game, 1, 2, 24, 60);
  fail_if (game->board[1][2] != 14);
  fail_if (game->n_gems != 2);
  fail_if (game->gems[1]->x != 24);
  fail_if (game->gems[1]->y != 60);
  fail_if (game->gems[1]->type != 2);
  fail_if (game->gems[1]->level != 3);
  game_move_gem (game, 1, 2, 24, 72);
  fail_if (game->board[1][2] != -1);
  fail_if (game->board[1][3] != 14);
  fail_if (game->n_gems != 2);
  fail_if (game->gems[1]->x != 24);
  fail_if (game->gems[1]->y != 72);
  fail_if (game->gems[1]->type != 2);
  fail_if (game->gems[1]->level != 3);

  game_destroy (game);
  return 0;
}
