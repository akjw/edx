#include <cs50.h>
#include <stdio.h>
#include <math.h>

// int main(void)
// {
//     float dollars;

//     do
//     {
//         dollars = get_float("Change owed: ");
//     }
//     while (dollars <= 0);

//     int cents = round(dollars * 100);
//     int num_coins = 0;

//     while (cents != 0)
//     {

//         if (cents >= 25)
//         {
//             num_coins += cents / 25;
//             cents = cents % 25;
//         }
//         else if (cents >= 10)
//         {
//             num_coins += cents / 10;
//             cents = cents % 10;
//         }
//         else if (cents >= 5)
//         {
//             num_coins += cents / 5;
//             cents = cents % 5;
//         }
//         else
//         {
//             num_coins += cents / 1;
//             cents = cents % 1;
//         }

//     }

//     printf("%i\n", num_coins);
// }

int main(void)
{
    float dollars;

    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars <= 0);

    int cents = round(dollars * 100);
    int num_coins = 0;

        num_coins += cents / 25;
        cents = cents % 25;

        printf("%i\n", num_coins);
        printf("%i\n", cents);

        num_coins += cents / 10;
        cents = cents % 10;

        printf("%i\n", num_coins);
        printf("%i\n", cents);

        // num_coins += cents / 5;
        // cents = cents % 5;

        // num_coins += cents / 1;
        // cents = cents % 1;

    printf("%i\n", num_coins);

}