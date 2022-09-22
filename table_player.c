/* Arthur Hendges da Silva
** 00332968
** Trabalho Final
*/

#include "functions.h"

// TABELA HASH PLAYER---------------------------------------------------------------------------------------------------------------------
// Cria uma chave para uma stirng, seguindo um padrao de um polinomio;
int chave_horner(int id, int M){
    return id % M;  
}

// Cria a tabela hash
void cria_tabela_hash_player(int id, char string[], char posicoes[], int M, ptLSE *vetor_tabela[]){
    //inicializa_lista_tabela_hash(vetor_tabela, M);
    int hash = chave_horner(id, M);
    insere_tabela_hash(hash, vetor_tabela, string, id, posicoes);
}

// Insere uma lista na tabela hash
void insere_tabela_hash(int hash, ptLSE *vetor_tabela[], char string[], int id, char posicoes[]){
    vetor_tabela[hash] = inserirFim_player(vetor_tabela[hash], string, id, posicoes, 0, 0);
}

// Cria listas em todas as posicoes da tabela
void inicializa_lista_tabela_hash(ptLSE *tabela_hash[], int M){
    for(int i = 0; i < M; i++){
        ptLSE *ptLista = criaLista();
        tabela_hash[i] = ptLista; 
    }
}

// Atualiza count a rating
// Enquanto eu faço a leitura do arquivo rating.csv
// quando eu ler o id_fifa chamo essa função
// acesso esse jogador na hash_table_player e count++ e rating += rating
void att_rating_player(ptLSE *tabela_player[], int id_fifa, float rating){
    int hash = chave_horner(id_fifa, PLAYER_TABLE_SIZE);
    att_lista(tabela_player[hash], id_fifa, rating);
}

// LISTA -----------------------------------------------------------------------------------------------------------------------------------
// Cria lista
ptLSE *criaLista(){
    return NULL;
}

// Insere na lista
// ALTERADA, inserindo no inicio ** -> 
ptLSE *inserirFim_player(ptLSE *ptLista, char str[], int id, char posicoes[], int count, float rating){
    ptLSE *novo, *ptAux;

    novo = (ptLSE*)malloc(sizeof(ptLSE));
    strcpy(novo->nome, str);
    novo->id = id;
    strcpy(novo->posicoes, posicoes);
    novo->count = 0;
    novo->rating = 0;

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

// atualiza valores count e rating de um jogador
void att_lista(ptLSE *ptLista, int id_fifa, float rating){
    ptLSE *ptAux;
    
    if(ptLista == NULL){
        return;
    }else{
        for(ptAux = ptLista; ptAux != NULL; ptAux = ptAux->prox){
            if(ptAux->id == id_fifa){
                ptAux->count++;
                ptAux->rating += rating;
                return;
            }
        }
        return;
    }  
}