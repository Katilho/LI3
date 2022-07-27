#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./../include/exercicio-1.h"
#include "./../include/exercicio-2.h"
#include "./../include/parsing.h"
#include "./../include/query.h"
#include "./../include/printer.h"

int main(int argc, char const *argv[]){
	int qNum = -1, n;
	char dateI[30], dateF[30], language[50];

	//Filtração dos ficheiros
	printf ("\nFiltrando linhas inválidas..\n");
	exercicio1();
	exercicio2();

	printf ("A organizar os ficheiros..\n");
	TupleU tu = vusers();
    TupleC tc = vcommits();
    TupleR tr = vrepos();

	if(argc > 1){
		query(tu, tc, tr, argv[1]);
	}

	else{

		int outN = 1;

		while(qNum != 0){

			printf ("\n-------------------------------------------------------------------------------------------\n");
			printf ("| 1 |                   Quantidade de bots, organizações e utilizadores                   |\n");
			printf ("-------------------------------------------------------------------------------------------\n");
			printf ("| 2 |                    Número médio de colaboradores por repositório                    |\n");
			printf ("-------------------------------------------------------------------------------------------\n");
			printf ("| 3 |                         Quantidade de repositórios com bots                         |\n");
			printf ("-------------------------------------------------------------------------------------------\n");
			printf ("| 4 |                     Quantidade média de commits por utilizador                      |\n");
			printf ("-------------------------------------------------------------------------------------------\n");
			printf ("| 5 |        Top N de utilizadores mais ativos num determinado intervalo de datas         |\n");
			printf ("-------------------------------------------------------------------------------------------\n");
			printf ("| 6 | Top N de utilizadores com mais commits em repositórios de uma determinada linguagem |\n");
			printf ("-------------------------------------------------------------------------------------------\n");
			printf ("| 7 |               Repositórios inativos a partir de uma determinada data                |\n");
			printf ("-------------------------------------------------------------------------------------------\n");
			printf ("| 8 |        Top N de linguagens mais utilizadas a partir de uma determinada data         |\n");
			printf ("-------------------------------------------------------------------------------------------\n");
			printf ("| 9 |  Top N de utilizadores com mais commits em repositórios cujo owner é um amigo seu   |\n");
			printf ("-------------------------------------------------------------------------------------------\n");
			printf ("| 10 |      Top N de utilizadores com as maiores mensagens de commit por repositório      |\n");
			printf ("-------------------------------------------------------------------------------------------\n");
			printf ("| 0 |                                  Sair do programa                                   |\n");
			printf ("-------------------------------------------------------------------------------------------\n");

			printf("\nInsira opção: ");
			scanf("%d", &qNum);
			printf("\n");


			if (qNum > 10 || qNum < 0){
				printf("Opção de query inválida! Escolha uma das seguintes opções:\n");
			}

			else{

				switch(qNum){
				case 1:
					query1(tu, outN);
					printQ1(outN);
					break;

				case 2:
					query2(tc, tr, outN);
					printQ2(outN);
					break;

				case 3:
					query3(tu, tc, outN);
					printQ3(outN);
					break;

				case 4:
					query4(tu, tc, outN);
					printQ4(outN);
					break;

				case 5:
					printf("Insira número de utilizadores: ");
					scanf("%d", &n);

					printf("Insira a data inicial (YYYY/MM/DD): ");
					scanf("%s", dateI);

					printf("Insira a data final (YYYY/MM/DD): ");
					scanf("%s", dateF);
					printf("\n");

					query5(tu, tc, n, dateI, dateF, outN);
					printQ5 (outN);
					break;

				case 6:
					printf("Insira número de utilizadores: ");
					scanf("%d", &n);

					printf("Insira a linguagem: ");
					scanf("%s", language);
					printf("\n");

					query6(tu, tc, tr, n, language, outN);
					printQ6 (outN);
					break;

				case 7:
					printf("Insira a data (YYYY/MM/DD): ");
					scanf("%s", dateI);
					printf("\n");

					query7(tc, tr, dateI, outN);
					printQ7 (outN);
					break;

				case 8:
					printf("Insira número de linguagens: ");
					scanf("%d", &n);

					printf("Insira a data (YYYY/MM/DD): ");
					scanf("%s", dateI);
					printf("\n");

					query8(tr, n, dateI, outN);
					printQ8 (outN);
					break;

				case 9:
					printf("Insira número de utilizadores: ");
					scanf("%d", &n);
					printf("\n");

					query9(tu, tc, n, outN);
					printQ9 (outN);
					break;

				case 10:
					printf("Insira número de utilizadores: ");
					scanf("%d", &n);
					printf("\n");

					query10(tc, tu, n, outN);
					printQ10 (outN);
					break;
				}

			outN++;
			}
		}
	}
	freeTupleU(tu);
	freeTupleC(tc);
	freeTupleR(tr);

	return 0;
}