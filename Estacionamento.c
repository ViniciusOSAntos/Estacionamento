#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Estacionamento.h"

// variáveis nc e np geralmente representarão o número de carros e o número de pilhas, respectivamente.
// DEFINIÇÕES básicas das funções estão descritas no arquivo .h

Pilha* pilha_cria(void)
{

    Pilha *p = malloc(sizeof(Pilha));
    if(p == NULL)
    {
        printf("\nNão há memória o suficiente!\n");
        system("pause");
        exit(EXIT_SUCCESS);
    }
    p->nCarros = 0;
    p->topo = NULL;


    return p;
}

Pilha** inicia_estacionamento(int np)
{

    Pilha** estacionamento = malloc(np*sizeof(Pilha*));
    int i;

    for(i = 0; i < np; i++)
    {
        Pilha* p = pilha_cria();

        estacionamento[i] = p;
    }

    return estacionamento;
}


void insere_carro(Pilha *p, char *placa, float tempo)
{

    Carro *novo = malloc(sizeof(Carro));

    if(novo == NULL)
    {
        printf("\nProblema de alocação de memória\n");
        system("pause");
        exit(EXIT_SUCCESS);
    }

    novo ->placa = placa;
    novo ->prox = p->topo;
    novo ->tempo = tempo;
    p->topo = novo;

    p->nCarros++;
}


void imprime_estacionamento(Pilha *p, int total_carros)
{

    int i;
    Carro *e = p->topo;


    for(i = total_carros; i > 0; i--)
    {
        if(i <= p->nCarros)
        {
            printf("|\t%-9s|", e->placa);
            e = e->prox;
        }
        else
        {
            printf("|\t%-9s|","VAGA");
        }
        printf("|");
    }
}
// HEURIÍSTICA DE INSERÇÃO
int  sugere_posicao(Pilha** estacionamento, int np, int nc, int tempo) // retorna -1 caso o estacionamento esteja cheio! Retorno útil em teste da main
{
    int i = 0, j = 0, num = 999, teste, menor = -1,cont = 0;


    for(i = 0; i < np; i++)
    {
        teste = pilha_cheia(estacionamento[i], nc); //calcula quantas fileiras do estacionamento estão cheias!
        if(teste == 1)
            j++;
        if(j == np)
        {
            //caso o estacionamento esteja lotado retorna -1, que é tratado na main
            return -1;
        }

    }

    for(i = 0; i < np; i++)  //indica a primeira pilha vazia
    {
        if(pilha_vazia(estacionamento[i]) == 1)
        {
            j = i;
            printf("Pilha Sugerida: ");
            printf("Pilha %d\n", i+1);
            teste = 1+i;
            i = 0;
            while(i < np)
            {
                imprime_estacionamento(estacionamento[i], nc);
                i++;
                printf("\n");
            }
            return teste;
        }

    }
    i = 0;
    j = 0;

    for(i = 0; i < np; i++)  //indica a pilha onde o carro do topo demorará mais a sair
    {

        if(estacionamento[i]->topo->tempo > menor && estacionamento[i]->nCarros < nc)
        {

            menor = estacionamento[i]->topo->tempo;
            j = i;
            if(i == np-2)
            {
                printf("Pilha Sugerida: ");
                printf("Pilha %d\n", i+1);
                teste = i+1;
                while(j < np)
                {
                    imprime_estacionamento(estacionamento[j], nc);
                    j++;
                    printf("\n");
                }
                return teste;
            }

        }
        cont++;
    }

    i = 0;
    for(i = 0; i < np; i++) //encontra uma pilha NÂO vazia com a menor quantidade de carros e indica ao usuário
    {
        if(estacionamento[i]->nCarros <= num)
        {
            num = estacionamento[i]->nCarros;
            teste = i;
        }
    }
    printf("Pilha Sugerida: ");
    printf("Pilha %d\n", teste+1);
    i = 0;
    while(i < np)
    {
        imprime_estacionamento(estacionamento[i], nc);
        i++;
        printf("\n");
    }
    return teste+1;


}

