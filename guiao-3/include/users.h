#include "user.h"

typedef struct users *USERS;


// Função que inicializa uma estrutura de dados Users.
USERS initUsers();

// Função que insere um User, na estrutura Users.
USERS insertUsers(USERS c, User sc);

// Função que organiza uma estrutura Users, para melhor procura de dados.
void sortUsers(USERS u);


// Função que retorna o Login associado a um determinado id.
char* returnLoginWithId (USERS u, int x);

// Função que retorna em array de inteiros, os ids de bots.
int* getIdBots(USERS u, int nb, int *n);

// Função que verifica se um author é amigo de um commiter.
int isFriend (USERS u, int commiter, int author);

// Função que retorna o nº de users inseridos na estrutura de dados Users.
int getUsersUsed (USERS u);

// Função que liberta a estrutura de dados Users.
void freeUsers(USERS c);