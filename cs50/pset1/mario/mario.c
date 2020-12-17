#include <cs50.h>
#include <stdio.h>


void REPEAT(char str, int times);

int main(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (!(height >= 1) || !(height <= 8));


    for (int i = 0; i < height; i++)
    {
        REPEAT(' ', height - i - 1);
        REPEAT('#', i + 1);
        REPEAT(' ', 2);
        REPEAT('#', i + 1);
        printf("\n");
    }

}

void REPEAT(char str, int times)
{
    for (int i = 0; i < times; ++i)
    {
        printf("%c", str);
    }
}