#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./../include/stats.h"
#include "./../include/tuple.h"
#include "./../include/query.h"
#include "./../include/auxFunctions.h"


static char* fileNames(int n){
    char *file = malloc(sizeof(char)*35);
    sprintf(file, "saida/command%d_output.txt", n);
    return file;
}


typedef struct vids {
    int num;
    char *str;
} *Vids;//, **VIDS;

static Vids* init_vids (int size){
    Vids *r = malloc(sizeof(Vids)*size);
    return r;
}
//                                           indice de onde é pra ser inserido os valores no array
static Vids* insert_vids (Vids* v, int num, char *str, int ind){
    v[ind] = malloc (sizeof(struct vids));
    (v[ind])->num = num;
    (v[ind])->str = strdup(str);
    free (str);

    return v;
}

static void free_vids (Vids* v, int size){
    int i;
    for (i=0; i<size; i++){
        free ((v[i])->str);
        free (v[i]);
    }
    free(v);
}


static int cmpvids(const void* va, const void* vb) {
    struct vids *a = *(struct vids**)va;
    struct vids *b = *(struct vids**)vb;

    if (a->num < b->num) return 1;
    else if (a->num > b->num) return -1;
    else return 0;
}

static void sort_vids(Vids* d, int used){
	qsort (d, used, sizeof(Vids), cmpvids);
}



static int cmpDATES(const void* a, const void* b) {
    struct vids *date_a = *(struct vids**)a;
    struct vids *date_b = *(struct vids**)b;

    int c_pal, r = 0;
    char *aux = NULL;
    char *string = NULL, *found = NULL;

    //obtencao dos valores do dia, mes e ano de cada uma das duas datas(strings).
    int aa, ma, da;
    string = strdup(date_a->str);
    aux = string;
    for (c_pal = 0; c_pal < 3 && ((found = strsep(&string,"- ")) != NULL); c_pal++){
        if(c_pal == 0) {aa = atoi(found);}
        else if(c_pal == 1) {ma = atoi(found);}
        else {da = atoi(found);}
    }
    free(aux);

    int ab, mb, db;
    string = strdup(date_b->str);
    aux = string;
    for (c_pal = 0; c_pal < 3 && ((found = strsep(&string,"- ")) != NULL); c_pal++){
        if(c_pal == 0) {ab = atoi(found);}
        else if(c_pal == 1) {mb = atoi(found);}
        else {db = atoi(found);}
    }
    free(aux);

    if (aa>ab) { r = 1;}
    else if (aa<ab) { r = -1;}
    else if (aa==ab && ma>mb) { r = 1;}
    else if (aa==ab && ma<mb) { r = -1;}
    else if (aa==ab && ma==mb && da>=db) { r = 1;}
    else if (aa==ab && ma==mb && da<db) { r = -1;}

    return r;
}

static void sort_Dates(Vids* d, int used){
  qsort (d, used, sizeof(Vids), cmpDATES);
}

////////////////////////////////////////////////////////

typedef struct vidx {
    int id;
    int x;
} *Vidx, **VIDX;


static void free_vidx (Vidx *v, int n){
	int i;
	for (i=0; i<n; i++){
		free (v[i]);
	}
	free(v);
}

static int cmpvidx(const void* va, const void* vb) {
    Vidx a = *(VIDX)va;
    Vidx b = *(VIDX)vb;

    if (a->x < b->x) return 1;
    else if (a->x > b->x) return -1;
    else return 0;
}

static VIDX create_vidx (int *v, int n, int *used){
	if (n == 0) return NULL;

	int size = 1000, i;
	VIDX r = malloc(sizeof(Vidx) * size); 

	int j = 0, ant = v[0], sofar = 1;
	r[0] = malloc(sizeof(struct vidx));
	r[0]->id = ant;
	for (i=1; i<n; i++){
		
		if (v[i] == ant) sofar++;

		else {
			r[j++] -> x = sofar; sofar = 1;
			if (size == j){
				size *= 2;
				r = realloc (r, size * sizeof (Vidx));
			}
			ant = v[i];
			r[j] =  malloc (sizeof(struct vidx));
			r[j]->id = ant;
		}
	}
	r[j++] -> x = sofar;

	// free(v); // free do array argumento.
	//r = realloc(r, j*sizeof(Vidx));

	qsort(r, j, sizeof(Vidx), cmpvidx); // ordena de forma decrescente os valores, relativamente ao campo "x".

	*used = j;
	return r;
}


