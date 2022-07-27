#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./../include/repo.h"
#include "./../include/repos.h"

struct repos{
	Repo *arrR;
	int used;
	int size;
};

REPOS initRepos(){
	int initialSize = 1000000;
	REPOS r = malloc (sizeof(struct repos));
	r->arrR = malloc(initialSize * sizeof(Repo));
	r->used = 0;
	r->size = initialSize;
	return r;
}

REPOS insertRepos(REPOS r, Repo sr){

  if (r->used == r->size) {
    r->size += 100000; 
    r->arrR = realloc(r->arrR, r->size * sizeof(Repo));
  }
  r->arrR[r->used] = sr;
  r->used++;

  return r;
}

void sortRepos(REPOS r){
  qsort (r->arrR, r->used, sizeof(Repo), cmpRepos);
}


static int getREPOId(REPOS r, int n){
	return (getRepoId(r->arrR[n]));
}

static char* getREPODescription(REPOS r, int n){
	char* l = (getRepoDescription(r->arrR[n]));  
	return l;
}

static char* getREPOLanguage(REPOS r, int n){
	char* l = (getRepoLanguage(r->arrR[n]));  
	return l;
}

static char* getREPOCreatedAt(REPOS r, int n){
	char* l = (getRepoCreatedAt(r->arrR[n]));  
	return l;
}

static char* getREPOUpdatedAt(REPOS r, int n){
	char* l = (getRepoUpdatedAt(r->arrR[n]));  
	return l;
}



int* getNRepoLanguage(REPOS r, char* language, int *n){
	int used = r->used;
	int *l = malloc(sizeof(int)*used);
	int i, j=0;

	for(i=0; i<used; i++){
		if(strcmp(getREPOLanguage(r, i), language) == 0){
			l[j] = getREPOId(r, i); j++;
		}
	}
	l = realloc(l, sizeof(int)*j);
	*n = j;
	return l;
}


int* getRepoInvDate(REPOS r, char* date, int *n){
	int used = r->used;
	int *l = malloc(sizeof(int)*used);

	char *string = strdup(date);
	char *found;
	int i, j=0, c_pal;
	int ano, mes, dia;

	for (c_pal = 0; ((found = strsep(&string,"-\n")) != NULL); c_pal++){
		if(c_pal == 0){ano = atoi(found);}
		else if(c_pal == 1){mes = atoi(found);}
		else if(c_pal == 2){dia = atoi(found);}
	}

	free(string); free(found);

	char *line;
	int a, m, d;

	for (i = 0; i<used; i++){
		line = getREPOUpdatedAt(r, i);
		for (c_pal = 0; ((found = strsep(&line,"- ")) != NULL); c_pal++){
			if(c_pal == 0){a = atoi(found);}
			else if(c_pal == 1){m = atoi(found);}
			else if(c_pal == 2){d = atoi(found);}

		}

		free(line);

		if (a<ano) {l[j] = getREPOId(r, i); j++;}
		else if (a==ano && m<mes) {l[j] = getREPOId(r, i); j++;}
		else if (a==ano && m==mes && d<dia) {l[j] = getREPOId(r, i); j++;}
	}

	free(found);

	l = realloc(l, sizeof(int)*j);
	*n = j;
	return l;
}

static int binSearchRepos(REPOS r, int b, int c, int n){
    
    int x;

    if (c < b) return (-1);
    int mid = (b + c) / 2; 
    x = getREPOId(r, mid);
    if (n == x) return mid;
    if (n > x) return binSearchRepos(r, (mid + 1), c, n);
    return binSearchRepos(r, b, (mid - 1), n);
}


char* returnDescriptionWithId (REPOS r, int x){

    int used = r->used;
    int res = binSearchRepos (r, 0, used, x);
    if (res==-1) {
        printf ("Nao foi encontrado o ID pedido!");
        return ("error");
    }
    else return ((getREPODescription(r, res)));
}


int* getArrayRids (REPOS r){
	int i, max = r->used;
	int* v = malloc (sizeof(int)*max);
	for (i=0; i<max; i++){
		v[i] = getREPOId (r, i);
	}
	return v;
}

static int binarySearch(int arr[], int b, int c, int n){
    if (c < b)
        return 0;
    int mid = (b + c) / 2; 
    if (n == arr[mid]) return 1;
    if (n > arr[mid]) return binarySearch(arr, (mid + 1), c, n);
    return binarySearch(arr, b, (mid - 1), n);
}

int* getInactiveIds (REPOS r, int* arr, int n, int *len){

	int max = r->used;
	int* res = malloc(sizeof(int)*max); 

	int i, j = 0, id, checker;
	for (i=0; i<max; i++){
		id = getREPOId(r,i);
		checker = binarySearch (arr, 0, n, id);
		if (checker == 0) res[j++] = id;
	}

	res = realloc(res, sizeof(int)*j);
	*len = j;

	return res;
}

static int validDate(int ano, int mes, int dia, char* date){
	int c_pal, checker = 0;
	char *found;
	char *line = strdup(date);
	int a, m, d;

    for (c_pal = 0; ((found = strsep(&line,"- ")) != NULL); c_pal++){
        if(c_pal == 0){a = atoi(found);}
        else if(c_pal == 1){m = atoi(found);}
        else if(c_pal == 2){d = atoi(found);}
    }

    free(line); free(found);

    if (a>ano) {checker = 1;}
    else if (a==ano && m>mes) { checker = 1;}
    else if (a==ano && m==mes && d>dia) { checker = 1;}

    return checker;
}

void langCounter (REPOS r, int ano, int mes, int dia, char **words, int *count, int *nir){
	
	int used = getReposUsed(r);
	int i, l, checker, index, isUnique;
    
    char *word;
    char *string;

    for (i=0; i<1000; i++) count[i] = 0;

    index = 0;

    for (i=0; i<used; i++){
        string = getREPOCreatedAt(r, i); // talvez seja getREPOUpdatedAt
        checker = validDate(ano, mes, dia, string);
        free (string);

        if (checker == 1) {
            
            word = getREPOLanguage(r, i);
            
            isUnique = 1;
            
            for (l=0; l<index && isUnique; l++) {
                if (strcmp(words[l], word) == 0)
                    isUnique = 0;
            }

            if (isUnique) {
                words[index] = strdup(word);
                count[index]++;
                index++;
            }

            else { count[l - 1]++; } 

            free (word); 
        }
        checker = 0;
    }
    *nir = index;
}


int getReposUsed (REPOS r){
    return (r->used);
}


void freeRepos(REPOS r) {
    int i;
    int used = r->used;
    for (i=0; i < used; i++){
        freeRepo(r->arrR[i]);
    }
    free(r->arrR);
    r->used = r->size = 0;
    free (r);
}