#include <stdio.h>

typedef struct task_t{
	/*funçao a ser executada em forma de processo*/
	void* (*func)(void*);                            //WHATFUCK?????? VE EXEMPLO ABAIXO
	/*id do processo criado*/
	int id;
	/*prioridade do processo que vai ser criado*/
	int p;
	/*quantum calculado pela política de escalonamento atual*/
	int quantum;
}task;

/*Nao sei o que porra ele quer com esse typedef acima. Vou tentar chegar proximo
do que ele pediu. */

/*-------------------------------------------------------------------*/

struct processRR{
  int name;
  int burst;
  int waitingTime;
  int burstTotal;
  int tipoEscalonamento; // Poderia ser  int set_scheduler_type(scheduler_type scheduler) que ele pede..

}processoRR[20];

void roundrobi();

void executaProcessoRR(int, int);
void contaWaitingTimeRR(int, int);



/*-------------------------------------------------------------------*/

//void* (*func)(void*); Pra essa linha, pensei em algo assim.

void createProcess(process *p1){
  int pid, status;

  if((pid = fork()) == 0) {
    status = execv(p1->file_name, p1->params) //Procura pelo o que a funcao "execv" faz.
    // Exemplo: ./fatorial 50
    if (status == -1) {
        printf("O programa %s nao existe.\n", p1->file_name);
    }
    exit(1);
  }
  //pid->pid = pid;
  (*pid).pid = pid;
  //time(&p1->inicio_execucao);
  //kill(pid, SIGTSTIP);
}

typedef enum {
	NORMAL,
	FIFO,
	RR
}scheduler_type;

/*
  @brief Fuçao que inicializa uma tarefa (processo) específica.
  @param task_ a tarefa a ser executada. ----- ABAIXO
  Na linha '21' pensei em algo parecido. Nos passamos
  a tarefa que sera executada. Pensei num programa qualquer. Que a gente chama ele por meio daquela estrutura.
  @return 0 em caso de sucesso, -1 em caso de falha.
 */
int start_task (task *task_);

/*
  @brief Fuçao que recupera a estrutura dentro do escalonador.
  @param id identificador da task desejada
  @return uma referencia para a estrutura task em caso de sucesso, NULL em caso de falha.
 */
task* get_task (int id);

/*
  @brief Muda o tipo de escalonador usado para um dos tipos específicos (NORMAL, FIFO e RR). QUAL EH O NORMAL?
  @param sheduler tipo do escalonador desejado.
  @return 0 em caso de sucesso, -1 em caso de falha.
 */
int set_scheduler_type(scheduler_type scheduler)



//SABER QUAL O ALGORITMO "NORMAL" QUE ELE PEDE!!!

//Padrao de algoritmos encontrados
//FCFS First Come, First Served. - Acredito que seja o FIFO

void fcfs(){
  int n, bt[20], wt[20], tat[20], avwt=0, avtat=0, i, j;
  printf("Entre com o Numero de Processos (max20): \n", ); //Entra com o numero de processos
  scanf("%d\n", &n);
  printf("\nEntre com o Burst Time do Processo\n");

  for(i=0; i<n; i++){ //Preenchimento de burst dos processos
    printf("P[%d]:",i+1);
    scanf("%d",&bt[i]); //Burst eh gravado em bt[]
  }

  wt[0]=0; // O tmepo de espera para o primeiro processo eh 0 #WaitingTime

  for(i=1; i<n; i++){
    wt[i]=0;
    for(j=0; j<i; j++){
      wt[i] += bt[j]; //Somatorio do tempo de WaitingTime
    }
  }

  printf("\nProcess\t \tBurst Time \tTurnaround Time"); //Cabecalho
  for(i=0;i<n;i++){
    tat[i]=bt[i]+wt[i]; //TurnAroundTime = BurstTIme + WaitingTime
    avwt+=wt[i]; //AverageWaitingTime = AverageWaitingTime + WaitingTime
    avtat+=tat[i]; //AverageTurnAroundTime = AverageTurnAroundTime + TurnAroundTime
    printf("\nP[%d]\t\t%d\t\t%d\t\t%d", i+1, bt[i], wt[i],tat[i]); //Apresentacao da linha de dados dentro da table
  }

  avwt=/i; //AverageWaitingTime = AverageWaitingTime / numero de processos
  avtat=/i //AverageTurnAroundTime = AverageTurnAroundTime / numerodeprocessos
  printf("\n\nAverage Waiting Time: %d", avwt);
  printf("\nAverage Turnaround Time: %d", avtat);

}

//Esse sera o padrao de algoritmo do RR que voce encontrara
void roundrobin(){

  int n, quantum, tat[20], avwt=0, avtat=0, i, j;
  printf("\nEntre com o numero de processos (max20): \n");
  scanf("%d\n", &n);
  printf("\nQual o quantum de tempo da CPU: \n", );
  scanf("%d\n", &quantum );

  for(i=0; i<n; i++){   //Preenchendo o burst dos processos
    printf("\nQual o Burst Time do processo \n", );
    printf("P[%d]:\n", i+1 );
    processoRR[i].name = i+1;
    scanf("%d\n", &processoRR[i].burst ); //burst sendo gravado na struct do processo
    processoRR[i].waitingTime = 0; // O waitingTime de cada processo eh setado para 0
    processoRR[i].burtTotal = processoRR[i].burst;
  }

  for(i=0; i<n; i++){
    if(processoRR[i].burst > 0){
      executaProcessoRR(quantum,n);
      i = 0;
    }

  }

  for(i=0; i<n; i++){ // Para sempre que existir processo, ele execute
    if (processoRR[i].burst > 0) {
      executaProcessoRR(quantum,n);
      i = 0;
    }

  }


  printf("\nProcess \t\tBurst time\tWaiting Time \tTurnaround Time", );

  for (i=0; i<n; i++){
    tat[i]=processoRR[i].burstTotal+processoRR[i].waitingTime; // TurnAroundTIme = BurstTIme + WaitingTime
    avwt+=processoRR[i].waitingTime;  //AverageWaitingTime = AverageWaitingTime + WaitingTime
    avtat+=tat[i];

    printf("\nP[%d]\t\t%d\t\t%d\t\t%d", processoRR[i].name, processoRR[i].burstTotal, processoRR[i].waitingTime, tat[i]);

  }

  avwt /=i;
  avtat/=i;
  printf("\n\nAverage Waiting Time: %d", avwt);
  printf("\nAverage Turnaround Time: %d\n\n", avtat);

}

void executaProcessoRR(int quantum, int n){
  int i,j;
  for (i=0; i < n; i++) {
    if(processoRR[i].burst > 0){
      for(j=0; j!=quantum; j++){ //processo sendo executado no tempo do quantum
        if(processoRR[i].burst != 0){
          processoRR[i].burst -= 1;
          contaWaitingTimeRR(i,n);
        }else{
          break;
        }

      }//Close second for
    } //Close if
  }//Close first for


}

void contaWaitingTimeRR(int atual, int n){
  int i, j;
  for(i=0; i<n; i++){//Percorre a lista de processos
    if(i != atual){
      if(processoRR[i].burst > 0){
        processoRR[i].waitingTime += 1; //Conta o tempo de espera do processo
      }
    }
  }
}
