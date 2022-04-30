#include <stdio.h>

int data[]={1,2,3,4};

int swap(int i,int j)
{
    int temp;
    if(i==j) return 0;
    temp = data[i];
    data[i]=data[j];
    data[j]=temp;
    return 0;
}

int Permutation(int TotalN,int N)
{
    int i;

    if( N==1 ) {
        for(i=0;i<TotalN;i++){
            printf("%d ",data[i]);
        }
        printf("\n");
        return 0;
    }

    for(i=0;i<N;i++){
        swap(i,N-1);
        Permutation(TotalN,N-1);
        swap(i,N-1);
    }
}

int main()
{
    int N=sizeof(data)/sizeof(int);
    Permutation(N,N);
    return 0;
}