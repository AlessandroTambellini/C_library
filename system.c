#include <stdio.h>
#include <stdlib.h>

// NOTE: substitute <parameter> with the actual argument

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

    // the output of the executable is stored in <output_file>. If <output_file> does not exist, it is created
    res = system("<executable> <optional_argument> > <output_file>");
    if (res == 0)
	printf("command succeded.\n");
    else
	printf("command failed.\n");

    return 0;
}
