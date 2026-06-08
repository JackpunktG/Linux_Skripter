#include "../lib/easy_args.h"
#define ARENA_MEMORY_IMPLEMENTATION
#include "../lib/arena_memory.h"
#include "../lib/var_types.inc"
#include "assert.h"


#define ALIAS_LEN_MAX  124
#define SKRIPT_LEN_MAX 256
typedef struct
{
    char alias[ALIAS_LEN_MAX];
    char skript[SKRIPT_LEN_MAX];
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
        fread(arr->skript, sizeof(Skript_Node), count, fp);
        fclose(fp);
    }
    else
        arr->skript = NULL;

    return arr;
}

void skript_add(Skript_Arr* arr, Skript_Node* new_node)
{
    FILE* fp = fopen(data_file_path, "wb");
    if (!fp)
        return;

    fwrite(&arr->count, sizeof(u32), 1, fp);

    fwrite(new_node, sizeof(Skript_Node), 1, fp);
    fwrite(arr->skript, sizeof(Skript_Node), arr->count -1, fp);

    fclose(fp);
}

void skript_remove(Skript_Arr* arr, const u32 remove_index)
{
    FILE* fp = fopen(data_file_path, "wb");
    if (!fp)
        return;

    const u32 count = arr->count - 1;
    fwrite(&count, sizeof(u32), 1, fp);

    for (u32 i = 0; i < arr->count; ++i)
    {
        if (i == remove_index)
            continue;

        fwrite(&arr->skript[i], sizeof(Skript_Node), 1, fp);
    }

    fclose(fp);
}

#define NO_SKRIPT_FOUND -1
i32 skript_find(Skript_Arr* arr, const char* alias)
{
    for (u32 i = 0; i < arr->count; i++)
    {
        if (strcmp(arr->skript[i].alias, alias) == 0)
            return (i32)i;
    }

    return NO_SKRIPT_FOUND;
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
        {
            printf("Error: missing alias and/or skript\n");
        }
        else
        {
            const char* alias  = flags.unknown_arg[0];
            const char* skript = flags.unknown_arg[1];

            if (skript_find(arr, alias) >= 0)
            {
                printf("Alias '%s' already exists\n", alias);
            }
            else
            {
                Skript_Node new;
                memset(&new, 0, sizeof(Skript_Arr));

                strncpy(new.alias, alias, ALIAS_LEN_MAX -1);
                strncpy(new.skript, skript, SKRIPT_LEN_MAX -1);

                arr->count++;
                skript_add(arr, &new);

                printf("Added '%s'\n", alias);
            }
        }
    }
    else if (is_flag_set(&flags, FLAG_REMOVE))
    {
        if (flags.unknown_arg_count < 1)
        {
            printf("Error: missing alias\n");
        }
        else
        {
            const char* alias = flags.unknown_arg[0];

            i32 idx = skript_find(arr, alias);

            if (idx < 0)
            {
                printf("Alias '%s' not found\n", alias);
            }
            else
            {
                printf("Alias '%s' removed\n", alias);
                skript_remove(arr, idx);
            }
        }
    }
    else if (is_flag_set(&flags, FLAG_DUMP))
    {
        if (arr->count == 0)
        {
            printf("No skripts stored\n");
        }
        else
        {
            for (u32 i = 0; i < arr->count; i++)
            {
                printf("%s -> %s\n", arr->skript[i].alias, arr->skript[i].skript);
            }
        }
    }
    else if (is_flag_set(&flags, FLAG_PRINT))
    {
        if (flags.unknown_arg_count < 1)
        {
            printf("Error: missing alias\n");
        }
        else
        {

        }

    }

    // Clean up
    arena_destroy(arr->arena);

}




