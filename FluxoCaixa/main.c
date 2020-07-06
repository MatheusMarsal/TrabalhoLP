#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"

int main()
{
    printf("\nLOADING...\n\n");

    int p = inicializar();
    int opc = 0;
    int cons = 0;
    int codigoBarras;


    printf("LOADING COMPLETO!\n");

    do
    {
        system("cls");

        printf("\nFluxo de caixa\n\n");

        printf("1.: Cadastrar \n");
        printf("2.: Consultar preco do produto\n");
        printf("3.: Exibir todos \n");
        printf("4.: Quantidade de Cadastrados \n");
        printf("5.: Abrir operacao de venda \n");
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

                printf("Digite o codigo de barras: \n");
                codigoBarras = isNum();
                printf("\n");

                cons = consultar(codigoBarras, p);

                break;

            case 3:
                system("cls");

                imprimirTodos(p);

                break;

            case 4:
                system("cls");

                printf("Quantidade de produtos cadastrados: %d \n", p);

                system("pause");
                break;

            case 5:
                system("cls");

                abrirVenda(p);

                system("pause");
                break;

            case 9:
                system("cls");

                printf("Finalizou o fluxo de caixa! \n");

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

