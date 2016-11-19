#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

#include "lexic.h"

char* readCommand(int argc, char *argv[]);
void ajuda(char *nome_programa);
FILE* openFile(char * filename);

int main(int argc, char *argv[]) {

  char* filename = readCommand(argc, argv);
  FILE* file = openFile(filename);
  //printf("%s\n", filename);
  lexical_analyzer(file);


}

char* readCommand(int argc, char *argv[]){
  int opcao;
  bool i_flag = false;

  while ((opcao = getopt(argc,argv,"hi:")) != -1) {
    switch (opcao) {
      case 'i':
        return optarg;
      case 'h':
        ajuda(argv[0]);
        return "";
      case '?':
      case ':':
      default:
        ajuda(argv[0]);
    }
  }

  if (!i_flag) {
  
    ajuda(argv[0]);
  }

  return optarg;
}

void ajuda(char *nome_programa) {
  printf("AJUDA!!\n");
  /*sprintf(buffer_err, "\n Usage: %s -i arquivo_entrada <opcoes>\n\
    \n  OPCOES:\n\
    -h,                      mostra tela de ajuda.\n", nome_programa);
  errexit(buffer_err);*/
}

FILE* openFile(char* filename){
  return fopen(filename, "r");
}