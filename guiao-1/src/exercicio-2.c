#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int binarySearch(int arr[], int b, int c, int n){
    if (c < b)
        return 0;
    int mid = (b + c) / 2; /*b + (c - b)/2;*/
    if (n == arr[mid])
        return 1;
    if (n > arr[mid])
        return binarySearch(arr, (mid + 1), c, n);
    return binarySearch(arr, b, (mid - 1), n);
}

// Função de comparação de dois elementos necessária à função qsort
static int cmp (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

// Cria um array com os ids de cada ficheiro
int* createArray (int *n, int fich){
    FILE *rFich;
    if(fich == 0) rFich = fopen ("saida/users-ok.csv" , "r");
    else if(fich == 1) rFich = fopen ("saida/commits-final.csv" , "r"); // abrimos o commits-final para comparar o repos com os commits ja filtrados
    else if(fich == 2) rFich = fopen ("saida/repos-ok.csv" , "r");
 
    char line[200000];
    char *string, *found;
    int i, id;
    int max = 500000;
    int* ids = malloc (max * sizeof(int));

    for (i=-1; ( fgets(line, 200000, (FILE*)rFich) ) != NULL; i++) {
        
        if (i!=-1) {

            string = strdup(line);

            if (i == max) {
                max += 200000;
                ids = realloc (ids, max * sizeof(int));
            }

            found = strsep(&string,";");
            id = atoi(found);
            ids[i] = id;
        }
    }

    fclose (rFich);

    //ids = realloc (ids, i*sizeof(int));

    qsort(ids, i, sizeof(int), cmp);

    *n = i;

    return ids;
}

// Criação do "users-final.csv"
void remUsers () {
    FILE *rUsers = fopen ("saida/users-ok.csv" , "r");
    FILE *wUsers = fopen ("saida/users-final.csv" , "w");
   
    char line[250000];

    for ( ; ( fgets(line, 250000, (FILE*)rUsers) ); ) {
        fprintf(wUsers,"%s", line);
      }

    fclose (rUsers);
    fclose (wUsers);
}

// Criação do "commits-final.csv"
void remCommits (int arrU[], int nU, int arrR[],  int nR){
   FILE *rCommits = fopen ("saida/commits-ok.csv" , "r");
   FILE *wCommits = fopen ("saida/commits-final.csv" , "w");
   
   char line[4000];
   char *string, *found;
   int i;
   int repo_id, author_id, commiter_id;
   int checker;

   for (i=0; ( fgets(line, 4000, (FILE*)rCommits) ) != NULL; i++) {
        
        string = strdup(line);

        if (i == 0) fprintf (wCommits,"%s", line);

        else { 
            
            found = strsep(&string,";"); // 1ª palavra é o repo_id

            repo_id = atoi(found);

            checker = binarySearch (arrR, 0, nR, repo_id);

            if(checker == 1){

                found = strsep(&string,";"); // 2ª palavra é o author_id

                author_id = atoi(found);

                checker = binarySearch (arrU, 0, nU, author_id);

                if(checker == 1){
                    
                    found = strsep(&string,";"); // 3ª palavra é o commiter_id

                    commiter_id = atoi(found);

                    checker = binarySearch (arrU, 0, nU, commiter_id);

                    if(checker == 1){
                        fprintf (wCommits,"%s", line);
                    }
                }
            }
      }
   }
   fclose (rCommits);
   fclose (wCommits);
}

// Criação do "repos-final.csv"
void remRepos (int arrU[], int nU, int arrC[], int nC) {
    FILE *rRepos = fopen ("saida/repos-ok.csv" , "r");
    FILE *wRepos = fopen ("saida/repos-final.csv", "w");

    char line[80000];
    char *string, *found;
    int i, id, checker = 0;

    for (i=0; ( fgets(line, 80000, (FILE*)rRepos) ) != NULL; i++) {
        
        string = strdup(line);

        if (i == 0) fprintf (wRepos,"%s", string);

        else { 
            
            found = strsep(&string,";"); // found = 1ª palavra da string (repo_id)

            id = atoi(found);
            
            checker = binarySearch (arrC, 0 , nC , id); // verifica se o id do repositorio se encontra no array dos commits

            found = strsep(&string,";"); // faço strsep duas vezes para conseguir a 2ª palavra da string (owner_id).

            id = atoi(found);

            if (checker == 1) checker = binarySearch (arrU, 0 , nU, id); // verifica se o id se encontra no array dos users

            if (checker == 1) fprintf (wRepos,"%s", line);
        }
    }

   fclose (rRepos);
   fclose (wRepos);
}

// Função principal
int exercicio2 (){
   int *arrU;
   int *arrCR;
   int nU, nC, nR;

   remUsers();

   arrU = createArray (&nU, 0);
   arrCR = createArray (&nR, 2); // cria array com os ids dos repos

   // abrir o commits-ok e ver se está bem
   remCommits(arrU, nU, arrCR, nR);

   free (arrCR);

   arrCR = createArray (&nC, 1); // cria array com os ids dos commits

   // abrir os repos-ok e ver se está bem
   remRepos(arrU, nU, arrCR, nC);

   free (arrU);
   free (arrCR);
   return 0;
}