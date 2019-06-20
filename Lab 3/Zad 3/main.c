#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int BS(long int* A, int p, int q, int v, int *c){
    int mid = floor((p+q)/2);
    c[0]++;
    if (A[mid] == v) return 1;
    else if (q-p == 0) {
        c[0]++;
        return 0;
    } else if (A[mid] > v) {
        c[0]+=2;
        return BS(A, p, mid, v, c);
    } else {
        c[0]+=2;
        return BS(A, mid+1, q, v, c);
    }
}

long int *createList(int n) {
    long int *list = malloc(n * sizeof(long int));
    list[0] = rand()%(n*10);
    for (int i = 1; i < n; i++) {
        list[i] = list[i-1] + 1 + rand()%10;
    }
    return list;
}

int main(){
    srand(time(NULL));
    FILE *f = fopen("data.txt", "a");
    for(long int n = 1000; n<1000000; n+=1000){
        int c[1] = {0};
        long int *list = createList(n);
        clock_t start, end;

        start = clock();
        BS(list, 0, n-1, rand()%(n*10), c);
        end = clock();
        //n, comps, time
        fprintf(f, "%i, %i, %f\n", n, c[0], ((double) (end - start)) / CLOCKS_PER_SEC);
        free(list);
    }
    fclose(f);
}