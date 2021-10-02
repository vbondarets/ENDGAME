#include <../inc/header.h>


void entity_init(void) {
    entity_pool = malloc(sizeof(t_entity) * ENTITY_POOL_SIZE);
    free_entity_pool_slots = new_stack(ENTITY_POOL_SIZE, sizeof(int));
    for(int i = 0; i < ENTITY_POOL_SIZE; i++) {
        entity_pool[i].index = i;
        entity_pool[i].active = false;
        entity_pool[i].data = NULL;
        entity_pool[i].on_collision = NULL;
        entity_pool[i].update = NULL;
        stack_push(&free_entity_pool_slots, &i);
    }
}

t_entity* entity_pool_get(int x, int y, e_etype type) {
    int index = *((int*)stack_pop(&free_entity_pool_slots));
    entity_pool[index].x = x;
    entity_pool[index].y = y;
    entity_pool[index].active = true;
    entity_pool[index].etype = type;
    return &entity_pool[index];
}

void entity_pool_free(t_entity* entity) {
    free(entity->data);
    entity->data = NULL;
    entity->active = false;
    entity->on_collision = NULL;
    entity->update = NULL;
    if(entity->collider)
        collider_pool_free(entity->collider);
    entity->collider = NULL;
    stack_push(&free_entity_pool_slots, &(entity->index));
}

void entity_update(void) {
    for(int i = 0; i < ENTITY_POOL_SIZE; i++) {
        if(entity_pool[i].active) {
            entity_pool[i].update(&entity_pool[i]);
        }
    }
}

void keep_on_screen(t_entity* entity) {
    t_stats* entity_data = (t_stats*)(entity->data);

    if(entity->x < entity_data->w / 2) {
        entity->x = entity_data->w / 2;
    }
    if(entity->y < entity_data->h / 2) {
        entity->y = entity_data->h / 2;
    }
    if(entity->x > WINDOW_WIDTH - entity_data->w / 2) {
        entity->x = WINDOW_WIDTH - entity_data->w / 2;
    }
    if(entity->y > WINDOW_HEIGHT - entity_data->h / 2) {
        entity->y = WINDOW_HEIGHT - entity_data->h / 2;
    }
}

void entity_pool_clear(void) {
    stack_clear(&free_entity_pool_slots);

    for(int i = 0; i < ENTITY_POOL_SIZE; i++) {
        if(entity_pool[i].active) {
            entity_pool[i].active = false;
            if(entity_pool[i].data)
                free(entity_pool[i].data);
            entity_pool[i].data = NULL;
            entity_pool[i].update = NULL;
            entity_pool[i].on_collision = NULL;
            if(entity_pool[i].collider)
                collider_pool_free(entity_pool[i].collider);
            entity_pool[i].collider = NULL;
            stack_push(&free_entity_pool_slots, &i);
        }
    }
}

