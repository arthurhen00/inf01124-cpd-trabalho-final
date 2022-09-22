/* Arthur Hendges da Silva
** 00332968
** Trabalho Final
*/

#include "functions.h"

// tab hash -----------------
// Cria a tabela hash
void cria_tabela_hash_tags(int id_user, int id_player, char tag[], int M, ptLSE_tags *vetor_tabela[]){
    int hash = chave_horner_string(tag, M);
    insere_tabela_hash_tags(hash, vetor_tabela, id_user, id_player, tag);
}

// Insere uma lista na tabela hash
void insere_tabela_hash_tags(int hash, ptLSE_tags *vetor_tabela[], int id_user, int id_player, char tag[]){
    vetor_tabela[hash] = inserir_tags(vetor_tabela[hash], id_user, id_player, tag);
}



// Lista -------------------------
// Cria uma chave para uma stirng, seguindo um padrao de um polinomio;
int chave_horner_string(char string[NAME_SIZE], int M){
    int p = 257;
    int hash = 0;
    int ascci = 0;
        for(int j = 0; j < strlen(string); j++){
            ascci += (int)string[j];
            hash = (p * hash + ascci) % M;
        }
        return hash;  
}

// Cria lista
ptLSE_tags *criaLista_tags(){
    return NULL;
}

// Cria listas em todas as posicoes da tabela
void inicializa_lista_tabela_hash_tags(ptLSE_tags *tabela_hash[], int M){
    for(int i = 0; i < M; i++){
        ptLSE_tags *ptLista = criaLista_tags();
        tabela_hash[i] = ptLista; 
    }
}

ptLSE_tags *inserir_tags(ptLSE_tags *ptLista, int id_user, int id_player, char tag[]){
    ptLSE_tags *novo, *ptAux;
    int tag_repetida = 0;

    novo = (ptLSE_tags*)malloc(sizeof(ptLSE_tags));
    novo->id_user = id_user;
    novo->id_player = id_player;
    strcpy(novo->tag, tag);
    
    for(ptAux = ptLista; ptAux != NULL; ptAux = ptAux->prox){
        if(ptAux->id_player == id_player){
            tag_repetida = 1;
        }
    }
    if(tag_repetida != 1){
        novo->prox = ptLista;
        ptLista = novo;
    }
    
    return ptLista;
}