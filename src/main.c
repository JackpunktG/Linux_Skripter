#include "../lib/easy_args.h"
#define ARENA_MEMORY_IMPLEMENTATION
#include "../lib/arena_memory.h"
#include "../lib/var_types.inc"
#include "assert.h"


typedef struct
{
    char alias[124];
    char skript[256];
} Skript_Node;

typedef struct
{
    Arena* arena;
    u32 count;
    Skript_Node* skript;
} Skript_Arr;

Skript_Arr* skript_load();

#define data_file_path "data/data.b"

Skript_Arr* skript_load()
{
    u32 count;

    FILE* fp = fopen(data_file_path, "r");
    if (!fp)
        count = 0;
    else
        fread(&count, sizeof(u32), 1, fp);

    Arena* arena    = arena_init(ARENA_BLOCK_SIZE, 8);
    Skript_Arr* arr = arena_alloc(arena, sizeof(Skript_Arr) + sizeof(Skript_Node) * count, NULL);
    assert(arr);

    arr->arena  = arena;
    arr->count  = count;

    if (count > 0)
    {
        arr->skript = (Skript_Node*)(arr +1);
        fread(&arr->skript, sizeof(Skript_Node), count, fp);
        fclose(fp);
    }
    else
        arr->skript = NULL;

    return arr;
}




i32 main(i32 argc, char* argv[])
{
    Program_Flags flags;
    if (!set_flags(&flags, argc, argv, ARG_TRUE))
        return 1;

    Skript_Arr* arr = skript_load();

    if (is_flag_set(&flags, FLAG_ADD))
    {
        if (flags.unknown_arg_count < 2)
            printf("Error: missing alias and/or skript\n");
        else
        {

        }
    }
    else if (is_flag_set(&flags, FLAG_REMOVE))
    {

        if (flags.unknown_arg_count < 1)
            printf("Error: missing alias\n");
        else
        {

        }
    }
    else if (is_flag_set(&flags, FLAG_DUMP))
    {

    }
    else if (is_flag_set(&flags, FLAG_PRINT))
    {
        if (flags.unknown_arg_count < 1)
            printf("Error: missing alias\n");
        else
        {

        }
    }

    // Clean up
    arena_destroy(arr->arena);

}




