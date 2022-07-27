#include "./../libs/exercicio-1.h"
#include "./../libs/exercicio-2.h"

int main(int argc, char** argv) {
	if(strcmp(argv [1], "exercicio-1") == 0) {
		exercicio1 ();
	}
	else if(strcmp(argv [1], "exercicio-2") == 0){
		exercicio2 ();
	}
}