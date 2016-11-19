#include "lexic.h"
#include <stdbool.h>
#include <string.h>

char keys[32][10]={"auto","break","case","char","const","continue","default",
"do","double","else","enum","extern","float","for","goto",
"if","int","long","register","return","short","signed",
"sizeof","static","struct","switch","typedef","union",
"unsigned","void","volatile","while"};
int keys_length = 32;

char* symbols = ",;(){}[]#\"";
int symbols_length = 10;

char* oper = "!%^&*-+=~|.<>/?";
int oper_length = 15;

char* separation = " \n\t";
int separation_length = 3;

char token[50];
int linha = 0;
int coluna = 0;
int ch_lido = 0;

void getNextToken(FILE* file);
bool isSeparation(char ch);
bool isSymbol(char ch);
bool isOperator(char ch);
bool isKey();
bool isIdentifier();
bool isPertence(char ch, int min, int max);

void lexical_analyzer(FILE* file){
  int i;
  for(i = 0; i < 10; i++){
    getNextToken(file);
    printf("%s -- ", token);
    //printf("\n\n");
    if(isKey()){
      printf("%s\n", "KEYWORD");
    } else if(isOperator(token[0])){
      printf("%s\n", "OPERATOR");
    } else if(isSymbol(token[0])){
      printf("%s\n", "SYMBOL");
    } else if(isIdentifier()){
      printf("%s\n", "IDENTIFIER");
    } else {
      printf("%s\n", "NUMBER");
    }

    printf("\n");
  }
  
}

void getNextToken(FILE* file){
  //token = "";
  int i = 0;
  
  for(i = 0; i < 50; i++){
    token[i] = '\0';
  }

  i = 0;

  fseek(file, 0, ch_lido);
  char ch = fgetc(file);
  coluna++;
  ch_lido++;

  while(isSeparation(ch) || isSymbol(ch)){
    if(ch == '\n'){
      linha++;
      coluna = 0;
    }

    ch = fgetc(file);
    coluna++;
    ch_lido++;

    if(isSymbol(ch)){
      token[0] = ch;
      return;
    }

  }

  while(!isSeparation(ch) && !isSymbol(ch) && ch != EOF){
    
    //printf("CH => %c\n", ch);
    token[i] = ch;
    i++;
    //strcat(token, &ch);
    ch = fgetc(file);
    coluna++;
    ch_lido++;
  }
  if(ch == '\n'){
    linha++;
    coluna = 0;
  }

  if(isSymbol(ch)){
    coluna--;
    ch_lido--;
  }

  //return token;
}

bool isSeparation(char ch){
  int i;
  for(i = 0; i < separation_length; i++){
    if(ch == separation[i]){
      return true;
    }
  }
  return false;
}

bool isSymbol(char ch){
  int i;
  for(i = 0; i < symbols_length; i++){
    if(ch == symbols[i]){
      return true;
    }
  }
  return false;
}

bool isOperator(char ch){
  int i;
  for(i = 0; i < oper_length; i++){
    if(ch == oper[i]){
      return true;
    }
  }
  return false;
}

bool isKey(){
  int i,j;
  bool find = false;
  for(i = 0; i < keys_length; i++){
    if(find){
      return true;
    }
    for(j = 0; j < 10; j++){
      if(keys[i][j] != token[j]){
        find = false;
        break;
      } else {
        find = true;
      }
    }
  }
  return false;
}

bool isIdentifier(){
  if(!isPertence(token[0], 65, 90) && !isPertence(token[0], 95, 95) && !isPertence(token[0], 97, 122)){
    return false;
  }

  //printf("PRIMEIRO IF => %s\n", token);
  int i;

  for(i = 1; i < 50; i++){
    if(token[i] == '\0'){
      return true;
    }
    if(!isPertence(token[i], 65, 90) && !isPertence(token[i], 95, 95) && !isPertence(token[i], 97, 122) && !isPertence(token[i], 48, 57)){
      return false;
    }
  }
  return true;
}


bool isPertence(char ch, int min, int max){
  int i;
  for(i = min; i <= max; i++){
    if(ch == i){
      return true;
    }
  }
  return false;
}