
/*Vimos que o escalonador padrão do linux permite o controle do
comportamento de processos em diversos níveis. O escalonador permite,
dentre outras atividades a mudança das políticas de escalonamento,
mudanças das prioridades dos processos além da mudança de parâmetros específicos
de cada tipo de política de escalonamento escolhida.

No entanto, vimos que não é possível controlar, sem permissão de super usuário,
muitos desses parâmetros. O que, para muitas aplicações, pode ser necessário.
Para esse trabalho, iremos implementar um escalonador que executa no nível de usuário comum.
Assim como no Linux, o nosso escalonador irá controlar a execução de processos
rodando sobre o sistema operacional linux.

Por estarmos executando dentro do próprio sistema operacional, ainda somos sucetíveis às mesmas regras
do escalonador padrão, porém, qualquer processo iniciado sob o comando do nosso escalonador será, também,
controlado por ele.
*/

//TENTAR ENTENDER O QUE O PROFESSOR QUER
//PRIMEIRO PONTO: "iremos implementar um escalonador que executa no nível de usuário comum"


//A implementaçao deve connter as seguintes funções:

typedef struct task_t{
	/*funçao a ser executada em forma de processo*/
	void* (*func)(void*);
	/*id do processo criado*/
	int id;
	/*prioridade do processo que vai ser criado*/
	int p;
	/*quantum calculado pela política de escalonamento atual*/
	int quantum;
}task;

typedef enum {
	NORMAL,
	FIFO,
	RR
}scheduler_type;

/*
 * @brief Fuçao que inicializa uma tarefa (processo) específica.
 * @param task_ a tarefa a ser executada.
 * @return 0 em caso de sucesso, -1 em caso de falha.
 */
int start_task (task *task_);

/*
 * @brief Fuçao que recupera a estrutura dentro do escalonador.
 * @param id identificador da task desejada
 * @return uma referencia para a estrutura task em caso de sucesso, NULL em caso de falha.
 */
task* get_task (int id);


/*
 * @brief Muda o tipo de escalonador usado para um dos tipos específicos (NORMAL, FIFO e RR).
 * @param sheduler tipo do escalonador desejado.
 * @return 0 em caso de sucesso, -1 em caso de falha.
 */
int set_scheduler_type(scheduler_type scheduler)

/*
Usando essas estruturas implemente as funções do escalonador e programas de teste
que permitam testar os três tipos de escalonamento listados bem como ilustrar o funcionamento do escalonador
para programas de exemplo. */
