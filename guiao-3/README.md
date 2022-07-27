## Requisitos
Implementação de um menu interativo com o utilizador e de um mecanismo de medição de desempenho das queries. 
Especificação dos requisitos do guião III no seguinte [enunciado](https://github.com/Katilho/LI3/blob/main/guiao-3/LI3-Guia%CC%83o%20III.pdf).  

## Comandos da Makefile
Este comando gera o executável.
```
$ make
```  
Este comando invoca o menu de escolha de queries.
```
$ make menu
```  
Este comando executa as queries especificadas no ficheiro de texto "commands.txt".
```
$ make query
```  
Este comando executa as queries especificadas no ficheiro de texto "testcommands.txt" dando informaçôes sobre o desempenho das queries.
```
$ make test
```  
Este comando elimina ficheiros resultantes da compilação e execução do executável.
```
$ make clean
```  
