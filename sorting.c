#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// 데이터 바꾸기
void swap(int a[], int b, int c)
{
    int temp = a[b];
    a[b] = a[c];
    a[c] = temp;
};

// 데이터 삽입
int *InsertData(int *arr, int size, char *command)
{
    srand((unsigned)time(NULL));
    if (!strcmp(command, "random"))
    {
        for (int i = 0; i < size; i++)
        {
            arr[i] = (rand() << 7 | rand()) % size + 1;
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            arr[i] = i;
        }
    }
    return arr;
}

// - 정렬알고리즘
// 1. bubble sort
void bubbleSort(int a[], int n)
{
    int swapped = 1;
    for (int scope = n - 1; scope > 0 && swapped; scope--)
    {
        swapped = 0;
        for (int i = 0; i < scope; i++)
        {
            if (a[i] > a[i + 1])
            {
                swap(a, i, i + 1);
                swapped = 1;
            }
        }
    }
}

// 2. selection sort
void selectionSort(int a[], int n)
{
    int min_index, i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        min_index = i;
        for (j = i + 1; j < n; j++)
        {
            if (a[min_index] > a[j])
            {
                min_index = j;
            }
        }
        swap(a, i, min_index);
    }
}

// 3. insertion sort
void insertionSort(int a[], int n)
{
    int i, j, key;
    for (i = 1; i < n; i++)
    {
        key = a[i];
        j = i - 1;
        while (key < a[j] && j >= 0)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

// 4. merge sort
void Merge(int a[], int temp[], int left, int right, int right_end)
{
    int i, j, left_end, size, temp_pos;
    left_end = right - 1;
    size = right_end - left + 1;
    i = left;
    j = right;
    temp_pos = left;

    while ((i <= left_end) && (j <= right_end))
    {
        if (a[i] <= a[j])
        {
            temp[temp_pos++] = a[i];
            i += 1;
        }
        else
        {
            temp[temp_pos++] = a[j];
            j += 1;
        }
    }
    while (i <= left_end)
    {
        temp[temp_pos++] = a[i];
        i += 1;
    }
    while (j <= right_end)
    {
        temp[temp_pos++] = a[j];
        j += 1;
    }

    for (i = left; i <= right_end; i++)
    {
        a[i] = temp[i];
    }
}
void Mergesort(int a[], int temp[], int left, int right)
{
    int mid;
    if (left < right)
    {
        mid = (left + right) / 2;
        Mergesort(a, temp, left, mid);
        Mergesort(a, temp, mid + 1, right);
        Merge(a, temp, left, mid + 1, right);
    }
}

// 5. quick sort
int partition(int a[], int left, int right)
{
    int low, high, pivot_val = a[left];
    low = left;
    high = right;
    while (low < high)
    {
        while (low <= right && a[low] <= pivot_val)
        {
            low++;
        }
        while (high >= left && a[high] > pivot_val)
        {
            high--;
        }
        if (low < high)
        {
            swap(a, low, high);
        }
    }
    a[left] = a[high];
    a[high] = pivot_val;
    return high;
}
void quickSort(int a[], int left, int right)
{
    if (left < right)
    {
        int fixed = partition(a, left, right);
        quickSort(a, left, fixed - 1);
        quickSort(a, fixed + 1, right);
    }
}

// 6. Randomized quick sort
int Rpartition(int a[], int left, int right)
{
    // random index
    srand((unsigned)time(NULL));
    int random = ((rand() << 7 | rand()) % right) + 1;
    int low, high, pivot_val = a[random];
    swap(a, random, left);
    low = left;
    high = right;

    while (low < high)
    {
        while (low <= right && a[low] <= pivot_val)
        {
            low++;
        }
        while (high >= left && a[high] > pivot_val)
        {
            high--;
        }
        if (low < high)
        {
            swap(a, low, high);
        }
    }
    a[left] = a[high];
    a[high] = pivot_val;
    return high;
}

void RquickSort(int a[], int left, int right)
{
    if (left < right)
    {
        int fixed = Rpartition(a, left, right);
        quickSort(a, left, fixed - 1);
        quickSort(a, fixed + 1, right);
    }
}

// (0) 정렬 알고리즘 정확성 체크
void checkSort(int size)
{
    int *arr1 = (int *)malloc(sizeof(int) * size);
    int *arr2 = (int *)malloc(sizeof(int) * size);
    int *arr3 = (int *)malloc(sizeof(int) * size);
    int *arr4 = (int *)malloc(sizeof(int) * size);
    int *arr5 = (int *)malloc(sizeof(int) * size);
    int *temp = (int *)malloc(sizeof(int) * size);

    arr1 = InsertData(arr1, size, "random");

    for (int i = 0; i < size; i++)
    {
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
        arr4[i] = arr1[i];
        arr5[i] = arr1[i];
    }

    bubbleSort(arr1, size);
    selectionSort(arr2, size);
    insertionSort(arr3, size);
    Mergesort(arr4, temp, 0, size - 1);
    quickSort(arr5, 0, size - 1);

    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr1[i]);
    }
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr2[i]);
    }
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr3[i]);
    }
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr4[i]);
    }
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr5[i]);
    };

    free(arr1);
    free(arr2);
    free(arr3);
    free(arr4);
    free(arr5);
    free(temp);
}

