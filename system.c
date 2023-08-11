#include <stdio.h>
#include <stdlib.h>

int main()
{
    // delete all the executables in the project folder
    int res = system("find . -type f  -executable -delete");
    if (res == 0)
        printf("command succeded.\n");
    else
        printf("command failed.\n");

    // check if 2 files are identical 
    res = system("cmp --silent <file1> <file2> && echo \"files are identical\" || echo \"files are different\"");
    if (res == 0) 
	printf("command succeded.\n");
    else
	printf("command failed.\n");
    return 0;
}
