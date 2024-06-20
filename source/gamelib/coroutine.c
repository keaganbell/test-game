#include "gamelib/coroutine.h"

#include "gamelib/game.h"

#include "stdio.h"

b8 begin_coroutine(game_t *game, coroutine_t *coroutine) {
    // darray_push(&game->state->coroutines, coroutine)
    if (coroutine->id > MAX_COROUTINES) {
        printf("ERROR: not enough space to add coroutine\n");
        return false;
    }
    coroutine_t *coroutine_out = &game->state->coroutines[coroutine->id];
    coroutine_out->id = coroutine->id; 
    coroutine_out->timer.target_time = coroutine->timer.target_time; 
    coroutine_out->timer.elapsed_time = 0;
    coroutine_out->done = false; 
    coroutine_out->update = coroutine->update; 
    return true;
}

b8 init_coroutines(game_t *game) {
    return true;
}
