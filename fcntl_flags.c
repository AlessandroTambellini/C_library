#include <fcntl.h>
#include <stdio.h>

void display_flags(char *, __uint32_t);
void binary_print(__uint32_t);

int main(int argc, char **argv)
{
    printf("\n");

    printf("\e[1mLIST OF OPTIONS\e[m\n");
    display_flags("\tO_ACCMODE\t\t", O_ACCMODE);
    display_flags("\tO_APPEND\t\t", O_APPEND);
    display_flags("\tO_ASYNC\t\t\t", O_ASYNC);
    display_flags("\tO_CREAT\t\t\t", O_CREAT);
    display_flags("\tO_EXCL\t\t\t", O_EXCL);
    display_flags("\tO_FSYNC\t\t\t", O_FSYNC);
    display_flags("\tO_NDELAY\t\t", O_NDELAY);
    display_flags("\tO_NOCTTY\t\t", O_NOCTTY);
    display_flags("\tO_NONBLOCK\t\t", O_NONBLOCK);
    display_flags("\tO_RDONLY\t\t", O_RDONLY);
    display_flags("\tO_RDWR\t\t\t", O_RDWR);
    display_flags("\tO_SYNC\t\t\t", O_SYNC);
    display_flags("\tO_TRUNC\t\t\t", O_TRUNC);
    display_flags("\tO_WRONLY\t\t", O_WRONLY);

    printf("\n");

    printf("\e[1mEXAMPLE\e[m\n");
    display_flags("\tO_WRONLY | O_CREAT | O_APPEND", O_WRONLY | O_CREAT | O_APPEND);
    printf("\t(open file for write-only access) && (create file if it doesn't exist) && (write data at the end of the file)\n");
    printf("\texample program in file_descriptor.c\n");

    printf("\n");

    printf("\e[1mFLAGS MEANING\e[m\n");
    printf("\tO_ACCMODE\t: to determine the access mode of a file\n");
    printf("\tO_APPEND\t: append data to the end of file\t\n");
    printf("\tO_ASYNC\t\t: asynchronous notification for input/output operations on a file\t\n");
    printf("\tO_CREAT\t\t: create a new file if it doesn't already exist\n");
    printf("\tO_EXCL\t\t: ensure that the file is created exclusively by the calling process\n");
    printf("\tO_FSYNC\t\t: to request synchronous (or buffered) I/O operations\n");
    printf("\tO_NDELAY\t: set a file descriptor to non-blocking mode\n");
    printf("\tO_NOCTTY\t: to prevent a newly opened terminal file from becoming the controlling terminal for the calling process\n");
    printf("\tO_NONBLOCK\t: same as O_NDELAY\n");
    printf("\tO_RDONLY\t: open file for read-only access\n");
    printf("\tO_RDWR\t\t: open file for read and write access\n");
    printf("\tO_SYNC\t\t: same as O_FSYNC\n");
    printf("\tO_TRUNC\t\t: if the file already exists, truncate the file to 0 length\n");
    printf("\tO_WRONLY\t: open file for write-only access\n");

    printf("\n");
}

void display_flags(char *label, __uint32_t value)
{
    if (value == O_FSYNC || value == O_SYNC)
        printf("%s\t: %d\t:", label, value);
    else
        printf("%s\t: %d\t\t:", label, value);
    binary_print(value);
    printf("\n");
}

void binary_print(__uint32_t value)
{
    __uint32_t mask = 0xff000000;
    __uint32_t shift = 256 * 256 * 256;
    __uint32_t byte, byte_iterator, bit_iterator;

    for (byte_iterator = 0; byte_iterator < 4; byte_iterator++) {
        byte = (value & mask) / shift;
        printf(" ");
        for (bit_iterator = 0; bit_iterator < 8; bit_iterator++) {
            if (byte & 0x80)
                printf("1");
            else
                printf("0");
            byte *= 2;
        }
        mask /= 256;
        shift /= 256;
    }
}