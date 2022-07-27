#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./../include/commit.h"

struct commit{
	int repo_id;
	int author_id;
	int commiter_id;
	char *commit_at;
	char *message;	
} ;

Commit insertCommit(int repo_id, int author_id, int commiter_id, char *commit_at, char *message) {
  
  Commit c = malloc(sizeof(struct commit));
  c->repo_id = repo_id;
  c->author_id = author_id;
  c->commiter_id = commiter_id;
  c->commit_at = strdup(commit_at);
  c->message = strdup(message);

  return c;
}

int cmpCommits(const void* a, const void* b) {
    struct commit *commit_a = *(struct commit**)a;
    struct commit *commit_b = *(struct commit**)b;

    if (commit_a->commiter_id < commit_b->commiter_id) return -1;
    else if (commit_a->commiter_id > commit_b->commiter_id) return 1;
    else return 0;
}

int getCommitRepoId (Commit c){
    return c->repo_id;
}


int getCommitAuthorId (Commit c){
    return c->author_id;
}

int getCommitCommiterId (Commit c){
    return c->commiter_id;
}

char* getCommitCommitAt (Commit c){
    char* l = strdup (c->commit_at);
    return l;
}

char* getCommitMessage (Commit c){
    char* l = strdup (c->message); 
    return l;
}


void freeCommit (Commit c){
    free (c->commit_at);
    free (c->message);
    free (c);
}