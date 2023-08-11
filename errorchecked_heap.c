#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *errorchecked_malloc(uint32_t);

int main(int argc, char **argv)
{
    char *char_ptr;
    int *int_ptr;
    int mem_size;

    if (argc < 2)
        mem_size = 50; // if there is not command-line argument, use 50 as default value
    else
        mem_size = atoi(argv[1]);

    printf("\n");

    printf("\t\x1b[1;32m[+]\x1b[0m allocating %d bytes of memory on the heap for char_ptr\n", mem_size);
    char_ptr = (char *)errorchecked_malloc(mem_size);

    strcpy(char_ptr, "This is memory is allocated on the heap.");
    printf("\e[1mchar_ptr\e[m (%p) --> '%s'\n", char_ptr, char_ptr);
    printf("\t\x1b[1;32m[+]\x1b[0m allocating 12 bytes of memory on the heap for int_ptr\n");
    int_ptr = (int *)errorchecked_malloc(12);

    *int_ptr = 31337;
    printf("\e[1mint_ptr\e[m (%p) --> %d\n", int_ptr, *int_ptr);

    printf("\t\x1b[1;31m[-]\x1b[0m freeing char_ptr's heap memory...\n");
    free(char_ptr);

    printf("\t\x1b[1;32m[+]\x1b[0m allocaring another 15 bytes for char_ptr\n");
    char_ptr = (char *)errorchecked_malloc(15);

    strcpy(char_ptr, "new memory");
    printf("\e[1mchar_ptr\e[m (%p) --> '%s'\n", char_ptr, char_ptr);

    printf("\t\x1b[1;31m[-]\x1b[0m freeing int_ptr's heap memory...\n");
    free(int_ptr);
    printf("\t\x1b[1;31m[-]\x1b[0m freeing char_ptr's heap memory...");
    free(char_ptr);

    printf("\n\n");
}

void *errorchecked_malloc(uint32_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Error: coid not allocate heap memory.\n");
        exit(-1);
    }
    return ptr;
}