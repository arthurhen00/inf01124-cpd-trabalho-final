/* Arthur Hendges da Silva
** 00332968
** Trabalho Final
*/

#include "functions.h"

ptLSE_rating *tabela_rating[RATING_TABLE_SIZE];

int main(){

    clock_t t;
    t = clock();

    char entrada[NAME_SIZE];
    char *token;

    struct TrieNode *root = getNode();

    // Processamento ---------------------------------------------------------------------------------------------------------------------------------------

    // Lê o arquivo players.csv e salva as informações em uma tabela hash
    ptLSE *tabela7507_player[PLAYER_TABLE_SIZE];
    inicializa_lista_tabela_hash(tabela7507_player, PLAYER_TABLE_SIZE);

    FILE *arq0 = fopen("INF01124_FIFA21_clean/players.csv", "r");
    if(!arq0){
        printf("\nErro ao abrir o arquivo ***INF01124_FIFA21_clean/players.csv*** --- (caminho nao encontrado)\n\n");
        fclose(arq0);
        return 0;
    }
    fgets(entrada, NAME_SIZE, arq0); // COLUNAS -> lixo
    int qtd_entrada = 0;
    while(feof(arq0) == 0 && qtd_entrada <= 18945){
        qtd_entrada++;
        fgets(entrada, NAME_SIZE, arq0);
        entrada[strlen(entrada)-1] = '\0';
        //printf("[%s]\n", entrada);

        char buffer_fifa_id[NAME_SIZE];
        token = strtok(entrada, ",");
        strcpy(buffer_fifa_id,token);
        //printf("[%s]\n", buffer_fifa_id);

        char buffer_name[NAME_SIZE];
        if(token != NULL){
            token = strtok(NULL, ",");     
            if(token != NULL){
                strcpy(buffer_name,token);
                char format_name[NAME_SIZE];
                string_tolower(buffer_name, format_name);
                insert(root, format_name, atoi(buffer_fifa_id));
                //printf("[%s]\n", buffer_name);
            }
        }

        char buffer_positions[NAME_SIZE];
        if(token != NULL){
            token = strtok(NULL, "\0");
            strcpy(buffer_positions, token);
            if(buffer_positions[0] == '"'){
                for(int i = 0; i < strlen(buffer_positions); i++){
                    buffer_positions[i] = buffer_positions[i+1];
                }
                buffer_positions[strlen(buffer_positions)-1] = '\0';
            }
            
            //printf("[%s]\n", buffer_positions);
        }
        
        cria_tabela_hash_player(atoi(buffer_fifa_id), buffer_name, buffer_positions, PLAYER_TABLE_SIZE, tabela7507_player);
    }
    fclose(arq0);

    // Leitura do arquivo rating.csv
    inicializa_lista_tabela_hash_rating(tabela_rating, RATING_TABLE_SIZE);

    FILE *arq1 = fopen("INF01124_FIFA21_clean/rating.csv", "r");
    if(!arq1){
        printf("\nErro ao abrir o arquivo ***INF01124_FIFA21_clean/rating.csv*** --- (caminho nao encontrado)\n\n");
        fclose(arq1);
        return 0;
    }
    fgets(entrada, NAME_SIZE, arq1); // COLUNAS -> lixo
    while(feof(arq1) == 0){
        fgets(entrada, NAME_SIZE, arq1);
        entrada[strlen(entrada)-1] = '\0';
        
        char buffer_user_id[NAME_SIZE];
        token = strtok(entrada, ",");
        strcpy(buffer_user_id,token);

        char buffer_fifa_id[NAME_SIZE];
        if(token != NULL){
            token = strtok(NULL, ",");     
            if(token != NULL){
                strcpy(buffer_fifa_id,token);
            }
        }
        char buffer_user_rating[NAME_SIZE];
        if(token != NULL){
            token = strtok(NULL, ",");
            strcpy(buffer_user_rating,token);
        }

        att_rating_player(tabela7507_player, atoi(buffer_fifa_id), atof(buffer_user_rating));
        
        cria_tabela_hash_rating(atoi(buffer_user_id), atoi(buffer_fifa_id), atof(buffer_user_rating),  RATING_TABLE_SIZE, tabela_rating);

    }
    fclose(arq1);

    // Leitura do arquivo tags.csv
    ptLSE_tags *tabela_tags[TAGS_TABLE_SIZE];
    inicializa_lista_tabela_hash_tags(tabela_tags, TAGS_TABLE_SIZE);

    FILE *arq2 = fopen("INF01124_FIFA21_clean/tags.csv", "r");
    if(!arq2){
        printf("\nErro ao abrir o arquivo ***INF01124_FIFA21_clean/tags.csv*** --- (caminho nao encontrado)\n\n");
        fclose(arq2);
        return 0;
    }
    fgets(entrada, NAME_SIZE, arq2); // COLUNAS -> lixo
    while(feof(arq2) == 0){
        fgets(entrada, NAME_SIZE, arq2);
        entrada[strlen(entrada)-1] = '\0';
        
        char buffer_tags[NAME_SIZE];
        char buffer_id_user[NAME_SIZE];
        char buffer_id_player[NAME_SIZE];
        
        token = strtok(entrada, ",");
        strcpy(buffer_id_user, token);
        //printf(" %s ", buffer_id_user);

        token = strtok(NULL, ",");
        if(token != NULL){ 
            strcpy(buffer_id_player, token);
            //printf(" %s ", buffer_id_player);

            token = strtok(NULL, ",");
            if(token == NULL){
                strcpy(buffer_tags, "null");
            }else{
                strcpy(buffer_tags, token);
                //printf("[%s]\n ", buffer_tags);
            }
            
        }

        char format_name[NAME_SIZE];
        string_tolower(buffer_tags, format_name);
        //printf("%s\n", format_name);
        cria_tabela_hash_tags(atoi(buffer_id_user), atoi(buffer_id_player), format_name, TAGS_TABLE_SIZE, tabela_tags);
        
    }

    fclose(arq2);

    t = clock() - t;

    // AREA DO MENU
    
    char buffer_select[NAME_SIZE];
    char buffer_property[NAME_SIZE];
    do{
        printf(" $ ");
        scanf("%s", &buffer_select);
        if(strcmp(buffer_select, "exit")){
            if(!strcmp(buffer_select, "search")){
                fgets(buffer_property, NAME_SIZE, stdin);
                buffer_property[strlen(buffer_property)-1] = '\0';
                char format_name[NAME_SIZE];
                string_tolower(buffer_property, format_name);

                prefix_search(root, format_name, tabela7507_player);
            }else if(!strcmp(buffer_select, "user")){
                scanf("%s", &buffer_property);
                select_user(atoi(buffer_property), tabela_rating, tabela7507_player);
            }else if(buffer_select[0] == 't' && buffer_select[1] == 'o' && buffer_select[2] == 'p'){

                token = strtok(buffer_select, "p"); // macete
                token = strtok(NULL, "p");

                scanf("%s", &buffer_property);
                select_position(buffer_property, tabela7507_player, atoi(token));
            }else if(!strcmp(buffer_select, "tags")){
                fgets(buffer_property, NAME_SIZE, stdin);
                buffer_property[strlen(buffer_property)-1] = '\0';

                select_tag(buffer_property, tabela_tags, tabela7507_player);

            }else if(!strcmp(buffer_select, "cls")){
                system("cls");
            }else if(!strcmp(buffer_select, "time")){
                printf("Tempo de processamento: %.2lfs\n",((double)t)/((CLOCKS_PER_SEC)));
            }else{
                printf("*** unknown query *** \n");
            }
        }
            
        printf("\n");
    }while(strcmp(buffer_select, "exit"));

    return 0;
}