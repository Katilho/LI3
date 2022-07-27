#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./../include/user.h"
#include "./../include/users.h"


struct users{
	User *arrU;
	int used;
	int size;
};


USERS initUsers() {
  int initialSize = 1000000;
  USERS c = malloc (sizeof(struct users));
  c->arrU = malloc(initialSize * sizeof(User));
  c->used = 0;
  c->size = initialSize;
  return c;
}


USERS insertUsers(USERS c, User sc) {

  if (c->used == c->size) {
    c->size += 100000; 
    c->arrU = realloc(c->arrU, c->size * sizeof(User));
  }
  c->arrU[c->used] = sc;
  c->used++;

  return c;
}

void sortUsers(USERS u){
  qsort (u->arrU, u->used, sizeof(User), cmpUsers);
}


static int getUSERId(USERS u, int n){
  return (getUserId(u->arrU[n]));
}

static char* getUSERLogin(USERS u, int n){
  char* l = (getUserLogin(u->arrU[n]));
  return l;
}

static char* getUSERType(USERS u, int n){
  char* l = (getUserType(u->arrU[n]));
  return l;
}

static int getUSERFollowers(USERS u, int n){
  return (getUserFollowers(u->arrU[n]));
}

static int* getUSERFollower_list(USERS u, int n){
  int* l = (getUserFollower_list(u->arrU[n]));
  return l; 
}

static int getUSERFollowing(USERS u, int n){
  return (getUserFollowing(u->arrU[n]));
}

static int* getUSERFollowing_list(USERS u, int n){
  int* l = (getUserFollowing_list(u->arrU[n]));
  return l;
}

static int binSearchUsers(USERS u, int b, int c, int n){
    
    int x;

    if (c < b) return (-1);
    int mid = (b + c) / 2; 
    x = getUSERId(u, mid);
    if (n == x) return mid;
    if (n > x) return binSearchUsers(u, (mid + 1), c, n);
    return binSearchUsers(u, b, (mid - 1), n);
}


char* returnLoginWithId (USERS u, int x){

    int used = u->used;
    int r = binSearchUsers (u, 0, used, x);
    if (r==-1) {
        printf ("Nao foi encontrado o ID pedido!");
        return ("error");
    }
    else return ((getUSERLogin(u, r)));
}



//Cria um array com os ids dos bots
int* getIdBots(USERS u, int nb, int *n){
  int used = u->used;

  int* l = malloc (sizeof(int)*nb);
  int i, j=0;

  for (i = 0; i<used; i++){
    if(strcmp("Bot", getUSERType(u, i)) == 0){
      l[j] = getUSERId(u, i);
      j++;
    }
  }
  *n = j;
  return l;
}

static int elem (int *v, int n, int x){
    int i, r=0;
    for (i=0; i<n; i++) if (v[i] == x) return 1;
    
    return r;
} 

int isFriend (USERS u, int commiter, int author){
    if(commiter == author) return 0;

    int i, j, checker = 0, used = u->used;

    i = binSearchUsers(u, 0, used, commiter);

    int followers = getUSERFollowers (u,i);
    int following = getUSERFollowing (u,i);
    int *followers_l;
    int *following_l;

    if (followers){
        followers_l = getUSERFollower_list (u,i);
        for (j=0; j<followers; j++) {

            checker = elem (followers_l, followers, author);
            if (checker) break;
        }
    }

    if (following && checker) {
        checker = 0;
        following_l = getUSERFollowing_list(u,i);
        for (j=0; j<following; j++) {

            checker = elem (following_l, following, author);
            if (checker) break;
        }
    }

    return checker;
}



int getUsersUsed (USERS u){
    return (u->used);
}

void freeUsers(USERS c) {
    int i;
    int used = c->used;
    for (i=0; i < used; i++){
        freeUser(c->arrU[i]);
    }
    free(c->arrU);
    c->used = c->size = 0;
    free (c);
}
