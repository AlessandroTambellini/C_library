#include <fcntl.h> // open(), O_WRONLY, O_CREAT, O_APPEND
#include <stddef.h> // NULL
#include <stdio.h> // printf(), perror()
#include <stdlib.h> // malloc(), free(), exit()
#include <string.h> // strncat(), strlen(), strcpy()
#include <sys/stat.h> // S_IRUSR, S_IWUSR
#include <unistd.h> // write(), close()

void usage(char *prog_name, char *filename);
void fatal(char *);
void *ec_malloc(__uint32_t);

int main(int argc, char **argv)
{
    int fd; // file descriptor
    char *buffer, *datafile;

    buffer = (char *)ec_malloc(100);
    datafile = (char *)ec_malloc(20);
    strcpy(datafile, "input.txt");

    if (argc < 2)
        usage(argv[0], datafile);

    strcpy(buffer, argv[1]);

    printf("[DEBUG] buffer   @ %p: \"%s\"\n", buffer, buffer);
    printf("[DEBUG] datafile @ %p: \"%s\"\n", datafile, datafile);

    strcat(buffer, "\n");

    fd = open(datafile, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if (fd == -1)
        fatal("in main() while opening file");
    printf("[DEBUG] file descriptor is %d\n", fd);

    if (write(fd, buffer, strlen(buffer)) == -1)
        fatal("in main() while writing buffer to file");

    if (close(fd) == -1)
        fatal("in main() while closing file");

    printf("Note has been saved.\n");
    free(buffer);
    free(datafile);
}

void usage(char *prog_name, char *filename)
{
    printf("Usage: %s <data to add to %s>\n", prog_name, filename);
    exit(-1);
}

void fatal(char *message)
{
    char error_message[100];
    strcpy(error_message, "[!!] Fatal Error ");
    strncat(error_message, message, 83);
    perror(error_message); // translate and print the method default error
    exit(-1);
}

void *ec_malloc(__uint32_t size)
{
    void *ptr;
    ptr = malloc(size);
    if (ptr == NULL)
        fatal("in ec_malloc() on memory allocation");
    return ptr;
}