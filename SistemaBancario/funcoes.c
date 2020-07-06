#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // Para utilizar o getch()
#include <ctype.h> // Para utilizar o isdigit()
#include <string.h>
#include <inttypes.h> //não consegui fazer bom uso...
#include "biblioteca.h"
#define T 100

struct Cliente
{
    char nome[256];
    int cpf;
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

        fflush(stdin);
        fscanf(arqContas, "%d", &vConta[p]->numero_da_conta);
        fscanf(arqContas, "%d", &vConta[p]->cliente.cpf);
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
    fprintf(arqContas, " %d", vConta[p]->cliente.cpf);

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
int consultar(int64_t cpf, int lim){
    int i;

    for(i = 0; i < lim; i++)
    {
        if(vConta[i] != NULL)
        {
            if(cpf == vConta[i]->cliente.cpf)
            {
                printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
                printf("Conta num.: %d \n", vConta[i]->numero_da_conta);
                printf("cpf:        %d \n", vConta[i]->cliente.cpf);
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
            printf("cpf:        %d \n", vConta[i]->cliente.cpf);
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

 void abrirOperacoes(int lim)
{
    int cpf;
    int cons;
    int opc = 0;

    system("cls");

    fflush(stdin);

    printf("Digite o CPF do cliente para fazer as operacoes: \n");
    cpf = isNum();
    printf("\n");

    cons = consultar(cpf, lim);

    if(cons < 0)
    {
        printf("\nVoltando ao menu principal!\n\n");

        return;
    }

    FILE *arqRelatorio = abrirArqEscrever("relatorio.txt");

    fprintf(arqRelatorio, "\n\n -= Relatorio de uso do Sistema Bancario - Banco LP S\\A \n\n");

    fclose(arqRelatorio);

    do
    {
        FILE *arqRelatorio = abrirArqEscrever("relatorio.txt");

        system("cls");

        printf("\n-= Banco LP S/A =-\n\n");

        printf("1.: Deposito \n");
        printf("2.: Consultar saldo\n");
        printf("3.: Saque \n");
        printf("9.: Voltar menu principal \n\n");

        printf("Digite a operacao que deseja realizar: \n");
        opc = isNum();

        switch(opc)
        {
            case 1:
                system("cls");

                fclose(arqRelatorio);

                realizarDeposito(cons, lim);

                break;

            case 2:
                system("cls");

                printf("Saldo atual de %s: %.2f reais\n", vConta[cons]->cliente.nome, vConta[cons]->saldo);

                fprintf(arqRelatorio ,"Saldo atual de %s: %.2f \n", vConta[cons]->cliente.nome, vConta[cons]->saldo);
                fprintf(arqRelatorio ,"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

                atualizarArqContas(lim);

                fclose(arqRelatorio);

                system("pause");

                break;

            case 3:
                system("cls");

                fclose(arqRelatorio);

                realizarSaque(cons, lim);

                break;

            case 9:
                system("cls");

                printf("Voltando ao menu principal! \n\n");

                fprintf(arqRelatorio ,"Fim da operacao!\n");
                fprintf(arqRelatorio ,"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

                fclose(arqRelatorio);

                return;

                break;

            default:
                system("cls");

                fclose(arqRelatorio);

                printf("Opcao invalida \n\n");

                system("pause");
        }

    } while(opc != 9);

}
void realizarDeposito(int cons, int lim)
{
    float valorDeposito;

    FILE *arqRelatorio = abrirArqEscrever("relatorio.txt");

    system("cls");

    printf("Digite o valor do deposito para %s:\n", vConta[cons]->cliente.nome);
    printf("(Lembrando que nao se faz deposito de moedas!)\n");
    valorDeposito = isNum();

    if(valorDeposito)
    {
        vConta[cons]->saldo = vConta[cons]->saldo + valorDeposito;

        printf("Deposito de %.2f real(is) na conta de %s foi realizado com sucesso!\n\n", valorDeposito, vConta[cons]->cliente.nome);

        fprintf(arqRelatorio ,"Deposito de %.2f real(is) na conta de %s foi realizado com sucesso!\n", valorDeposito, vConta[cons]->cliente.nome);
        fprintf(arqRelatorio ,"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

        system("pause");

        fclose(arqRelatorio);

        atualizarArqContas(lim);

        return;
    }

    printf("Deposito nao foi realizado! Motivo: valor nulo!\n\n");

    fclose(arqRelatorio);

    system("pause");

}
void realizarSaque(int cons, int lim)
{
    float valorSaque;

    FILE *arqRelatorio = abrirArqEscrever("relatorio.txt");

    system("cls");

    if(vConta[cons]->saldo > 0)
    {
        printf("Digite o valor do saque para %s:\n", vConta[cons]->cliente.nome);
        printf("(Lembrando que nao se faz saque de moedas!)\n");
        valorSaque = isNum();

        if(vConta[cons]->saldo >= valorSaque)
        {
            vConta[cons]->saldo = vConta[cons]->saldo - valorSaque;

            printf("Saque de %.2f real(is) na conta de %s foi realizado com sucesso!\n\n", valorSaque, vConta[cons]->cliente.nome);

            fprintf(arqRelatorio ,"Saque de %.2f real(is) na conta de %s foi realizado com sucesso!\n", valorSaque, vConta[cons]->cliente.nome);
            fprintf(arqRelatorio ,"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

            system("pause");

            fclose(arqRelatorio);

            atualizarArqContas(lim);

            return;
        }
    }

    printf("Saque nao foi realizado! Motivo: sem saldo!\n");

    fclose(arqRelatorio);

    system("pause");
}
void atualizarArqContas(int lim)
{
    int linhas = lim;
    int p;

    FILE *arqContas = fopen("contas.txt", "w");

    for(p = 0; p < linhas; p++)
    {
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
        if(p > 0)
        {
            fprintf(arqContas, "\n");
        }

        fprintf(arqContas, "%d", vConta[p]->numero_da_conta);
        fprintf(arqContas, " %d", vConta[p]->cliente.cpf);
        fprintf(arqContas, " %s", vConta[p]->cliente.nome);
        fprintf(arqContas, " %.2f", vConta[p]->saldo);

        printf("\n\nSaldo atual: %.2f\n\n", vConta[p]->saldo);

        system("pause");

        if(p == (linhas - 2))
        {
            fprintf(arqContas, "\n");

            p++;

            fprintf(arqContas, "%d", vConta[p]->numero_da_conta);
            fprintf(arqContas, " %d", vConta[p]->cliente.cpf);
            fprintf(arqContas, " %s", vConta[p]->cliente.nome);
            fprintf(arqContas, " %.2f", vConta[p]->saldo);

            fclose(arqContas);

            return;
        }
    }
}


int isNum()
{
    char digitado[13]; // Armazena o que foi digitado pelo usuário
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
