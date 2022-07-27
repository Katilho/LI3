#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "./../include/tuple.h"
#include "./../include/query.h"
#include "./../include/timetests.h"

//Número de testes feitos em cada query
#define NUM_TESTS  10 // minimo de 3.


void querytests(TupleU tu, TupleC tc, TupleR tr, const char* file){
	FILE *fp = fopen (file , "r");
	char line[200];
    char *string, *found, *aux;
    int c_pal, query_id, n;
    char *language, *date, *time;
    int i, j;

    clock_t start, end;
    double cpu_time_used, cpu_time_sums , min , max;

    printf("O número de execuções feitas para cada query é %d.\n", NUM_TESTS);

    for(i=1; fgets(line, 200, (FILE*)fp) ; i++){

		string = strdup(line);
		aux = string;

		for (c_pal = 0; ((found = strsep(&string," \n")) != NULL); c_pal++){

			if (c_pal == 0) {query_id = atoi(found);}
			else if(query_id == 5 && c_pal == 1) {n = atoi(found);}
			else if(query_id == 5 && c_pal == 2) {date = strdup(found);}
			else if(query_id == 5 && c_pal == 3) {time = strdup(found);}
			else if(query_id == 6 && c_pal == 1) {n = atoi(found);}
			else if(query_id == 6 && c_pal == 2) {language = strdup(found);}
			else if(query_id == 7 && c_pal == 1) {date = strdup(found);}
			else if(query_id == 8 && c_pal == 1) {n = atoi(found);}
			else if(query_id == 8 && c_pal == 2) {date = strdup(found);}
			else if(query_id == 9 && c_pal == 1) {n = atoi(found);}
			else if(query_id == 10 && c_pal == 1) {n = atoi(found);}

		}

		free(aux);

		if (query_id == 1) {
			printf("\nTestes na Query 1:\n");
			for(j=0, min = 5000, max = -1, cpu_time_sums = 0; j<NUM_TESTS; j++){
				start = clock();
				query1(tu, i);
				end = clock();

				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
				if (cpu_time_used < min) min = cpu_time_used;
				if (cpu_time_used > max) max = cpu_time_used;
				cpu_time_sums += cpu_time_used;
			}
		}
		else if (query_id == 2) {
			printf("\nTestes na Query 2:\n");
			for(j=0, min = 5000, max = -1, cpu_time_sums = 0; j<NUM_TESTS; j++){
				start = clock();
				query2(tc, tr, i);
				end = clock();

				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
				if (cpu_time_used < min) min = cpu_time_used;
				if (cpu_time_used > max) max = cpu_time_used;
				cpu_time_sums += cpu_time_used;
			}
		}
		else if (query_id == 3) {
			printf("\nTestes na Query 3:\n");
			for(j=0, min = 5000, max = -1, cpu_time_sums = 0; j<NUM_TESTS; j++){
				start = clock();
				query3(tu, tc, i);
				end = clock();

				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
				if (cpu_time_used < min) min = cpu_time_used;
				if (cpu_time_used > max) max = cpu_time_used;
				cpu_time_sums += cpu_time_used;
			}
		}
		else if (query_id == 4) {
			printf("\nTestes na Query 4:\n");
			for(j=0, min = 5000, max = -1, cpu_time_sums = 0; j<NUM_TESTS; j++){
				start = clock();
				query4(tu, tc, i);
				end = clock();

				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
				if (cpu_time_used < min) min = cpu_time_used;
				if (cpu_time_used > max) max = cpu_time_used;
				cpu_time_sums += cpu_time_used;
			}
		}
		else if (query_id == 5) {
			printf("\nTestes na Query 5:\n");
			printf("Argumentos utilizados: N = %d | Data inicial: %s | Data final: %s\n", n, date, time);
			for(j=0, min = 5000, max = -1, cpu_time_sums = 0; j<NUM_TESTS; j++){
				start = clock();
				query5(tu, tc, n, date, time, i);
				end = clock();

				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
				if (cpu_time_used < min) min = cpu_time_used;
				if (cpu_time_used > max) max = cpu_time_used;
				cpu_time_sums += cpu_time_used;
			}
			free(date); free (time);
		}
		else if (query_id == 6) {
			printf("\nTestes na Query 6:\n");
			printf("Argumentos utilizados: N = %d | Linguagem: %s\n", n, language);
			for(j=0, min = 5000, max = -1, cpu_time_sums = 0; j<NUM_TESTS; j++){
				start = clock();
				query6(tu, tc, tr, n, language, i);
				end = clock();

				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
				if (cpu_time_used < min) min = cpu_time_used;
				if (cpu_time_used > max) max = cpu_time_used;
				cpu_time_sums += cpu_time_used;
			}
			free(language);
		}
		else if (query_id == 7) {
			printf("\nTestes na Query 7:\n");
			printf("Argumentos utilizados: Data: %s\n", date);
			for(j=0, min = 5000, max = -1, cpu_time_sums = 0; j<NUM_TESTS; j++){
				start = clock();
				query7(tc, tr, date, i);
				end = clock();

				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
				if (cpu_time_used < min) min = cpu_time_used;
				if (cpu_time_used > max) max = cpu_time_used;
				cpu_time_sums += cpu_time_used;
			}
			free(date);
		}
		else if (query_id == 8) {
			printf("\nTestes na Query 8:\n");
			printf("Argumentos utilizados: N = %d | Data: %s\n", n, date);
			for(j=0, min = 5000, max = -1, cpu_time_sums = 0; j<NUM_TESTS; j++){
				start = clock();
				query8(tr, n, date, i);
				end = clock();

				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
				if (cpu_time_used < min) min = cpu_time_used;
				if (cpu_time_used > max) max = cpu_time_used;
				cpu_time_sums += cpu_time_used;
			}
			free(date);
		}
		else if (query_id == 9) {
			printf("\nTestes na Query 9:\n");
			printf("Argumentos utilizados: N = %d\n", n);
			for(j=0, min = 5000, max = -1, cpu_time_sums = 0; j<NUM_TESTS; j++){
				start = clock();
				query9(tu, tc, n, i);
				end = clock();

				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
				if (cpu_time_used < min) min = cpu_time_used;
				if (cpu_time_used > max) max = cpu_time_used;
				cpu_time_sums += cpu_time_used;
			}
		}
		else if (query_id == 10) {
			printf("\nTestes na Query 10:\n");
			printf("Argumentos utilizados: N = %d\n", n);
			for(j=0, min = 5000, max = -1, cpu_time_sums = 0; j<NUM_TESTS; j++){
				start = clock();
				query10(tc, tu, n, i);
				end = clock();

				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
				if (cpu_time_used < min) min = cpu_time_used;
				if (cpu_time_used > max) max = cpu_time_used;
				cpu_time_sums += cpu_time_used;
			}
		}

		cpu_time_sums = cpu_time_sums - max - min;
		cpu_time_used = cpu_time_sums / (NUM_TESTS-2);

		printf("CPU Average Time: %f seg.\n", cpu_time_used );

    }
    fclose(fp);
}
