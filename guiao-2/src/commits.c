#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./../include/commit.h"
#include "./../include/commits.h"


struct commits{
	Commit *arrC;
	int used;
	int size;
};


COMMITS initCommits() {
  int initialSize = 1000000;
  COMMITS c = malloc (sizeof(struct commits));
  c->arrC = malloc(initialSize * sizeof(Commit));
  c->used = 0;
  c->size = initialSize;
  return c;
}


COMMITS insertCommits(COMMITS c, Commit sc) {

  if (c->used == c->size) {
    c->size += 100000; 
    c->arrC = realloc(c->arrC, c->size * sizeof(Commit));
  }
  c->arrC[c->used] = sc;
  c->used++;

  return c;
}

void sortCommits(COMMITS c){
  qsort (c->arrC, c->used, sizeof(Commit), cmpCommits);
}


static int getCOMMITRepoId (COMMITS c, int n){
    return (getCommitRepoId(c->arrC[n]));
}


static int getCOMMITAuthorId (COMMITS c, int n){
    return (getCommitAuthorId(c->arrC[n]));
}

static int getCOMMITCommiterId (COMMITS c, int n){
    return (getCommitCommiterId(c->arrC[n]));
}


static char* getCOMMITCommitAt (COMMITS c, int n){
    char* l = (getCommitCommitAt(c->arrC[n]));
    return l;
}


static int elem (int *v, int n, int x){
    int i, r=0;
    for (i=0; i<n; i++) if (v[i] == x) return 1;
    
    return r;
} 


int getDifsOfCommiterId (COMMITS c){
    
    int ant = -1, i, j=0, x, used = c->used;
    
    for (i=0; i<used; i++){
    
        x = getCOMMITCommiterId (c, i);
    
        if (ant!=x) {
            ant = x;
            j++;
        }
    }
    return j;
}

// Devolve o nº de colaboradores diferentes.
int getDifsOfColaboradores (COMMITS c){
    
    int i, j=0, used = c->used;
    int author_id, commiter_id, repo_id, ant = -1, antRepos = -1, antAuthor = -1;

    for (i=0; i<used; i++){
        author_id = getCOMMITAuthorId(c, i);
        commiter_id = getCOMMITCommiterId(c, i);
        repo_id = getCOMMITRepoId(c, i);
         
        if (antRepos != repo_id) {
            antRepos = repo_id;
            antAuthor = author_id;
            j++;
            ant = commiter_id;
            if (author_id != commiter_id) j++;
        }
        else if (ant != commiter_id) {
            if (commiter_id != antAuthor) {
                j++; ant = commiter_id;
            }
        }
        
    }
    return j;
}

//Devolve o número de bots colaboradores
int getNBotColaborate(int *b, int nb, COMMITS c){
    int i, j=0;
    int author_id, committer_id;
    int used = c->used;
    int v[used];
    int x;

    for(i=0; i<used; i++){
        author_id = getCOMMITAuthorId(c, i);
        committer_id = getCOMMITCommiterId(c, i);
        if(elem(b, nb, author_id) || elem(b, nb, committer_id)){
            //printf("1\n");
            x = getCOMMITRepoId(c, i);

            if(!elem(v, j, x)){
                v[j] = x; j++;
            }
        }
    }
    return j; 
}


int* getCommiterLanguage(COMMITS c, int *vr, int nr, int *n){
    int used = getCommitsUsed(c);
    int *l = malloc(sizeof(int)*used);
    int i, j=0;
    int repo_id;

    for (i=0; i<used; i++){
        repo_id = getCOMMITRepoId(c, i);
        if(elem(vr, nr, repo_id)){
            l[j] = getCOMMITCommiterId(c, i); j++;
        }
    }
    l = realloc(l, sizeof(int)*j);
    *n = j;
    return l;
}

