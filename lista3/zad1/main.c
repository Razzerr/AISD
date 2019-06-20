#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


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
//function for creating rows for results
double *createResultTemplate() {
    double *temp = malloc(5 * sizeof(double));
    for (int i = 0; i < 5; i++) {
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
            cs[1]++;
            toSort[pos] = toSort[pos - 1];
            pos--;
        }
        cs[0]++;
        cs[1]++;
        toSort[pos] = val;
    }
    cs[2]+=3*sizeof(int);
}

void countSort(int *toSort, int n, int *flag, int *cs, int exp) {
    int output[n]; // output array
    int i, count[10] = {0};

    for (i = 0; i < n; i++)
        count[(toSort[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[--count[(toSort[i] / exp) % 10]] = toSort[i];
    }

    for (i = 0; i < n; i++) {
	toSort[i] = output[i];
	cs[1]++;
    }
    
    cs[2]+=sizeof(int) + sizeof(count) + sizeof(output);
}

void radixSort(int *toSort, int n, int *flag, int *cs){
    int temp[n];
    int max = toSort[0];
    for (int i = 1; i < n; i++){
        if (toSort[i] > max) max = toSort[i];
    }

    for (int exp = 1; max/exp > 0; exp *= 10)
        countSort(toSort, n, flag, cs, exp);

    if (*flag == 1){
        for (int i = 0; i < n; i++){
            temp[i] = toSort[i];
        }
        for (int i = 0; i < n; i++){
            toSort[i] = temp[n-1-i];
        }
	cs[2]+=2*sizeof(int) + sizeof(temp);
    }
    cs[2]+=3*sizeof(int);
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
        //knowing that both R and L are sorted, we put them back in the array by comparing the "top" elements
        while (i < ls && j < rs) {
            cs[0]++;
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
	cs[2]+=6*sizeof(int) + sizeof(L) + sizeof(R);
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
	    cs[2]+=sizeof(int);
            swap(toSort, j, ++i);
        }
    }
    cs[1]++;
    //swap pivot and index i so that the array is 'sorted' [comp(p, j), p, comp(j, p)]
    swap(toSort, p, i);
    cs[2]+=sizeof(t) + 3*sizeof(int);
    return i;
}

void quickSort(int *toSort, int n, int *flag, int *cs, int p, int q) {
    if (p < q) {
        //pivot is sorted, so we sort on the left and right of it
        int pivot = partition(toSort, n, flag, cs, p, q);
        quickSort(toSort, n, flag, cs, p, pivot - 1);
        quickSort(toSort, n, flag, cs, pivot + 1, q);
	cs[2]+=sizeof(int);
    }
}

void statMain(char *filename, int k){
    //initial variables
    int flag = 0;
    int cs[] = {0, 0, 0};
    clock_t start, end;
    //lists for results
    double **insertResults = malloc(9*sizeof(double*));
    double **mergeResults = malloc(9*sizeof(double*));
    double **quickResults = malloc(9*sizeof(double*));
    double **radixResults = malloc(9*sizeof(double*));
    for (int i = 0; i<9; i++){
        insertResults[i] = createResultTemplate();
        mergeResults[i] = createResultTemplate();
        quickResults[i] = createResultTemplate();
        radixResults[i] = createResultTemplate();
    }
    //datasize = [100, 10000]
    int n[] = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000};
    for (int h = 0; h<k; h++){
	for (int index = 0; index < 9; index++){
	    int j = n[index];
            int *list = randomList(j);
            int *worklist = malloc(j*sizeof(int));

            memcpy(worklist, list, j* sizeof(int));
            cs[0] = 0; cs[1] = 0; cs[2] = 0;
            start = clock();
            insertionSort(worklist, j, &flag, cs);
            end = clock();
            insertResults[index][0] = j;
            insertResults[index][1] += cs[0];
            insertResults[index][2] += cs[1];
            insertResults[index][3] += ((double) (end - start)) / CLOCKS_PER_SEC;
	    insertResults[index][4] += cs[2];

            memcpy(worklist, list, j* sizeof(int));
            cs[0] = 0; cs[1] = 0; cs[2] = 0;
            start = clock();
            mergeSort(worklist, j, &flag, cs, 0, j-1);
            end = clock();
            mergeResults[index][0] = j;
            mergeResults[index][1] += cs[0];
            mergeResults[index][2] += cs[1];
            mergeResults[index][3] += ((double) (end - start)) / CLOCKS_PER_SEC;
	    mergeResults[index][4] += cs[2];

            memcpy(worklist, list, j* sizeof(int));
            cs[0] = 0; cs[1] = 0; cs[2] = 0;
            start = clock();
            quickSort(worklist, j, &flag, cs, 0, j-1);
            end = clock();
            quickResults[index][0] = j;
            quickResults[index][1] += cs[0];
            quickResults[index][2] += cs[1];
            quickResults[index][3] += ((double) (end - start)) / CLOCKS_PER_SEC;
	    quickResults[index][4] += cs[2];

            memcpy(worklist, list, j* sizeof(int));
            cs[0] = 0; cs[1] = 0; cs[2] = 0;
            start = clock();
            radixSort(worklist, j, &flag, cs);
            end = clock();
            radixResults[index][0] = j;
            radixResults[index][1] += cs[0];
            radixResults[index][2] += cs[1];
            radixResults[index][3] += ((double) (end - start)) / CLOCKS_PER_SEC;
	    radixResults[index][4] += cs[2];

	    free(list);
	    free(worklist);
        }
    }
    //Writing to a file
    FILE *f = fopen(filename, "w");
    if (f == NULL){
        printf("You screwed!");
    } else {
        for (int i = 0; i < 9; i++) {
            fprintf(f, "insert, %f, %f, %f, %f, %f\n", insertResults[i][0], insertResults[i][1]/k, insertResults[i][2]/k,
                    insertResults[i][3]/k, insertResults[i][4]/k);
            fprintf(f, "merge, %f, %f, %f, %f, %f\n", mergeResults[i][0], mergeResults[i][1]/k, mergeResults[i][2]/k,
                    mergeResults[i][3]/k, mergeResults[i][4]/k);
            fprintf(f, "quick, %f, %f, %f, %f, %f\n", quickResults[i][0], quickResults[i][1]/k, quickResults[i][2]/k,
                    quickResults[i][3]/k, quickResults[i][4]/k);
            fprintf(f, "radix, %f, %f, %f, %f, %f\n", radixResults[i][0], radixResults[i][1]/k, radixResults[i][2]/k,
                    radixResults[i][3]/k, radixResults[i][4])/k;
        }
    }
    fclose(f);
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
            } else if (!strcmp(argv[i + 1], "radix")) {
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
        } else if (!strcmp(argv[i], "--stat") && argc > i+2){
            char* ptr;
            statMain(argv[i+1], (int)strtol(argv[i+2], &ptr, 10));
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
            radixSort(list, n, &compflag, cs);
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
}
