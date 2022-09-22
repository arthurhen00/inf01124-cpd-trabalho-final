/* Arthur Hendges da Silva
** 00332968
** Trabalho Final
*/

#include "functions.h"

// Select (prefix_name) ******************************************************************************************************************************************
void prefix_search(struct TrieNode *root, char str[], ptLSE *vetor_tabela[]){
    
    int level;
    int length = strlen(str);
    int index;
    struct TrieNode *pCrawl = root;
  
    printf("%9s| %47s| %16s| %6s| %9s|\n", "sofifa_id", "name", "player_positions", "count", "rating");

    for (level = 0; level < length; level++)
    {
        
        index = CHAR_TO_INDEX(str[level]);
        if (!pCrawl->children[index]){
            return;
        }
        pCrawl = pCrawl->children[index];
    }

    int vet_achados[20000] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    int achados = 0;

    rec(pCrawl, 0, &achados, vet_achados);
    
    // lista jogadores achados
    
    for(int i = 0; i < 10; i++){
        int hash = chave_horner(vet_achados[i], PLAYER_TABLE_SIZE);
        consulta_lista(vetor_tabela[hash], vet_achados[i]);
    }

}

void rec(struct TrieNode *pCrawl, int index, int *achados, int vet_achados[]){

    for(int i = 0; i < 26; i++){    
        if(pCrawl->children[i]){
            rec(pCrawl->children[i], 0, achados, vet_achados);
        }
    }
    
    if(pCrawl->isEndOfWord){
        vet_achados[*achados] = pCrawl->id_player;
        *achados += 1;
    }
 
}

void consulta_lista(ptLSE *ptLista, int id_player){
    ptLSE *ptAux;
    
    if(ptLista == NULL){
        return;
    }else{
        for(ptAux = ptLista; ptAux != NULL; ptAux = ptAux->prox){
            if(ptAux->id == id_player){
                printf("%9d| %47s| %16s| %6d| %9.2f|\n", ptAux->id, ptAux->nome, ptAux->posicoes, ptAux->count ,ptAux->rating/ptAux->count);
                return;
            }
        }
        return;
    }  
}



// Select (user_id) ******************************************************************************************************************************************

void select_user(int id_user, ptLSE_rating *vetor_tabela_rating[], ptLSE *vetor_tabela_player[]){
    int hash = chave_horner(id_user, RATING_TABLE_SIZE);
    consulta_lista_rating(vetor_tabela_rating[hash], id_user, vetor_tabela_player);
}

void consulta_lista_rating(ptLSE_rating *ptLista, int id_user, ptLSE *vetor_tabela_player[]){
    ptLSE_rating *ptAux;
    float player_rating[SORT_SIZE][2] = {0}; // inicialzar para em uma segunda busca nao puxar lixo, nos testes estava bugando
    int count = 0;

    printf("%9s| %47s| %13s| %6s| %9s|\n", "sofifa_id", "name", "global_rating", "count", "rating");
    
    if(ptLista == NULL){
        return;
    }else{
        for(ptAux = ptLista; ptAux != NULL; ptAux = ptAux->prox){
            if(ptAux->id_user == id_user){
                player_rating[count][0] = ptAux->id_player;
                player_rating[count][1] = ptAux->rating;
                //printf("%.0f - %.2f\n",player_rating[count][0],player_rating[count][1]);
                count++;
            }
        }

        // sort
        quicksort_hoare_random(player_rating, 0, count);

        // list 20 desc
        ptLSE *ptAux1;
        for(int i = count; i > count - 20; i--){
            int hash = chave_horner(player_rating[i][0], PLAYER_TABLE_SIZE);
            for(ptAux1 = vetor_tabela_player[hash]; ptAux1 != NULL; ptAux1 = ptAux1->prox){
                if(ptAux1->id == (int)player_rating[i][0]){
                    printf("%9.0f| %47s| %13.2f| %6d| %9.2f|\n", player_rating[i][0], ptAux1->nome, ptAux1->rating/ptAux1->count, ptAux1->count, player_rating[i][1]);
                }
            }
        }

        return;
    }  
}

