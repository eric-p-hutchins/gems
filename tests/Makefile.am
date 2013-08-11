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
 key-released

loop_exists_SOURCES = loop-exists.c ../src/game.c
frame_starts_at_zero_SOURCES = frame-starts-at-zero.c ../src/game.c
loop_increments_frame_SOURCES = loop-increments-frame.c ../src/game.c
screen_exists_SOURCES = screen-exists.c ../src/game.c
state_exists_SOURCES = state-exists.c ../src/game.c
key_states_exist_SOURCES = key-states-exist.c ../src/game.c
prev_key_states_exist_SOURCES = prev-key-states-exist.c ../src/game.c
prev_key_states_SOURCES = prev-key-states.c ../src/game.c
key_pressed_SOURCES = key-pressed.c ../src/game.c
key_released_SOURCES = key-released.c ../src/game.c

check_PROGRAMS = $(TESTS)
