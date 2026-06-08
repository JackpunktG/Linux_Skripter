#include "stdio.h"
#include "../lib/easy_args.h"
#include "../lib/var_types.inc"



i32 main(i32 argc, char* argv[])
{
    Program_Flags flags;
    if (!set_flags(& flags, argc, argv, ARG_TRUE))
        return 1;

    print_program_flags(&flags);

    print_args_table();

    if (is_flag_set(&flags, FLAG_TEST))
    {}
}
