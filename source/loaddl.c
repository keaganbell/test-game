#include <dlfcn.h>
#include <stdio.h>

#include "loaddl.h"

static void *dl = NULL;

b8 load_game_dl(game_t *game)
{
    dl = dlopen("libgame.so", RTLD_NOW);
    game->init = dlsym(dl, "game_init");
    game->update = dlsym(dl, "game_update");
    game->shutdown = dlsym(dl, "game_shutdown");
    
    if (!game->init)
    {
        printf("ERROR: failed to load library function game.init()\n");
        return false;
    }
    if (!game->update)
    {
        printf("ERROR: failed to load library function game.update()\n");
        return false;
    }
    if (!game->shutdown)
    {
        printf("ERROR: failed to load library function game.shutdown()\n");
        return false;
    }

    printf("INFO: game library was loaded successfully.\n");
    return true;
}

b8 unload_game_dl(game_t *game)
{
    if (dl == NULL)
    {
        return true;
    }

    if (dlclose(dl))
    {
        printf("ERROR: failed to unload game library.\n");
        return false;
    }
    
    game->init = NULL;
    game->update = NULL;
    game->shutdown = NULL;
    return true;
}

b8 hot_reload(game_t *game)
{
    if (!unload_game_dl(game))
    {
        return false;
    }
    // recompile game dll?
    if (!load_game_dl(game))
    {
        printf("ERROR: failed to load game library.\n");
        return false;
    }
    return true;
}
