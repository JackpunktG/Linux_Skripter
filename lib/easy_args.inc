#ifndef ARG
#define ARG(flag, arg_string, abbr, ...) {(uint8_t*)(arg_string), sizeof(arg_string) -1, (abbr), __VA_ARGS__},
#define ARG_INFO(info_string)  sizeof(info_string) -1, (uint8_t*)(info_string),
#define ARG_ABBR_NO 0
#endif

/* ===============================================================
   Add your args here, with the syntax: *optional
   ARG(flag, "trigger_input_string", 'char' for single char trigger input(abbr.) / 0 for not used, *ARG_INFO("flag help page info"))
   the below and examples, replace them with your flags of choice
   ==============================================================*/
ARG(FLAG_ADD, "--add", 'a', ARG_INFO(
        "to add a new skript\n"
        "\t-a [alias] [skript]"
))
ARG(FLAG_REMOVE, "--remove", 'r', ARG_INFO(
        "remove a skript\n"
        "\t-r [alias]"
))
ARG(FLAG_DUMP, "--dump", 'd', ARG_INFO(
        "print out all saved skripts"
))
ARG(FLAG_PRINT, "--print", 'p', ARG_INFO(
        "print out a skript"
        "\t-p [alias]"
))

#undef ARG_ABBR_NO
#undef ARG_INFO
#undef ARG
