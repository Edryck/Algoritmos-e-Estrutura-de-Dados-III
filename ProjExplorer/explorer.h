#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definição do Tipo Booleano
typedef int bool;
#define TRUE 1
#define FALSE 0

// Estrutura do Nó
typedef struct No {
    char nome[50]; // Nome do nó
    bool eArquivo; // Booleano para dizer se o nó atual é arquivo ou diretório        
    struct No *pai; // Nó pai do nó atual  
    struct No *primFilho; // Nó filho do nó atual
    struct No *proxIrmao; // Nó que está do lado do nó atual
} No;

// Funções de Criação e Estrutura
// Cria a estrutura do nó
No* criaNo(char *nome, bool eArquivo);
// Faz a inserção
void insereFilho(No *pai, No *filho);
// Procura pelo nó filho
No* buscaFilho(No *pai, char *nome);
// Carrega o arquivo (in.txt)
void carregarArquivo(No *raiz, char *caminhoArquivo);
// Libera a Árvore
void liberarArvore(No *no);
// Procura um nó "pai" pelo nome
No* buscarAncestral(No *atual, char *nome);
// Simula a abertura de um arquivo
void abrirArquivo(No *atual, char *nome);
// Move um nó da pasta atual para a lixeira
void moverParaLixeira(No *pai, char *nomeAlvo, No *lixeira);
// Esvazia a lixeira
void esvaziarLixeira(No *lixeira);
// <list> Lista o conteúdo do diretório
void listar(No *atual);
// <search> Procura por um arquivo ou diretório na árvore
void search(No *raiz, char *alvo);
// <lixeira> Remove da maneira definitiva as coisa que estão na lixeira
void removerDefinitivo(No *pai, char *nomeAlvo);
// Sugere o nome do diretório
void sugerirDiretorios(No *pai, char *termo);
// Imprime o caminho, ex: C:/Meus Documentos
void imprimeCaminho(No *no);

// Exibe o Menu de Ajuda
void exibirHelp();