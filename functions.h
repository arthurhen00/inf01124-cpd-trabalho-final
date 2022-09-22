// Common ********************************************************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>

#define NAME_SIZE 256
#define POSICOES_SIZE 8
#define QTD_POSICOES 16
#define PLAYER_TABLE_SIZE 7507
#define RATING_TABLE_SIZE 1261721
#define TAGS_TABLE_SIZE 433373
#define SORT_SIZE 10000
#define QTD_TAGS 512

// Trie ********************************************************************************************************************************
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define ALPHABET_SIZE (26)
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
    int id_player;
};

// Lista ********************************************************************************************************************************
typedef struct tipoNo ptLSE;
struct tipoNo{
    int id;
    char nome[NAME_SIZE];
    char posicoes[NAME_SIZE];
    float rating;
    int count;
    ptLSE *prox;
};

typedef struct tipoNo1 ptLSE_rating;
struct tipoNo1{
    int id_user;
    int id_player;
    float rating;
    ptLSE_rating *prox;
};

typedef struct tipoNo2 ptLSE_tags;
struct tipoNo2{
    int id_user;
    int id_player;
    char tag[NAME_SIZE];
    ptLSE_tags *prox;
};

// Sort *************************************************************************************************************************************
int partition_hoare(float v[][2], int i, int f);
void random(float v[][2], int i, int f);
void quicksort_hoare_random(float v[][2], int i, int f);

/*

*/

// Lista ********************************************************************************************************************************
ptLSE *criaLista();
ptLSE *inserirFim_player(ptLSE *ptLista, char str[], int id, char posicoes[], int count, float rating);
void att_lista(ptLSE *ptLista, int id_fifa, float rating);
void consulta_lista(ptLSE *ptLista, int id_player);

// Hash player ********************************************************************************************************************************
int chave_horner(int id, int M);
void cria_tabela_hash_player(int id, char string[], char posicoes[], int M, ptLSE *vetor_tabela[]);
void insere_tabela_hash(int hash, ptLSE *vetor_tabela[], char string[], int id, char posicoes[]);
void inicializa_lista_tabela_hash(ptLSE *tabela_hash[], int M);
void att_rating_player(ptLSE *tabela_player[], int id_fifa, float rating);

// Hash rating ********************************************************************************************************************************
void cria_tabela_hash_rating(int id_user, int id_player, float rating, int M, ptLSE_rating *vetor_tabela[]);
void insere_tabela_hash_rating(int hash, ptLSE_rating *vetor_tabela[], int id_user, int id_player, float rating);
ptLSE_rating *inserirFim_rating(ptLSE_rating *ptLista, int id_user, int id_player, float rating);
ptLSE_rating *criaLista_rating();
void inicializa_lista_tabela_hash_rating(ptLSE_rating *tabela_hash[], int M);

void consulta_lista_rating(ptLSE_rating *ptLista, int id_user, ptLSE *vetor_tabela_player[]);
void select_user(int id_user, ptLSE_rating *vetor_tabela_rating[], ptLSE *vetor_tabela_player[]);

void select_position(char position[], ptLSE *vetor_tabela_player[], int tam);

// Hash tags ********************************************************************************************************************************
ptLSE_tags *inserir_tags(ptLSE_tags *ptLista, int id_user, int id_player, char tag[]);
void inicializa_lista_tabela_hash_tags(ptLSE_tags *tabela_hash[], int M);
ptLSE_tags *criaLista_tags();
int chave_horner_string(char string[NAME_SIZE], int M);
void insere_tabela_hash_tags(int hash, ptLSE_tags *vetor_tabela[], int id_user, int id_player, char tag[]);
void cria_tabela_hash_tags(int id_user, int id_player, char tag[], int M, ptLSE_tags *vetor_tabela[]);

void select_tag(char tags[], ptLSE_tags *vetor_tabela[], ptLSE *vetor_tabela_player[]);


// Trie ********************************************************************************************************************************
bool search(struct TrieNode *root, const char *key);
void insert(struct TrieNode *root, const char *key, int id_player);
struct TrieNode *getNode(void);
void string_tolower(char str1[], char str2[]);
void prefix_search(struct TrieNode *root, char str[], ptLSE *vetor_tabela[]);
void rec(struct TrieNode *root, int index, int *achados, int vet_achados[]);

