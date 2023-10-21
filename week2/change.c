#include <stdio.h>

int main()
{
    const int AMOUNT = 100;
    int price = 0;

    printf("Please enter the amount: ");
    scanf("%d", &price);

    int change = AMOUNT - price;

    printf("Here is your change: %d.", change);

    return 0;
}