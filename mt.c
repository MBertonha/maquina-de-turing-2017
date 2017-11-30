#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inserirTuplas(char alfabeto[50], char estados[50], char funcao[50][50], char estadoInicial[3], char estadosFinais[50], char alfabetoAux[50], char simboloInicial[2],int *quantidade){
            int i = 0;
            int cont = 2;
            printf("\nSimbolos do alfabeto: FORMATO a,b,c\n\n");
            scanf("%s", alfabeto);
            fflush(stdin); //limpa o buffer do teclado
            printf("\nConjunto de estados possiveis: FORMATO q0,q1,q2\n");
            scanf("%s", estados);
            fflush(stdin);
            printf("Quantidadeidade de transicoes: \n");
            scanf("%d",&(*quantidade));
            for(i=0; i<*quantidade; i++){
                printf("Informe a transicao %d: \nFORMATO q0,a,A,D,q1 Isso equivale a (q0,a) = (q1,A,D))\n", i+1);
                scanf("%s", funcao[i]);
                fflush(stdin);
            }

            printf("Informe o estado inicial: \n");
            scanf("%s", estadoInicial);
            fflush(stdin);
            printf("Conjunto de estados finais: \n");
            printf("FORMATO: q0,q1,q2\n");
            scanf("%s", estadosFinais);
            fflush(stdin);
            printf("Essa MT possui alfabeto auxiliar?   Y-SIM / 2-NAO\n");
            scanf("%d",&cont);
            if(cont==1){
                printf("Informe o alfabeto auxiliar: FORMATO: a,b,c\n");
                scanf("%s",alfabetoAux);
                fflush(stdin);
            }
            else alfabetoAux[0] = '\0';

            printf("Informe o marcador de inicio\n");
            scanf("%s",simboloInicial);
            fflush(stdin);
}
int testarEstadoAtual(char estadoAtual[3], char estadosFinais[50]){  //Verifica se o estado passado (atual) é o um dos estados finais
    char aux[3];
    int i=0;
    int j=0;
    for(i=0; i<strlen(estadosFinais); i++){   //calcula o tamanho da string até o comprimento final
            if(estadosFinais[i]==','){
               j=0;
               continue;
            }
            aux[j] = estadosFinais[i];
            j++;
            if(j==2){
                aux[2] = '\0';
                if(strcmp(estadoAtual,aux)==0)
                    return 1;
            }
    }
    return 0;
}
void reconhecerPalavra(char alfabeto[50], char estados[50], char funcao[50][50], char estadoInicial[3], char estadosFinais[50], char alfabetoAux[50], char simboloInicial[2], char simbFim[2], int *quantidade, char palavra[100]){
    int cont = 0;
    int cont2 = 0;
    int i=0;
    char palavraAux[100];
    palavraAux[0] = simboloInicial[0];
    char estadoAtual[3];
    char estadoAux[3];
    char aux2[3];
    int j=0;
    int cont3=0;
//Concatena o simbolo inicial com a palavra que foi inserida
    for(i=0; i<49;i++)
        palavraAux[i] = '~';
        palavraAux[49] = '\0';
        palavraAux[0] = simboloInicial[0];
    for(i=1; i<=strlen(palavra); i++){ //faz com que o resto da palavra seja passada para a palavra auxiliar e assim passar
        palavraAux[i] = palavra[j];
        j++;
    }
    j=1;

    strcpy(estadoAtual, estadoInicial);  //copia a string estadu atual para o estado inicial

    while(testarEstadoAtual(estadoAtual, estadosFinais) == 0){  //executa a função de comparação até que um estado final é encontrado
            cont3 = 0;
            for(i=0; i<*quantidade; i++){  //looping para a quantidade de funções
                estadoAux[0] = funcao[i][0]; //passa os valores da função que ele deseja para a variavel auxiliar
                estadoAux[1] = funcao[i][1];
                estadoAux[2] = '\0';
                if(strcmp(estadoAtual, estadoAux)==0){ //se o estado inicial for igual ao estado atual da fita, entra no if
                        if(palavraAux[j]==funcao[i][3]){
                            cont3 = 1;
                            palavraAux[j] = funcao[i][5]; //escreve o simbolo X na fita
                            if(funcao[i][7]=='D'){   //compara se o bit de avançar é o mesmo da função
                                j++;
                            }
                            else{  //se nao vai para a D vai para a E
                                j--;
                            }
                            estadoAtual[0] = funcao[i][9]; //passa todo o conteudo do final da função principal para o estado atual
                            estadoAtual[1] = funcao[i][10]; //ou seja se a função fala que (q1,a) -> (q2,A,D)
                            estadoAtual[2] = '\0';
                            if(j<0){
                                cont2 = 1;
                                break;
                            }
                            break;
                        }
                }
            }
            if(cont2==1)  //verifica se a fita passou do limite se ela nao foi muito para a E
                break;
            if(cont3==0) //significa que nao entrou em nenhuma outra função que satisfaça o estado atual
                break;
    }
    if(cont2==1||cont3==0||(testarEstadoAtual(estadoAtual, estadosFinais)==0)){
        printf("A palavra %s foi REJEITADA!\n", palavra);
    }
    else{
        if((testarEstadoAtual(estadoAtual, estadosFinais)==1)){
            printf("A palavra %s foi ACEITA!\n", palavra);
        }
    }
}
int main(){
    char alfabeto[50];
    char estados[50];
    char funcao[50][50];
    char estadoInicial[3];
    char estadosFinais[50];
    char alfabetoAux[50];
    char simboloInicial[2];
    char simbFim[2];
    int i = 0;
    int quantidade=0;
    char palavra[100];
    int resp=1;

    inserirTuplas (alfabeto, estados, funcao, estadoInicial, estadosFinais, alfabetoAux, simboloInicial,&quantidade);
    do{
        printf("Informe a palavra a ser reconhecida: \n");
        scanf("%s", palavra);
        fflush(stdin);
        reconhecerPalavra(alfabeto, estados, funcao, estadoInicial, estadosFinais, alfabetoAux, simboloInicial, simbFim, &quantidade, palavra);
        printf("Deseja reconhecer outra palavra ? 1-SIM / 2-NAO\n");
        scanf("%d",&resp);
    }
    while(resp==1);
system("pause");
return 0;
}
