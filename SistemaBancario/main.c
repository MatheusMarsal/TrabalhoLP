#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"

int main()
{
    printf("\nLOADING...\n\n");

    int p = inicializar();
    int opc = 0;
    int cons = 0;
    int cpf;


    printf("LOADING COMPLETO!\n");

    do
    {
        system("cls");

        printf("\n-= Banco LP S/A =-\n\n");

        printf("1.: Cadastrar \n");
        printf("2.: Consultar uma conta\n");
        printf("3.: Exibir todas \n");
        printf("4.: Quantidade de conta cadastrados \n");
        //printf("5.: Abrir operacao na conta\n");
        printf("9.: Sair \n\n");

        printf("Digite a operacao que deseja realizar: \n");
        opc = isNum();

        printf("\n");

        switch(opc)
        {
            case 1:
                cadastrar(p);
                //deslocar a posicao
                p++;
                break;

            case 2:
                system("cls");

                fflush(stdin);

                printf("Digite o CPF: \n");
                cpf = isNum();
                printf("\n");

                cons = consultar(cpf, p);

                break;

            case 3:
                system("cls");

                imprimirTodos(p);

                break;

            case 4:
                system("cls");

                printf("Quantidade de contas cadastrados: %d \n", p);

                system("pause");
                break;

            //case 5:
                //system("cls");

                //abrirOperacoes(p);

                //system("pause");
                //break;

            case 9:
                system("cls");

                printf("Logout com sucesso! \n");

                return 0;

                break;

            default:
                system("cls");

                printf("Opcao invalida \n");

                system("pause");
        }

    } while(opc != 9);

    return 0;
}

