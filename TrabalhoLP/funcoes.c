#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // Para utilizar o getch()
#include <ctype.h> // Para utilizar o isdigit()
#include <string.h>
#include "biblioteca.h"
#define T 100

struct Produto
{
    int codigoBarras;
    char descricao[70];
    float precoUnit;
};

struct Carrinho
{
    struct Produto produto;
    int quantidade;
    float totalPrecoItem;
};

int inicializar()
{
    int i;
    int p = 0;
    int linhas = 1;
    char c, fimLinha = '\n';

    for(i = 0; i < 100; i++)
    {
        vCarrinho[i] = NULL;
    }

    FILE * arqProdutos = abrirArqLeitura("produtos.txt");

    //Lendo o arquivo 1 por 1
    while(fread (&c, sizeof(char), 1, arqProdutos))
    {
        if(c == fimLinha)
        {
            linhas++;
        }
    }
    fclose(arqProdutos);

    abrirArqLeitura("produtos.txt");

    do
    {
        fflush(stdin);

        if(p == T)
        {
            printf("Ocupou toda a memoria \n");
            exit(1);
        }

        if(vCarrinho[p] == NULL)
        {
            vCarrinho[p] = (pCarrinho)malloc(sizeof(struct Carrinho));
        }

        fflush(stdin);
        fscanf(arqProdutos, "%d", &vCarrinho[p]->produto.codigoBarras);
        fscanf(arqProdutos, "%s", vCarrinho[p]->produto.descricao);
        fscanf(arqProdutos, "%f", &vCarrinho[p]->produto.precoUnit);

        p++;

    } while(p < linhas);

    fclose(arqProdutos);

    return p;
}
void cadastrar(int p)
{
    FILE * arqProdutos = abrirArqEscrever("produtos.txt");

    if(p == T)
    {
        printf("Ocupou toda a memoria \n");
        exit(1);
    }
    if(vCarrinho[p] == NULL)
    {
        vCarrinho[p] = (pCarrinho)malloc(sizeof(struct Carrinho));
    }

    fflush(stdin);
    printf("Insira o codigo de barras: \n");
    vCarrinho[p]->produto.codigoBarras = isNum();
    fprintf(arqProdutos, "\n%d", vCarrinho[p]->produto.codigoBarras);

    fflush(stdin);
    printf("Digite a descricao: \n");
    gets(vCarrinho[p]->produto.descricao);
    fprintf(arqProdutos, " %s", vCarrinho[p]->produto.descricao);
    fflush(stdin);

    fflush(stdin);
    printf("Digite o preco unitario: \n");
    scanf("%f", &vCarrinho[p]->produto.precoUnit);
    fprintf(arqProdutos, " %.2f", vCarrinho[p]->produto.precoUnit);

    fclose(arqProdutos);
}
int consultar(int codBarras, int lim){
    int i;

    for(i = 0; i < lim; i++)
    {
        if(vCarrinho[i] != NULL)
        {
            if(codBarras == vCarrinho[i]->produto.codigoBarras)
            {
                printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
                printf("Descricao:    %s \n", vCarrinho[i]->produto.descricao);
                printf("Valor unit:   %.2f reais\n", vCarrinho[i]->produto.precoUnit);
                printf("Cod. Barra:   %d \n", vCarrinho[i]->produto.codigoBarras);
                printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
                system("pause");
                return i;
            }
        }
    }
    printf("Nenhum produto com este codigo de barras! \n\n");
    system("pause");
    return -1;
}
void imprimirTodos(int lim){
    int i;
    for(i = 0; i < lim; i++)
    {
        if(vCarrinho[i] != NULL)
        {
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
            printf("Descricao:    %s \n", vCarrinho[i]->produto.descricao);
            printf("Valor unit:   %.2f reais\n", vCarrinho[i]->produto.precoUnit);
            printf("Cod. Barra:   %d \n", vCarrinho[i]->produto.codigoBarras);
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
        }
    }
    system("pause");
}
FILE *abrirArqEscrever(char *caminho)
{
    FILE *p_arquivo = fopen(caminho, "a");
    return p_arquivo;
}
FILE *abrirArqLeitura(char *caminho)
{
    FILE * p_arquivo = fopen(caminho, "r");
    return p_arquivo;
}

void abrirVenda(int lim)
{
    float precoTotalCompra = 0;
    int codigoBarras;
    int quantidade;
    int cons;
    int p = 0;

    printf("\n\n -= CUPOM FISCAL ELETRONICO - SAT =- ");

    while(lim)
    {
        fflush(stdin);

        printf("\n\nDigite o codigo de barras: \n");
        codigoBarras = isNum();

        printf("\n");

        if(codigoBarras == 777)
        {
            printf("\n\nFim da operacao!\n\n");
            if(precoTotalCompra)
            {
                printf("Valor total atual da compra:   %.2f reais\n\n", precoTotalCompra);
            }
            return;
        }

        cons = consultar(codigoBarras, lim);

        if(cons >= 0)
        {
            do
            {
                printf("\n\nDigite a quantidade deste item: \n");
                quantidade = isNum();

            } while(quantidade < 1);

            vCarrinho[p]->quantidade = quantidade;
            vCarrinho[p]->totalPrecoItem = vCarrinho[cons]->produto.precoUnit * vCarrinho[p]->quantidade;

            printf("\nValor total do item:   %.2f reais\n", vCarrinho[p]->totalPrecoItem);
            precoTotalCompra += vCarrinho[p]->totalPrecoItem;
            printf("Valor total atual da compra:   %.2f reais\n", precoTotalCompra);
        }
    }
}
int isNum()
{
    char digitado[30]; // Armazena o que foi digitado pelo usuário
    char c; // Armazena cada caractere digitado pelo usuário
    int i = 0; // Variável para controlar o índice do vetor de caracteres
    int numero = 0; // Variável para armazenar a conversão do que foi digitado pelo usuário

        do
        {
            c = getch(); // Captura o caractere digitado pelo usuário

            if (isdigit(c) != 0) // Se for um número
            {
                digitado[i] = c; // Armazena no vetor de caracteres
                i++; // Incrementa o índice do vetor de caracteres
                printf ("%c", c); // Exibe o caractere digitado
            }

            else if(c == 8 && i) // Se for pressionada a tecla BACKSPACE e houver caracteres já digitados
            {
                digitado[i] = '\0'; // O índice atual do vetor de caracteres recebe a terminação da string
                i--; // O índice do vetor de caracteres é decrementado
                printf("\b \b"); // O caractere digitado é apagado da tela
            }

        }while(c != 13); // O loop vai ser executado até que a tecla pressionada seja o ENTER (código 13 na tabela ASCII)

    digitado[i] = '\0'; // O índice atual do vetor de caracteres recebe a terminação da string
    numero = atoi(digitado); // A variável numero recebe o valor do vetor de caracteres convertido para inteiro

    printf("\n");
    return numero;
}
