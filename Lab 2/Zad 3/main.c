/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//swaping elements on a list
void swap(int *list, int idx1, int idx2){
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
//function for creating rows for results
double *createResultTemplate() {
    double *temp = malloc(4 * sizeof(double));
    for (int i = 0; i < 4; i++) {
        temp[i] = 0;
    }
    return temp;
}
//generating random list of size n
int *randomList(int n) {
    int *list = malloc(n * sizeof(int));
    time_t t;
    srand((unsigned) time(&t));
    for (int i = 0; i < n; i++) {
        list[i] = rand() % 1000;
    }
    return list;
}

void insertionSort(int *toSort, int n, int *flag, int *cs) {
    //for every element in the array
    for (int i = 0; i < n; i++) {
        int val = toSort[i];
        int pos = i;
        //as long as current element is not yet where it should be
        while (pos > 0 && comp(val, toSort[pos - 1], flag) == 1) {
            cs[0]++;
            cs[1]++;
            toSort[pos] = toSort[pos - 1];
            pos--;
        }
        cs[0]++;
        cs[1]++;
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
            if (comp( L[i], R[j], flag) == 1) {
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

int *DPQSp(int *toSort, int n, int *flag, int *cs, int p, int q) {
    time_t t;
    srand((unsigned) time(&t));

    int i1 = p + rand() % (q - p+1);
    int i2 = p + rand() % (q - p+1);
    while (i2 == i1) {
        i2 = p + rand() % (q - p+1);
    }

    cs[1]+=2;
    swap(toSort, p, i1);
    swap(toSort, q, i2);
    //if pivots chosen in opposite order
    if (comp(toSort[q], toSort[p], flag) == 1) {
        swap(toSort, p, q);
    }

    i1 = p;
    i2 = q;
    int j = i1 + 1;
    while (j < i2) {
        //count strategy
        if (q - i2 > i1 - p) {
            cs[0] += 2;
            if (comp(toSort[q], toSort[j], flag) == 1) {
                cs[0]--; cs[1]++;
                swap(toSort, j, --i2);
            } else if (comp(toSort[j], toSort[p], flag) == 1) {
                cs[1]++;
                swap(toSort, j, ++i1);
                j++;
            } else {
                j++;
            }
        } else {
            cs[0] += 2;
            if (comp(toSort[j], toSort[p], flag) == 1) {
                cs[0]--; cs[1]++;
                swap(toSort, j, ++i1);
                j++;
            } else if (comp(toSort[q], toSort[j], flag) == 1) {
                cs[1]++;
                swap(toSort, j, --i2);
            } else {
                j++;
            }
        }
    }
    cs[1]+=2;
    swap(toSort, p, i1);
    swap(toSort, q, i2);

    int *pivots = malloc(sizeof(int) * 2);
    pivots[0] = i1;
    pivots[1] = i2;
    return pivots;
}

void DPQS(int *toSort, int n, int *flag, int *cs, int p, int q) {
    if (p < q) {
        int *pivot = DPQSp(toSort, n, flag, cs, p, q);
        DPQS(toSort, n, flag, cs, p, pivot[0] - 1);
        DPQS(toSort, n, flag, cs, pivot[0] + 1, pivot[1] - 1);
        DPQS(toSort, n, flag, cs, pivot[1] + 1, q);
    }
}

void statMain(char *filename, int k) {
    //initial variables
    int flag = 0;
    int cs[] = {0, 0};
    clock_t start, end;
    //lists for results
    double **dpqsResults = malloc(100 * sizeof(double *));
    double **quickResults = malloc(100 * sizeof(double *));
    for (int i = 0; i < 100; i++) {
        dpqsResults[i] = createResultTemplate();
        quickResults[i] = createResultTemplate();
    }

    //k iterations
    for (int i = 0; i<k; i++){
        //datasize = [100, 10000]
        printf("Iteration: %i\n", i);
        for (int j = 100; j < 10001; j += 100) {
            int *list = randomList(j);
            int *worklist = malloc(j * sizeof(int));

            memcpy(worklist, list, j * sizeof(int));
            cs[0] = 0;
            cs[1] = 0;
            start = clock();
            DPQS(worklist, j, &flag, cs, 0, j-1);
            end = clock();
            dpqsResults[(j / 100) - 1][0] = j;
            dpqsResults[(j / 100) - 1][1] += cs[0];
            dpqsResults[(j / 100) - 1][2] += cs[1];
            dpqsResults[(j / 100) - 1][3] += ((double) (end - start)) / CLOCKS_PER_SEC;

            memcpy(worklist, list, j * sizeof(int));
            cs[0] = 0;
            cs[1] = 0;
            start = clock();
            quickSort(worklist, j, &flag, cs, 0, j - 1);
            end = clock();
            quickResults[(j / 100) - 1][0] = j;
            quickResults[(j / 100) - 1][1] += cs[0];
            quickResults[(j / 100) - 1][2] += cs[1];
            quickResults[(j / 100) - 1][3] += ((double) (end - start)) / CLOCKS_PER_SEC;
        }
    }
    //Writing to a file
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("You screwed!");
    } else {
        for (int i = 0; i < 100; i++) {
            fprintf(f, "dpqs, %f, %f, %f, %f\n", dpqsResults[i][0], dpqsResults[i][1] / k,
                    dpqsResults[i][2] / k,
                    dpqsResults[i][3] / k);
            fprintf(f, "quick, %f, %f, %f, %f\n", quickResults[i][0], quickResults[i][1] / k, quickResults[i][2] / k,
                    quickResults[i][3] / k);
        }
    }
    fclose(f);
}

int main(int argc, char *argv[]) {
    //sorttype: 0 - insert, 1 - merge, 2 - quick, 3 - dpqs
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
            } else if (!strcmp(argv[i + 1], "dpqs")) {
                sorttype = 3;
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
        } else if (!strcmp(argv[i], "--stat") && argc > i + 2) {
            char *ptr;
            statMain(argv[i + 1], (int) strtol(argv[i + 2], &ptr, 10));
            return 0;
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
        case 3:
            start = clock();
            DPQS(list, n, &compflag, cs, 0, n - 1);
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