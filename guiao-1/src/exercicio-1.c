#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>

// Verifica se a string representa um número inteiro não negativo
int validpos (char *found) {

   int i, r = 1;

   if (strlen(found) == 0) return 0;

   if (found [0] == '\r' || found [0] == '\n') return 0;

   for (i=0; r == 1 && found[i] != '\0' && found[i] != '\r' && found[i] != '\n' ; i++){
        if (!(isdigit (found [i])) ) r = 0;
   }
   
   return r;
}

// Verifica se a string está vazia
int validstring (char *found) {
   if(strlen(found) == 0)
      return 0;
   return 1;
}

// Verifica se a string é "User", "Bot" ou "Organization"
int validtype (char *found) {
   int r = 0;

   if (strcmp (found, "User") == 0) r = 1;
   else if (strcmp (found, "Bot") == 0) r = 1;
   else if (strcmp (found, "Organization") == 0) r = 1;
   
   return r;
}

// Verifica se a data está de acordo com os limites definidos (usa o include <time.h>)
int validdata (char *found) {

   int ano, mes, dia, hora, min, seg, r, i;
   char *data;

   time_t t = time(NULL);
 
   struct tm tm = *localtime(&t);

   for (i = 0; (data = strsep(&found, "- :.")); i++) {
      if (i == 0){
         ano = atoi(data);
      }
      if (i == 1){
         mes = atoi(data);
      }
      if (i == 2){
         dia = atoi(data);
      }
      if (i == 3){
         hora = atoi(data);
      }
      if (i == 4){
         min = atoi(data);
      }
      if (i == 5){
         seg = atoi(data);
      }
   }

   r = 1;

   if (i != 6) r = 0;
   else if (ano < 2005 || ano > tm.tm_year + 1900) r = 0; //
   else if (ano <= 0 || mes <= 0 || mes > 12 || dia <= 0 || dia > 31) r = 0;
   else if (ano == tm.tm_year + 1900 && mes > tm.tm_mon + 1) r = 0; //
   else if (ano == tm.tm_year + 1900 && mes == tm.tm_mon + 1 && dia > tm.tm_mday) r = 0; //
   else if (ano == tm.tm_year + 1900 && mes == tm.tm_mon + 1 && dia == tm.tm_mday && hora > tm.tm_hour) r = 0; //
   else if (ano == tm.tm_year + 1900 && mes == tm.tm_mon + 1 && dia == tm.tm_mday && hora == tm.tm_hour && min > tm.tm_min) r = 0; //
   else if (ano == tm.tm_year + 1900 && mes == tm.tm_mon + 1 && dia == tm.tm_mday && hora == tm.tm_hour && min == tm.tm_min && seg > tm.tm_sec) r = 0; //
   else if (ano == 2005 && mes < 4) r = 0;
   else if (ano == 2005 && mes == 4 && dia < 7) r = 0;
   else if (mes <= 7 && (mes % 2) == 0 && dia > 30) r = 0;
   else if (mes > 7 && (mes % 2) == 1 && dia > 30) r = 0;
   else if (mes == 2 && dia > 29) r = 0;
   else if ( (!( ( ano % 4 == 0 && ano % 100 != 0 ) || ano % 400 == 0 ) ) && mes == 2 && dia > 28) r = 0; // trata dos anos bissextos
   else if (hora > 23 || min > 59 || seg > 59) r = 0;

   return r;
}

// Remove os chars "[" e "]" de uma string.
void removePrts(char *str) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != ']' && *dst != '[') dst++;
    }
    *dst = '\0';
}


// Indica quantos elementos tem um array(string)
int n_array (char *found) {
   char *number;
   int i;

   if (strlen (found) == 0) return -1;  

   if (found [0] != '[') return -1;

   removePrts (found);

   for (i = 0; (number = strsep(&found, ",")); i++) {

      if (strlen (number) == 0) return 0;

   }
   
   return i;
}


// Para validar tipos Bool
int validBool (char *found) {

   int r = 0;

   if (strcmp ("True", found) == 0) r = 1;
   else if (strcmp ("False", found) == 0) r = 1;
   
   return r;
}

