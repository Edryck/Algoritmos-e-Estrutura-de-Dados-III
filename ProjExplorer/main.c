#include "explorer.h"

int main() {
    No *raiz = criaNo("C:", FALSE);
    
    // Cria a Lixeira como uma pasta oculta na raiz
    No *lixeira = criaNo("Lixeira", FALSE);
    insereFilho(raiz, lixeira);

    No *atual = raiz;
    carregarArquivo(raiz, "in.txt");
    
    printf("Sistema Iniciado.\n");

    char entrada[100], comando[20], argumento[80];

    while (1) {
        // Exibe "Lixeira>" se estiver nela, senão exibe caminho normal
        if (atual == lixeira) printf("\n[Lixeira]> ");
        else {
            printf("\n");
            imprimeCaminho(atual);
            printf("> ");
        }
        
        if (fgets(entrada, sizeof(entrada), stdin) == NULL) break;
        entrada[strcspn(entrada, "\n")] = 0;
        
        // Limpa buffers
        memset(comando, 0, sizeof(comando));
        memset(argumento, 0, sizeof(argumento));

        int itensLidos = sscanf(entrada, "%s %[^\n]", comando, argumento);
        if (itensLidos < 1) continue;

        if (strcmp(comando, "exit") == 0) {
            liberarArvore(raiz);
            break;
        }
        else if (strcmp(comando, "help") == 0) exibirHelp();
        else if (strcmp(comando, "clear") == 0) {
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
        }
        else if (strcmp(comando, "list") == 0) listar(atual);
        
        // Comando para abrir arquivos <open>
        else if (strcmp(comando, "open") == 0) {
            if (itensLidos < 2) printf("Uso: open <arquivo>\n");
            else abrirArquivo(atual, argumento);
        }

        // Comando para criar <mkdir>
        else if (strcmp(comando, "mkdir") == 0) {
            if (itensLidos < 2) printf("Uso: mkdir <nome>\n");
            else if (buscaFilho(atual, argumento)) printf("Erro: Ja existe.\n");
            else {
                insereFilho(atual, criaNo(argumento, FALSE));
                printf("Criado.\n");
            }
        }

        // Comando para remover <rm>
        else if (strcmp(comando, "rm") == 0) {
            if (itensLidos < 2) printf("Uso: rm <nome>\n");
            else {
                // Se já estiver na lixeira, deleta permanente
                if (atual == lixeira) {
                    removerDefinitivo(atual, argumento);
                } else {
                    // Senão, move para lixeira
                    moverParaLixeira(atual, argumento, lixeira);
                }
            }
        }

        // Comandos da lixeira <lixeira>
        else if (strcmp(comando, "lixeira") == 0) {
            atual = lixeira; // Vai para a pasta da lixeira
            listar(atual);
        }
        else if (strcmp(comando, "empty") == 0) {
            esvaziarLixeira(lixeira);
        }

        // Comando de busca <search>
        else if (strcmp(comando, "search") == 0) {
            if (itensLidos < 2) printf("Uso: search <nome>\n");
            else search(raiz, argumento);
        }

        // Comando de navegação <cd>
        else if (strcmp(comando, "cd") == 0) {
            if (itensLidos < 2) printf("Uso: cd <nome>\n");
            else if (strcmp(argumento, "..") == 0) {
                if (atual->pai != NULL) atual = atual->pai;
                else printf("Ja esta na raiz.\n");
            }
            // Verifica se o usuário digitou o nome da raiz, ex: C:
            else if (strcmp(argumento, raiz->nome) == 0) {
                atual = raiz;
            }
            else {
                No *destino = buscaFilho(atual, argumento);
                
                // Se não achou no filho, volta as pastas, ex: C:/Meus Documentos -> C:
                if (destino == NULL) {
                    destino = buscarAncestral(atual, argumento);
                }

                if (destino != NULL) {
                    if (destino->eArquivo) printf("Erro: E um arquivo.\n");
                    else atual = destino;
                } else {
                    sugerirDiretorios(atual, argumento);
                }
            }
        }
        else printf("Comando desconhecido.\n");
    }
    return 0;
}