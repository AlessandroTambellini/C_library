#include <stdio.h>

#define RESET "\e[m" // you can also use "\x1b[0m"

#define BLACK "\x1B[30m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"

#define BG_BLACK "\x1b[40m"
#define BG_RED "\x1b[41m"
#define BG_GREEN "\x1b[42m"
#define BG_YELLOW "\x1b[43m"
#define BG_BLUE "\x1b[44m"
#define BG_MAGENTA "\x1b[45m"
#define BG_CYAN "\x1b[46m"
#define BG_WHITE "\x1b[47m"

#define BOLD "\x1b[1m"
#define FUMY "\x1b[2m"
#define UNDERSCORE "\x1b[4m"
#define BLINK "\x1b[5m"
#define REVERSE "\x1b[7m"
#define HIDDEN "\x1b[8m"

int main(void)
{
    printf("\n");

    printf("\e[1mVISUAL OUTPUT OPTIONS\e[m\n");

    printf("\t\e[1mTEXT COLOR\e[m\n");
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", BLACK, RESET);
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", RED, RESET);
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", GREEN, RESET);
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", YELLOW, RESET);
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", BLUE, RESET);
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", MAGENTA, RESET);
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", CYAN, RESET);
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", WHITE, RESET);

    printf("\n");

    printf("\t\e[1mBACKGROUND COLOR\e[m\n");
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", BG_BLACK, RESET);
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", BG_RED, RESET);
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", BG_GREEN, RESET);
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", BG_YELLOW, RESET);
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", BG_BLUE, RESET);
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", BG_MAGENTA, RESET);
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", BG_CYAN, RESET);
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", BG_WHITE, RESET);

    printf("\n");

    printf("\t\e[1mTEXT EFFECT\e[m\n");
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", BOLD, RESET);
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", FUMY, RESET);
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", UNDERSCORE, RESET);
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", BLINK, RESET);
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", REVERSE, RESET);
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", HIDDEN, RESET);

    printf("\n");

    printf("\t\e[1mMIXED EXAMPLES\e[m\n");
    printf("\t\t%s%sLorem ipsum dolor sit amet%s\n", BOLD, BLINK, RESET);
    printf("\t\t%sLorem ipsum dolor sit amet%s\n", FUMY, RESET);
    printf("\t\t%s%s%sLorem ipsum dolor sit amet%s\n", UNDERSCORE, RED, BG_RED, RESET);
    printf("\t\t%s%sLorem ipsum dolor sit amet%s\n", BLACK, BG_RED, RESET);
    printf("\t\t%s%s%sLorem ipsum dolor sit amet%s\n", MAGENTA, REVERSE, BOLD, RESET);
    printf("\t\t%s%sLorem ipsum dolor sit amet%s\n", BLACK, FUMY, RESET);
}