// (1) 정렬알고리즘 시간측정
void DataSort(int size, char *numOfQuestion)
{
    int *arr1 = (int *)malloc(sizeof(int) * size);
    int *arr2 = (int *)malloc(sizeof(int) * size);
    int *arr3 = (int *)malloc(sizeof(int) * size);
    int *arr4 = (int *)malloc(sizeof(int) * size);
    int *arr5 = (int *)malloc(sizeof(int) * size);
    int *arr6 = (int *)malloc(sizeof(int) * size);
    int *temp = (int *)malloc(sizeof(int) * size);
    clock_t start, end;

    if (!strcmp(numOfQuestion, "(1)"))
    {
        arr1 = InsertData(arr1, size, "random");
    }
    else
    {
        arr1 = InsertData(arr1, size, "NoRandom");
    }

    for (int i = 0; i < size; i++)
    {
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
        arr4[i] = arr1[i];
        arr5[i] = arr1[i];
        arr6[i] = arr1[i];
    }

    start = clock();
    bubbleSort(arr1, size);
    end = clock();
    printf("\nbubble sort: %ld ms\n", end - start);

    start = clock();
    selectionSort(arr2, size);
    end = clock();
    printf("selection sort: %ld ms\n", end - start);

    start = clock();
    insertionSort(arr3, size);
    end = clock();
    printf("insertion sort: %ld ms\n", end - start);

    start = clock();
    Mergesort(arr4, temp, 0, size - 1);
    end = clock();
    printf("merge sort: %ld ms\n", end - start);

    start = clock();
    quickSort(arr5, 0, size - 1);
    end = clock();
    printf("quick sort: %ld ms\n", end - start);

    if (!strcmp(numOfQuestion, "(2)"))
    {
        start = clock();
        RquickSort(arr6, 0, size - 1);
        end = clock();
        printf("randomized quick sort: %ld ms\n", end - start);
    }

    free(arr1);
    free(arr2);
    free(arr3);
    free(arr4);
    free(arr5);
    free(arr6);
    free(temp);
}

int main(void)
{
    // (0) 정렬 알고리즘 정확성 체크(arr size = 30)
    checkSort(30);

    // (1) 랜덤데이터, 정렬 수행시간 측정
    for (int i = 10000; i <= 10000 * 10; i += 10000)
    {
        DataSort(i, "(1)");
    };

    // (2) 정렬된 데이터, 정렬 수행시간 측정
    for (int i = 10000; i <= 10000 * 10; i += 10000)
    {
        DataSort(i, "(2)");
    };

    return 0;
}

// ?
// 1. merge, quick 랜덤 데이터를 받을 경우, 둘 다 O(logn)이지만 quick이 근소하게 더 빠르다
// 이유 ? merge sort는 in-place 정렬이 아니라 추가 공간을 필요로 하며, 이에 따른 추가 연산이 수행되기에

// 2.하지만 quick은 정렬 데이터를 받을 경우, O(n2)을 나타낸다.
// 근데 왜 현실에선 quick sort를 많이 이용할까?
// 정렬의 과정을 거치지 않아도, 좋은 성능을 내기 때문.

// ?　
// heap sort도 구현해서 측정해보기 **
// 예상 ? heapify 하는 연산때문에 quick보단 느릴 것으로 생각.
