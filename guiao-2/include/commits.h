#include "commit.h"

typedef struct commits *COMMITS;


// Função que inicializa uma estrutura de dados Commits.
COMMITS initCommits ();

// Função que insere um Commit, na estrutura Commits.
COMMITS insertCommits(COMMITS c, Commit sc);

// Função que organiza uma estrutura Commits, para melhor procura de dados.
void sortCommits(COMMITS c);


// Retorna os diferentes commiters_id na estrutura de dados Commits.
int getDifsOfCommiterId (COMMITS c);

// Retorna os diferentes colaboradores na estrutura de dados Commits.
int getDifsOfColaboradores (COMMITS c);

// Devolve o número de bots colaboradores.
int getNBotColaborate(int *b, int nb, COMMITS c);


int* getCommiterLanguage(COMMITS c, int *vr, int nr, int *n);

int* getTopCommiters(COMMITS c, char *date, char *time, int *n);

int* getAboveDate (COMMITS c, int ano, int mes, int dia, int *n);

int* getAllAuthorIds(COMMITS c);

int* getAllCommiterIds(COMMITS c);

// Função que retorna o nº de commits inseridos na estrutura de dados Commits.
int getCommitsUsed (COMMITS c);

// Função que liberta a estrutura de dados Commits.
void freeCommits(COMMITS c);



// query10 

int* idsMessage(COMMITS c, int x);

int* tamMessage(COMMITS c, int x);

int* repoMessage(COMMITS c, int x);