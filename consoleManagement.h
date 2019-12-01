#ifndef DEF_CONSOLE_COLORS_H
#define DEF_CONSOLE_COLORS_H
//https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
//pour utiliser ces chaines ANSI, taper "printf(<code>)" pour changer la couleur de la console
#define FRONT_BLACK         "\x1b[30m"
#define BACK_BLACK          "\x1b[40m"
#define FRONT_RED           "\x1b[31m"
#define BACK_RED            "\x1b[41m"
#define FRONT_GREEN         "\x1b[32m"
#define BACK_GREEN          "\x1b[42m"
#define FRONT_YELLOW        "\x1b[33m"
#define BACK_YELLOW         "\x1b[43m"
#define FRONT_BLUE          "\x1b[34m"
#define BACK_BLUE           "\x1b[44m"
#define FRONT_MAGENTA       "\x1b[35m"
#define BACK_MAGENTA        "\x1b[45m"
#define FRONT_CYAN          "\x1b[36m"
#define BACK_CYAN           "\x1b[46m"
#define FRONT_GREY          "\x1b[90m"
#define BACK_GREY           "\x1b[100m"
#define FRONT_BRIGHT_GREY   "\x1b[37m"
#define BACK_BRIGHT_GREY    "\x1b[47m"
#define FRONT_BRIGHT_RED    "\x1b[91m"
#define BACK_BRIGHT_RED     "\x1b[101m"
#define FRONT_BRIGHT_GREEN  "\x1b[92m"
#define BACK_BRIGHT_GREEN   "\x1b[102m"
#define FRONT_BRIGHT_YELLOW "\x1b[93m"
#define BACK_BRIGHT_YELLOW  "\x1b[103m"
#define FRONT_BRIGHT_BLUE   "\x1b[94m"
#define BACK_BRIGHT_BLUE    "\x1b[104m"
#define FRONT_BRIGHT_MAGENTA"\x1b[95m"
#define BACK_BRIGHT_MAGENTA "\x1b[105m"
#define FRONT_BRIGHT_CYAN   "\x1b[96m"
#define BACK_BRIGHT_CYAN    "\x1b[106m"
#define FRONT_WHITE         "\x1b[97m"
#define BACK_WHITE          "\x1b[107m"


void moveCurs(int, int);


#endif