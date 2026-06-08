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
ARG(FLAG_TEST, "--test", ARG_ABBR_NO)
ARG(FLAG_ONE, "--one", 'o', ARG_INFO(
        "This is a longer test sentence meant to verify how the program handles\n"
        "\tindentation, line breaks, and formatted output across multiple lines.\n"
        "\tIt includes tabs at the beginning of lines,\n"
        "\tas well as normal text that continues after them.\n"
        "You should see clear separation between paragraphs,\n"
        "\tand consistent spacing when alignment is working correctly.\n"
        "Finally, this last line ends the test string."))
ARG(FLAG_TWO, "--two", 't')
ARG(FLAG_THREE, "--three", ARG_ABBR_NO, ARG_INFO("It's the third arg. thats kinda cool :)"))

#undef ARG_ABBR_NO
#undef ARG_INFO
#undef ARG
