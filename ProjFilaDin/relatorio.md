## Implementação de Grafo com Lista de Adjacência

#### Integrantes:
a2727617 - Edryck Freitas Nascimento
a2727820 - Samuel Oliveira Simões da Silva

### 1. Estrutura de Dados
#### Nó
Representa um nó na lista de adjacência:
- `destino`: vértice destino
- `peso`: peso da aresta
- `prox`: ponteiro para próximo nó

#### Grafo
Implementação com lista de adjacência:
- `vet`: array de listas encadeadas
- `nos`: quantidade de vértices
- `eh_ponderado`: indica se o grafo é ponderado

### 2. Funções Implementadas
#### `cria_Grafo()`
Aloca e inicializa um grafo com `nro_vertices` vértices.

#### `libera_Grafo()`
Libera toda a memória alocada, percorrendo e desalocando todas as listas.

#### `insereAresta()`
Insere aresta de `orig` para `dest`. Se não for digrafo, insere também a aresta reversa recursivamente.

#### `removeAresta()`
Remove aresta entre `orig` e `dest`, tratando o caso não-dirigido.

#### `imprime_Grafo()`
Exibe a representação do grafo com lista de adjacência, mostrando pesos se ponderado.

#### `buscaNo()`
Valida se um vértice existe no grafo.

#### `buscaMenorAresta()`
Encontra a aresta com menor peso no grafo.

#### `prim()`
Encontra o Árvore Geradora Mínima de um grafo.

####  Questão 3:
Utilizando o arquivo “ProjGrafo” e o seu respectivo código:
a)	Detalhe o funcionamento da função `Grafo* cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado)`. Utilize trechos do código para ilustrar sua resposta.

<small>A função `cria_Grafo()` aloca, ela primeiro aloca dinamicamente uma `struct grafo`. Se a alocação for bem sucedida, armazena em `gr->nos` o número de vértices informado por `nro_vertices`. 
Em seguida, normaliza o parametro `eh_ponderado` para 0 ou 1 e guarda em `gr->eh_ponderado`, indicando se o grafo usa pesos nas arestas. 
Depois disso, aloca um vetor em `gr->vet`, com uma posicao para cada vértice.
Cada posição desse vetor é inicializada com `NULL` indicando que, inicialmente nenhum vértice possui arestas saindo dele. 
Por fim, a função retorna o ponteiro para o grafo criado ou `NULL` caso a primeira alocação falhe.</small>


b)	Detalhe o funcionamento da função `libera_Grafo(Grafo* gr)`. Utilize trechos do código para ilustrar sua resposta.

<small>A função `libera_Grafo` apaga tudo que foi criado para o grafo, ela verifica se o ponteiro e válido, depois ela passa por todos os vértices e vai apagando cada no das listas usando `free`, quando todas as listas estiverem vazias, ela libera o vetor `gr->vet` e depois libera também a estrutura do grafo, Depois disso o grafo não pode mais ser usado.</small>

c)	Detalhe o funcionamento da função `insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso)`. Utilize trechos do código para ilustrar sua resposta.

<small>A função `insereAresta()` coloca uma nova aresta no grafo.
Ela primeiro verifica se o grafo é válido e se os vértices existem. Se tiver algo errado, ela retorna 0.
Se estiver tudo certo, ela cria um novo nó da lista e coloca nele o destino e o peso da aresta.
Se o grafo não for ponderado o peso vira 1.0 automaticamente.
Depois ela coloca esse nó no começo se o grafo não for digrafo (`eh_digrafo == 0`), ela chama de novo a função para inserir a aresta ao contrário, assim o grafo vira não direcionado, 
No final retorna 1 para indicar que deu certo.</small>

d) Detalhe o funcionamento da função `removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo)`. Utilize trechos do código para ilustrar sua resposta.

<small>A função `removeAresta` tira uma aresta da lista do grafo.
Ela verifica se o grafo existe e se os vértices são válidos se não for, retorna 0
Depois ela pega a lista do vértice `orig` e percorre ela até achar o destino que quer remover, se o nó que vai sair for o primeiro da lista, ela só muda a cabeça da lista para o próximo.
Se for outro nó mais pra frente, ela liga o nó anterior direto no seguinte. O nó removido e apagado com `free`.
Se o grafo não for digrafo (`eh_digrafo == 0`), ela também remove a aresta contrária chamando a mesma função.
Sempre retorna 1 no final, mesmo que a aresta não exista.</small>