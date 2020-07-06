//Definindo o tamanho maximo do vetor
#define T 100

//Criando um ponteiro para evitar consumo excessivo de memoria
typedef struct Carrinho *pCarrinho;
typedef struct Produto *pProduto;

//Definir um vetor de 100 posicoes para armazenar um ponteiro
//para Carrinho
pCarrinho vCarrinho[T];

//Inicializar o vetor (desalocar os lixos de memoria)
int inicializar();

//Solicitar a leitura dos dados e armazenar
//na posicao p informada do vetor
void cadastrar(int p);

//Imprimir os dados de um aluno de ra informado
int consultar(int codBarras, int lim);

//Imprimir todos os dados
void imprimirTodos(int lim);

//Abre o arquivo pelo caminho especificado
FILE *abrirArqEscrever(char * caminho);
FILE *abrirArqLeitura(char *caminho);

void abrirVenda(int lim);

//Verifica se o usuario digitou somente numeros
int isNum();


