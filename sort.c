/* Arthur Hendges da Silva
** 00332968
** Trabalho Final
*/

#include "functions.h"

int partition_hoare(float v[][2], int i, int f){

    int aux;

    float chave = v[i][1];
    float chave2 = v[i][0];
    int in = i, fi = f;

    while(in < fi){
        while(v[fi][1] > chave && in < fi)
            fi--;
        v[in][1] = v[fi][1];
        v[in][0] = v[fi][0];
        while(v[in][1] <= chave && in < fi)
            in++;
        v[fi][1] = v[in][1];
        v[fi][0] = v[in][0];
    }
    v[fi][1] = chave;
    v[fi][0] = chave2;

    return in;
}

void random(float v[][2], int i, int f){
    int p;
    float aux_rating, aux_player;

    srand(time(NULL));
    p = (rand() % (f - i + 1)) + i;
    
    aux_rating = v[i][1];
    aux_player = v[i][0];

    v[i][1] = v[p][1];
    v[i][0] = v[p][0];

    v[p][1] = aux_rating;
    v[p][0] = aux_player;
}

void quicksort_hoare_random(float v[][2], int i, int f){
    int p;
    if (f > i) {
        random(v,i,f);
        p = partition_hoare(v, i, f);
        quicksort_hoare_random(v, i, p-1);
        quicksort_hoare_random(v, p+1, f);
    }
}