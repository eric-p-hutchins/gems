#ifndef SESSION_H
#define SESSION_H

#include <stdbool.h>

#include "game.h"

void session_start (game_t *game);
void session_loop (game_t *game);
bool session_legal_move (game_t *game, int x1, int y1, int x2, int y2);

#endif
