/* Arthur Hendges da Silva
** 00332968
** Trabalho Final
*/

#include "functions.h"

// Cria a tabela hash
void cria_tabela_hash_rating(int id_user, int id_player, float rating, int M, ptLSE_rating *vetor_tabela[]){
    int hash = chave_horner(id_user, M);
    insere_tabela_hash_rating(hash, vetor_tabela, id_user, id_player, rating);
}

// Insere uma lista na tabela hash
void insere_tabela_hash_rating(int hash, ptLSE_rating *vetor_tabela[], int id_user, int id_player, float rating){
    vetor_tabela[hash] = inserirFim_rating(vetor_tabela[hash], id_user, id_player, rating);
}


// Listas ----------------------------------------------------------------------------------------------------------------------------------
// Insere na lista
// Cria lista
ptLSE_rating *criaLista_rating(){
    return NULL;
}

// Cria listas em todas as posicoes da tabela
void inicializa_lista_tabela_hash_rating(ptLSE_rating *tabela_hash[], int M){
    for(int i = 0; i < M; i++){
        ptLSE_rating *ptLista = criaLista_rating();
        tabela_hash[i] = ptLista; 
    }
}

// ALTERADA, inserindo no inicio ** -> 
ptLSE_rating *inserirFim_rating(ptLSE_rating *ptLista, int id_user, int id_player, float rating){
    ptLSE_rating *novo, *ptAux;

    novo = (ptLSE_rating*)malloc(sizeof(ptLSE_rating));
    novo->id_user = id_user;
    novo->id_player = id_player;
    novo->rating = rating;

    /*if(ptLista == NULL){
        novo->prox = ptLista;
        ptLista = novo;
    }else{
        for(ptAux = ptLista; ptAux->prox != NULL; ptAux = ptAux->prox){

        }
        ptAux->prox = novo;
        novo->prox = NULL;
    }*/
    novo->prox = ptLista;
    ptLista = novo;
    return ptLista;
}