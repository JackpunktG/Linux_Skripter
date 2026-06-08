#include "../lib/easy_args.h"
#include "../lib/var_types.inc"




typedef struct
{
    char alias[124];
    char skript[256];
} Skript_Node;


i32 main(i32 argc, char* argv[])
{
    Program_Flags flags;
    if (!set_flags(& flags, argc, argv, ARG_TRUE))
        return 1;

    print_program_flags(&flags);

    print_args_table();


}




