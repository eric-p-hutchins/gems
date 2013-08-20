AM_CPPFLAGS = -I../src

TESTS = \
 loop-exists \
 frame-starts-at-zero \
 loop-increments-frame \
 screen-exists \
 state-exists \
 key-states-exist \
 prev-key-states-exist \
 prev-key-states \
 key-pressed \
 key-released \
 splash-is-short \
 escape-quits-from-menu \
 menu-selection \
 menu-enter-triggers \
 menu-after-splash \
 session-starts-with-no-matches \
 three-in-column-drops-new-ones \
 three-in-row-drops-new-ones \
 four-in-column-makes-special1 \
 four-in-row-makes-special1 \
 t-shape-makes-special2 \
 l-shape-makes-special2 \
 five-in-row-or-col-makes-special3 \
 arrow-keys-move-board-cursor \
 legal-move \
 space-locks-board-cursor

GAME_SOURCES = \
 test.c \
 ../src/game.c \
 ../src/splash.c \
 ../src/menu.c \
 ../src/session.c

loop_exists_SOURCES = loop-exists.c $(GAME_SOURCES)
frame_starts_at_zero_SOURCES = frame-starts-at-zero.c $(GAME_SOURCES)
loop_increments_frame_SOURCES = loop-increments-frame.c $(GAME_SOURCES)
screen_exists_SOURCES = screen-exists.c $(GAME_SOURCES)
state_exists_SOURCES = state-exists.c $(GAME_SOURCES)
key_states_exist_SOURCES = key-states-exist.c $(GAME_SOURCES)
prev_key_states_exist_SOURCES = prev-key-states-exist.c $(GAME_SOURCES)
prev_key_states_SOURCES = prev-key-states.c $(GAME_SOURCES)
key_pressed_SOURCES = key-pressed.c $(GAME_SOURCES)
key_released_SOURCES = key-released.c $(GAME_SOURCES)
splash_is_short_SOURCES = splash-is-short.c $(GAME_SOURCES)
escape_quits_from_menu_SOURCES = escape-quits-from-menu.c $(GAME_SOURCES)
menu_selection_SOURCES = menu-selection.c $(GAME_SOURCES)
menu_enter_triggers_SOURCES = menu-enter-triggers.c $(GAME_SOURCES)
menu_after_splash_SOURCES = menu-after-splash.c $(GAME_SOURCES)
session_starts_with_no_matches_SOURCES = session-starts-with-no-matches.c $(GAME_SOURCES)
three_in_column_drops_new_ones_SOURCES = three-in-column-drops-new-ones.c $(GAME_SOURCES)
three_in_row_drops_new_ones_SOURCES = three-in-row-drops-new-ones.c $(GAME_SOURCES)
four_in_column_makes_special1_SOURCES = four-in-column-makes-special1.c $(GAME_SOURCES)
four_in_row_makes_special1_SOURCES = four-in-row-makes-special1.c $(GAME_SOURCES)
t_shape_makes_special2_SOURCES = t-shape-makes-special2.c $(GAME_SOURCES)
l_shape_makes_special2_SOURCES = l-shape-makes-special2.c $(GAME_SOURCES)
five_in_row_or_col_makes_special3_SOURCES = five-in-row-or-col-makes-special3.c $(GAME_SOURCES)
arrow_keys_move_board_cursor_SOURCES = arrow-keys-move-board-cursor.c $(GAME_SOURCES)
legal_move_SOURCES = legal-move.c $(GAME_SOURCES)
space_locks_board_cursor_SOURCES = space-locks-board-cursor.c $(GAME_SOURCES)

check_PROGRAMS = $(TESTS)
