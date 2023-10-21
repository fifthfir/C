#include <stdio.h>

int main()
{
    double foot = 0;
    double inch = 0;

    printf("Please enter your height in foot and inch:\n");
    scanf("%lf %lf", &foot, &inch);
    printf("%f", ((foot+inch/12)*0.3048));
    return 0;
}