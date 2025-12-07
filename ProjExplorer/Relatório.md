Relatório: Simulador de Sistema de Arquivos

Integrantes:
Edryck Freitas Nascimento, RA: a2727617
Samuel Oliveira Simões da Silva, RA: a2727820

Este projeto consiste no desenvolvimento de um simulador de sistema de arquivos utilizando a linguagem C. O objetivo foi aplicar conceitos de estruturas de dados, especificamente árvores genéricas representadas no modelo "Filho Esquerdo - Irmão Direito" (First Child / Next Sibling), para criar uma hierarquia de diretórios e arquivos navegável via linha de comando.
O sistema vai além das operações básicas, implementando funcionalidades inspiradas em sistemas operacionais reais, como Lixeira com remoção lógica e definitiva, navegação bidirecional, autocompletar inteligente e simulação de abertura de arquivos.

1. Estrutura de Dados
A escolha fundamental para este projeto foi a representação de árvore "Filho Esquerdo - Irmão Direito" (First Child / Next Sibling).
A Estrutura do Nó:
Para suportar navegação, como voltar pastas e localizar ancestrais, adicionamos um ponteiro para o nó pai, além dos ponteiros para o primeiro filho e para o próximo irmão, assim permitindo representar um diretório com qualquer quantidade de filhos:

typedef struct No {
    char nome[100];         
    bool eArquivo;        // Diferencia Arquivos de Pastas
    struct No *pai;       // Permite subir na árvore (cd ..)
    struct No *primFilho; // Aponta para o conteúdo da pasta (descida)
    struct No *proxIrmao; // Aponta para o próximo item no mesmo nível
} No;

Dessa forma permite que um diretório tenha um número potencialmente ilimitado de subpastas ou arquivos sem desperdício de memória e sem a complexidade de realocação de vetores dinâmicos.
Além disso, o uso de um tipo booleano (bool) auxilia na distinção clara entre nós que representam arquivos e nós que representam diretórios, simplificando as decisões de navegação e de operações como open, cd e rm.

2. Funcionalidades Implementadas
2.1. Navegação e Manipulação Básica
Carregamento (in.txt): O sistema inicializa lendo um arquivo de texto (in.txt), tokenizando as strings (por exemplo: Pasta/Sub/Arq) e montando a árvore dinamicamente. Cada linha é quebrada por '/', e para cada token:
Se já existir um filho com aquele nome, o sistema apenas navega até ele.
Se não existir, é criado um novo nó e inserido como filho.
A função também diferencia arquivos de diretórios com base na presença de extensão (uso de ponto . no nome), definindo o campo eArquivo de forma adequada.
mkdir e list:
mkdir: realiza a criação de novos diretórios como filhos do diretório atual, evitando duplicatas de nome.
list: lista os filhos do diretório atual, indicando se cada item é arquivo ([ARQ]) ou diretório ([DIR]). A pasta especial "Lixeira" é ocultada da listagem normal e só aparece quando o usuário está dentro dela.
search:
O comando search realiza uma busca em profundidade (DFS) em toda a árvore para localizar arquivos ou diretórios pelo nome, exibindo o caminho completo até cada ocorrência encontrada.

2.2. Navegação Inteligente (cd) e Sugestões
O comando cd foi significativamente aprimorado para tornar a navegação mais flexível e intuitiva:
Ancestrais:
Além do uso padrão de cd .. para retornar ao diretório pai, o sistema permite "pular" diretamente para um ancestral digitando seu nome.
Se o usuário estiver em uma subpasta profunda e digitar, por exemplo, cd C: ou cd Documentos, o algoritmo percorre os ponteiros pai recursivamente em busca de um nó ancestral com aquele nome, permitindo algo como "teletransporte" para níveis superiores da árvore.
Sugestão Case-Insensitive:
Foi implementado um algoritmo robusto de sugestão (sugerirDiretorios) que entra em ação quando o diretório alvo não é encontrado entre os filhos do diretório atual nem entre os ancestrais:
Ele ignora diferenças entre maiúsculas e minúsculas (usando tolower), tornando a navegação mais tolerante a variações de caixa.
Faz comparação por prefixo: se o usuário digitar cd me, o sistema verifica quais diretórios filhos possuem nomes cujo prefixo, ignorando caixa, coincide com "me" (por exemplo, sugerindo "Meus Documentos").
Feedback Claro: Primeiro informa que o diretório não foi encontrado e, em seguida, lista alternativas no formato "Você quis dizer:".
Caso nenhum candidato seja encontrado, o sistema informa claramente que o diretório não foi localizado.
Esse conjunto de comportamentos torna o comando cd mais próximo de shells reais, combinando navegação clássica (.., raiz) com uma navegação inteligente baseada em ancestrais e sugestões.