static void botsIdFile(int *b, int nb){
	int i, id;
	FILE *botsId = fopen ("tmp/botsIdQ3.txt" , "w");

	for(i=0; i<nb; i++){
		id = b[i];

		fprintf(botsId, "%d\n", id);
	}
	fclose(botsId);
}


static void commitAtFile(Vids* d, int used){
	int committer_id, i;
	char *commit_at;
	FILE *commitAtfile = fopen ("tmp/commitAtQ5.txt" , "w");

	for(i=0; i<used; i++){
		committer_id = (d[i])->num;
		commit_at = strdup((d[i])->str);

		fprintf(commitAtfile, "%d;%s\n", committer_id, commit_at);
		free(commit_at);
	}
	fclose(commitAtfile);
}

static int* getTopCommiters(FILE *fp, char *date, char *time, int *n){
    int size = 5000, c_pal;
    int *l = malloc(sizeof(int) * size);
    char *found, *string, *aux;
    int ano, mes, dia;
    int a,   m,   d;

    string = strdup(time);
    aux = string;
    for (c_pal = 0; ((found = strsep(&string,"-\n")) != NULL); c_pal++){
        if (c_pal == 0) {a = atoi(found);}
        else if (c_pal == 1) {m = atoi(found);}
        else if (c_pal == 2) {d = atoi(found);}
    }
    free(aux);

    string = strdup(date);

    if (validDate(string, a, m, d, 0)){
    	free(string);
    	*n = 0;
    	return NULL;
    }
    
    aux = string;
    for (c_pal = 0; ((found = strsep(&string,"-\n")) != NULL); c_pal++){
        if (c_pal == 0) {ano = atoi(found);}
        else if (c_pal == 1) {mes = atoi(found);}
        else if (c_pal == 2) {dia = atoi(found);}
    }
    free(aux);

    


    int j=0, id, checker = 1;
    char line[50];

/* melhoria/técnica de passar metade do ficheiro à frente.

    int pos; char c;
    fseek(fp, 0, SEEK_END); 
	pos = ftell(fp);
	pos /= 2;
	fseek(fp, pos, SEEK_SET);
	do{
		c = fgetc(fp);
	} while (c != '\n');

	fgets(line, 50, fp);
	string = strdup(line);
    aux = string;
    found = strsep(&string,";");
    found = strsep(&string,";\n"); // found = commit_at

    if (validDate(found, ano, mes, dia, 0)) fseek(fp,0,SEEK_SET);

    free(aux);
*/

    while(fgets(line, 50, (FILE*)fp) ){
        string = strdup(line);
        aux = string;
        found = strsep(&string,";");
        id = atoi(found);
        found = strsep(&string,";\n"); // found = commit_at

        if (checker == 1){
            if (validDate(found, ano, mes, dia, 0) ){
                checker = 0;
                l[j++] = id;
            }
        }
        else if (checker == 0){
            if (validDate(found, a, m, d, 0)){
                free(aux);
                break;
            }
            else {
                if (j==size) {
                    size *= 2;
                    l = realloc(l, size * sizeof(int));
                }
                l[j++] = id;                
            }
        }
 
        free(aux);
    }
    // l = realloc(l, sizeof(int)*j);
    *n = j;
    qsort (l, j, sizeof(int), cmp); // retorna array ordenado relativamente aos ids.
    return l;
}


static Vids *getTopLanguages(TupleR tr, char *date, int *length){

    char *string = strdup(date);
    char *found, *aux = string;
    int i, c_pal;
    int ano, mes, dia;

    for (c_pal = 0; ((found = strsep(&string,"-\n")) != NULL); c_pal++){
        if (c_pal == 0) {ano = atoi(found);}
        else if (c_pal == 1) {mes = atoi(found);}
        else if (c_pal == 2) {dia = atoi(found);}
    }
    free (aux);

    int index = 0;

    char **words = malloc(sizeof(char*)*1000);
    int* count = malloc (sizeof(int)*1000);
    langCounter (getREPOS(tr), ano, mes, dia, words, count, &index);

    Vids *result = init_vids(index);
    for (i=0; i<index; i++) {
        result = insert_vids (result, count[i], words[i], i);
    }

    free(count);
    free(words); // a insert_vids faz o free das strings do array "words".

    sort_vids(result, index);

    *length = index;
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

	int size = 70;
	int *l = malloc(sizeof(int)*size);

	for (i=0; i<used; i++){
		author_id = ai[i];
		committer_id = ci[i];

		if(isFriend(u, committer_id, author_id)){
			if (size == j){
				size *= 2;
				l = realloc (l, size * sizeof(int));
			}
			l[j++] = committer_id;
		}
	}
	free(ai);
	free(ci);

	//l = realloc(l, sizeof(int)*j);
    *n = j;
    return l;
}


