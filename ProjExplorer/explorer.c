#include "explorer.h"

// Funções Básicas
No* criaNo(char *nome, bool eArquivo) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo) {
        strcpy(novo->nome, nome);
        novo->eArquivo = eArquivo;
        novo->primFilho = NULL;
        novo->proxIrmao = NULL;
        novo->pai = NULL;
    }
    return novo;
}

void insereFilho(No *pai, No *filho) {
    if (pai == NULL || filho == NULL) return;

    filho->pai = pai; 
    filho->proxIrmao = NULL;

    if (pai->primFilho == NULL) {
        pai->primFilho = filho;
    } else {
        No *temp = pai->primFilho;
        while (temp->proxIrmao != NULL) {
            temp = temp->proxIrmao;
        }
        temp->proxIrmao = filho;
    }
}

No* buscaFilho(No *pai, char *nome) {
    if (pai == NULL || pai->primFilho == NULL) return NULL;
    No *temp = pai->primFilho;
    while (temp != NULL) {
        if (strcmp(temp->nome, nome) == 0) return temp;
        temp = temp->proxIrmao;
    }
    return NULL;
}

bool temExtensao(char *nome) {
    return strchr(nome, '.') != NULL;
}

// Sobe na árvore procurando um pai com o nome específico
No* buscarAncestral(No *atual, char *nome) {
    if (atual == NULL) return NULL;
    
    No *temp = atual->pai;
    while (temp != NULL) {
        if (strcmp(temp->nome, nome) == 0) {
            return temp;
        }
        temp = temp->pai;
    }
    return NULL;
}

void abrirArquivo(No *atual, char *nome) {
    No *alvo = buscaFilho(atual, nome);
    if (alvo == NULL) {
        printf("Erro: Arquivo '%s' nao encontrado.\n", nome);
    } else if (!alvo->eArquivo) {
        printf("Erro: '%s' e uma pasta, use 'cd' para entrar.\n", nome);
    } else {
        printf("------------------------------------------------\n");
        printf(" ABRINDO ARQUIVO: %s\n", alvo->nome);
        printf(" [ Simulando visualizacao de conteudo... ]\n");
        printf(" ... 1010101010101 ...\n");
        printf("------------------------------------------------\n");
    }
}

// Desconecta da pasta atual e conecta na lixeira
void moverParaLixeira(No *pai, char *nomeAlvo, No *lixeira) {
    if (pai == NULL || pai->primFilho == NULL) {
        printf("Erro: Item nao encontrado.\n");
        return;
    }

    No *anterior = NULL;
    No *atual = pai->primFilho;

    while (atual != NULL) {
        if (strcmp(atual->nome, nomeAlvo) == 0) {
            if (anterior == NULL)
                pai->primFilho = atual->proxIrmao;
            else
                anterior->proxIrmao = atual->proxIrmao;

            atual->proxIrmao = NULL;
            
            insereFilho(lixeira, atual);
            
            printf("Item '%s' movido para a Lixeira.\n", nomeAlvo);
            return;
        }
        anterior = atual;
        atual = atual->proxIrmao;
    }
    printf("Erro: '%s' nao encontrado.\n", nomeAlvo);
}

void liberarNosRecursivo(No *no) {
    if (no == NULL) return;
    liberarNosRecursivo(no->primFilho);
    liberarNosRecursivo(no->proxIrmao);
    free(no);
}

void esvaziarLixeira(No *lixeira) {
    if (lixeira->primFilho == NULL) {
        printf("Lixeira ja esta vazia.\n");
        return;
    }
    liberarNosRecursivo(lixeira->primFilho);
    lixeira->primFilho = NULL;
    printf("Lixeira esvaziada com sucesso.\n");
}

// Funções Auxiliares

void carregarArquivo(No *raiz, char *caminhoArquivo) {
    FILE *fp = fopen(caminhoArquivo, "r");
    if (!fp) {
        printf("Aviso: %s nao encontrado. Iniciando vazio.\n", caminhoArquivo);
        return;
    }
    char linha[256];
    while (fgets(linha, sizeof(linha), fp)) {
        linha[strcspn(linha, "\n")] = 0;
        No *atual = raiz;
        char *token = strtok(linha, "/");
        while (token != NULL) {
            No *proximo = buscaFilho(atual, token);
            if (proximo == NULL) {
                bool ehArq = temExtensao(token);
                No *novo = criaNo(token, ehArq);
                insereFilho(atual, novo);
                atual = novo;
            } else {
                atual = proximo;
            }
            token = strtok(NULL, "/");
        }
    }
    fclose(fp);
}

