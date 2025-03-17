#include <stdio.h>

#define ARENA_IMPL
#include "arena.h"

typedef struct Test
{
    int a;
    float b;
} Test;

int main()
{
    Arena a;
    arena_init(&a, 64);
    
    Test* t = arena_grab(&a, sizeof(Test));
    float* p = arena_grab(&a, sizeof(float));
    
    *p = 25.0f;
    t->a = 10312;
    t->b = 3.14f;

    printf("%f %d %f\n", *p, t->a, t->b);

    arena_grab(&a, 100);
    
    arena_deinit(&a);
    
    return 0;
}
