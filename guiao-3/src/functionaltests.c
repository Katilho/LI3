#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./../include/tuple.h"
#include "./../include/query.h"
#include "./../include/functionaltests.h"


static char* outputFile(int n){
	char *outputFile = malloc(sizeof(char)*30);
    sprintf(outputFile, "saida/command%d_output.txt", n);
    return outputFile;
}


static char* expectedFile(int n){
	char *expectedFile = malloc(sizeof(char)*30);
    sprintf(expectedFile, "expectedFiles/expectedFile%d.txt", n);
    return expectedFile;
}


static int compareFiles (char* file1, char* file2){
    int l = 1, r = 0;
    char c1 = 'a', c2 = 'a';

    FILE *f1 = fopen (file1 , "r");
    FILE *f2 = fopen (file2 , "r");

    if (f1 == NULL || f2 == NULL) {
        printf ("Não foi possível abrir um ficheiro!");
        fclose (f1);
        fclose (f2);
        return -1;
    }

    while (r == 0 && c1 != EOF && c2 != EOF){
        c1 = fgetc(f1);
        c2 = fgetc(f2);
        if (c1!=c2) r = l;
        if (c1 == '\n') l++;
    }

    if (c1 != EOF || c2 != EOF) r = l;

    fclose (f1);
    fclose (f2);
    return r;
}

static int num_of_commands(FILE *fp){
    int i;
    char line[200];
    for (i=0; fgets(line, 200, fp); i++);
    return i;
}


void compareQuery (const char* file){
	int i, n, nCommands;

    FILE *fp = fopen (file, "r");
    nCommands = num_of_commands(fp);
    fclose (fp);	

	for(i=1; i <= nCommands; i++){
		n = compareFiles(outputFile(i), expectedFile(i));
		if(n == 0){
			printf("A Query %d foi executada de forma correta\n", i);
		}

		else{
			printf("A Query %d não foi executada de forma correta, sendo encontrado uma diferença na linha %d\n", i, n);
		}
	}
}