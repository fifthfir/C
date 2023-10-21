#include <stdio.h>

int main()
{
    int a = 0;
    int b = 0;

    printf("Please enter two integers:\n");
    scanf("%d %d", &a, &b);
    printf("%d + %d = %d", a, b, a+b);
}