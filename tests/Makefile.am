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
 menu-selection

GAME_SOURCES = \
 ../src/game.c \
 ../src/splash.c \
 ../src/menu.c

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

check_PROGRAMS = $(TESTS)
