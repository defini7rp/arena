#ifndef ARENA_H
#define ARENA_H

#include <stdlib.h>

typedef struct Arena
{
    void* data;
    size_t cursor;
    size_t size;
} Arena;

void arena_init(Arena* arena, size_t size);
void arena_deinit(Arena* arena);

void* arena_grab(Arena* arena, size_t bytes);

typedef struct Test
{
    int a;
    float b;
} Test;

#ifdef ARENA_IMPL
#undef ARENA_IMPL

void arena_init(Arena* arena, size_t size)
{
    arena->data = malloc(sizeof(size));
    arena->size = size;
    arena->cursor = 0;
}

void arena_deinit(Arena* arena)
{
    arena->cursor = 0;
    arena->size = 0;
    free(arena->data);
}

void* arena_grab(Arena* arena, size_t bytes)
{
    if (arena->cursor + bytes >= arena->size)
    {
        fprintf(stderr, "no available memory in arena");
        return NULL;
    }
    
    void* ptr = (unsigned char*)arena->data + arena->cursor;
    arena->cursor += bytes;
    return ptr;
}

#endif

#endif // ARENA_H