void query1(TupleU tu, int num){
	int users, bots, organizations;
	StatsU s = getStatsUsers(tu);

	users = getNusers(s);
	bots = getNbots(s);
	organizations = getNorganizations(s);

	char *filename = fileNames(num);
	FILE *query1 = fopen (filename , "w");
	free(filename);

	fprintf(query1, "Bot: %d\nOrganization: %d\nUser: %d\n", bots, organizations, users);
	fclose(query1);
}


void query2(TupleC tc, TupleR tr, int num){
	int n_repos, n_colabs;

	n_repos = getRlength (getStatsRepos (tr));

	n_colabs = getDifsOfColaboradores (getCOMMITS (tc));


	char *filename = fileNames(num);
	FILE *query2 = fopen (filename , "w");
	free(filename);

	fprintf (query2, "%.2f\n", ((float)n_colabs/(float)n_repos));
	fclose (query2);
}


void query3(TupleU tu, TupleC tc, int num){
	int nb = getNbots(getStatsUsers(tu));
	FILE *f = fopen ("tmp/botsIdQ3.txt", "r");

	if(f == NULL){
		int n = 0;
		int *b = getIdBots(getUSERS(tu), nb, &n);

		botsIdFile(b, n);
		f = fopen ("tmp/botsIdQ3.txt", "r");
	}

	int i=0, id, botsId[nb];
	char line[15];
	while(fgets(line, 15, (FILE*)f) ){
		id = atoi(line);
		botsId[i] = id;
		i++;
	}
	fclose(f);
	
	int r = getNBotColaborate(botsId, nb, getCOMMITS(tc));

	char *filename = fileNames(num);
	FILE *query3 = fopen (filename , "w");
	free(filename);

	fprintf (query3, "%d", r);
	fclose (query3);
	
}


void query4(TupleU tu, TupleC tc, int num){
	int n_users, n_commits;

	n_users = getUlength (getStatsUsers (tu)); 
	//n_users = getDifsOfCommiterId (getCOMMITS (tc)); // se for necessário ver pelos commits.

	n_commits = getClength (getStatsCommits (tc));

	char *filename = fileNames(num);
	FILE *query4 = fopen (filename , "w");
	free(filename);

	fprintf (query4, "%.2f\n", ((float)n_commits/(float)n_users));
	fclose (query4);
}

void query5(TupleU tu, TupleC tc, int n, char *date, char *time, int num){
	int i, used = 0;
	FILE *f = fopen ("tmp/commitAtQ5.txt", "r");

	if(f == NULL){
		used = getCommitsUsed(getCOMMITS(tc));
		int *ids;
		char **dates;

		ids = getAllCommiterIds(getCOMMITS(tc));
		dates = getAllCommit_At(getCOMMITS(tc));

		int committer_id;
		char *commit_at;
		Vids *d = init_vids(used);

		for(i=0; i<used; i++){
			committer_id = ids[i];
			commit_at = dates[i];

			d = insert_vids(d, committer_id, commit_at, i);
		}

		sort_Dates(d, used);

		commitAtFile(d, used);

		free(ids); free(dates); // free do conteudo do array feito automaticamente na funcao insert_vids
		free_vids(d, used);
		f = fopen ("tmp/commitAtQ5.txt", "r");
	}

	int ni = 0;
	int *l = getTopCommiters(f, date, time, &ni);
	fclose(f);
	
	int lgt = 0;
	VIDX v = create_vidx (l, ni, &lgt);
	free(l);

	char *filename = fileNames(num);
	FILE *query5 = fopen (filename , "w");
	free(filename);

	int id, x;
	char *login;

	for (i=0; i<n && i<lgt; i++){
		id = v[i]->id;
		x = v[i]->x;

		login = returnLoginWithId(getUSERS(tu),id);

		fprintf (query5, "%d;%s;%d\n", id, login, x);

		free(login);
	}

	free_vidx (v, lgt);
	fclose (query5);
}

