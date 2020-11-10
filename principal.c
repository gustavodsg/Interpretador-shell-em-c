#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

void  remover_espacos(char *entrada, char **vetor_com_comando_e_argumentos){
     while (*entrada != '\0'){
          while ( *entrada == ' ' || *entrada == '\t')
               *entrada++ = '\0';
          *vetor_com_comando_e_argumentos++ = entrada;
          while (*entrada != '\0' && *entrada != ' ' && *entrada != '\t' && *entrada != '\n') 
               entrada++;
     }
     *vetor_com_comando_e_argumentos = '\0';
}

void  execucao(char **vetor_com_comando_e_argumentos){
     pid_t pid;
     int status;
     
     if ((pid = fork()) < 0){
          printf("Erro executando o fork.\n");
          exit(1);
     } else if (pid == 0){
          if (execvp(*vetor_com_comando_e_argumentos, vetor_com_comando_e_argumentos) < 0){
               printf("Comando não encontrado.\n");
               exit(1);
          }
     } else{
          while (wait(&status) != pid);
     }
}

void main(){
    char entrada[513];
    char *vetor_com_comando_e_argumentos[50];
    char *token;
      
    while(1){
          printf("meu-shell> ");
          gets(entrada);
          if(strlen(entrada)>512){
               printf("Erro: só é permitido a entrada máxima de 512 caracteres.\n");
          }
          token = strtok(entrada,",");
          while (token != NULL) { 
               remover_espacos(token, vetor_com_comando_e_argumentos);
               if(!strcmp(vetor_com_comando_e_argumentos[0],"quit"))
                    exit(0);
               execucao(vetor_com_comando_e_argumentos);
               token = strtok(NULL, ","); 
          }
     }
}

