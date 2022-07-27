#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/printer.h"

// numero de linhas de cada pagina
#define NUM_PAG  20

static char* fileNames(int n){
    char *file = malloc(sizeof(char)*35);
    sprintf(file, "saida/command%d_output.txt", n);
    return file;
}


void printQ1(int n){
	char *filename = fileNames (n);
	FILE *fp = fopen (filename , "r");
    free (filename);

    char line[300];

	while(fgets(line, 300, (FILE*)fp))
		printf ("%s", line);
	printf("\n");

	fclose (fp);
}


void printQ2(int n){
	char *filename = fileNames(n);
	FILE *fp = fopen(filename, "r");
    free(filename);

    char line[30];

	fgets(line, 30, (FILE*)fp);
	printf("Número médio de colaboradores por repositório: %s\n", line);

	fclose(fp);
}


void printQ3(int n){
	char *filename = fileNames(n);
	FILE *fp = fopen(filename, "r");
    free(filename);

    char line[30];

	fgets(line, 30, (FILE*)fp);
	printf("Número de repositórios com bots: %s\n\n", line);

	fclose(fp);
}


void printQ4(int n){
	char *filename = fileNames(n);
	FILE *fp = fopen(filename, "r");
	free(filename);

    char line[30];

	fgets(line, 30, (FILE*)fp);
	printf("Quantidade média de commits por utilizador: %s\n", line);

	fclose(fp);
}


static void freeStrings(char** words, int n){
	int i;
	for (i=0; i<n; i++){
		free(words[i]);
	}
	free (words);
}


static char** createWordsQ5(int *r, int n){
    char *file = fileNames(n);
    char line[300];
    int c_pal;
    int ind = 0;

    int mem = 3000;
    char** words = malloc(sizeof(char*) * mem);

    char *id, *login, *nCommits, *found;

    char *string, *aux;

    FILE *fp = fopen(file, "r");
    free(file);

    while (fgets(line, 300, (FILE*)fp)){

        string = strdup(line);
        aux = string;
        
        for (c_pal = 0; ((found = strsep(&string,";")) != NULL); c_pal++){
            if(c_pal == 0) id = strdup(found);
            else if(c_pal == 1) login = strdup(found);
            else if(c_pal == 2) nCommits = strdup(found);
        }

        file = malloc(sizeof(char)*400);
        sprintf(file, "%dº -> ID:%s  ; Login:%s  ; Nº de commits:%s", ind+1, id, login, nCommits);
        words[ind++] = file;

        free(aux); free(id); free(login); free(nCommits);
        if (ind == mem){ mem *= 2; words = realloc (words, mem * sizeof(char*));  }
    }
    fclose(fp);
    *r = ind;
    return words;
}


static void printPag(char** words, int ind, int pag){
    int i, j;
    // talvez acrescentar \n no inicio desta linha
    printf ("-----------------------------------------------------------\n");

    for(i=(pag-1)*NUM_PAG, j=0; j<NUM_PAG && i<ind; i++, j++){
        printf ("%s", words[i]);
    }

    printf ("-----------------------------------------------------------\n");

    printf ("--------Página %d de %d--------\n", pag, ind/NUM_PAG + (1 && ind%NUM_PAG));
}


static int getPag(int pag, int maxPag){
    printf ("P     -> Próxima\n");
    printf ("A     -> Anterior\n");
    printf ("S <N> -> Saltar para página\n");
    printf ("Q     -> Sair da query\n");
    printf ("\n");

    char input[5]; 
    char input2[5]; 
    printf ("Opção: ");

    scanf("%s", input);
    
    if (input[strlen(input)-1] == '\n') input[strlen(input)-1] = '\0';

    if ((strcmp(input, "P") == 0 || strcmp(input, "p") == 0) && pag < maxPag) pag++;
    else if ((strcmp(input, "A") == 0 || strcmp(input, "a") == 0) && pag != 1) pag--;
    else if (strcmp(input, "S") == 0 || strcmp(input, "s") == 0){
    	scanf("%s", input2);
    	pag = atoi(input2);
    	if (pag > maxPag) pag = maxPag;
    	else if (pag <= 0) pag = 1;
    }
    else if (strcmp(input, "Q") == 0 || strcmp(input, "q") == 0) pag = -1;

    printf ("\n");

    return pag;
}

