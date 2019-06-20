#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void swap(int *list, int idx1, int idx2){
    //switching(list[idx1], list[idx2]);
    int temp = list[idx1];
    list[idx1] = list[idx2];
    list[idx2] = temp;
}

int *randomList(int n) {
    int *list = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        list[i] = rand() % 1000;
    }
    return list;
}

int *permutedList(int n) {
    int *list = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        list[i] = i+1;
    }
    for (int i = n-1; i > 0; i--){
        int j = rand() % (i+1);
        swap(list, i, j);
    }

    return list;
}


int partition(int *toSort, int p, int q, int *cs) {
    int i = p + rand() % (q - p + 1);
    cs[1]++;
    fprintf(stderr, "\n Switching A[%i] = %i with A[%i] = %i", p, toSort[p], i, toSort[i]);
    swap(toSort, p, i);
    fprintf(stderr, "\n Pivot = %i", toSort[p]);

    i = p;
    for (int j = i + 1; j < q + 1; j++) {
        cs[0]++;
        fprintf(stderr, "\n Comparing A[%i] = %i with A[%i] = %i", j, toSort[j], p, toSort[p]);
        if (toSort[j] < toSort[p]) {
            cs[1]++;
            fprintf(stderr, "\n Switching A[%i] = %i with A[%i] = %i", j, toSort[j], i+1, toSort[i+1]);
            swap(toSort, j, ++i);
        }
    }
    cs[1]++;
    fprintf(stderr, "\n Switching A[%i] = %i with A[%i] = %i", p, toSort[p], i, toSort[i]);
    swap(toSort, p, i);
    return i;
}

int RAND_SELECT(int *A, int p, int q, int i, int *cs){
    fprintf(stderr, "\n\nRANDArray: ");
    for (int j = p; j<=q; j++){
        fprintf(stderr, "%i, ", A[j]);
    }
    fprintf(stderr, "\n k = %i ", i);
    if (p==q) return p;
    int r = partition(A, p, q, cs);
    int k = r - p + 1;
    if (i == k) return r;
    else if (i < k) return RAND_SELECT(A, p, r-1, i, cs);
    else return RAND_SELECT(A, r+1, q, i-k, cs);
}

int GET_MEDIAN(int *A, int p, int q, int *cs){
    return (RAND_SELECT(A, p, q, floor((q-p)/2)+1, cs));
}

int select_partition(int *toSort, int p, int q, int piv, int *cs) {
    fprintf(stderr, "\n Switching A[%i] = %i with A[%i] = %i", p, toSort[p], piv, toSort[piv]);
    swap(toSort, p, piv);
    cs[1]++;

    fprintf(stderr, "\n Pivot = %i", toSort[p]);
    int i = p;
    for (int j = i + 1; j < q + 1; j++) {
        cs[0]++;
        fprintf(stderr, "\n Comparing A[%i] = %i with A[%i] = %i", j, toSort[j], p, toSort[p]);
        if (toSort[j] < toSort[p]) {
            cs[1]++;
            fprintf(stderr, "\n Switching A[%i] = %i with A[%i] = %i", j, toSort[j], i+1, toSort[i+1]);
            swap(toSort, j, ++i);
        }
    }
    cs[1]++;
    fprintf(stderr, "\n Switching A[%i] = %i with A[%i] = %i", p, toSort[p], i, toSort[i]);
    swap(toSort, p, i);
    return i;
}

int SELECT(int *A, int p, int q, int i, int *cs){
    fprintf(stderr, "\n\nArray: ");
    for (int j = p; j<=q; j++){
        fprintf(stderr, "%i, ", A[j]);
    }
    fprintf(stderr, "\n k = %i ", i);
    if (p==q) return p;
    int *M = malloc(sizeof(int)*(floor((q-p)/5)+1));

    int index = 0;
    for(int j = p; j<=q; j+=5){
        if (q-j<4) M[index++] = A[GET_MEDIAN(A, j, q, cs)];
        else M[index++] = A[GET_MEDIAN(A, j, j+4, cs)];
    }

    int x = M[0];
    if (index > 1) x = M[SELECT(M, 0, index-1, floor(index/2), cs)];
    free(M);

    index = p;
    for (int j = p; j <=q; j++){
        if (A[j] == x) index = j;
    }
    
    x = select_partition(A, p, q, index, cs) + 1;
    
    if (i == x) return i-1;
    else if (i < x) return SELECT(A, p, x-2, i, cs);
    else return SELECT(A, x, q, i, cs);
}

int main(int argc, char *argv[]) {
    if (argc == 1){
        fprintf(stderr, "No arguments given!");
        return -1;
    }
    srand(time(NULL));

    int cs[2] = {0, 0};
    int n, k, *list, *list2;
    scanf("%i", &n);
    scanf("%i", &k);
    list = malloc(n * sizeof(int));
    list2 = malloc(n * sizeof(int));

    if (!strcmp(argv[1], "-r")) {
        list = randomList(n);
        for (int i = 0; i<n; i++){
            memcpy(&list2[i], &list[i], sizeof(int));
        }
    } else if (!strcmp(argv[1], "-p")){
        list = permutedList(n);
        for (int i = 0; i<n; i++){
            memcpy(&list2[i], &list[i], sizeof(int));
        }
    } else {
        fprintf(stderr, "Wrong argument given!");
        return -1;
    }

    fprintf(stderr, "-----------Select-----------\n");
    int indx1 = SELECT(list, 0, n-1, k, cs);
    fprintf(stderr, "\nComaprisons: %i; Switches %i\n", cs[0], cs[1]);
    cs[0] = 0, cs[1] = 0;
    fprintf(stderr, "\n\n---------Rand_Select--------\n");
    int indx2 = RAND_SELECT(list2, 0, n-1, k, cs);
    fprintf(stderr, "\nComaprisons: %i; Switches %i\n", cs[0], cs[1]);
    fprintf(stderr, "\n\n\n");
    for (int i = 0; i<n; i++){
        if (indx1 == i) printf("[%i] ", list[i]);
        else printf("%i ", list[i]);
    }
    /*printf("\n");
    for (int i = 0; i<n; i++){
        if (indx2 == i) printf("[%i] ", list2[i]);
        else printf("%i ", list2[i]);
    }*/
}
