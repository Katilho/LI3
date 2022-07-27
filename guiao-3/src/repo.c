#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./../include/repos.h"

struct repo{
	int id;
	int owner_id;
	char *full_name;
	char *license;
	char *has_wiki;
	char *description;
	char *language;
	char *default_branch;
	char *created_at;
	char *updated_at;
	int forks_count;
	int open_issues;
	int stargazers_count;
	int size;
} ;

Repo insertRepo(int id, int owner_id, char *full_name, char *license, char *has_wiki, char *description, char *language, char *default_branch, char *created_at, char *updated_at, int forks_count, int open_issues, int stargazers_count, int size){

	Repo r = malloc(sizeof(struct repo));
	r->id = id;
	r->owner_id = owner_id;
	r->full_name = strdup(full_name);
	r->license = strdup(license);
	r->has_wiki = strdup(has_wiki);
	r->description = strdup(description);
	r->language = strdup(language);
	r->default_branch = strdup(default_branch);
	r->created_at = strdup(created_at);
	r->updated_at = strdup(updated_at);
	r->forks_count = forks_count;
	r->open_issues = open_issues;
	r->stargazers_count = stargazers_count;
	r->size = size;

	return r;
}

int cmpRepos(const void* a, const void* b) {
    struct repo *repo_a = *(struct repo**)a;
    struct repo *repo_b = *(struct repo**)b;

    if (repo_a->id < repo_b->id) return -1;
    else if (repo_a->id > repo_b->id) return 1;
    else return 0;
}

int getRepoId(Repo r){
	return r->id;
}

int getRepoOwnerId(Repo r){
	return r->owner_id;
}

char* getRepoFullName(Repo r){
	char* l = strdup(r->full_name);
	return l;
}

char* getRepoLicense(Repo r){
	char* l = strdup(r->license);
	return l;
}

char* getRepoHasWiki(Repo r){
	char* l = strdup(r->has_wiki);
	return l;
}

char* getRepoDescription(Repo r){
	char* l = strdup(r->description);
	return l;
}

char* getRepoLanguage(Repo r){
	char* l = strdup(r->language);
	return l;
}

char* getRepoDefaultBranch(Repo r){
	char* l = strdup(r->default_branch);
	return l;
}

char* getRepoCreatedAt(Repo r){
	char* l = strdup(r->created_at);
	return l;
}

char* getRepoUpdatedAt(Repo r){
	char* l = strdup(r->updated_at);
	return l;
}

int getRepoForksCount(Repo r){
	return r->forks_count;
}

int getRepoOpenIssues(Repo r){
	return r->open_issues;
}

int getRepoStargazersCount(Repo r){
	return r->stargazers_count;
}

int getRepoSize(Repo r){
	return r->size;
}

void freeRepo (Repo r){
	free (r->full_name);
	free (r->license);
	free (r->has_wiki);
	free (r->description);
	free (r->language);
	free (r->default_branch) ;
	free (r->created_at); 
	free (r->updated_at);
    free(r);
}