
// Program to print all permutations of a string in sorted order.
#include <stdio.h>
#include<stdbool.h>
#include <stdlib.h>
#include <string.h>
//requirement for qsort
int compare(const void *a, const void * b)
{
    return ( *(char *)a - *(char *)b );
}

void swap(char* a, char* b)
{
    char t = *a;
    *a = *b;
    *b = t;
}

// This function finds the index of the smallest character
// which is greater than 'first' and is present in str[l..h]
int findCeil(char str[], char first, int l, int h)
{
    int ceilIndex = l;
    int i;
    for ( i = l+1; i <= h; i++)
        if (str[i] > first && str[i] < str[ceilIndex])
            ceilIndex = i;

    return ceilIndex;
}
//print the permutations in sorted order into the permutation file
void sortedPermutations(char str[])
{
	FILE *per=fopen("permutation.txt","w");
    int size = strlen(str);

    //library function used to sort the string in increasing order
	qsort(str, size, sizeof( str[0] ), compare);

    bool isFinished = 0;
    while (!isFinished)
{
        static int x = 1;
        fprintf(per,"%s\n", str);
        int i;
        for (i = size - 2; i >= 0; --i)
            if (str[i] < str[i+1])
                break;

        // If there is no such chracter, all are sorted in decreasing order,
        // means we just printed the last permutation and we are done.
        if (i == -1)
            isFinished = 1;
        else
       {
            int ceilIndex = findCeil(str, str[i], i + 1, size - 1);

            swap(&str[i], &str[ceilIndex]);

            qsort(str + i + 1, size - i - 1, sizeof(str[0]), compare);
        }
    }
}

int main()
{
    char str[45];
    printf("Enter the string\n");
	scanf("%s",str);
    sortedPermutations( str );
    return 0;
}
