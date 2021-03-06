#include <stdio.h>
#include <stdlib.h>

int Maxsubsequence(int A[], int K, int *First, int *Last)
{
    int Thissum, maxsum, f;
    *First = f = Thissum = 0;
    maxsum = -1;
    for (int i = 0; i < K; i++)
    {
        Thissum += A[i];
        if (Thissum > maxsum)
        {
            maxsum = Thissum;
            *Last = i;
            *First = f;
        }
        else if (Thissum < 0)
        {
            Thissum = 0;
            f = i + 1;
        }
    }
    return maxsum;
}
int main()
{
    int K, First, Last, sum = 0, flag = 0;
    scanf("%d", &K);
    int Subsequence[K];
    for (int i = 0; i < K; i++)
    {
        scanf("%d", &Subsequence[i]);
        if (Subsequence[i] >= 0)
        {
            flag = 1;
        }
    }
    if (flag)
    {
        sum = Maxsubsequence(Subsequence, K, &First, &Last);
    }
    else
    {
        First = 0;
        Last = K - 1;
    }
    printf("%d %d %d", sum, Subsequence[First], Subsequence[Last]);
    return 0;
}
