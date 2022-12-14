#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./../include/repo.h"
#include "./../include/repos.h"
#include "./../include/auxFunctions.h"

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
	int size = 1000;
	int *l = malloc(sizeof(int)*size);
	int i, j=0;

	for(i=0; i<used; i++){
		if(strcmp(getREPOLanguage(r, i), language) == 0){
			if (j==size){
				size *= 2;
				l = realloc (l, sizeof(int)*size);
			}
			l[j] = getREPOId(r, i); j++;
		}
	}
	//l = realloc(l, sizeof(int)*j);
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


static int* getArrayRids (REPOS r){
	int i, max = r->used;
	int* v = malloc (sizeof(int)*max);
	for (i=0; i<max; i++){
		v[i] = getREPOId (r, i);
	}
	return v;
}

// Obtem os ids dos reposit??rios que n??o pertencem ao array argumento (ou seja, obtem os ids que n??o t??m um commit ap??s uma determinada data).
int* getInactiveIds (REPOS r, int* arr, int n, int *len){

	if (n == 0){
		*len = getReposUsed(r);
		return (getArrayRids (r));
	}

	int used = r->used, size = 200000;
	int *res = malloc(sizeof(int)*size); 

	int i, j = 0, id, checker;

	for (i=0; i<used; i++){
		id = getREPOId(r,i);
		checker = binarySearch (arr, 0, n, id);
		if (checker == 0) {
			if (j == size) { size *= 2; res = realloc (res, sizeof(int)*size); }
			res[j++] = id;
		}
	}
	//res = realloc(res, sizeof(int)*j);
	*len = j;

	return res;
}

void langCounter (REPOS r, int ano, int mes, int dia, char **words, int *count, int *nir){
	
	int used = getReposUsed(r);
	int i, l, checker, index, isUnique;
    
    char *language;
    char *date;

    index = 0;

    for (i=0; i<used; i++){
        date = getREPOCreatedAt(r, i); // talvez seja getREPOUpdatedAt
        checker = validDate(date, ano, mes, dia, 0);
        free (date);

        if (checker == 1) {
            
            language = getREPOLanguage(r, i);
            
            isUnique = 1;
            
            for (l=0; l<index && isUnique; l++) {
                if (strcmp(words[l], language) == 0) isUnique = 0;
            }

            if (isUnique) {
                words[index] = strdup(language);
                count[index] = 1;
                index++;
            }

            else { count[l - 1]++; } 

            free (language); 
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