void listar(No *atual) {
    if (!atual) return;
    printf("\nDiretorio: ");
    imprimeCaminho(atual);
    printf("\n--------------------------\n");
    
    No *filho = atual->primFilho;
    if (!filho) {
        printf("  (vazio)\n");
        return;
    }
    while (filho != NULL) {
        if (strcmp(filho->nome, "Lixeira") != 0 || strcmp(atual->nome, "Lixeira") == 0) {
             printf("  %s %s\n", filho->eArquivo ? "[ARQ]" : "[DIR]", filho->nome);
        }
        filho = filho->proxIrmao;
    }
    printf("\n");
}

void imprimeCaminho(No *no) {
    if (no == NULL) return;
    if (no->pai != NULL) { 
        imprimeCaminho(no->pai);
        printf("/");
    }
    printf("%s", no->nome);
}

void search(No *raiz, char *alvo) {
    if (raiz == NULL) return;
    if (strcmp(raiz->nome, alvo) == 0) {
        printf("Encontrado: ");
        imprimeCaminho(raiz);
        printf("\n");
    }
    search(raiz->primFilho, alvo);
    search(raiz->proxIrmao, alvo);
}

// Remove Definitivo
void removerDefinitivo(No *pai, char *nomeAlvo) {
    if (pai == NULL || pai->primFilho == NULL) {
        printf("Erro: Item nao encontrado.\n");
        return;
    }
    No *anterior = NULL;
    No *atual = pai->primFilho;
    while (atual != NULL) {
        if (strcmp(atual->nome, nomeAlvo) == 0) {
            if (anterior == NULL) pai->primFilho = atual->proxIrmao;
            else anterior->proxIrmao = atual->proxIrmao;
            
            atual->proxIrmao = NULL; 
            liberarNosRecursivo(atual);
            printf("Item '%s' deletado permanentemente.\n", nomeAlvo);
            return;
        }
        anterior = atual;
        atual = atual->proxIrmao;
    }
    printf("Erro: '%s' nao encontrado.\n", nomeAlvo);
}

int prefixoIgual(char *str1, char *prefixo) {
    while (*prefixo) {
        if (!*str1) return 0;
        if (tolower(*str1) != tolower(*prefixo)) return 0;
        str1++;
        prefixo++;
    }
    return 1;
}

void sugerirDiretorios(No *pai, char *termo) {
    if (!pai || !pai->primFilho) {
        printf("Diretorio nao encontrado.\n");
        return;
    }

    int encontrados = 0;
    No *temp = pai->primFilho;
    
    while (temp != NULL) {
        if (!temp->eArquivo && prefixoIgual(temp->nome, termo)) {
            if (encontrados == 0) {
                printf("Diretorio '%s' nao encontrado.\n", termo);
                printf("Voce quis dizer:\n");
            }
            printf(" - %s\n", temp->nome);
            encontrados++;
        }
        temp = temp->proxIrmao;
    }
    if (encontrados == 0) {
        printf("Diretorio '%s' nao encontrado.\n", termo);
    }
}

void liberarArvore(No *no) {
    liberarNosRecursivo(no);
}

void exibirHelp() {
    printf("---------------------------------------------------------\n");
    printf("\t\tHELP\n");
    printf("---------------------------------------------------------\n");
    printf("cd <nome>       : Entra em uma pasta\n");
    printf("list            : Lista conteudo da pasta atual.\n");
    printf("open <arquivo>  : Abre um arquivo para visualizacao.\n");
    printf("rm <nome>       : Move item para a Lixeira.\n");
    printf("lixeira         : Exibe conteudo da lixeira.\n");
    printf("empty           : Esvazia a lixeira definitivamente.\n");
    printf("search <nome>   : Busca global.\n");
    printf("mkdir <nome>    : Cria pasta.\n");
    printf("exit            : Sair.\n");
    printf("---------------------------------------------------------\n");
}