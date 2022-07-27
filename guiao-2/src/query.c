#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./../include/stats.h"
#include "./../include/tuple.h"
#include "./../include/query.h"


static char* fileNames(int n){
    char *file = malloc(sizeof(char)*30);
    sprintf(file, "saida/command%d_output.txt", n);
    return file;
}


struct idx {
    int id;
    int x;
    struct idx *next;
};

struct ids {
	char *s;
	int x;
	struct ids *next;
};


static void freeListX (IDX l){
    IDX aux;

    while (l) {
        aux = l;
        l = l->next;
        free(aux);
    }
}


static IDX howManyX (int v[], int n){
	if (n==0) return NULL;
    int i;
    IDX list = malloc(sizeof(struct idx));
    IDX r = list;
    list->id = v[0];
    int ant = v[0];
    int x=1;
    for (i=1; i<n; i++){
        if (ant == v[i]) {
            x++;
        }
        else {
            ant = v[i];
            list->x = x;
            list->next = malloc(sizeof(struct idx));
            list = list->next;
            list->id = ant;// = v[i]
            x = 1;
        }
    }
    list->x = x;
    list->next = NULL;
    return r;
}


static void sortListX (IDX l){
     IDX t;
     IDX s;
     int x;
     t=l;
     while(t!=NULL){
          s=t->next;
          while(s!=NULL){
               if(t->x<s->x){
                    x=t->x;
                    t->x=s->x;
                    s->x=x;
                    x=t->id;
                    t->id=s->id;
                    s->id=x;
               }
               s=s->next;
          }
          t=t->next;
      }
      t=l;
}


static void freeListS (IDS l){
    IDS aux;

    while (l) {
        aux = l;
        l = l->next;
        free (aux->s);
        free (aux);
    }
}


static IDS insertL(IDS l, char* s, int x){
    IDS tmp;
    tmp = malloc (sizeof(struct ids));
    tmp->s = s;
    tmp->x = x;
    tmp->next = l;
    return tmp; 
}

static void sortListS (IDS l){
     IDS t;
     IDS s;
     int x;
     char *tmp;
     t=l;
     while(t!=NULL){
          s=t->next;
          while(s!=NULL){
               if(t->x<s->x){
                    x=t->x;
                    t->x=s->x;
                    s->x=x;
                    tmp=t->s;
                    t->s=s->s;
                    s->s=tmp;
               }
               s=s->next;
          }
          t=t->next;
      }
      t=l;
}


static IDS getTopLanguages(TupleR tr, char *date){
    REPOS r = getREPOS(tr);

    char *string = strdup(date);
    char *found;
    int i, c_pal;
    int ano, mes, dia;

    for (c_pal = 0; ((found = strsep(&string,"-\n")) != NULL); c_pal++){
        if (c_pal == 0) {ano = atoi(found);}
        else if (c_pal == 1) {mes = atoi(found);}
        else if (c_pal == 2) {dia = atoi(found);}
    }
    free (string);

    int index = 0;

    char **words = malloc(sizeof(char*)*1000);
    int* count = malloc (sizeof(int)*1000);
    langCounter (r, ano, mes, dia, words, count, &index);

    IDS result = NULL;
    for (i=0; i<index; i++) {
        result = insertL (result, words[i], count[i]);
    }

    free(count);
    free(words);

    sortListS (result);

    return result;
}


static int* getCommiterFriends(TupleU tu, TupleC tc, int *n){
	COMMITS c = getCOMMITS(tc);
	USERS u = getUSERS(tu);
	int i, used = getCommitsUsed(c), j=0;

	int *ai = getAllAuthorIds(c);
	int author_id;
	int *ci = getAllCommiterIds(c);
	int committer_id;

	int *l = malloc(sizeof(int)*used);

	for (i=0; i<used; i++){
		author_id = ai[i];
		committer_id = ci[i];

		if(isFriend(u, committer_id, author_id)){
			l[j] = committer_id;
			j++;
		}
	}
	free(ai);
	free(ci);
	l = realloc(l, sizeof(int)*j);
    *n = j;

    return l;
}


static void query1(TupleU tu, int num){
	int users, bots, organizations;
	StatsU s = getStatsUsers(tu);

	users = getNusers(s);
	bots = getNbots(s);
	organizations = getNorganizations(s);

	char *file = malloc(sizeof(char)*30);
	file = fileNames(num);

	FILE *query1 = fopen (file , "w");

	fprintf(query1, "Bot: %d\nOrganization: %d\nUser: %d\n", bots, organizations, users);
	fclose(query1);
	free(file);
}


