#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
    swap(toSort, p, i);

    i = p;
    for (int j = i + 1; j < q + 1; j++) {
        cs[0]+=1;
        if (toSort[j] < toSort[p]) {
            swap(toSort, j, ++i);
        }
    }
    swap(toSort, p, i);
    return i;
}

int RAND_SELECT(int *A, int p, int q, int i, int *cs){
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
    swap(toSort, p, piv);

    int i = p;
    for (int j = i + 1; j < q + 1; j++) {
        cs[0]+=1;
        if (toSort[j] < toSort[p]) {
            swap(toSort, j, ++i);
        }
    }
    swap(toSort, p, i);
    return i;
}

int SELECT(int *A, int p, int q, int i, int *cs){
    if (p==q) return p;
    int *M = malloc(sizeof(int)*(floor((q-p)/5)+1)), ss[1] = {0};

    int index = 0;
    for(int j = p; j<=q; j+=5){
        if (q-j<4) M[index++] = A[GET_MEDIAN(A, j, q, ss)];
        else M[index++] = A[GET_MEDIAN(A, j, j+4, ss)];
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

int main() {
    srand(time(NULL));
    int comps[1] = {0}, n, k, *list, *list2;
    FILE *f = fopen("data.txt", "a");

    for(n = 10; n < 10000; n+=10){
        k = floor(n/4);
        int maxCS=0, minCS=0, maxCR=0, minCR=0;
        float avgS = 0, avgR = 0, avg2S=0, avg2R=0;
        for(int j = 0; j < 100; j++){

            list = randomList(n);
            list2 = malloc(sizeof(int)*n);
            for (int k = 0; k<n; k++){
                memcpy(&list2[k], &list[k], sizeof(int));
            }
        
            comps[0] = 0;
            SELECT(list, 0, n-1, k, comps);
            if (comps[0]>maxCS) maxCS = comps[0];
            if (comps[0]<minCS || minCS == 0) minCS = comps[0];
            avgS += comps[0];
            avg2S += pow(comps[0], 2);
            
            comps[0] = 0;
            RAND_SELECT(list2, 0, n-1, k, comps);
            if (comps[0]>maxCR) maxCR = comps[0];
            if (comps[0]<minCR || minCR == 0) minCR = comps[0];
            avgR += comps[0];
            avg2R += pow(comps[0], 2);

            free(list);
            free(list2);
        }

        avgS = avgS/100;
        avgR = avgR/100;
        avg2S = avg2S/100;
        avg2R = avg2R/100;

        float devS = sqrt(avg2S - pow(avgS,2));
        float devR = sqrt(avg2R - pow(avgR,2));

        fprintf(f, "S, %i, %i, %i, %f, %f\n", n, minCS, maxCS, avgS, devS);
        fprintf(f, "R, %i, %i, %i, %f, %f\n", n, minCR, maxCR, avgR, devR);
    }
    fclose(f);
}