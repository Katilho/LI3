#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./../include/user.h"


struct user{
	int id;
	char *login;
	char *type;
    char *created_at;
    int followers;
    int *follower_list;
    int following;
    int *following_list;
    int public_gists;
    int public_repos;	
};

User insertUser(int id, char *login, char *type, char *created_at, int followers, int *follower_list, int following, int *following_list, int public_gists, int public_repos) {
  
    User u = malloc(sizeof(struct user));
    u->id = id;
    u->login = strdup(login);
    u->type = strdup(type);
    u->created_at = strdup(created_at);
    u->followers = followers;
    u->follower_list = (follower_list);
    u->following = following;
    u->following_list = (following_list);
    u->public_gists = public_gists;
    u->public_repos = public_repos;

  return u;
}

int cmpUsers(const void* a, const void* b) {
    struct user *user_a = *(struct user**)a;
    struct user *user_b = *(struct user**)b;

    if (user_a->id < user_b->id) return -1;
    else if (user_a->id > user_b->id) return 1;
    else return 0;
}


// Funcoes de obtencao de valores //

int getUserId (User u){
    return (u->id);
}

char* getUserLogin (User u){
    char* l = strdup (u->login);
    return l;
}

char* getUserType (User u){
    char* l = strdup (u->type);
    return l;
}

char* getUserCreatedAt (User u){
    char* l = strdup (u->created_at);
    return l;
}

int getUserFollowers (User u){
    return (u->followers);
}

int* getUserFollower_list (User u){
    int i, n = getUserFollowers (u);
    int* l = malloc (sizeof(int)*n);
    int* v = u->follower_list;
    for (i=0; i<n; i++)
    l[i] = v[i];
    return l;
}

int getUserFollowing (User u) {
    return (u->following);
}

int* getUserFollowing_list (User u){
    int i, n = getUserFollowing (u);
    int* l = malloc (sizeof(int)*n);
    int* v = u->following_list;
    for (i=0; i<n; i++)
    l[i] = v[i];
    return l;
}

int getUserPublic_gists (User u){
    return (u->public_gists);
}

int getUserPublic_repos (User u){
    return (u->public_repos);
}


void freeUser (User u){
    free (u->login);
    free (u->type);
    free (u->created_at);
    free (u->follower_list);
    free (u->following_list);
    free (u);
}