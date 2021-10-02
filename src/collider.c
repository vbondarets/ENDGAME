#include "header.h"

void colliders_init(void) {
    collider_pool = malloc(sizeof(t_collider) * COLLIDER_POOL_SIZE);
    free_collider_pool_slots = new_stack(COLLIDER_POOL_SIZE, sizeof(int));
    for(int i = 0; i < COLLIDER_POOL_SIZE; i++) {
        collider_pool[i].index = i;
        collider_pool[i].active = false;
        collider_pool[i].collisions = new_stack(32, sizeof(t_collider*));
        collider_pool[i].owner = NULL;
        stack_push(&free_collider_pool_slots, &i);
    }
}

t_collider* collider_pool_get(t_entity* owner, int x, int y, int w, int h) {
    int index = *((int*)stack_pop(&free_collider_pool_slots));
    collider_pool[index].offsetx = x;
    collider_pool[index].offsety = y;
    collider_pool[index].width = w;
    collider_pool[index].height = h;
    collider_pool[index].owner = owner;
    collider_pool[index].active = true;
    owner->collider = &collider_pool[index];
    return &collider_pool[index];
}

void collider_pool_free(t_collider* collider) {
    stack_clear(&(collider->collisions));
    collider->active = false;
    collider->owner->collider = NULL;
    collider->owner = NULL;
    stack_push(&free_collider_pool_slots, &(collider->index));
}

