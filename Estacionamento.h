#ifndef ESTACIONAMENTO_H_INCLUDED
#define ESTACIONAMENTO_H_INCLUDED

typedef struct carro{
    char *placa;
    struct carro *prox;
    float tempo;
}Carro;

typedef struct pilha{

    int inversao;
    int nCarros;
    Carro *topo;
}Pilha;
//cria pilha
Pilha* pilha_cria(void);
//cria o estacionamento
Pilha** inicia_estacionamento(int npilhas);
//insere carro no estacionamento na pilha indicada
void insere_carro(Pilha *p, char *placa, float tempo);
//printa o estacionamento, sendo a esquerda do console sua saída e a direita o fundo. também usado para printar a rua.
void imprime_estacionamento(Pilha *p, int total_carros);
//retira o topo da pilha, retorna um novo topo.
Carro* pilha_pop(Pilha* p);
//retorna 1 caso a pilha esteja vazia
int pilha_vazia (Pilha* p);
// uma heurística é usada para indicar o melhor lugar para inserir no estacionamento
int sugere_posicao(Pilha** estacionamento, int npilhas, int ncarros, int tempo);
// encontra uma específica placa na fila. útil em outras funçoes do tad para evitar repetições e utiliazada na main para evitar placas repetidas
int encontra_placa(Pilha **p, int npilhas, char *placa);
//copia uma pilha ou um estacionamento
Pilha** pilha_copia(Pilha** estacionamento, int np, int nc);
//retorna 1 caso a pilha esteja cheia
int pilha_cheia (Pilha* p, int numcarros);
// função que trata formas diferentes de simular a remoção de carros do estacionamento
void retira_carro_placa(Pilha **p,Pilha* rua, char *placa, int np, int nc, int nr);
//encontra a menor pilha no estacionamento
int encontra_pilha_menor(Pilha** p, int np, int nc);
// devolve a quantidade de carros no caminho de um dado carro
int carros_no_caminho(Pilha *p, char *placa);
//retorna 1 caso estacionamento esteja cheio
int est_cheio(Pilha** estacionamento, int np, int nc);
//encontra a quantidade de carros na pilha
int total_carros_na_pilha(Pilha *p);


#endif // ESTACIONAMENTO_H_INCLUDED
