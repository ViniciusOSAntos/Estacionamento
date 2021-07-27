#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Estacionamento.h"
//limpa a tela e espera qualquer entrada do usuário para seguir com o programa
void limpaTela();
// chama o menu
int item_menu(void);
// entradas de configuração do estacionamento
Pilha** configura_estacionamento(Pilha** estacionamento, Pilha* rua);
// utiliza a função de impressão do TAD para exibir um layout do estacionamento para o usuário
void exibe_estacionamento(Pilha** estacionamento);
// utiliza da função de inserção do tad e apresenta um layout para entradas do usuário
void insere(Pilha** estacionamento);
// entradas de configuração da rua
Pilha* configura_rua(Pilha* rua);
// utiliza da função de retirada do tad e apresenta um layout para entradas do usuário
void retira_carro(Pilha** estacionamento, Pilha* rua);
// utiliza a função de impressão do TAD para exibir um layout da rua para o usuário
void exibe_rua(Pilha* rua);


int numP, numC, numR, configurada = 0, cont = 0;;
int main()
{
    setlocale(LC_ALL, "");
    Pilha** estacionamento = NULL;
    Pilha* rua = NULL;
    int item;
    for(;;)
    {
        item = item_menu();
        switch(item)
        {
        case 1:
            estacionamento = configura_estacionamento(estacionamento, rua);
            rua = configura_rua(rua);
            limpaTela();
            break;
        case 2:
            insere(estacionamento);
            limpaTela();
            break;
        case 3:
            exibe_estacionamento(estacionamento);
            exibe_rua(rua);
            limpaTela();
            break;
        case 4:
            retira_carro(estacionamento, rua);
            limpaTela();
            break;
        case 0:
            exit(EXIT_SUCCESS);

        }
    }
}
int item_menu(void)
{
    fflush(stdin);
    char s[80];
    int c;

    printf("\n");
    printf("Menu:\n");
    printf("1. Configura estacionamento.\n");
    printf("2. Insere carro.\n");
    printf("3. Exibe estacionamento.\n");
    printf("4. Retira carro.\n");

    printf("0. Sair\n");

    do
    {
        printf("\nEntre com sua escolha: ");
        scanf("%s",s);
        c = atoi(s);
    }
    while(c<0 || c>=6);

    return c;
}
void limpaTela() //função auxiliar para interface com o usuário
{
    system("pause");
    system("cls");
}
Pilha** configura_estacionamento(Pilha** estacionamento, Pilha* rua) //lê propriedades, cria e imprime o estacionamento
{
    int num_carros, num_pilhas, i = 0;
    configurada = 1;
    system("cls");

    do
    {
        printf("Entre com o N de pilhas: ");  //leitrura
        scanf("%d", &num_pilhas);
        numP = num_pilhas;
    }
    while(num_pilhas < 1);
    do
    {
        printf("Entre com o N de carros por pilha: ");
        scanf("%d", &num_carros);
        numC = num_carros;
    }
    while(num_carros < 1);





    estacionamento = inicia_estacionamento(num_pilhas); //criação
    rua = pilha_cria();

    while(i < num_pilhas)
    {
        imprime_estacionamento(estacionamento[i], num_carros);
        i++;
        printf("\n");
    }
    return estacionamento;
}
Pilha* configura_rua(Pilha* rua) //lê propriedades, cria e imprime a rua
{
    int  num_carros_rua;
    do
    {
        printf("Entre com o N de carros na rua: ");
        scanf("%d", &num_carros_rua);
    }
    while(num_carros_rua < 1);

    numR = num_carros_rua;
    rua = pilha_cria();

    printf("\nRua:\n");
    imprime_estacionamento(rua, numR);
    printf("\n");
    return rua;

}
void exibe_estacionamento(Pilha** estacionamento) //printa o estacionamento usando a fucn imprime_estacionamento
{
    int i = 0;

    system("cls");
    if(configurada == 0)
    {
        printf("\nEstacionamento ainda NÃO configurado!\n");
        return;
    }
    while(i < numP)
    {
        imprime_estacionamento(estacionamento[i], numC);
        i++;
        printf("\n");
    }
}
void exibe_rua(Pilha* rua) // printa a rua usando a func imprime_estacionamento
{
    int i = 0;
    if(configurada == 0)
    {
        //printf("\nEstacionamento ainda NÃO configurado!\n");
        return;
    }

    printf("\nRua:\n");
    imprime_estacionamento(rua, numR);
    i++;
    printf("\n");

}
void insere(Pilha** estacionamento) //lê pos e usa sugere_posicao / insere_carro do tad
{
    int pos, aprova, tempo, teste;
    char* s = malloc(9*sizeof(char));
    system("cls");

    if(configurada == 0)
    {
        printf("\nEstacionamento ainda NÃO configurado!\n");
        return;
    }


    pos = est_cheio(estacionamento, numP,  numC);
    if(pos == 1)
    {
        printf("\nEstacionamento lotado!\n");
        return;
    }

    printf("\nEntre com a placa: ");
    fflush(stdin);
    gets(s);
    teste = encontra_placa(estacionamento, numP, s );

    if(teste != -1)
    {
        printf("\nPlaca já inserida no estacionamento!\n");  //impede placa repetida no estacionamento
        return;
    }

    do
    {
        do
        {
            printf("\nEntre com o tempo que o carro ficará no estacionamento: ");
            scanf("%d", &tempo);
        }while(tempo < 0 && tempo > 24);

        pos = sugere_posicao(estacionamento, numP, numC, tempo);
        printf("Aprova a sugestão? 1 - para aprovar 2 - para rejeitar:");
        scanf("%d", &aprova);

        if(aprova != 1)
        {
            do
            {
                printf("\nEm qual fileira deseja colocar o carro: ");
                scanf("%d", &pos);

            }
            while(pos < 1 || pos > numP);
            if(pilha_cheia(estacionamento[pos-1], numC) == 1)
                {
                    printf("Pilha cheia!\n");
                    return;
                }
        }

    }
    while(aprova <= 0 || aprova >2);


    insere_carro(estacionamento[pos-1], s, tempo);
}
void retira_carro(Pilha** estacionamento, Pilha* rua)
{
    char* s = malloc(sizeof(char));

    if(configurada == 0)
    {
        printf("\nEstacionamento ainda NÃO configurado!\n");
        return;
    }

    exibe_estacionamento(estacionamento);
    printf("\nEntre com a placa: ");
    scanf("%s",s);


    if(encontra_placa(estacionamento, numP, s) == -1)
    {
        printf("\nPlaca NÃO encontrada!\n");
        return;
    }

    retira_carro_placa(estacionamento, rua, s, numP, numC, numR);
    printf("\n");
    exibe_estacionamento(estacionamento);

}
