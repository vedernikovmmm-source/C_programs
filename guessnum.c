#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int game;

    printf("Choose game (1 or 2): ");
    scanf("%d", &game);

    srand(time(NULL));

    switch (game)
    {
        case 1:
        {
            int number = rand() % 1000 + 1;
            int answer;
            int attempts = 0;

            do
            {
                printf("Your guess (1-1000): ");
                if (scanf("%d", &answer) != 1)
                {
                    printf("Please enter a number.\n");
                    return 1;
                }
                if (answer < 1 || answer > 1000)
                {
                    printf("Choose a number from 1 to 1000.\n");
                    continue;
                }

                attempts++;
                if (answer < number)
                    printf("Number is greater.\n");
                else if (answer > number)
                    printf("Number is lower.\n");
                else
                    printf("You guessed!\n");
            } while (answer != number);

            printf("Attempts: %d\n", attempts);
            break;
        }
        case 2:
        {
            int low = 1;
            int high = 1000;
            char answer;

            printf("Think of a number from 1 to 1000.\n");
            while (low <= high)
            {
                int guess = low + (high - low) / 2;

                printf("My guess is %d. Is your number lower (l) or greater (g), "
                       "or I guess it (y)? ",
                       guess);
                scanf(" %c", &answer);
                if (answer == 'y')
                {
                    printf("I guessed your number!\n");
                    return 0;
                }
                else if (answer == 'l')
                    high = guess - 1;
                else if (answer == 'g')
                    low = guess + 1;
                else
                    printf("Please enter l, g, or y.\n");
            }

            printf("Your number is outside the range.\n");
            break;
        }
        default:
            printf("Choose game 1 or 2, not any other number or character!!!!!\n");
            return 1;
    }

    return 0;
}