static int validDate(char *s, int ano, int mes, int dia, int minMax){
    char *string = strdup(s);
    char *found;
    int a, m, d;
    int checker = 0, c_pal;

    for (c_pal = 0; ((found = strsep(&string,"- ")) != NULL); c_pal++){
        if(c_pal == 0){a = atoi(found);}
        else if(c_pal == 1){m = atoi(found);}
        else if(c_pal == 2){d = atoi(found);}
    }

    free(string); free(found);

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


int* getTopCommiters(COMMITS c, char *date, char *time, int *n){
    int used = c->used, i, c_pal, j=0;
    int *l = malloc(sizeof(int)*used);
    char *found, *string;
    int ano, mes, dia;
    int a,   m,   d;

    string = strdup(date);

    for (c_pal = 0; ((found = strsep(&string,"-\n")) != NULL); c_pal++){
        if (c_pal == 0) {ano = atoi(found);}
        else if (c_pal == 1) {mes = atoi(found);}
        else if (c_pal == 2) {dia = atoi(found);}
    }

    free(string); free(found);
    
    string = strdup(time);

    for (c_pal = 0; ((found = strsep(&string,"-\n")) != NULL); c_pal++){
        if (c_pal == 0) {a = atoi(found);}
        else if (c_pal == 1) {m = atoi(found);}
        else if (c_pal == 2) {d = atoi(found);}
    }

    free(string); free(found);

    char *s;

    for (i=0; i<used; i++){
        s = getCOMMITCommitAt(c, i);
        if(validDate(s, ano, mes, dia, 0)){
            if(validDate(s, a, m, d, 1)){
                l[j] = getCOMMITCommiterId(c, i); j++;
            }
        }
        free(s);
    }
    l = realloc(l, sizeof(int)*j);
    *n = j;
    return l;
}


// Função de comparação de dois elementos necessária à função qsort
static int cmp (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}


int* getAboveDate (COMMITS c, int ano, int mes, int dia, int *n){
    int i, id, ant = 0, ind = 0, max = c->used;
    int* arr = malloc(sizeof(int)*max);
    char* date;

    for (i=0; i<max; i++){
        date = getCOMMITCommitAt (c, i);
        if (validDate(date, ano, mes, dia, 0)){
            id = getCOMMITRepoId (c, i);
            if (id != ant) { 
                ant = id;
                arr[ind++] = id;
            }
        }
        free(date);
    }

    arr = realloc (arr, sizeof(int)*ind);
    qsort (arr, ind, sizeof(int), cmp);
    
    *n = ind;
    return arr;
}


int* getAllAuthorIds(COMMITS c){
    int i, used = c->used;
    int author_id;

    int *ai = malloc(sizeof(int)*used);

    for (i=0; i<used; i++){
        author_id = getCOMMITAuthorId(c, i);
        ai[i] = author_id;
    }
    return ai;
}


int* getAllCommiterIds(COMMITS c){
    int i, used = c->used;
    int committer_id;

    int *ci = malloc(sizeof(int)*used);

    for (i=0; i<used; i++){
        committer_id = getCOMMITCommiterId(c, i);
        ci[i] = committer_id;
    }
    return ci;
}


int getCommitsUsed (COMMITS c){
    return (c->used);
}



void freeCommits(COMMITS c) {
    int i;
    int used = c->used;
    for (i=0; i < used; i++){
        freeCommit(c->arrC[i]);
    }
    free(c->arrC);
    c->used = c->size = 0;
    free (c);
}



// query10 


static char* getCOMMITMessage (COMMITS c, int n){
    char* l = (getCommitMessage(c->arrC[n]));
    return l;
}


int* idsMessage(COMMITS c, int x){
    int used = c->used;
    int *tam = malloc(sizeof(int)*x);
    int *ids = malloc(sizeof(int)*x);
    int i,j,k;
    
    for (i=0; i<x; i++){  
        tam[i] = strlen(getCOMMITMessage(c, i));
        ids[i] = getCOMMITAuthorId(c, i);
    } 

    int auxM, auxId;

    for(i=0; i<x-1; i++){
        for(j=0; j<x-i-1; j++){
            if(tam[j]<tam[j+1]){
                auxM     = tam[j];
                tam[j]   = tam[j+1];
                tam[j+1] = auxM;
    
                auxId    = ids[j];
                ids[j]   = ids[j+1];
                ids[j+1] = auxId;
            } 
        } 
    }

    for(k=x; k<used; k++){
        if(tam[x-1] < strlen(getCOMMITMessage(c, k))){
            tam[x-1] = strlen(getCOMMITMessage(c, k));
            ids[x-1] = getCOMMITAuthorId(c,k );
            for(i=0; i<x-1; i++){
                for(j=0; j<x-i-1; j++){
                    if(tam[j]<tam[j+1]){
                        auxM     = tam[j];
                        tam[j]   = tam[j+1];
                        tam[j+1] = auxM;
    
                        auxId    = ids[j];
                        ids[j]   = ids[j+1];
                        ids[j+1] = auxId;
                    }
                }
            }
        }
    }

    free(tam);
    return ids;
}



int* tamMessage(COMMITS c, int x){
    int used = c->used;
    int *tam = malloc(sizeof(int)*x);
    int *ids = malloc(sizeof(int)*x);
    int i,j,k;
    
    for (i=0; i<x; i++){  
        tam[i] = strlen(getCOMMITMessage(c, i));
        ids[i] = getCOMMITAuthorId(c, i);
    } 

    int auxM, auxId;

    for(i=0; i<x-1; i++){
        for(j=0; j<x-i-1; j++){
            if(tam[j]<tam[j+1]){
                auxM     = tam[j];
                tam[j]   = tam[j+1];
                tam[j+1] = auxM;
    
                auxId    = ids[j];
                ids[j]   = ids[j+1];
                ids[j+1] = auxId;
            } 
        } 
    }

    for(k=x; k<used; k++){
        if(tam[x-1] < strlen(getCOMMITMessage(c, k))){
            tam[x-1] = strlen(getCOMMITMessage(c, k));
            ids[x-1] = getCOMMITAuthorId(c,k );
            for(i=0; i<x-1; i++){
                for(j=0; j<x-i-1; j++){
                    if(tam[j]<tam[j+1]){
                        auxM     = tam[j];
                        tam[j]   = tam[j+1];
                        tam[j+1] = auxM;
    
                        auxId    = ids[j];
                        ids[j]   = ids[j+1];
                        ids[j+1] = auxId;
                    }
                }
            }
        }
    }

    free(ids);
    return tam;
}


int* repoMessage(COMMITS c, int x){
    int used = c->used;
    int *tam = malloc(sizeof(int)*x);
    int *repo = malloc(sizeof(int)*x);
    int i,j,k;
    
    for (i=0; i<x; i++){  
        tam[i] = strlen(getCOMMITMessage(c, i));
        repo[i] = getCOMMITRepoId(c, i);
    } 

    int auxM, auxId;

    for(i=0; i<x-1; i++){
        for(j=0; j<x-i-1; j++){
            if(tam[j]<tam[j+1]){
                auxM     = tam[j];
                tam[j]   = tam[j+1];
                tam[j+1] = auxM;
    
                auxId     = repo[j];
                repo[j]   = repo[j+1];
                repo[j+1] = auxId;
            } 
        } 
    }

    for(k=x; k<used; k++){
        if(tam[x-1] < strlen(getCOMMITMessage(c, k))){
            tam[x-1] = strlen(getCOMMITMessage(c, k));
            repo[x-1] = getCOMMITRepoId(c,k );
            for(i=0; i<x-1; i++){
                for(j=0; j<x-i-1; j++){
                    if(tam[j]<tam[j+1]){
                        auxM     = tam[j];
                        tam[j]   = tam[j+1];
                        tam[j+1] = auxM;
    
                        auxId     = repo[j];
                        repo[j]   = repo[j+1];
                        repo[j+1] = auxId;
                    }
                }
            } 
        }
    }

    free(tam);
    return repo;
}

