#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <math.h>

// Código adaptado de https://github.com/gpsilva2003/MPI/blob/main/src/mpi_primos.c

int primo (long int n) { /* mpi_primos.c  */
	int i;
       
	for (i = 3; i < (int)(sqrt(n) + 1); i+=2) {
			if(n%i == 0) return 0;
	}
	return 1;
}

int main(int argc, char *argv[]) {
	double t_inicial, t_final;
	int cont = 0, total = 0;
	long int i, n;
	int meu_ranque, num_procs, inicio, salto;

	if (argc < 2) {
        	printf("Valor inválido! Entre com um valor do maior inteiro\n");
       	 	return 0;
    	} else {
        	n = strtol(argv[1], (char **) NULL, 10);
       	}

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);	
    t_inicial = MPI_Wtime();
    inicio = 3 + meu_ranque*2;
    salto = num_procs*2;
	for (i = inicio; i <= n; i += salto) 
	{	
		if(primo(i) == 1) cont++;
	}
		
	if(meu_ranque == 0) {
		int* resultados = malloc((num_procs - 1) * sizeof(int));    //cria um vetor para guardar os resultados dos outros processos
		MPI_Request* reqs = malloc((num_procs - 1) * sizeof(MPI_Request));	//cria um vetor para aguardar os resultados das comunicações via irecv

		// Dispara um recieve pra cada processo, exceto o primeiro
		for (i = 1; i < num_procs; i++) {
			MPI_Irecv(&resultados[i - 1], 1, MPI_INT, i, 1, MPI_COMM_WORLD, &reqs[i - 1]);
		}

		// Espera receber todos os resultados dos processos
		MPI_Waitall(num_procs - 1, reqs, MPI_STATUSES_IGNORE);

		//Agrega os resultados
		for (i = 0; i < num_procs - 1; i++) {
			cont += resultados[i];
		}
		total = cont;

		free(resultados);
		free(reqs);
	} else {
		MPI_Request req;
		MPI_Isend(&cont, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &req);
        MPI_Wait(&req, MPI_STATUS_IGNORE);
	}
	
	t_final = MPI_Wtime();

	if (meu_ranque == 0) {
        if (n >= 2) {
            total += 1;    /* Acrescenta o dois, que também é primo */
        }
		printf("Quant. de primos entre 1 e n: %d \n", total);
		printf("Tempo de execucao: %1.3f \n", t_final - t_inicial);	 
		printf("%1.5f\n", t_final - t_inicial); // para cálculo de média
	}
	MPI_Finalize();
	return(0);
}