// Select (top<N> <position>) ******************************************************************************************************************************************
void select_position(char position[], ptLSE *vetor_tabela_player[], int tam){
    float player_rating[SORT_SIZE][2] = {0}; // inicialzar para em uma segunda busca nao puxar lixo, nos testes estava bugando
    char buffer_position[NAME_SIZE];
    char *token;
    int count = 0;

    printf("%9s| %47s| %13s| %6s| %9s|\n", "sofifa_id", "name", "player_positions", "rating", "count");

    for(int i = 0; i < PLAYER_TABLE_SIZE; i++){
        if(vetor_tabela_player[i] != NULL){
            // percorrer a lista desse hash
            ptLSE *ptAux;
            for(ptAux = vetor_tabela_player[i]; ptAux != NULL; ptAux = ptAux->prox){

                strcpy(buffer_position, ptAux->posicoes);
                token = strtok(buffer_position, ",");

                while(token != NULL){
                    if(token[0] == ' '){
                        for(int j = 0; j < strlen(token); j++){
                            token[j] = token[j+1];
                        }
                    }
                    strcpy(buffer_position, token);
                    token = strtok(NULL, ",");
                    // if buffer_position == position da query
                    if(!strcmp(buffer_position, position)){
                        player_rating[count][0] = ptAux->id;
                        if(ptAux->count == 0){ // div por zero
                            player_rating[count][1] = 0;
                        }else{
                            player_rating[count][1] = (float)(ptAux->rating/(float)ptAux->count);
                        }
                        //printf("[%s - %s]\n", buffer_position, position);
                        //printf("[id: %.2f - rating: %f ||| total_rating: %f count: %d]\n", player_rating[count][0], player_rating[count][1], ptAux->rating, ptAux->count);
                        count++;
                    }
                }
            }
        }
    }

    // sort
    quicksort_hoare_random(player_rating, 0, count);

    // list
    ptLSE *ptAux1;

    if(tam > count){
        tam = count;
    }

    for(int i = count; i > count - tam; i--){
        int hash = chave_horner(player_rating[i][0], PLAYER_TABLE_SIZE);
        for(ptAux1 = vetor_tabela_player[hash]; ptAux1 != NULL; ptAux1 = ptAux1->prox){
            if(ptAux1->id == (int)player_rating[i][0]){
                printf("%9.0f| %47s| %16s| %6.2f| %9d|\n", player_rating[i][0], ptAux1->nome, ptAux1->posicoes, player_rating[i][1], ptAux1->count);
            }
        }
    }

}

// Select (tags <tag1,tag2,...,tagn>) ******************************************************************************************************************************************
void select_tag(char tags[], ptLSE_tags *vetor_tabela[], ptLSE *vetor_tabela_player[]){
    char *token;
    ptLSE_tags *ptAux;
    int id_player[10000][2];
    int passada = 1;
    int count1 = 0, count2 = 0, count3 = 0;

    printf("%9s| %47s| %13s| %6s| %9s|\n", "sofifa_id", "name", "player_positions", "rating", "count");

    token = strtok(tags, ",");
    while(token != NULL){
        count2 = 0;
        char format_name[NAME_SIZE];
        string_tolower(token, format_name);

        int hash = chave_horner_string(format_name, TAGS_TABLE_SIZE);
        for(ptAux = vetor_tabela[hash]; ptAux != NULL; ptAux = ptAux->prox){

            char format_name_table[NAME_SIZE];
            string_tolower(ptAux->tag, format_name_table);

            if(passada == 1){
                if(!strcmp(format_name_table, format_name)){
                    id_player[count1][0] = ptAux->id_player;
                    count1++;
                }
            }else{
                if(!strcmp(format_name_table, format_name)){
                    
                    for(int i = 0; i < count1; i++){
                        //printf("[%d - %d]\n", id_player[i][0], ptAux->id_player);
                        if(id_player[i][0] == ptAux->id_player){
                            id_player[count2][1] = ptAux->id_player;
                            count2++;
                        }
                    }//printf("%d\n", count2);

                    for(int i = 0; i < count2; i++){
                        id_player[i][0] = id_player[i][1];
                        //printf("[%d]\n", id_player[i][0]);
                    }
                    if(count2 != 0){
                        count3 = count2;
                    }
                }
            } 
        }
        passada++;
        token = strtok(NULL, ",");
    }//printf("|%d %d %d|",count2, count1, count3);

    if(count3 == 0){
        count3 = count1;
    }

    // vetor id_player[i][0] com os ids da minha busca
    // USA COUNT3; tem um jeito melhor
    ptLSE *ptAux1;
    for(int i = 0; i < count3; i++){
        int hash = chave_horner(id_player[i][0], PLAYER_TABLE_SIZE);
        for(ptAux1 = vetor_tabela_player[hash]; ptAux1 != NULL; ptAux1 = ptAux1->prox){  
            if(ptAux1->id == id_player[i][0]){
                if(ptAux1->count == 0){
                    printf("%9d| %47s| %16s| %6.2f| %9d|\n", ptAux1->id, ptAux1->nome, ptAux1->posicoes, 0, ptAux1->count);
                }else{
                    printf("%9d| %47s| %16s| %6.2f| %9d|\n", ptAux1->id, ptAux1->nome, ptAux1->posicoes, ptAux1->rating/ptAux1->count, ptAux1->count);
                }
            }
        }
    }


}