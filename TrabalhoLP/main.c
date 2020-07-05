#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"

int main()
{
    /*printf("\nLOADING...\n\n");

        int p = 0;
        int opc;

        inicializar();

    /*printf("LOADING COMPLETO!\n");

    printf("\nPressione qualquer tecla para continuar!\n");
    getch();

    printf("\n\n\t\t-= MENU PRINCIPAL =-\n\n");
    do
    {
        printf("Digite 1 para comecar a compra! \n");
        printf("Digite 2 para adicionar um novo produto! \n");
        printf("Digite 3 para editar um produto existente! \n");
        printf("Digite 4 para excluir um produto existente! \n");
        printf("Digite 5 para sair do programa! \n");

        opc = isNum();

        switch ( opc )
        {
            case 1:
                system("cls");

                //carrinho(p);
                p++;

                break;

            case 2:
                system("cls");

                //Adc novo produto

                break;

            case 3:
                system("cls");

                //editar

                break;

            case 4:
                system("cls");

                //excluir

                break;

            case 5:
                system("cls");

                return 0;

                break;

            default :
                system("cls");
                printf("\n\nEscolha uma das opcoes abaixo!\n\n");
        }

    } while(opc < 1 || opc > 5); */

    printf("\nLOADING...\n\n");

    int p = 0;
    int codigoBarras = 0;
    int opc = 0;
    inicializar();

    printf("LOADING COMPLETO!\n");

    do
    {
        system("cls");

        printf("\nFluxo de caixa\n\n");

        printf("1.: Cadastrar \n");
        printf("2.: Consultar produto \n");
        printf("3.: Exibir todos \n");
        printf("4.: Quantidade de Cadastrados \n");
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
                scanf("%d", &codigoBarras);

                imprimir(codigoBarras);

                break;

            case 3:
                system("cls");

                imprimirTodos();

                break;

            case 4:
                system("cls");

                printf("Quantidade de cadastrados: %d \n", p);

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