static void query2(TupleC tc, TupleR tr, int num){
	int n_repos, n_colabs;

	n_repos = getRlength (getStatsRepos (tr));

	n_colabs = getDifsOfColaboradores (getCOMMITS (tc));


	char *file = malloc(sizeof(char)*30);
	file = fileNames(num);

	FILE *query2 = fopen (file , "w");

	fprintf (query2, "%.2f\n", ((float)n_colabs/(float)n_repos));
	fclose (query2);
	free(file);
}


static void query3(TupleU tu, TupleC tc, int num){
	int n = 0;
	int nb = getNbots(getStatsUsers(tu));
	int *b = getIdBots(getUSERS(tu), nb, &n);

	int r = getNBotColaborate(b, n, getCOMMITS(tc));

	char *file = malloc(sizeof(char)*30);
	file = fileNames(num);

	FILE *query3 = fopen (file , "w");

	fprintf (query3, "%d", r);
	fclose (query3);
	free(file);
}


static void query4(TupleU tu, TupleC tc, int num){
	int n_users, n_commits;

	n_users = getUlength (getStatsUsers (tu)); 
	//n_users = getDifsOfCommiterId (getCOMMITS (tc)); // se for necessário ver pelos commits.


	n_commits = getClength (getStatsCommits (tc));
	
	char *file = malloc(sizeof(char)*30);
	file = fileNames(num);

	FILE *query4 = fopen (file , "w");

	fprintf (query4, "%.2f\n", ((float)n_commits/(float)n_users));
	fclose (query4);
	free(file);
}


static void query5(TupleU tu, TupleC tc, int n, char *date, char *time, int num){
	int id, x, i;
	char *login;
	int ni = 0;
	int *l = getTopCommiters(getCOMMITS(tc), date, time, &ni);

	IDX list = howManyX(l, ni);
	free(l);
	sortListX(list);
	IDX aux;

	char *file = malloc(sizeof(char)*30);
	file = fileNames(num);

	FILE *query5 = fopen (file , "w");

	for (i=0; list && i<n; i++){
		id = list->id;
		x = list->x;
		aux = list;
		list = list->next;
		free (aux);

		login = returnLoginWithId(getUSERS(tu),id);

		fprintf (query5, "%d;%s;%d\n", id, login, x);

		free(login);
	}

	freeListX(list);
	fclose (query5);
	free(file);
}


static void query6(TupleU tu, TupleC tc, TupleR tr, int n, char *language, int num){
	int nc = 0, nr = 0, i;
	int *rId = getNRepoLanguage(getREPOS(tr), language, &nr);
	int *cId = getCommiterLanguage(getCOMMITS(tc), rId, nr, &nc);
	free(rId);
	int id, x;
	char *login;
	IDX aux;

	IDX list = howManyX(cId, nc);
	free (cId);
	sortListX(list);

	char *file = malloc(sizeof(char)*30);
	file = fileNames(num);

	FILE *query6 = fopen (file , "w");

	for (i=0; list && i<n; i++){
		id = list->id;
		x = list->x;
		aux = list;
		list = list->next;
		free (aux);

		login = returnLoginWithId(getUSERS(tu),id);

		fprintf (query6, "%d;%s;%d\n", id, login, x);

		free (login);
	}

	freeListX(list);
	fclose (query6);
	free(file);
}


static void query7(TupleC tc, TupleR tr, char *date, int num){
	
	int i, lenArr1 = 0, lenArr2 = 0;

	char *string = strdup(date);
	char *found;
	int c_pal;
	int ano, mes, dia;

	for (c_pal = 0; ((found = strsep(&string,"-\n")) != NULL); c_pal++){
		if(c_pal == 0){ano = atoi(found);}
		else if(c_pal == 1){mes = atoi(found);}
		else if(c_pal == 2){dia = atoi(found);}
	}
	free(string);

	int *arr = getAboveDate(getCOMMITS(tc), ano, mes, dia, &lenArr1);
	int *repos_ids;
	if (lenArr1 != 0) repos_ids = getInactiveIds (getREPOS(tr), arr, lenArr1, &lenArr2);
	else {repos_ids = getArrayRids(getREPOS(tr)); lenArr2 = getReposUsed(getREPOS(tr));}

	free (arr);

	char *file = malloc(sizeof(char)*30);
	file = fileNames(num);

	FILE *query7 = fopen (file , "w");
	char *description;

	for(i=0; i<lenArr2; i++){
		description = returnDescriptionWithId(getREPOS(tr), repos_ids[i]);
		fprintf(query7, "%d;%s\n", repos_ids[i], description);
		free (description);
	}

	free (repos_ids);
	fclose (query7);
	free(file);
}




