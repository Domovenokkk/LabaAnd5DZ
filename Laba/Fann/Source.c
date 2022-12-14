#include <stdio.h>
int fibon(int N)  
{
    if (N == 1 || N == 2)
        return 1; 
    return fibon(N - 1) + fibon(N - 2); 
}
int main()
{
    int N;
    printf("N=");
    scanf_s("%d", &N); 
    for (int i = 1; i <= N; i++) 
        printf("%d ", fibon(i));
    getchar(); getchar();
    return 0;
}