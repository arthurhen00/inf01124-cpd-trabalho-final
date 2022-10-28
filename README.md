# cpd-trabalho-final

A maioria dos testes foram realizados com os arquivos da pasta "INF01124_FIFA21_clean"  
Incluir a pasta "INF01124_FIFA21_clean" com os arquivos players.csv, rating.csv, tags.csv  
Comando para compilar:

`gcc -c main.c select.c table_player.c trie.c table_rating.c sort.c table_tags.c`  
`gcc -o exe main.o select.o table_player.o trie.o table_rating.o sort.o table_tags.o`  
`./exe`  

## consultas:

### $ search (prefix)  
Retorna 10 jogadores que começam pelo prefixo passado, em ordem alfabética.  
Ex:
 
![IMG](https://media.discordapp.net/attachments/1024295551388364800/1024295607050965012/unknown.png)

**Tem um bug nessa implementação**  
*Na hora de armazenar as strings com os nomes dos jogadores na árvore trie os espaços da string foram retirados, isso impediu de diferenciar certos nomes*  
*Ex:*  
*Na busca do prefixo `cristiano` temos o retorno de Cristiano... e Cristian..., isso acontece pois nao sabemos se a pesquisa é Cristiano(Sobrenome) ou Cristian O(Sobrenome)*

### $ user (number)

Retorna 20 jogadores avaliados pelo usuário passado, em ordem decrescente do rating dado.

Ex:

![IMG](https://media.discordapp.net/attachments/1024295551388364800/1024297146339569734/unknown.png)

### $ top(number) (position)

Retorna o número passado de jogadores que jogam na posição passada, em ordem decrescente de rating.

Ex:

![IMG](https://media.discordapp.net/attachments/1024295551388364800/1024298324163039274/unknown.png)

### $ tags (tag1, tag2, ..., tagN)

Retorna todos os jogadores que possuem todas as tags passadas.

Ex:

![IMG](https://media.discordapp.net/attachments/1024295551388364800/1024299010988720158/unknown.png)

### $ time

Retorna o tempo de processamento dos arquivos.

Ex:

![IMG](https://media.discordapp.net/attachments/1024295551388364800/1024299519808126996/unknown.png)

### $ cls

Limpa o console.
