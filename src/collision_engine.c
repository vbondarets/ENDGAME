#include "header.h"

void check_collisions(void) {
    for(int i = 0; i < COLLIDER_POOL_SIZE; i++) {
        for(int j = i + 1; j < COLLIDER_POOL_SIZE; j++) {
            t_collider* a = &collider_pool[i];
            t_collider* b = &collider_pool[j];
            if(a->active && b->active) {
                int afromx, afromy, atox, atoy, bfromx, bfromy, btox, btoy;
                afromx = a->owner->x + a->offsetx;
                afromy = a->owner->y + a->offsety;
                atox = a->owner->x + a->offsetx + a->width;
                atoy = a->owner->y + a->offsety + a->height;
                bfromx = b->owner->x + b->offsetx;
                bfromy = b->owner->y + b->offsety;
                btox = b->owner->x + b->offsetx + b->width;
                btoy = b->owner->y + b->offsety + b->height;
                if(afromx < btox && afromy < btoy && atox > bfromx && atoy > bfromy) {
                    stack_push(&(a->collisions), b);
                    stack_push(&(b->collisions), a);
                }
            }
        }
    }
}

void resolve_collisions(void) {
    for(int i = 0; i < COLLIDER_POOL_SIZE; i++) {
        while(collider_pool[i].collisions.size) {
            t_collider* collision = (t_collider*)stack_pop(&(collider_pool[i].collisions));
            if(collider_pool[i].owner->on_collision && collision->active && collider_pool[i].owner && collider_pool[collision->index].owner) {
                collider_pool[i].owner->on_collision(collider_pool[i].owner, collider_pool[collision->index].owner);
            }
        }
    }
}