// Criação do "users-ok.csv"
void vusers () {
   FILE *fp = fopen ("entrada/users.csv" , "r");
   FILE *users_ok = fopen ("saida/users-ok.csv" , "w");
   char line[200000];
   char *string, *found;
   int c_pal;
   int followers, following;
   int checker;

      for (int i=0; ( fgets(line, 200000, (FILE*)fp) ); i++) {

         if (i==0) fprintf(users_ok,"%s", line);

         else {

    string = strdup(line);

    for (c_pal = 0, checker = 1 ; ((found = strsep(&string,";")) != NULL && checker != 0); c_pal++) {
      
      //id
      if (c_pal == 0) {checker = validpos (found);}

      //login
      if (c_pal == 1) {checker = validstring (found);}

      //type
      if (c_pal == 2) {checker = validtype (found);}

      //created_at
      if (c_pal == 3) {checker = validdata (found);}

      //followers
      if (c_pal == 4) {
         checker = validpos (found);
         followers = atoi (found);
      }

      //followers_list
      if (c_pal == 5) {
         checker = (n_array (found) == followers) ;
      } 


      //following
      if (c_pal == 6) {
         checker = validpos (found);
         following = atoi (found);
      }

      //following_list
      if (c_pal == 7) {
         checker = (n_array (found) == following) ;
      }

      //public_gists
      if (c_pal == 8) {checker = validpos (found);}

      //public_repos
      if (c_pal == 9) {checker = validpos (found);}

       }
    }

    if (checker != 0 && c_pal == 10) fprintf(users_ok,"%s", line);
 }
    fclose (fp);
    fclose (users_ok);
}

// Criação do "commits-ok.csv"
void vcommits () {
   FILE *fp = fopen ("entrada/commits.csv" , "r");
   FILE *commits_ok = fopen ("saida/commits-ok.csv" , "w");
   char line[800];
   char *string, *found;
   int c_pal;
   int checker;

      for (int i=0; ( fgets(line, 800, (FILE*)fp) ); i++) {

         if (i==0) fprintf(commits_ok,"%s", line);

         else {

    string = strdup(line);

    for (c_pal = 0, checker = 1 ; ((found = strsep(&string,";")) != NULL && checker != 0); c_pal++) {
      
      //repo_id
      if (c_pal == 0) {checker = validpos (found);}

      //author_id
      if (c_pal == 1) {checker = validpos (found);}

      //committer_id
      if (c_pal == 2) {checker = validpos (found);}

      //commit_at
      if (c_pal == 3) {checker = validdata (found);}

      //message
      if (c_pal == 4) {checker = 1;}
       }
    }

    if (checker != 0 && c_pal == 5) fprintf(commits_ok,"%s", line);
 }
    fclose (fp);
    fclose (commits_ok);
}

// Criação do "repos-ok.csv"
void vrepos () {
   FILE *fp = fopen ("entrada/repos.csv" , "r");
   FILE *repos_ok = fopen ("saida/repos-ok.csv" , "w");
   char line[66000];
   char *string, *found;
   int c_pal;
   int checker;

      for (int i=0; ( fgets(line, 66000, (FILE*)fp) ); i++) {

         if (i==0) fprintf(repos_ok,"%s", line);

         else {

    string = strdup(line);

    for (c_pal = 0, checker = 1 ; ((found = strsep(&string,";")) != NULL && checker != 0); c_pal++) {
      
      //id
      if (c_pal == 0) {checker = validpos (found);}

      //owner_id
      if (c_pal == 1) {checker = validpos (found);}

      //full_name
      if (c_pal == 2) {checker = validstring (found);}

      //license
      if (c_pal == 3) {checker = validstring (found);}

      //has_wiki
      if (c_pal == 4) {checker = validBool (found);}

      //description
      if (c_pal == 5) {checker = 1;}

      //language
      if (c_pal == 6) {checker = validstring (found);}

      //default_branch
      if (c_pal == 7) {checker = validstring (found);}

      //created_at
      if (c_pal == 8) {checker = validdata (found);}

      //updated_at
      if (c_pal == 9) {checker = validdata (found);}

      //forks_count
      if (c_pal == 10) {checker = validpos (found);}

      //open_issues
      if (c_pal == 11) {checker = validpos (found);}

      //stargazers_count
      if (c_pal == 12) {checker = validpos (found);}

      //size
      if (c_pal == 13) {checker = validpos (found);}
       }
    }

    if (checker != 0 && c_pal == 14) fprintf(repos_ok,"%s", line);
 }
    fclose (fp);
    fclose (repos_ok);
}

// Função principal
int exercicio1 () {
   vusers();
   vcommits();
   vrepos();
   return 0;
}