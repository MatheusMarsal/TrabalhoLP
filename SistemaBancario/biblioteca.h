//Definindo o tamanho maximo do vetor
#define T 100

//Criando um ponteiro para evitar consumo excessivo de memoria
typedef struct Conta *pConta;

//Definir um vetor de 100 posicoes para armazenar um ponteiro
//para Conta
pConta vConta[T];

//Inicializar o vetor (desalocar os lixos de memoria) e alimentar vContas com as contas do arquivo texto
int inicializar();

//Solicitar a leitura dos dados e armazenar
//na posicao p informada do vetor
void cadastrar(int p);

//Imprimir os dados da conta pelo CPF informado
int consultar(int cpf, int lim);

//Imprimir todos as contas cadastrados
void imprimirTodos(int lim);

//Abre o arquivo pelo caminho especificado
FILE *abrirArqEscrever(char * caminho);
FILE *abrirArqLeitura(char *caminho);


void abrirOperacoes(int lim);

//Verifica se o usuario digitou somente numeros
int isNum();
