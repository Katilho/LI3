#include "repo.h"

typedef struct repos *REPOS;


// Função que inicializa uma estrutura de dados Repos.
REPOS initRepos();

// Função que insere um Repo, na estrutura Repos.
REPOS insertRepos(REPOS r, Repo sr);

// Função que organiza uma estrutura Repos, para melhor procura de dados.
void sortRepos(REPOS r);


// Devolve um array de ids de repositórios com uma determinada linguagem.
int* getNRepoLanguage(REPOS r, char* language, int *n);

int* getRepoInvDate(REPOS r, char* date, int *n);

char* returnDescriptionWithId(REPOS r, int id);

int* getInactiveIds (REPOS r, int* arr, int n, int *len);

void langCounter (REPOS r, int ano, int mes, int dia, char **words, int *count, int *nir);

// Função que retorna o nº de repos inseridos na estrutura de dados Repos.
int getReposUsed (REPOS r);

// Função que liberta a estrutura de dados Repos.
void freeRepos(REPOS r);