Carro* pilha_pop(Pilha* p) // retira o topo da pilha
{
    Carro *t, *q;
    //char* v = malloc(9*sizeof(char));

    if (pilha_vazia(p))
    {
        return NULL; //não indica erro;
    }
//teste externo necessário

    t = p->topo;
    q = t;
    p->topo = t->prox;
    free(t);
    p->nCarros--;
    return q;
}
int pilha_vazia (Pilha* p) // retorna 1 caso a pilha esteja vazia
{
    if(p->topo == NULL)
        return 1;
    return 0;
}
int pilha_cheia (Pilha* p, int nc) // retorna  1 caso a pilha esteja cheia
{
    if(p->nCarros == nc)
        return 1;
    return 0;
}
void retira_carro_placa(Pilha **p, Pilha* rua, char *placa, int np, int nc, int nr)
{

    Pilha **estacionamento = p;
    Carro *e;

    int i, j = 0;
    int seq = encontra_pilha_menor(estacionamento, np, nc), carros;
    int pos = 0, rua_usada = 0;
    Pilha *p2 = pilha_cria();
    //Pilha *p3 = pilha_cria();

    pos = encontra_placa(estacionamento, np, placa); //localiza pilha da placa

    carros = carros_no_caminho(estacionamento[pos], placa);
    printf("\nCarros no caminho: %d\n ", carros);

    if(nc == 1 && np == 1)
    {
        pilha_pop(estacionamento[0]); //solução para caso específico
        return;
    }

    if(est_cheio(estacionamento, np, nc) == 1)
    {
        for (i = 0; i < carros; i++)
        {
            if(carros > nr)
            {
                printf("Pedido de retirada recusado! Não há espaço para manobras!\n"); // alerta para caso o estacionamento esteja cheio e a rua nao comportar a quantidaade de carros
                for(j = 0; j < np; j++)
                {
                    imprime_estacionamento(estacionamento[j], nc);
                    printf("\n");
                }
                printf("\nRua:\n");
                imprime_estacionamento(rua, nr);
                printf("\n");
                return;
            }
            else
            {
                rua_usada = 1;
                p2->topo = pilha_pop(estacionamento[pos]);
                insere_carro(rua, p2->topo->placa, p2->topo->tempo);  //manobra carros para rua, insere
                rua_usada = 1;
                printf("\nEstacionamento: \n");
                for(j = 0; j < np; j++)
                {
                    imprime_estacionamento(estacionamento[j], nc);
                    printf("\n");
                }
                printf("\n");
                printf("\nRua:\n");
                imprime_estacionamento(rua, nr);
                printf("\n");

            }

        }
        e = estacionamento[pos]->topo;
        estacionamento[pos]->topo = e->prox;
        free(e);
        estacionamento[pos]->nCarros--;

        if(rua_usada == 1) //devolve os carros da rua para o estacionamento
        {


            for(i = 0; i < carros; i++)
            {

                    printf("\n");
                    printf("\nEstacionamento\n");
                    for(j = 0; j < np; j++)
                    {

                        imprime_estacionamento(estacionamento[j], nc);
                        printf("\n");
                    }
                    printf("\nRua:\n");
                    imprime_estacionamento(rua, nr);
                    printf("\n");

                    insere_carro(estacionamento[pos], rua->topo->placa, rua->topo->tempo); //insere carro do topo da rua para o estacionamento
                    system("pause");
                    printf("\n");
                    e = rua->topo;
                    rua->topo = e->prox;
                    free(e);
                    rua->nCarros--;
                    printf("\nEstacionamento\n");
                    for(j = 0; j < np; j++)
                    {
                        imprime_estacionamento(estacionamento[j], nc);
                        printf("\n");
                    }
                    printf("\nRua:\n");
                    imprime_estacionamento(rua, nr);
                    printf("\n");
                    system("pause");

            }

            return;
       }
    }

    system("cls");
    if(rua_usada != 1 && carros > 0) //sem necessidade de usar a rua
    {
        printf("\nEstacionamento:\n");
        for(i = 0; i < carros; i++)
        {

            p2->topo = pilha_pop(estacionamento[pos]);
            insere_carro(estacionamento[seq-1], p2->topo->placa, p2->topo->tempo);

        }
        for(j = 0; j < np; j++)
        {
            imprime_estacionamento(estacionamento[j], nc);
            printf("\n");
        }
        printf("\nRua:\n");
        imprime_estacionamento(rua, nr);
        printf("\n");
        system("pause");
    }


    e = estacionamento[pos]->topo;
    estacionamento[pos]->topo = e->prox;
    free(e);
    estacionamento[pos]->nCarros--;

}
//encontra a pilha de uma placa
int encontra_placa(Pilha **estacionamento, int np, char *placa)
{

    Pilha *t;
    Carro *e;
    int i, j, pil;
    for(i = 0; i < np; i++)
    {
        t = estacionamento[i];
        e = t->topo;
        for(j = 0; j < estacionamento[i]->nCarros; j++)
        {
            if(strcmp(e->placa, placa) == 0)
            {
                pil = i;
                return pil;
            }
            else
                e = e->prox;
        }
    }
    return -1;
}
int encontra_pilha_menor(Pilha** p, int np, int nc)
{

    int i, j = nc;
    int menor_pilha;
    Pilha** estacionamento = p;

    for(i = 0; i < np; i++)
    {
        if(j >= total_carros_na_pilha(estacionamento[i]))
        {
            menor_pilha = i + 1;
            j = total_carros_na_pilha(estacionamento[i]);
        }

    }

    return menor_pilha;
}
int est_cheio(Pilha** estacionamento, int np, int nc)
{
    int i, carros, cont = 0;

    for(i =0; i < np; i++)
    {
        carros = total_carros_na_pilha(estacionamento[i]);
        if(carros == nc)
            cont++;
    }
    //cont*np;
    if(cont ==  np)
        return 1;
    else return 0;
}
int carros_no_caminho(Pilha *p, char *placa)
{

    Carro *e = p->topo;
    int i = 0;

    while(e != NULL)
    {
        if(strcmp(e->placa, placa) != 0)
        {
            e = e->prox;
            i++;
        }
        else
            break;
    }

    return i;
}
int total_carros_na_pilha(Pilha *p)
{

    return p->nCarros;
}
