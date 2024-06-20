#pragma once
#include "defines.h"

#define MAX_COROUTINES 5

typedef struct game game_t;

typedef struct stopwatch {
    f64 target_time;
    f64 elapsed_time;
} stopwatch_t;

typedef struct coroutine {
    i32 id;
    stopwatch_t timer;
    b8 done;
    b8 (*update)(game_t *game);
} coroutine_t;

b8 begin_coroutine(game_t *game, coroutine_t *coroutine);
b8 init_coroutines(game_t *game);
