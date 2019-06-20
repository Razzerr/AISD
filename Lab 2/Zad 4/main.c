/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//swaping elements on a list
void swapChar(char **list, int idx1, int idx2) {
    //switching(list[idx1], list[idx2]);
    char *temp = list[idx1];
    list[idx1] = list[idx2];
    list[idx2] = temp;
}

//function for comparing based on flag
int comp_char(char *a, char *b, int *flag) {
    switch (*flag) {
        case 0:
            for (int i = 0; i < __min(sizeof(a) / sizeof(char), sizeof(b) / sizeof(char)); i++) {
                if (a[i] < b[i]) return 1;
                else if (a[i] > b[i]) return 0;
            }
            return 1;
        case 1:
            for (int i = 0; i < __min(sizeof(a) / sizeof(char), sizeof(b) / sizeof(char)); i++) {
                if (a[i] > b[i]) return 1;
                else if (a[i] < b[i]) return 0;
            }
            return 0;
        default:
            fprintf(stderr, "Unexpected error occurred.");
            exit;
    }
}

//quick check for sorted data
int isSortedChar(char **list, int n, int *flag) {
    for (int i = 1; i < n; i++) {
        if (comp_char(list[i - 1], list[i], flag)) return 0;
    }
    return 1;
}

//swaping elements on a list
void swap(int *list, int idx1, int idx2){
    //switching(list[idx1], list[idx2]);
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
        case 0:
            for (int i = 1; i < n; i++) {
                if (list[i - 1] < list[i]) return 0;
            }
            break;
        case 1:
            for (int i = 1; i < n; i++) {
                if (list[i - 1] > list[i]) return 0;
            }
            break;
    }
    return 1;
}
//function for creating rows for results

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
        list[i] = rand()%1000;
    }
    return list;
}