void printQ5(int n){
	int ind = 0;
    char** words = createWordsQ5(&ind, n);
    
    if (ind > 0){
    	printPag(words, ind, 1);

    	int pag = 1, maxPag = ind/NUM_PAG + (1 && ind%NUM_PAG);
    	while(pag <= maxPag){
        	pag = getPag(pag, maxPag);
        	if(pag == -1) break;
        	printPag(words, ind, pag);
    	}
	}
	else printf("Não foram encontrados resultados!\n\n");
    freeStrings(words, ind);
}


void printQ6(int n){
	int ind = 0;
    char** words = createWordsQ5(&ind, n);
    
    if (ind > 0){
    	printPag(words, ind, 1);

    	int pag = 1, maxPag = ind/NUM_PAG + (1 && ind%NUM_PAG);
    	while(pag <= maxPag){
        	pag = getPag(pag, maxPag);
        	if(pag == -1) break;
        	printPag(words, ind, pag);
    	}
	}
	else printf("Não foram encontrados resultados!\n\n");
    freeStrings(words, ind);
}


// funcao que verifica se o ultimo char é um '\n'.
static int lastn (char* s){

    if (s[strlen (s)-1] == '\n') return 1;
    else return 0;
}

static char** createWordsQ7(int *r, int n){
    char line[5000];
    int c_pal;
    int ind = 0;

    int mem = 25000;
    char **words = malloc(sizeof(char*) * mem);

    char *repo_id, *descricao;
    char *string, *found, *aux;

    char *file = fileNames(n);
    FILE *fp = fopen(file, "r");
    free(file);

    while (fgets(line, 5000, fp)){

        string = strdup(line);

        while (!lastn(string) && !feof(fp)) {
            fgets(line, 5000, fp);
            aux = strdup(line);
            string = realloc(string, strlen(string)*2);
            strcat (string, aux);
            free(aux);
        }

        aux = string;
        
        for (c_pal = 0; ((found = strsep(&string,";")) != NULL); c_pal++){
            if(c_pal == 0) repo_id = strdup(found);
            else if(c_pal == 1) descricao = strdup(found);
        }

        free (aux);

        file = malloc(strlen(repo_id) + strlen(descricao) + 50);
        sprintf(file, "ID do Repositório: %s; Descrição: %s", repo_id, descricao);
        words[ind++] = file;

        free(repo_id); free(descricao);
        if (ind == mem){ mem *= 2; words = realloc (words, mem * sizeof(char*)); }
    }
    fclose(fp);
    *r = ind;
    return words;
}


void printQ7(int n){
	int ind = 0;
    char** words = createWordsQ7(&ind, n);
    
    if (ind > 0){
    	printPag(words, ind, 1);

    	int pag = 1, maxPag = ind/NUM_PAG + (1 && ind%NUM_PAG);
    	while(pag <= maxPag){
        	pag = getPag(pag, maxPag);
        	if(pag == -1) break;
        	printPag(words, ind, pag);
    	}
    	
	}
	else printf("Não foram encontrados resultados!\n\n");
	freeStrings(words, ind);
}

static char** createWordsQ8(int *r, int n){
    char *file = fileNames(n);
    char line[3000];
    int ind = 0;

    int mem = 10000;
    char** words = malloc(sizeof(char*) * mem);

    char *language;

    FILE *fp = fopen(file, "r");
    free(file);

    while (fgets(line, 3000, (FILE*)fp)){

        language = strdup(line);

        file = malloc(sizeof(char)*3000);
        sprintf(file, "%dº -> %s", ind+1, language);
        words[ind++] = file;

        free(language);
        if (ind == mem){ mem *= 2; words = realloc (words, mem * sizeof(char*)); }
    }
    fclose(fp);
    *r = ind;
    return words;
}

