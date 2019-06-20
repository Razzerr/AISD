/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void comparing(int val1, int val2) {
    fprintf(stderr, "Comparing %i with %i\n", val1, val2);
    return;
}

void switching(int val1, int val2) {
    fprintf(stderr, "Switching %i with %i\n", val1, val2);
    return;
}
//swaping elements on a list
void swap(int *list, int idx1, int idx2){
    switching(list[idx1], list[idx2]);
    int temp = list[idx1];
    list[idx1] = list[idx2];
    list[idx2] = temp;
}
//function for comparing based on flag
int comp(int a, int b, int *flag) {
    switch (*flag) {
        case 0:
            return (a <= b ? 1 : 0);
        case 1:
            return (a >= b ? 1 : 0);
        default:
            fprintf(stderr, "Unexpected error occurred.");
            exit;
    }
}
//quick check for sorted data
int isSorted(int *list, int n, int *flag) {
    switch (*flag) {
        case 1:
            for (int i = 1; i < n; i++) {
                if (list[i - 1] < list[i]) return 0;
            }
            break;
        case 0:
            for (int i = 1; i < n; i++) {
                if (list[i - 1] > list[i]) return 0;
            }
            break;
    }
    return 1;
}

void insertionSort(int *toSort, int n, int *flag, int *cs) {
    //for every element in the array
    for (int i = 0; i < n; i++) {
        int val = toSort[i];
        int pos = i;
        //as long as current element is not yet where it should be
        while (pos > 0 && comp(val, toSort[pos - 1], flag) == 1) {
            cs[0]++;
            comparing(val, toSort[pos-1]);
            cs[1]++;
            switching(val, toSort[pos-1]);
            toSort[pos] = toSort[pos - 1];
            pos--;
        }
        comparing(val, toSort[pos-1]);
        cs[0]++;
        cs[1]++;
        switching(val, toSort[pos]);
        toSort[pos] = val;
    }
}

void mergeSort(int *toSort, int n, int *flag, int *cs, int p, int q) {
    //p - start of toSort, q - end of toSort (for current recursion)
    if (p < q) {
        int mid = (q + p) / 2;
        //splitting elements to singletons
        mergeSort(toSort, n, flag, cs, p, mid);
        mergeSort(toSort, n, flag, cs, mid + 1, q);

        int i, j, k;
        int ls = mid - p + 1;
        int rs = q - mid;

        int L[ls], R[rs];
        //creating temporary arrays for left and right half
        for (i = 0; i < ls; i++) {
            L[i] = toSort[p + i];
        }
        for (j = 0; j < rs; j++) {
            R[j] = toSort[mid + 1 + j];
        }

        i = 0;
        j = 0;
        k = p;
        //Knowing that both R and L are sorted, we put them back in the array by comparing the "top" elements
        while (i < ls && j < rs) {
            cs[0]++;
            comparing(R[j], L[i]);
            if (comp(L[i], R[j], flag) == 1) {
                toSort[k] = L[i];
                i++;
            } else {
                toSort[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < ls) {
            toSort[k] = L[i];
            i++;
            k++;
        }

        while (j < rs) {
            toSort[k] = R[j];
            j++;
            k++;
        }
    }
}

int partition(int *toSort, int n, int *flag, int *cs, int p, int q) {
    time_t t;
    srand((unsigned) time(&t));
    //choosing random pivot
    int i = p + rand() % (q - p + 1);
    //putting pivot on the beginning of toSort array
    cs[1]++;
    swap(toSort, p, i);

    i = p;
    //if any element is "out of order" then put it on the right of pivot and mark it with 'i'
    for (int j = i + 1; j < q + 1; j++) {
        cs[0]++;
        comparing(toSort[p], toSort[j]);
        if (comp(toSort[j], toSort[p], flag) == 1) {
            cs[1]++;
            swap(toSort, j, ++i);
        }
    }
    cs[1]++;
    //swap pivot and index i so that the array is 'sorted' [comp(p, j), p, comp(j, p)]
    swap(toSort, p, i);
    return i;
}

void quickSort(int *toSort, int n, int *flag, int *cs, int p, int q) {
    if (p < q) {
        //pivot is sorted, so we sort on the left and right of it
        int pivot = partition(toSort, n, flag, cs, p, q);
        quickSort(toSort, n, flag, cs, p, pivot - 1);
        quickSort(toSort, n, flag, cs, pivot + 1, q);
    }
}

int main(int argc, char *argv[]) {
    //sorttype: 0 - insert, 1 - merge, 2 - quick
    int compflag = 0, sorttype = 0;
    //"menu" for switching arguments
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--type") && argc > i + 1) {
            if (!strcmp(argv[i + 1], "insert")) {
                sorttype = 0;
            } else if (!strcmp(argv[i + 1], "merge")) {
                sorttype = 1;
            } else if (!strcmp(argv[i + 1], "quick")) {
                sorttype = 2;
            } else {
                fprintf(stderr, "Wrong '--type' argument given: %s", argv[i + 1]);
                return -1;
            }
        } else if (!strcmp(argv[i], "--comp") && argc > i + 1) {
            if (!strcmp(argv[i + 1], "\'>=\'")) {
                compflag = 1;
            } else if (!strcmp(argv[i + 1], "\'<=\'")) {
                compflag = 0;
            } else {
                fprintf(stderr, "Wrong '--comp' argument given: %s", argv[i + 1]);
                return -1;
            }
        }
    }
    //scanning number of inputs, then inputs
    int n, *list;
    scanf("%i", &n);
    list = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%i", &list[i]);
    }
    //initializing variables for measurements
    int cs[] = {0, 0};
    clock_t start, end;

    switch (sorttype) {
        case 0:
            start = clock();
            insertionSort(list, n, &compflag, cs);
            end = clock();
            break;
        case 1:
            start = clock();
            mergeSort(list, n, &compflag, cs, 0, n - 1);
            end = clock();
            break;
        case 2:
            start = clock();
            quickSort(list, n, &compflag, cs, 0, n - 1);
            end = clock();
            break;
    }


    fprintf(stderr, "Is sorted: %i\nComparisons: %i\nSwitches: %i\nTime: %f", isSorted(list, n, &compflag), cs[0],
            cs[1],
            ((double) (end - start)) / CLOCKS_PER_SEC);

    //printing as specified by the task
    printf("%i\n", n);
    for (int i = 0; i < n; i++) {
        printf("%i ", list[i]);
    }
    return 0;
}*/