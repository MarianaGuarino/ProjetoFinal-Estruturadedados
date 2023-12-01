#include <stdio.h>
#include <stdlib.h>

#define OP_MIN          0
#define OP_MAX          10
#define SAIR            0
#define INCLUSAO        1
#define LISTAGEM_PRE    2
#define LISTAGEM_EM     3
#define LISTAGEM_POS    4
#define CONSULTA        5
#define MINIMO          6
#define MAXIMO          7

struct tProduto {
    int codigo;
    char descricao[50];
};

struct tNo {
    struct tProduto dado;
    struct tNo *esq;
    struct tNo *dir;
};

struct tNo *minimo(struct tNo *arvore) {
    if (arvore == NULL || arvore->esq == NULL)
        return arvore;
    return minimo(arvore->esq);
}

struct tNo *maximo(struct tNo *arvore) {
    if (arvore == NULL || arvore->dir == NULL)
        return arvore;
    return maximo(arvore->dir);
}

int mostrarMenu();
void inicializar(struct tNo **);
void incluir(struct tNo **, struct tNo *);
void listarPre(struct tNo *);
void listarEm(struct tNo *);
void listarPos(struct tNo *);
struct tNo *consultar(struct tNo *, int);
void alterar(struct tNo **);
void excluir(struct tNo **, struct tNo *);
struct tNo *menor(struct tNo *);
void destruir(struct tNo *);

int main(void) {
    struct tNo *raiz, *p;

    int opcao, codigo;

    inicializar(&raiz);

    do {

        system("cls");
        opcao = mostrarMenu();

        switch (opcao) {
        case INCLUSAO:
            system("cls");
            printf("--> INCLUSAO \n\n");
            p = malloc(sizeof(struct tNo));
            printf("Digite o codigo: ");
            fflush(stdin);
            scanf("%d", &(p->dado.codigo));
            printf("Digite a descricao: ");
            fflush(stdin);
            gets(p->dado.descricao);
            incluir(&raiz, p);
            putchar('\n');
            system("pause");
            break;

        case LISTAGEM_PRE:
            system("cls");
            printf("--> LISTAGEM (Pre-ordem)\n\n");
            listarPre(raiz);
            putchar('\n');
            system("pause");
            break;

        case LISTAGEM_EM:
            system("cls");
            printf("--> LISTAGEM (Em-ordem)\n\n");
            listarEm(raiz);
            putchar('\n');
            system("pause");
            break;

        case LISTAGEM_POS:
            system("cls");
            printf("--> LISTAGEM (Pos-ordem)\n\n");
            listarPos(raiz);
            putchar('\n');
            system("pause");
            break;

        case CONSULTA:
            system("cls");
            printf("--> CONSULTA \n\n");
            printf("Digite o codigo: ");
            scanf("%d", &codigo);
            p = consultar(raiz, codigo);
            if (p == NULL)
                printf("\nNenhum resultado para a busca....\n\n");
            else {
                printf("\n--> Codigo ...: %d\n", p->dado.codigo);
                printf("--> Descricao .: %s\n", p->dado.descricao);
            }
            system("pause");
            break;

        case MINIMO:
            p = minimo(raiz);
            if (p != NULL)
                printf("Menor codigo: %d\n", p->dado.codigo);
            else {
                printf("Arvore vazia.\n");
            }
            system("pause");
            break;

        case MAXIMO:
            p = maximo(raiz);
            if (p != NULL)
                printf("Maior codigo: %d\n", p->dado.codigo);
            else {
                printf("Arvore vazia.\n");
            }
            system("pause");
            break;

        case SAIR:
            break;
        }

    } while (opcao != SAIR);

    destruir(raiz);

    return 0;
}

void inicializar(struct tNo **arvore) {
    (*arvore) = NULL;
}

void incluir(struct tNo **arvore, struct tNo *novo) {
    if ((*arvore) == NULL) {
        novo->dir = novo->esq = NULL;
        (*arvore) = novo;
    } else if (novo->dado.codigo < (*arvore)->dado.codigo)
        incluir(&((*arvore)->esq), novo);
    else
        incluir(&((*arvore)->dir), novo);
}

void listarPre(struct tNo *arvore) {
    if (arvore == NULL)
        return;
    printf("--> %d - %s\n", arvore->dado.codigo, arvore->dado.descricao);
    listarPre(arvore->esq);
    listarPre(arvore->dir);
}

void listarEm(struct tNo *arvore) {
    if (arvore == NULL)
        return;
    listarEm(arvore->esq);
    printf("--> %d - %s\n", arvore->dado.codigo, arvore->dado.descricao);
    listarEm(arvore->dir);
}

void listarPos(struct tNo *arvore) {
    if (arvore == NULL)
        return;
    listarPos(arvore->esq);
    listarPos(arvore->dir);
    printf("--> %d - %s\n", arvore->dado.codigo, arvore->dado.descricao);
}

struct tNo *consultar(struct tNo *arvore, int codigo) {
    if ((arvore == NULL) || (arvore->dado.codigo == codigo))
        return arvore;
    if (codigo < arvore->dado.codigo)
        return consultar(arvore->esq, codigo);
    return consultar(arvore->dir, codigo);
}

void alterar(struct tNo **no) {
    printf("\nDigite a nova descricao: ");
    fflush(stdin);
    gets((*no)->dado.descricao);
}

void excluir(struct tNo **arvore, struct tNo *no) {
    struct tNo *p;
    if ((*arvore)->dado.codigo == no->dado.codigo) {
        if ((no->esq == NULL) && (no->dir == NULL)) { // Grau 0
            (*arvore) = NULL;
            free(no);
        } else if ((no->esq != NULL) && (no->dir != NULL)) { // Grau 2
            p = menor((*arvore)->esq);
            (*arvore)->dado = p->dado;
            excluir(&((*arvore)->esq), p);
        } else { // Grau 1
            p = *arvore;
            if((*arvore)->esq != NULL)
                (*arvore) = (*arvore)->esq;
            else
                (*arvore) = (*arvore)->dir;
            free(p);
        }
    } else {
        if(no->dado.codigo < (*arvore)->dado.codigo)
            excluir(&((*arvore)->esq), no);
        else
            excluir(&((*arvore)->dir), no);   
    }
}

struct tNo *menor(struct tNo *arvore) {
    if((arvore == NULL) || (arvore->esq == NULL))
        return arvore;
    return menor(arvore->esq);
}

void destruir(struct tNo *arvore) {
    if(arvore == NULL)
        return;
    destruir(arvore->esq);
    destruir(arvore->dir);
    free(arvore);
}


int mostrarMenu(){
    int op;
    
    printf("***************************\n");
    printf("*           MENU          *\n");
    printf("***************************\n");
    printf("* INCLUSAO              1 *\n");
    printf("* LISTAGEM (Pre-ordem)  2 *\n");
    printf("* LISTAGEM (Em-ordem)   3 *\n");
    printf("* LISTAGEM (Pos-ordem)  4 *\n");
    printf("* CONSULTA              5 *\n");
    printf("* MINIMO                6 *\n");
    printf("* MAXIMO                7 *\n");
    printf("* SAIR                  0 *\n");
    printf("***************************\n");
    
    do{
        printf("Qual a opcao desejada: ");
        scanf("%d", &op);
        if(op < OP_MIN || op > OP_MAX)
            printf("Valor invalido, digite novamente... \n");
    }while(op < OP_MIN || op > OP_MAX);

    return op;
}