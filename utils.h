#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fatal(char *message)
{
    char error_message[100];
    strcpy(error_message, "[!] FATAL ERROR ");
    strncat(error_message, message, 84); // the string above is 16 characters
    perror(error_message);
    exit(-1);
}

void *ec_malloc(uint32_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL)
        fatal("in ec_malloc() in memory allocation");
    return ptr;
}