2.3. Sistema de Lixeira (Recycle Bin)
Implementamos uma lógica completa de Soft Delete vs Hard Delete para arquivos e diretórios:
Lixeira Oculta:
Ao iniciar, o sistema cria uma pasta especial "Lixeira" na raiz (C:).
Essa pasta é tratada como uma pasta de sistema, ficando oculta da listagem padrão (list) quando o usuário está em qualquer outro diretório que não seja a própria Lixeira.
Comando rm (Mover/Deletar):
Quando o usuário executa rm <nome> em um diretório comum, o item não é imediatamente liberado da memória.
Em vez disso, a função localiza o nó na lista de filhos do diretório atual, "descostura" os ponteiros para removê-lo dali e o reinsere como filho da pasta "Lixeira".
Isso caracteriza uma remoção lógica (Soft Delete): o item sai da visão do diretório original, mas permanece acessível dentro da Lixeira.
Comando lixeira:
O comando lixeira permite entrar nessa pasta especial, alterando o diretório atual para a Lixeira e exibindo seu conteúdo.
A partir deste contexto, os comandos passam a operar diretamente sobre o conteúdo descartado.
Recuperação e Limpeza (Hard Delete):
Dentro da Lixeira, o comando rm deixa de apenas mover e passa a realizar a remoção definitiva de um item específico, liberando recursivamente toda a memória associada àquele nó e ao seu sub-ramo.
O comando empty esvazia a Lixeira como um todo, aplicando liberação recursiva a todos os filhos da pasta "Lixeira" e garantindo que nenhum nó descartado permaneça alocado.
Dessa forma, a Lixeira modela dois estágios distintos de remoção: primeiro lógico (movimentação para a Lixeira) e depois definitivo (deleção permanente com liberação de memória).

2.4. Simulação de Arquivos (open)
O sistema diferencia claramente arquivos de diretórios por meio do campo eArquivo. Com isso:
O comando cd é bloqueado quando o alvo é um arquivo, informando ao usuário que se trata de um arquivo e sugerindo o uso de open.
O comando open <arquivo> simula a visualização do conteúdo, validando se o alvo existe no diretório atual e se é realmente um arquivo.
Em caso de sucesso, o sistema exibe uma saída formatada que representa a "abertura" do arquivo, reforçando o comportamento típico de um shell, ainda que sem conteúdo real associado.

Desafios Técnicos:
Comparação de Strings (Case Insensitive)
A biblioteca padrão string.h não possui uma função portável padrão para comparação ignorando caixa alta/baixa (por exemplo, strcasecmp não é parte do padrão ANSI C). Por isso, foi necessário implementar uma função auxiliar prefixoIgual, que percorre as strings caractere a caractere, convertendo ambos para minúsculo antes da comparação.
Essa função garante que a sugestão de diretórios funcione corretamente para entradas como "me", "ME" ou "Me", sem depender de extensões específicas de compilador.
Manipulação de Ponteiros na Lixeira
Mover um sub-ramo inteiro da árvore exige precisão na manipulação de ponteiros:
Localizar o item correto na lista de irmãos do diretório atual.
"Costurar" a lista, fazendo com que o nó anterior passe a apontar para o próximo, removendo o alvo do encadeamento sem quebrar a estrutura.
Isolar o nó movido (garantindo que proxIrmao seja NULL) antes de inseri-lo na Lixeira, evitando que, ao mover um item, outros irmãos sejam levados junto de forma indevida.
Em operações de remoção definitiva (rm dentro da Lixeira ou empty), garantir que a função recursiva de liberação percorra tanto filhos quanto irmãos, liberando toda a memória associada ao sub-ramo.
Esses cuidados foram essenciais para evitar vazamentos de memória, ponteiros pendentes e comportamentos indefinidos durante o uso intenso de rm, lixeira e empty.

O projeto atendeu os requisitos propostos e expandiu o escopo com funcionalidades robustas. A utilização de uma árvore genérica com representação "Filho Esquerdo - Irmão Direito" mostrou-se eficiente para modelar hierarquias de diretórios e arquivos, e a implementação de algoritmos de sugestão, navegação por ancestrais e sistema de Lixeira (com remoção lógica e definitiva) aproximou significativamente a experiência do usuário da de um shell real.
Além disso, o desenvolvimento exigiu o domínio de manipulação de ponteiros, recursão, gerenciamento manual de memória e técnicas de comparação de strings, consolidando na prática conceitos fundamentais de estruturas de dados e de organização de sistemas de arquivos em C.
