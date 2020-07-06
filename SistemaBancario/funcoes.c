#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // Para utilizar o getch()
#include <ctype.h> // Para utilizar o isdigit()
#include <string.h>
#include <inttypes.h>
#include "biblioteca.h"
#define T 100

struct Cliente
{
    char nome[256];
    int64_t cpf;
};

struct Conta
{
    int numero_da_conta;
    struct Cliente cliente;
    float saldo;
};

int inicializar()
{
    int i;
    int p = 0;
    int linhas = 1;
    char c, fimLinha = '\n';

    for(i = 0; i < 100; i++)
    {
        vConta[i] = NULL;
    }

    FILE * arqContas = abrirArqLeitura("contas.txt");

    //Contando as linhas do arquivo
    while(fread (&c, sizeof(char), 1, arqContas))
    {
        if(c == fimLinha)
        {
            linhas++;
        }
    }
    fclose(arqContas);

    abrirArqLeitura("contas.txt");

    do
    {
        fflush(stdin);

        if(p == T)
        {
            printf("Ocupou toda a memoria \n");
            exit(1);
        }

        if(vConta[p] == NULL)
        {
            vConta[p] = (pConta)malloc(sizeof(struct Conta));
        }

        vConta[p]->cliente.cpf = 1ll;

        fflush(stdin);
        fscanf(arqContas, "%d", &vConta[p]->numero_da_conta);
        fscanf(arqContas, "%"PRId64"", &vConta[p]->cliente.cpf);
        fscanf(arqContas, "%s", vConta[p]->cliente.nome);
        fscanf(arqContas, "%f", &vConta[p]->saldo);

        p++;

    } while(p < linhas);

    fclose(arqContas);

    return p;
}
void cadastrar(int p)
{
    FILE * arqContas = abrirArqEscrever("contas.txt");

    if(p == T)
    {
        printf("Ocupou toda a memoria \n");
        exit(1);
    }
    if(vConta[p] == NULL)
    {
        vConta[p] = (pConta)malloc(sizeof(struct Conta));
    }

    fflush(stdin);
    vConta[p]->numero_da_conta = p + 1;
    fprintf(arqContas, "\n%d", vConta[p]->numero_da_conta);

    fflush(stdin);
    printf("Insira o cpf do cliente: \n");
    vConta[p]->cliente.cpf = isNum();
    fprintf(arqContas, " %"PRId64"", vConta[p]->cliente.cpf);

    fflush(stdin);
    printf("Digite o nome do cliente: (Favor substituir espacos por _)\n");
    gets(vConta[p]->cliente.nome);
    fprintf(arqContas, " %s", vConta[p]->cliente.nome);
    fflush(stdin);

    fflush(stdin);
    vConta[p]->saldo = 0.00;
    fprintf(arqContas, " %.2f", vConta[p]->saldo);

    fclose(arqContas);
}
int consultar(int cpf, int lim){
    int i;

    for(i = 0; i < lim; i++)
    {
        if(vConta[i] != NULL)
        {
            if(cpf == vConta[i]->cliente.cpf)
            {
                printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
                printf("Conta num.: %d \n", vConta[i]->numero_da_conta);
                printf("cpf:        %"PRId64" \n", vConta[i]->cliente.cpf);
                printf("Nome:       %s \n", vConta[i]->cliente.nome);
                printf("Saldo:      %.2f reais \n", vConta[i]->saldo);
                printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
                system("pause");
                return i;
            }
        }
    }
    printf("Nenhum cliente cadastrado neste CPF! \n\n");
    system("pause");
    return -1;
}
void imprimirTodos(int lim){
    int i;
    for(i = 0; i < lim; i++)
    {
        if(vConta[i] != NULL)
        {
            printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
            printf("Conta num.: %d \n", vConta[i]->numero_da_conta);
            printf("cpf:        %"PRId64" \n", vConta[i]->cliente.cpf);
            printf("Nome:       %s \n", vConta[i]->cliente.nome);
            printf("Saldo:      %.2f reais \n", vConta[i]->saldo);
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

/* void abrirOperac(int lim)
{
    float precoTotalCompra = 0;
    int codigoBarras;
    int quantidade;
    int cons;
    int quantidadeItems = 0;

    FILE *arqCompra = abrirArqEscrever("relatorio.txt");

    //printf("\n\n -= Relatorio de uso do Sistema bancanrio - Banco LP S\\A =- ");
    fprintf(arqCompra, "\n\n -= Relatorio de uso do Sistema bancanrio - Banco LP S\\A \n\n");

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

            vConta[cons]->quantidade = quantidade;
            vConta[cons]->totalPrecoItem = vConta[cons]->produto.precoUnit * vConta[cons]->quantidade;


            printf("\nValor total do item:         %.2f reais\n", vConta[cons]->totalPrecoItem);

            precoTotalCompra += vConta[cons]->totalPrecoItem;

            printf("Valor total atual da compra:   %.2f reais\n\n", precoTotalCompra);

            system("pause");

            system("cls");

            fprintf(arqCompra ,"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
            fprintf(arqCompra ,"#:                     %d \n", quantidadeItems);
            fprintf(arqCompra ,"Cod. Barra:            %d \n", vConta[cons]->produto.codigoBarras);
            fprintf(arqCompra ,"Descricao:             %s \n", vConta[cons]->produto.descricao);
            fprintf(arqCompra ,"Valor unit:            %.2f reais\n", vConta[cons]->produto.precoUnit);
            fprintf(arqCompra ,"Quantidade:            %d unidade(s)\n", vConta[cons]->quantidade);
            fprintf(arqCompra ,"Valor total do item:   %.2f reais\n", vConta[cons]->totalPrecoItem);
        }
    }
} */
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
