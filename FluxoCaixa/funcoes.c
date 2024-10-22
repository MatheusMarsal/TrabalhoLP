#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // Para utilizar o getch()
#include <ctype.h> // Para utilizar o isdigit()
#include <string.h>
#include "biblioteca.h"
#define T 150

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

    for(i = 0; i < T; i++)
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
                printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
                printf("Descricao:    %s \n", vCarrinho[i]->produto.descricao);
                printf("Valor unit:   %.2f reais\n", vCarrinho[i]->produto.precoUnit);
                printf("Cod. Barra:   %d \n", vCarrinho[i]->produto.codigoBarras);
                printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
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
            printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
            printf("Descricao:    %s \n", vCarrinho[i]->produto.descricao);
            printf("Valor unit:   %.2f reais\n", vCarrinho[i]->produto.precoUnit);
            printf("Cod. Barra:   %d \n", vCarrinho[i]->produto.codigoBarras);
            printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
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
    int quantidadeItems = 0;

    FILE *arqCompra = abrirArqEscrever("compra.txt");

    printf("\n\n -= CUPOM FISCAL ELETRONICO - SAT =- ");
    fprintf(arqCompra, "\n\n -= CUPOM FISCAL ELETRONICO - SAT =- \n\n");

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

                fprintf(arqCompra ,"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
                fprintf(arqCompra ,"Valor total do compra: %.2f reais\n", precoTotalCompra);
                fprintf(arqCompra ,"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
            }
            else
            {
                fprintf(arqCompra ,"\nCupom em branco!\n");
            }

            fclose(arqCompra);

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

            quantidadeItems++;

            printf("\nNumero do item:               %d \n", quantidadeItems);

            vCarrinho[cons]->quantidade = quantidade;
            vCarrinho[cons]->totalPrecoItem = vCarrinho[cons]->produto.precoUnit * vCarrinho[cons]->quantidade;


            printf("\nValor total do item:         %.2f reais\n", vCarrinho[cons]->totalPrecoItem);

            precoTotalCompra += vCarrinho[cons]->totalPrecoItem;

            printf("Valor total atual da compra:   %.2f reais\n\n", precoTotalCompra);

            system("pause");

            system("cls");

            fprintf(arqCompra ,"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
            fprintf(arqCompra ,"#:                     %d \n", quantidadeItems);
            fprintf(arqCompra ,"Cod. Barra:            %d \n", vCarrinho[cons]->produto.codigoBarras);
            fprintf(arqCompra ,"Descricao:             %s \n", vCarrinho[cons]->produto.descricao);
            fprintf(arqCompra ,"Valor unit:            %.2f reais\n", vCarrinho[cons]->produto.precoUnit);
            fprintf(arqCompra ,"Quantidade:            %d unidade(s)\n", vCarrinho[cons]->quantidade);
            fprintf(arqCompra ,"Valor total do item:   %.2f reais\n", vCarrinho[cons]->totalPrecoItem);
        }
    }
}
int isNum()
{
    char digitado[30]; // Armazena o que foi digitado pelo usu�rio
    char c; // Armazena cada caractere digitado pelo usu�rio
    int i = 0; // Vari�vel para controlar o �ndice do vetor de caracteres
    int numero = 0; // Vari�vel para armazenar a convers�o do que foi digitado pelo usu�rio

        do
        {
            c = getch(); // Captura o caractere digitado pelo usu�rio

            if (isdigit(c) != 0) // Se for um n�mero
            {
                digitado[i] = c; // Armazena no vetor de caracteres
                i++; // Incrementa o �ndice do vetor de caracteres
                printf ("%c", c); // Exibe o caractere digitado
            }

            else if(c == 8 && i) // Se for pressionada a tecla BACKSPACE e houver caracteres j� digitados
            {
                digitado[i] = '\0'; // O �ndice atual do vetor de caracteres recebe a termina��o da string
                i--; // O �ndice do vetor de caracteres � decrementado
                printf("\b \b"); // O caractere digitado � apagado da tela
            }

        }while(c != 13); // O loop vai ser executado at� que a tecla pressionada seja o ENTER (c�digo 13 na tabela ASCII)

    digitado[i] = '\0'; // O �ndice atual do vetor de caracteres recebe a termina��o da string
    numero = atoi(digitado); // A vari�vel numero recebe o valor do vetor de caracteres convertido para inteiro

    printf("\n");
    return numero;
}
