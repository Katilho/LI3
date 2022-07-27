#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./../include/auxFunctions.h"

// Função de comparação de dois elementos necessária à função qsort
int cmp (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int elem (int *v, int n, int x){
    int i;
    for (i=0; i<n; i++) if (v[i] == x) return 1;
    
    return 0;
} 

int binarySearch(int arr[], int b, int c, int n){
    if (c < b)
        return 0;
    int mid = (b + c) / 2; 
    if (n == arr[mid]) return 1;
    if (n > arr[mid]) return binarySearch(arr, (mid + 1), c, n);
    return binarySearch(arr, b, (mid - 1), n);
}

int validDate(char *s, int ano, int mes, int dia, int minMax){
    char *string = strdup(s);
    char *found, *aux = string;
    int a, m, d;
    int checker = 0, c_pal;

    for (c_pal = 0; ((found = strsep(&string,"- ")) != NULL); c_pal++){
        if(c_pal == 0){a = atoi(found);}
        else if(c_pal == 1){m = atoi(found);}
        else if(c_pal == 2){d = atoi(found);}
    }

    free(aux);

    if(minMax == 0){
        if (a>ano) {checker = 1;}
        else if (a==ano && m>mes) { checker = 1;}
        else if (a==ano && m==mes && d>=dia) { checker = 1;}
    }
    else{
        if (a<ano) {checker = 1;}
        else if (a==ano && m<mes) { checker = 1;}
        else if (a==ano && m==mes && d<dia) { checker = 1;}
    }

    return checker;
}