/* Arthur Hendges da Silva
** 00332968
** Trabalho Final
*/

#include "functions.h"

// ------------------------------------------------------------------------------------
// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = NULL;
  
    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
  
    if (pNode)
    {
        int i;
  
        pNode->isEndOfWord = false;
  
        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
    }
  
    return pNode;
}
  
// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, const char *key, int id_player)
{
    int level;
    int length = strlen(key);
    int index;
  
    struct TrieNode *pCrawl = root;
  
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
  
        pCrawl = pCrawl->children[index];
    }
  
    // mark last node as leaf
    pCrawl->isEndOfWord = true;
    pCrawl->id_player = id_player;
}
  
// Returns true if key presents in trie, else false
bool search(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;
  
    for (level = 0; level < length; level++)
    {
        
        index = CHAR_TO_INDEX(key[level]);

        if (!pCrawl->children[index]){
            return false;
        }
  
        pCrawl = pCrawl->children[index];
    }

    return (pCrawl->isEndOfWord);

    
}

// transforma todas as letras para minusculo
// remove todos os char especiais [97 122]
// str1 -> str2
void string_tolower(char str1[], char str2[]){
    int i = 0;
    while(str1[i] != '\0'){  
        str2[i] = tolower(str1[i]);
        i++;
    }
    str2[i] = '\0';

    int count = 0;
    for(i = 0; str2[i] ; i++){
        if((int)str2[i] >= 97 && (int)str2[i] <= 122){
            str2[count++]=str2[i];
        }
    }
    str2[count]='\0';

}