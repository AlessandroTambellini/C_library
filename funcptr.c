#include <stdio.h>

void func_one(void)
{
    printf("Hello from func_one()!\n");
}

int func_two(void)
{
    return 1;
}

char func_three(char c)
{
    return c + 1;
}

int main(void)
{
    void (*function_ptr)() = func_one;
    int (*function_ptr_2)() = func_two;
    char (*function_ptr_3)(char) = func_three;

    printf("function_ptr = %p\n", function_ptr);
    printf("function_ptr_2 = %p\n", function_ptr_2);
    printf("function_ptr_3 = %p\n", function_ptr_3);
}
