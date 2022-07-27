#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./../include/tuple.h"
#include "./../include/stats.h"
#include "./../include/users.h"
#include "./../include/commits.h"
#include "./../include/repos.h"
#include "./../include/parsing.h"


// Para retirar os \n e \r do final das linhas obtidas dos ficheiros
static void removeNL(char *str) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != '\n' && *dst != '\r') dst++;
    }
    *dst = '\0';
}

// Para retirar os '[' e ']' da string
static void removeparts(char *str){
    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != '[' && *dst != ']') dst++;
    }
    *dst = '\0';    
}


static int* parseArray (char *found, int n){
    
    if (n==0) return NULL;
    
    char *number;
    int i;
    int *v = malloc (sizeof(int)*n);

    removeparts (found);

    for (i = 0; (number = strsep(&found, ",")); i++) {
        v[i] = atoi(number);
    }
    free(number);
   
    return v;
}


// Devolve um tuplo com o catálogo de users e as suas estatísticas.
TupleU vusers() {
    FILE *fp = fopen ("entrada/users-g2.csv" , "r");
    char line[230000];
    char *string, *found;
    int c_pal;
    StatsU stats = initStatsU();
    USERS cat = initUsers();
    User c;

    int id, followers, following, public_gists, public_repos;
    char *login, *type, *created_at;
    int *follower_list, *following_list; 

        for (int i=0; ( fgets(line, 230000, (FILE*)fp) ); i++) {

        if (i!=0) {

            string = strdup(line);

            for (c_pal = 0; ((found = strsep(&string,";")) != NULL); c_pal++) {
      
                //id
                if (c_pal == 0) {id = atoi (found);}

                //login
                else if (c_pal == 1) {login = strdup (found);}

                //type
                else if (c_pal == 2) {
                    type = strdup (found);
                    if (strcmp("User", found) == 0) stats = incUsers (stats);
                    else if (strcmp("Bot", found) == 0) stats = incBots (stats);
                    else if (strcmp("Organization", found) == 0) stats = incOrganizations (stats);
                }

                //created_at
                else if (c_pal == 3) {created_at = strdup (found);}

                //followers
                else if (c_pal == 4) {
                    followers = atoi (found);
                }

                //follower_list
                else if (c_pal == 5) {
                    follower_list = parseArray (found, followers);
                } 

                //following
                else if (c_pal == 6) {
                    following = atoi (found);
                }

                //following_list
                else if (c_pal == 7) {
                    following_list = parseArray (found, following);
                }

                //public_gists
                else if (c_pal == 8) {public_gists = atoi (found);}

                //public_repos
                else if (c_pal == 9) {public_repos = atoi (found);}
            }

            c = insertUser(id, login, type, created_at, followers, follower_list, following, following_list, public_gists, public_repos);
            cat = insertUsers (cat, c);
            free(string); free(found);
        }

    }

    fclose (fp);
    sortUsers(cat);
    
    // Colocar nas stats quantos Users foram lidos.
    stats = setStatsUlength (stats, getUsersUsed(cat));

    TupleU tuple = createTupleU (stats, cat);

    return tuple;
}



// Devolve um tuplo com o catálogo de commits e as suas estatísticas.
TupleC vcommits() {
    FILE *fp = fopen ("entrada/commits-g2.csv" , "r");
    char line[15000];
    char *string, *found;
    int c_pal;
    StatsC stats = initStatsC();
    COMMITS cat = initCommits();
    Commit c;

    int repo_id, author_id, committer_id;
    char *commit_at, *message; 

        for (int i=0; ( fgets(line, 15000, (FILE*)fp) ); i++) {

        if (i!=0) {

            string = strdup(line);

            for (c_pal = 0; ((found = strsep(&string,";")) != NULL); c_pal++) {
      
                //repo_id
                if (c_pal == 0) {repo_id = atoi(found);}

                //author_id
                else if (c_pal == 1) {author_id = atoi(found);}

                //committer_id
                else if (c_pal == 2) {committer_id = atoi(found);}

                //commit_at
                else if (c_pal == 3) {commit_at = strdup (found);}

                //message
                else if (c_pal == 4) {
                    message = strdup(found);
                    removeNL (message);
                }
      
            }

            c = insertCommit(repo_id, author_id, committer_id, commit_at, message);
            cat = insertCommits (cat, c);
            free (string); free(found);
        }

}
    fclose (fp);
    sortCommits(cat);

    // Colocar nas stats quantos commits foram lidos.
    stats = setStatsClength (stats, getCommitsUsed(cat));

    TupleC tuple = createTupleC (stats, cat);

    return tuple;
}

// Devolve um tuplo com o catálogo de repos e as suas estatísticas.
TupleR vrepos() {
    FILE *fp = fopen ("entrada/repos-g2.csv" , "r");
    char line[80000];
    char *string, *found;
    int c_pal;
    StatsR stats = initStatsR();
    REPOS cat = initRepos();
    Repo c;

    int id, owner_id, forks_count, open_issues, stargazers_count, size;
    char *full_name, *license, *has_wiki, *description, *language, *default_branch, *created_at, *updated_at; 

        for (int i=0; ( fgets(line, 80000, (FILE*)fp) ); i++) {

        if (i!=0) {

            string = strdup(line);

            for (c_pal = 0; ((found = strsep(&string,";")) != NULL); c_pal++) {
      
                //id
                if (c_pal == 0) {id = atoi(found);}

                //owner_id
                else if (c_pal == 1) {owner_id = atoi(found);}

                //full_name
                else if (c_pal == 2) {full_name = strdup(found);}

                //license
                else if (c_pal == 3) {license = strdup(found);}

                //has_wiki
                else if (c_pal == 4) {has_wiki = strdup(found);}

                //description
                else if (c_pal == 5) {description = strdup(found);}

                //language
                else if (c_pal == 6) {language = strdup(found);}

                //default_branch
                else if (c_pal == 7) {default_branch = strdup(found);}

                //created_at
                else if (c_pal == 8) {created_at = strdup(found);}

                //updated_at
                else if (c_pal == 9) {updated_at = strdup(found);}

                //forks_count
                else if (c_pal == 10) {forks_count = atoi(found);}

                //open_issues
                else if (c_pal == 11) {open_issues = atoi(found);}

                //stargazers_count
                else if (c_pal == 12) {stargazers_count = atoi(found);}

                //size
                else if (c_pal == 13) {size = atoi(found);}
            }

            c = insertRepo(id, owner_id, full_name, license, has_wiki, description, language, default_branch, created_at, updated_at, forks_count, open_issues, stargazers_count, size);
            cat = insertRepos (cat, c);
            free (string); free(found);
        }

    }
    fclose (fp);
    sortRepos(cat);
    
    // Colocar nas stats quantos repos foram lidos.
    stats = setStatsRlength (stats, getReposUsed(cat));

    TupleR tuple = createTupleR (stats, cat);

    return tuple;
}