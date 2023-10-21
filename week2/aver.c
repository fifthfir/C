#include <stdio.h>

int main()
{
    int a, b;
    scanf("%d %d",  &a, &b);
    double c = (a + b) / 2.0;
    printf("AVERAGE of %d and %d IS %f", a, b, c);
}