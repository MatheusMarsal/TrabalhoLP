//Definindo o tamanho maximo do vetor
#define T 100

//Criando um ponteiro para evitar consumo excessivo de memoria
typedef struct Carrinho *pCarrinho;

//Definir um vetor de 100 posicoes para armazenar um ponteiro
//para Carrinho
pCarrinho vCarrinho[T];

//Inicializar o vetor (desalocar os lixos de memoria)
void inicializar();

//Solicitar a leitura dos dados e armazenar
//na posicao p informada do vetor
void cadastrar(int p);

//Imprimir os dados de um aluno de ra informado
void imprimir(int codBarras);

//Imprimir todos os dados
void imprimirTodos();

//Verifica se o usuario digitou somente numeros
int isNum();