static void query8(TupleR tr, int n, char *date, int num){
	int i;
	char *language;
	IDS aux;

	IDS list = getTopLanguages(tr, date);

	char *file = malloc(sizeof(char)*30);
	file = fileNames(num);

	FILE *query8 = fopen (file , "w");

	for (i=0; list && i<n ; i++){
		language = strdup(list->s);
		aux = list;
		list = list->next;
		free(aux->s);
		free(aux);

		fprintf (query8, "%s\n", language);

		free(language);
	}

	freeListS(list);
	fclose (query8);
	free(file);
}


static void query9(TupleU tu, TupleC tc, int n, int num){
	int id, i;
	char *login;
	int nl = 0;

	int *l = getCommiterFriends(tu, tc, &nl);

	IDX list = howManyX(l, nl), aux;
	free(l);
	sortListX(list);


	char *file = malloc(sizeof(char)*30);
	file = fileNames(num);

	FILE *query9 = fopen (file , "w");

	for (i=0; list && i<n ; i++){
		id = list->id;
		aux = list;
		list = list->next;
		free (aux);

		login = returnLoginWithId(getUSERS(tu), id);

		fprintf (query9, "%d;%s\n", id, login);

		free(login);
	}

	freeListX(list);
	fclose (query9);
	free(file);
}

//query 10 

static void query10(TupleC tc, TupleU tu, int n, int num){
    int i=0;
    char *login;
    int *id = idsMessage(getCOMMITS(tc), n);
    int *tamanho = tamMessage(getCOMMITS(tc), n);
    int *repo = repoMessage(getCOMMITS(tc), n);

    char *file = malloc(sizeof(char)*600);
	file = fileNames(num);

	FILE *query10 = fopen (file , "w");

	for(i=0; i<n; i++){
        login = returnLoginWithId(getUSERS(tu),id[i]);
        fprintf(query10, "%d;%s;%d;%d\n", id[i], login, tamanho[i]-1, repo[i]);
        free (login);
	}

	free(id);
	free(tamanho);
	free(repo);
	fclose (query10);
	free(file);
}



void query(TupleU tu, TupleC tc, TupleR tr, const char* file){
	FILE *fp = fopen (file , "r");
	char line[10000];
    char *string, *found;
    int c_pal, query_id, n;
    char *language, *date, *time;
    int i;

    for(i=1; fgets(line, 10000, (FILE*)fp) ; i++){

		string = strdup(line);

		for (c_pal = 0; ((found = strsep(&string," \n")) != NULL); c_pal++){

			if (c_pal == 0) {query_id = atoi(found);}
			else if(query_id == 5 && c_pal == 1) {n = atoi(found);}
			else if(query_id == 5 && c_pal == 2) {date = found;}
			else if(query_id == 5 && c_pal == 3) {time = found;}
			else if(query_id == 6 && c_pal == 1) {n = atoi(found);}
			else if(query_id == 6 && c_pal == 2) {language = found;}
			else if(query_id == 7 && c_pal == 1) {date = found;}
			else if(query_id == 8 && c_pal == 1) {n = atoi(found);}
			else if(query_id == 8 && c_pal == 2) {date = found;}
			else if(query_id == 9 && c_pal == 1) {n = atoi(found);}
			else if(query_id == 10 && c_pal == 1) {n = atoi(found);}

		}

		if (query_id == 1) { query1(tu, i); }
		else if (query_id == 2) { query2(tc, tr, i); }
		else if (query_id == 3) { query3(tu, tc, i); }
		else if (query_id == 4) { query4(tu, tc, i); }
		else if (query_id == 5) { query5(tu, tc, n, date, time, i); }
		else if (query_id == 6) { query6(tu, tc, tr, n, language, i);}
		else if (query_id == 7) { query7(tc, tr, date, i);}
		else if (query_id == 8) { query8(tr, n, date, i);}
		else if (query_id == 9) { query9(tu, tc, n, i);}
		else if (query_id == 10) { query10(tc, tu, n, i);} 

		free (string);
    }

    fclose(fp);
}
