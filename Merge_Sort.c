#include <stdio.h>

void printArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void merge(int a[], int mid, int low, int high)
{
    int i, j, k, b[100];
    i = low;
    j = mid + 1;
    k = low;

    while (i <= mid && j <= high)
    {
        if (a[i] < a[j])
        {
            b[k] = a[i];
            i++;
            k++;
        }
        else
        {
            b[k] = a[j];
            j++;
            k++;
        }
    }

    while (i <= mid)
    {
        b[k] = a[i];
        i++;
        k++;
    }

    while (j <= high)
    {
        b[k] = a[j];
        j++;
        k++;
    }

    for (int i = low; i <= high; i++)
    {
        a[i] = b[i];
    }
}

void mergeSort(int a[], int low, int high)
{
    int mid;
    if (low < high)
    {
        mid = (low + high) / 2;
        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        merge(a, mid, low, high);
    }
}

int main()
{
    int n, choice;
    int a[100];

    do
    {
        printf("\nMenu:\n");
        printf("1. Enter size of array\n");
        printf("2. Enter elements in the array\n");
        printf("3. Perform Merge Sort\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter size of array: ");
            scanf("%d", &n);
            break;

        case 2:
            printf("Enter elements in the array\n");
            for (int i = 0; i < n; i++)
            {
                printf("a%d : ", i);
                scanf("%d", &a[i]);
            }
            printf("Original array\n");
            printArray(a, n);
            break;

        case 3:
            mergeSort(a, 0, n - 1);
            printf("Array after Merge Sort\n");
            printArray(a, n);
            break;

        case 4:
            printf("Exiting the program.\n");
            break;

        default:
            printf("Invalid choice\n");
        }

    } while (choice != 4);

    return 0;
}


