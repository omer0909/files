#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubleSort(int arr[], int size)
{
    while (1)
    {
        int a = 1;
        for (int i = 1; i < size; i++)
        {
            if (arr[i - 1] > arr[i])
            {
                a = 0;
                int tmp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = tmp;
            }
        }
        if (a)
            break;
    }
}

void quickSort(int arr[], int head, int end)
{
    int pivot = arr[head];
    int index = head;

    for (int i = head + 1; i < end; i++)
    {
        if (arr[i] < pivot)
        {
            index++;
            int tmp = arr[i];
            arr[i] = arr[index];
            arr[index] = tmp;
        }
    }
    arr[head] = arr[index];
    arr[index] = pivot;

    if (1 < index - head)
        quickSort(arr, head, index);

    if (2 < end - index)
        quickSort(arr, index + 1, end);
}

void quickSortPlay(int arr[], int size)
{
    quickSort(arr, 0, size);
}

void merge(int left[], int leftSize, int right[], int rightSize, int result[])
{
    int leftC = 0;
    int rightC = 0;
    int size = leftSize + rightSize;

    for (int i = 0; i < size; i++)
    {
        int a = 1;

        if (left[leftC] < right[rightC])
        {
            if (leftC < leftSize)
                a = 1;
            else
                a = 0;
        }
        else
        {
            if (rightC < rightSize)
                a = 0;
            else
                a = 1;
        }

        if (a)
        {
            result[i] = left[leftC];
            ++leftC;
        }
        else
        {
            result[i] = right[rightC];
            ++rightC;
        }
    }
}

void mergeSort(int arr[], int size)
{
    const int leftSize = size / 2;
    const int rightSize = size - leftSize;

    int left[leftSize];
    int right[rightSize];

    for (int i = 0; i < leftSize; i++)
    {
        left[i] = arr[i];
    }
    for (int i = 0; i < rightSize; i++)
    {
        right[i] = arr[i + leftSize];
    }

    if (leftSize > 1)
        mergeSort(left, leftSize);
    if (rightSize > 1)
        mergeSort(right, rightSize);

    merge(left, leftSize, right, rightSize, arr);
}

void play(void sort(int arr[], int size), int size)
{
    int arr[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100;
    }

    clock_t begin = clock();

    sort(arr, size);

    printf("time: %lf\n", (double)(clock() - begin) / CLOCKS_PER_SEC);

    --size;
    for (int i = 0; i < size; i++)
    {
        printf("%i, ", arr[i]);
    }
    printf("%i", arr[size]);
}

int main()
{
    play(bubleSort, 5000);
}