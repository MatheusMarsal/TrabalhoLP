#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // Para utilizar o getch()
#include <ctype.h> // Para utilizar o isdigit()
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
    float totalCarrinho;
};

void inicializar()
{
    int i;

    for(i = 0; i < 100; i++)
    {
        vCarrinho[i] = NULL;
    }
}
void cadastrar(int p)
{
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

    fflush(stdin);
    printf("Digite a descricao: \n");
    gets(vCarrinho[p]->produto.descricao);
    fflush(stdin);

    fflush(stdin);
    printf("Digite o preco unitario: \n");
    scanf("%f", &vCarrinho[p]->produto.precoUnit);
}
void imprimir(int codBarras){
    int i;
    for(i = 0; i < 100; i++)
    {
        if(vCarrinho[i] != NULL)
        {
            if(codBarras == vCarrinho[i]->produto.codigoBarras)
            {
                system("cls");
                printf("Descricao:    %s \n", vCarrinho[i]->produto.descricao);
                printf("Valor unit:   %.2f reais\n", vCarrinho[i]->produto.precoUnit);
                printf("Cod. Barra:   %d \n", vCarrinho[i]->produto.codigoBarras);
                system("pause");
            }
        }
    }
    printf("Nenhum produto com este codigo de barras \n");
    system("pause");
}
void imprimirTodos(){
    int i;
    for(i = 0; i < 100; i++)
    {
        if(vCarrinho[i] != NULL)
        {
            printf("Descricao:    %s \n", vCarrinho[i]->produto.descricao);
            printf("Valor unit:   %.2f reais\n", vCarrinho[i]->produto.precoUnit);
            printf("Cod. Barra:   %d \n", vCarrinho[i]->produto.codigoBarras);
            printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
        }
    }
    system("pause");
}



int isNum()
{
    char digitado[10]; // Armazena o que foi digitado pelo usu�rio
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
