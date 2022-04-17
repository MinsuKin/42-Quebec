#include <stdio.h>

void QuickSort(int *arr, int left, int right);
int Partition(int *arr, int left, int right);
void swap(int *a, int *b);

int main()
{
    int arr[] = {9,6,5,8,10,1,3,7,4,2};

    QuickSort(arr, 0, 9);
    //정렬된 배열의 출력
    for(int c=0;c<=9;c++){
        printf("%d ",arr[c]);
    }
}

void QuickSort(int *arr, int left, int right)
{
    if(left < right)
    {
    int NewPivot = Partition(arr, left, right);

    //피벗을 기준으로 두 그룹으로 만들어서 다시 정렬한다.
    QuickSort(arr, left, NewPivot-1);
    QuickSort(arr, NewPivot+1, right);
    }
}

int Partition(int *arr, int left, int right)
{
    int low, high, pivot = 0;

    pivot = arr[right];
    low = left;
    high = right-1;

    while(low < high)
    {

        while(low<=right && arr[low]<pivot)
        {
            low++;
        }
        while(high>=left && arr[high]>pivot)
        {
            high--;
        }
        if(low<high)
        {
            swap(&arr[low], &arr[high]);
        }
    }
    //피벗을 중간 자리로 이동시켜준다.
    swap(&arr[low], &arr[right]);
    return low;
}

void swap(int *a, int *b)
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
}