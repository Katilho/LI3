#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <time.h>

#include "./../include/exercicio-1.h"
#include "./../include/exercicio-2.h"
#include "./../include/parsing.h"
//#include "./../include/query.h"
#include "./../include/timetests.h"
#include "./../include/functionaltests.h"



int main(int argc, char const *argv[]){


	   //clock_t start, end;
	   //double cpu_time_used;

        printf ("\nFiltrando linhas inválidas..\n");
    
        //start = clock();
        exercicio1();
        exercicio2();
        //end = clock();
        //cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
        //printf("Linhas inválidas filtradas em %f seg.\n", cpu_time_used);

    
        printf ("A organizar os ficheiros..\n");

        //start = clock();
        TupleU tu = vusers();
        TupleC tc = vcommits();
        TupleR tr = vrepos();
        //end = clock();
        //cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        //printf("Ficheiros organizados em %f seg.\n", cpu_time_used);

    
        printf("\nTestes de Desempenho:\n");
        
        if (argc == 1) querytests(tu, tc, tr, "testcommands.txt");
        else querytests(tu, tc, tr, argv[1]);

        freeTupleU(tu);
        freeTupleC(tc);
        freeTupleR(tr);

        printf("\nTestes Funcionais:\n");
        
        if (argc == 1) compareQuery("testcommands.txt");
        else compareQuery(argv[1]);


    return 0;
}