void printQ8(int n){
	int ind = 0;
    char** words = createWordsQ8(&ind, n);
    
    if (ind>0){
    	printPag(words, ind, 1);

    	int pag = 1, maxPag = ind/NUM_PAG + (1 && ind%NUM_PAG);
    	while(pag <= maxPag){
        	pag = getPag(pag, maxPag);
        	if(pag == -1) break;
        	printPag(words, ind, pag);
    	}
	}
    else printf("Não foram encontrados resultados!\n\n");
    freeStrings(words, ind);
}


static char** createWordsQ9(int *r, int n){
	char *file = fileNames(n);
    char line[3000];
    int c_pal;
    int ind = 0;

    int mem = 2000;
    char** words = malloc(sizeof(char*) * mem);

    char *found, *string, *aux;
    char *id, *login;
    
    FILE *fp = fopen(file, "r");
    free(file);

    while (fgets(line, 3000, (FILE*)fp)){

        string = strdup(line);
        aux = string;
        
        for (c_pal = 0; ((found = strsep(&string,";")) != NULL); c_pal++){
            if(c_pal == 0) id = strdup(found);
            else if(c_pal == 1) login = strdup(found);
        }

        free(aux);

        file = malloc(sizeof(char)*30000);
        sprintf(file, "%dº -> ID do Utilizador: %s ; Login: %s", ind+1, id, login);
        words[ind++] = file;

        free(id); free(login);
        if (ind == mem){ mem *= 2; words = realloc (words, mem * sizeof(char*)); }
    }
    fclose(fp);
    *r = ind;
    return words;
}


void printQ9(int n){
	int ind = 0;
	char** words = createWordsQ9(&ind, n);
    
    if (ind>0){
    	printPag(words, ind, 1);

    	int pag = 1, maxPag = ind/NUM_PAG + (1 && ind%NUM_PAG);
    	while(pag <= maxPag){
        	pag = getPag(pag, maxPag);
        	if(pag == -1) break;
        	printPag(words, ind, pag);
    	}
	}
    else printf("Não foram encontrados resultados!\n\n");
    freeStrings(words, ind);
}


static char** createWordsQ10(int *r, int n){
	char *file = fileNames(n);
    char line[3000];
    int c_pal;
    int ind = 0;

    int mem = 100;
    char** words = malloc(sizeof(char*) * mem);

    char *id, *login, *size, *repo_id;

    char *found, *string, *aux;

    FILE *fp = fopen(file, "r");
    free(file);

    while (fgets(line, 3000, (FILE*)fp)){

        string = strdup(line);        
        aux = string;
        
        for (c_pal = 0; ((found = strsep(&string,";")) != NULL); c_pal++){
            if(c_pal == 0) id = strdup(found);
            else if(c_pal == 1) login = strdup(found);
            else if(c_pal == 2) size = strdup(found);
            else if(c_pal == 3) repo_id = strdup(found);
        }

        free(aux);

        file = malloc(sizeof(char)*30000);
        sprintf(file, "%dº -> ID do Utilizador: %s ; Login: %s ; Tamanho da Mensagem: %s ; ID do Repositório: %s", ind+1, id, login, size, repo_id);
        words[ind++] = file;

        free(id);free(login);
        if (ind == mem){ mem *= 2; words = realloc (words, mem * sizeof(char*)); }
    }
    fclose(fp);
    *r = ind;
    return words;
}


void printQ10(int n){
	int ind = 0;
	char** words = createWordsQ10(&ind, n);
    
    if (ind>0){
    	printPag(words, ind, 1);

    	int pag = 1, maxPag = ind/NUM_PAG + (1 && ind%NUM_PAG);
    	while(pag <= maxPag){
        	pag = getPag(pag, maxPag);
        	if(pag == -1) break;
        	printPag(words, ind, pag);
    	}
	}
    else printf("Não foram encontrados resultados!\n\n");
    freeStrings(words, ind);
}