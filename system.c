#include <stdio.h>
#include <stdlib.h>

int main()
{
    int res = system("find . -type f  -executable -delete");
    if (res == 0)
        printf("command succeded.\n");
    else
        printf("command failed.\n");
    return 0;
}