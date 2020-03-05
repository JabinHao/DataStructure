#include <stdio.h>
#include <stdlib.h>

int maxsubsequence(int A[], int N)
{
    int ThisSum, MaxSum, i;
    ThisSum = MaxSum = 0;
    for (i = 0; i < N; i++)
    {
        ThisSum += A[i];
        if (ThisSum > MaxSum)
            MaxSum = ThisSum;
        else if (ThisSum < 0)
            ThisSum = 0;
    }
    return MaxSum;
}

int main(void)
{
    int K;
    scanf("%d", &K);
    int Subsequence[K];
    for (int i = 0; i < K; i++)
    {
        scanf("%d", &Subsequence[i]);
    }
    int sum = maxsubsequence(Subsequence, K);
    printf("%d", sum);
    return 0;
}