void insertionSortChar(char **toSort, int n, int *flag, int *cs) {
    //for every element in the array
    for (int i = 0; i < n; i++) {
        char *val = toSort[i];
        int pos = i;
        //as long as current element is not yet where it should be
        while (pos > 0 && comp_char(toSort[pos - 1], val, flag) == 1) {
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

void mergeSortChar(char **toSort, int n, int *flag, int *cs, int p, int q) {
    //p - start of toSort, q - end of toSort (for current recursion)
    if (p < q) {
        int mid = (q + p) / 2;
        //splitting elements to singletons
        mergeSortChar(toSort, n, flag, cs, p, mid);
        mergeSortChar(toSort, n, flag, cs, mid + 1, q);

        int i, j, k;
        int ls = mid - p + 1;
        int rs = q - mid;

        char* L[ls];
        char *R[rs];
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
        //Knowing that both R and L are sorted, we put them back in the array by comp_chararing the "top" elements
        while (i < ls && j < rs) {
            cs[0]++;
            if (comp_char(R[j], L[i], flag) == 1) {
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

int partitionChar(char **toSort, int n, int *flag, int *cs, int p, int q) {
    time_t t;
    srand((unsigned) time(&t));
    //choosing random pivot
    int i = p + rand() % (q - p + 1);
    //putting pivot on the beginning of toSort array
    cs[1]++;
    swapChar(toSort, p, i);

    i = p;
    //if any element is "out of order" then put it on the right of pivot and mark it with 'i'
    for (int j = i + 1; j < q + 1; j++) {
        cs[0]++;
        if (comp_char(toSort[p], toSort[j], flag) == 1) {
            cs[1]++;
            swapChar(toSort, j, ++i);
        }
    }
    cs[1]++;
    //swap pivot and index i so that the array is 'sorted' [comp_char(p, j), p, comp_char(j, p)]
    swapChar(toSort, p, i);
    return i;
}

void quickSortChar(char **toSort, int n, int *flag, int *cs, int p, int q) {
    if (p < q) {
        //pivot is sorted, so we sort on the left and right of it
        int pivot = partitionChar(toSort, n, flag, cs, p, q);
        quickSortChar(toSort, n, flag, cs, p, pivot - 1);
        quickSortChar(toSort, n, flag, cs, pivot + 1, q);
    }
}

void hybridChar(char **toSort, int n, int *flag, int *cs, int p, int q) {
    if (q - p < 50) {
        char ***wlist = malloc((q - p + 1) * sizeof(char **));
        int j = 0;
        for (int i = p; i <= q; i++) {
            wlist[j] = malloc(sizeof(char**));
            wlist[j] = &toSort[i];
            j++;
        }
        insertionSortChar(*wlist, q - p + 1, flag, cs);
        free(wlist);
    } else {
        int pivot = partitionChar(toSort, n, flag, cs, p, q);
        hybridChar(toSort, n, flag, cs, p, pivot - 1);
        hybridChar(toSort, n, flag, cs, pivot + 1, q);
    }
}

void insertionSort(int *toSort, int n, int *flag, int *cs) {
    //for every element in the array
    for (int i = 0; i < n; i++) {
        int val = toSort[i];
        int pos = i;
        //as long as current element is not yet where it should be
        while (pos > 0 && comp( toSort[pos - 1], val, flag) == 1) {
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
            if (comp(R[j], L[i], flag) == 1) {
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
        if (comp(toSort[p], toSort[j], flag) == 1) {
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

void hybrid(int *toSort, int n, int *flag, int *cs, int p, int q) {
    if (q - p < 50) {
        int **wlist = malloc((q - p + 1) * sizeof(int *));
        int j = 0;
        for (int i = p; i <= q; i++) {
            wlist[j] = malloc(sizeof(int*));
            wlist[j] = &toSort[i];
            j++;
        }
        insertionSort(*wlist, q - p + 1, flag, cs);
        free(wlist);
    } else {
        int pivot = partition(toSort, n, flag, cs, p, q);
        hybrid(toSort, n, flag, cs, p, pivot - 1);
        hybrid(toSort, n, flag, cs, pivot + 1, q);
    }
}

void statMain(char *filename, int k) {
    //initial variables
    int flag = 0;
    int cs[] = {0, 0};
    clock_t start, end;
    //lists for results
    double **insertResults = malloc(100 * sizeof(double *));
    double **mergeResults = malloc(100 * sizeof(double *));
    double **quickResults = malloc(100 * sizeof(double *));
    double **hybridResults = malloc(100 * sizeof(double *));
    for (int i = 0; i < 100; i++) {
        insertResults[i] = createResultTemplate();
        mergeResults[i] = createResultTemplate();
        quickResults[i] = createResultTemplate();
        hybridResults[i] = createResultTemplate();
    }
    //k iterations
    for (int i = 0; i < k; i++) {
        //datasize = [1, 100]
        for (int j = 1; j < 101; j++) {
            int *list = randomList(j);
            int *worklist = malloc(j*sizeof(int));

            memcpy(worklist, list, j*sizeof(int));
            cs[0] = 0;
            cs[1] = 0;
            start = clock();
            insertionSort(worklist, j, &flag, cs);
            end = clock();
            insertResults[j - 1][0] = j;
            insertResults[j - 1][1] += cs[0];
            insertResults[j - 1][2] += cs[1];
            insertResults[j - 1][3] += ((double) (end - start)) / CLOCKS_PER_SEC;

            memcpy(worklist, list, j*sizeof(int));
            cs[0] = 0;
            cs[1] = 0;
            start = clock();
            mergeSort(worklist, j, &flag, cs, 0, j - 1);
            end = clock();
            mergeResults[j - 1][0] = j;
            mergeResults[j - 1][1] += cs[0];
            mergeResults[j - 1][2] += cs[1];
            mergeResults[j - 1][3] += ((double) (end - start)) / CLOCKS_PER_SEC;

            memcpy(worklist, list, j*sizeof(int));
            cs[0] = 0;
            cs[1] = 0;
            start = clock();
            quickSort(worklist, j, &flag, cs, 0, j - 1);
            end = clock();
            quickResults[j - 1][0] = j;
            quickResults[j - 1][1] += cs[0];
            quickResults[j - 1][2] += cs[1];
            quickResults[j - 1][3] += ((double) (end - start)) / CLOCKS_PER_SEC;

            memcpy(worklist, list, j*sizeof(int));
            cs[0] = 0;
            cs[1] = 0;
            start = clock();
            hybrid(worklist, j, &flag, cs, 0, j - 1);
            end = clock();
            hybridResults[j - 1][0] = j;
            hybridResults[j - 1][1] += cs[0];
            hybridResults[j - 1][2] += cs[1];
            hybridResults[j - 1][3] += ((double) (end - start)) / CLOCKS_PER_SEC;
        }
    }
    //Writing to a file
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("You screwed!");
    } else {
        for (int i = 0; i < 100; i++) {
            fprintf(f, "insert, %f, %f, %f, %f\n", insertResults[i][0], insertResults[i][1] / k,
                    insertResults[i][2] / k,
                    insertResults[i][3] / k);
            fprintf(f, "merge, %f, %f, %f, %f\n", mergeResults[i][0], mergeResults[i][1] / k, mergeResults[i][2] / k,
                    mergeResults[i][3] / k);
            fprintf(f, "quick, %f, %f, %f, %f\n", quickResults[i][0], quickResults[i][1] / k, quickResults[i][2] / k,
                    quickResults[i][3] / k);
            fprintf(f, "hybrid, %f, %f, %f, %f\n", hybridResults[i][0], hybridResults[i][1] / k,
                    hybridResults[i][2] / k,
                    hybridResults[i][3] / k);
        }
    }
    fclose(f);
}

int main(int argc, char *argv[]) {
    //sorttype: 0 - insert, 1 - merge, 2 - quick, 3 - hybrid
    int compflag = 0, sorttype = 0, datatype = 0;
    //"menu" for switching arguments
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--type") && argc > i + 1) {
            if (!strcmp(argv[i + 1], "insert")) {
                sorttype = 0;
            } else if (!strcmp(argv[i + 1], "merge")) {
                sorttype = 1;
            } else if (!strcmp(argv[i + 1], "quick")) {
                sorttype = 2;
            } else if (!strcmp(argv[i + 1], "hybrid")) {
                sorttype = 3;
            } else {
                fprintf(stderr, "Wrong '--type' argument given: %s", argv[i + 1]);
                return -1;
            }
        } else if (!strcmp(argv[i], "--comp") && argc > i + 1) {
            if (!strcmp(argv[i + 1], "\'>=\'")) {
                compflag = 0;
            } else if (!strcmp(argv[i + 1], "\'<=\'")) {
                compflag = 1;
            } else {
                fprintf(stderr, "Wrong '--comp' argument given: %s", argv[i + 1]);
                return -1;
            }
        } else if (!strcmp(argv[i], "--data") && argc > i + 1) {
            if (!strcmp(argv[i + 1], "int")) {
                datatype = 0;
            } else if (!strcmp(argv[i + 1], "str")) {
                datatype = 1;
            } else {
                fprintf(stderr, "Wrong '--data' argument given: %s", argv[i + 1]);
                return -1;
            }
        } else if (!strcmp(argv[i], "--stat") && argc > i + 2) {
            char *ptr;
            statMain(argv[i + 1], (int) strtol(argv[i + 2], &ptr, 10));
            return 0;
        }
    }
    //initializing variables for measurements
    int cs[] = {0, 0};
    clock_t start, end;

    if (datatype == 1) {
        int n;
        char **list;
        scanf("%i", &n);
        list = malloc(n * sizeof(char *));
        for (int i = 0; i < n; i++) {
            list[i] = malloc(sizeof(char *));
            scanf("%s", list[i]);
        }

        switch (sorttype) {
            case 0:
                start = clock();
                insertionSortChar(list, n, &compflag, cs);
                end = clock();
                break;
            case 1:
                start = clock();
                mergeSortChar(list, n, &compflag, cs, 0, n - 1);
                end = clock();
                break;
            case 2:
                start = clock();
                quickSortChar(list, n, &compflag, cs, 0, n - 1);
                end = clock();
                break;
            case 3:
                start = clock();
                hybridChar(list, n, &compflag, cs, 0, n - 1);
                end = clock();
                break;
        }
        for (int i = 0; i < n; i++) {
            printf("%s ", list[i]);
        }
    } else if (datatype == 0){
        int n, *list;
        scanf("%i", &n);
        list = malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%i", &list[i]);
        }

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
                hybrid(list, n, &compflag, cs, 0, n-1);
                break;
        }
        for (int i = 0; i < n; i++) {
            printf("%i ", list[i]);
        }
    }

    return 0;
}*/