void query6(TupleU tu, TupleC tc, TupleR tr, int n, char *language, int num){
	int nc = 0, nr = 0, i;
	int *rId = getNRepoLanguage(getREPOS(tr), language, &nr);
	int *cId = getCommiterLanguage(getCOMMITS(tc), rId, nr, &nc);
	free(rId);

	int lgt = 0;
	VIDX v = create_vidx (cId, nc, &lgt);
	free(cId);

	char *filename = fileNames(num);
	FILE *query6 = fopen (filename , "w");
	free(filename);

	int id, x;
	char *login;

	for (i=0; i<n && i<lgt; i++){
		id = v[i]->id;
		x = v[i]->x;

		login = returnLoginWithId(getUSERS(tu),id);

		fprintf (query6, "%d;%s;%d\n", id, login, x);

		free(login);
	}

	free_vidx (v, lgt);
	fclose (query6);
}


void query7(TupleC tc, TupleR tr, char *date, int num){
	
	int i, lenArr1 = 0, lenArr2 = 0;

	char *found, *aux, *string = strdup(date);
	aux = string;
	int c_pal;
	int ano, mes, dia;

	for (c_pal = 0; ((found = strsep(&string,"-\n")) != NULL); c_pal++){
		if(c_pal == 0){ano = atoi(found);}
		else if(c_pal == 1){mes = atoi(found);}
		else if(c_pal == 2){dia = atoi(found);}
	}

	free(aux);

	int *arr = getAboveDate(getCOMMITS(tc), ano, mes, dia, &lenArr1);
	int *repos_ids;
	repos_ids = getInactiveIds (getREPOS(tr), arr, lenArr1, &lenArr2);
	free (arr);

	char *filename = fileNames(num);
	FILE *query7 = fopen (filename , "w");
	free(filename);

	char *description;

	for(i=0; i<lenArr2; i++){
		description = returnDescriptionWithId(getREPOS(tr), repos_ids[i]);
		fprintf(query7, "%d;%s\n", repos_ids[i], description);
		free (description);
	}

	free (repos_ids);
	fclose (query7);
}


void query8(TupleR tr, int n, char *date, int num){
	int i, length = 0;

	Vids *v = getTopLanguages(tr, date, &length);

	char *filename = fileNames(num);
	FILE *query8 = fopen (filename , "w");
	free(filename);

	for (i=0; i<n && i<length ; i++){
		fprintf (query8, "%s\n", v[i]->str);
	}

	free_vids(v, length);
	fclose (query8);
}


void query9(TupleU tu, TupleC tc, int n, int num){
	int nl = 0, lgt = 0;

	int *l = getCommiterFriends(tu, tc, &nl);

	VIDX v = create_vidx (l, nl, &lgt);

	char *filename = fileNames(num);
	FILE *query9 = fopen (filename , "w");
	free(filename);

	int id, i;
	char *login;

	for (i=0; i<n && i<lgt; i++){
		id = v[i]->id;

		login = returnLoginWithId(getUSERS(tu),id);
		fprintf (query9, "%d;%s\n", id, login);
		free(login);
	}

	free_vidx (v, lgt);
	fclose (query9);
}

//query 10 

void query10(TupleC tc, TupleU tu, int n, int num){
    int i=0;
    char *login;
    int *id = idsMessage(getCOMMITS(tc), n);
    int *tamanho = tamMessage(getCOMMITS(tc), n);
    int *repo = repoMessage(getCOMMITS(tc), n);

	char *filename = fileNames(num);
	FILE *query10 = fopen (filename , "w");
	free(filename);


	for(i=0; i<n; i++){
        login = returnLoginWithId(getUSERS(tu),id[i]);
        fprintf(query10, "%d;%s;%d;%d\n", id[i], login, tamanho[i]-1, repo[i]);
        free (login);
	}

	free(id);
	free(tamanho);
	free(repo);
	fclose (query10);
}



void query(TupleU tu, TupleC tc, TupleR tr, const char* file){
	FILE *fp = fopen (file , "r");
	char line[10000];
    char *string, *found, *aux;
    int c_pal, query_id, n;
    char *language, *date, *time;
    int i;

    for(i=1; fgets(line, 10000, (FILE*)fp) ; i++){

		string = strdup(line);
		aux = string;

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

		free (aux);
    }

    fclose(fp);
}
