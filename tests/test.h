#ifndef TEST_H
#define TEST_H

#define press_key_and_loop(game, key)  \
  game->key_states[key] = true;        \
  game_loop (game);

#define release_key_and_loop(game, key)         \
  game->key_states[key] = false;                \
  game_loop (game);

#define fail_if(condition)                      \
  if (condition)                                \
    {                                           \
      exit (1);                                 \
    }

#endif
