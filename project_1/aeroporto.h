#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Definicoes gerais */
#define MAX_LEN_COMANDO 100  /* Comprimento maximo do comando de input*/


#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#define MIN(x,y) (((x) < (y)) ? (x) : (y))



/* Comprimento maximo do ID do aeroporto*/
#define MAX_LEN_ID_AEROPORTO 4

/*
 * Tipo AEROPORTO
 * O parametro id_voo permite destacar a ordem pelo qual foram inseridos
 * no sistema
 * */
 
#ifndef AEROPORTO
typedef struct aeroporto_t {
	char codigo_id[MAX_LEN_ID_AEROPORTO];
	int max_capacidade;
	int estado;
	int id_ordem;
	int voos_in;
	int voos_out;
} AEROPORTO;
#endif


#define MAX_AEROPORTOS 1000

AEROPORTO aeroportos[MAX_AEROPORTOS];
int voos[MAX_AEROPORTOS][MAX_AEROPORTOS] = {{0}};
int numeroAeroportos = 0; /* Numero total de aeroportos */

#define ABERTO 1
#define ENCERRADO 0

/*
 * getVoosAeroporto -> devolve o numero de voos descontando os RT (ida e volta)
 * getVoosAeroportoTotal -> devolve o numero de voos total inclusive os RT
 * */
/*#define getVoosAeroporto(id_ordem) ((int)aeroportos[id_ordem].voos/2)*/
#define getVoosIN(id_ordem) (aeroportos[id_ordem].voos_in)
#define getVoosOUT(id_ordem) (aeroportos[id_ordem].voos_out)
#define setVoosIN(id_ordem, val) (aeroportos[id_ordem].voos_in = val)
#define setVoosOUT(id_ordem, val) (aeroportos[id_ordem].voos_out = val)

#define getVoosAeroportoTotal(id_ordem) (aeroportos[id_ordem].voos_in + aeroportos[id_ordem].voos_out)
#define estaAberto(id_ordem) (aeroportos[id_ordem].estado)
#define estaLotado(id_ordem) (getVoosAeroportoTotal(id_ordem)+1 > aeroportos[id_ordem].max_capacidade)
#define estaLotadoRT(id_ordem) (getVoosAeroportoTotal(id_ordem)+2 > aeroportos[id_ordem].max_capacidade)

#define ePossivelRemover(id_ordem) ((getVoosIN(id_ordem)-1 < 0) || (getVoosOUT(id_ordem)-1 < 0))
#define ePossivelRemoverIN(id_ordem) (getVoosIN(id_ordem)-1 < 0)
#define ePossivelRemoverOUT(id_ordem) (getVoosOUT(id_ordem)-1 < 0)

#define ePossivelRemoverRT(id_ordem) ((getVoosIN(id_ordem)-1 < 0) && (getVoosOUT(id_ordem)-1 < 0))

#define getCodigoAeroporto(id_ordem) (aeroportos[id_ordem].codigo_id)
#define setCodigoAeroporto(id_ordem, codigo) (strcpy(aeroportos[id_ordem].codigo_id, codigo))

#define getMaxCapacidade(id_ordem) (aeroportos[id_ordem].max_capacidade)
#define setMaxCapacidade(id_ordem, capacidade) (aeroportos[id_ordem].max_capacidade = capacidade)

#define setAberto(id_ordem) (aeroportos[id_ordem].estado = ABERTO)
#define setEncerrado(id_ordem) (aeroportos[id_ordem].estado = ENCERRADO)

#define setVoosInit(id_ordem) (aeroportos[id_ordem].voos_in = 0, aeroportos[id_ordem].voos_out = 0)
#define incVoosIN(id_ordem) (aeroportos[id_ordem].voos_in++)
#define decVoosIN(id_ordem) (aeroportos[id_ordem].voos_in--)
#define incVoosOUT(id_ordem) (aeroportos[id_ordem].voos_out++)
#define decVoosOUT(id_ordem) (aeroportos[id_ordem].voos_out--)

/* Tipo Voo */
#define incVoosRota(voo1, voo2) (voos[voo1][voo2]++)
#define decVoosRota(voo1, voo2) (voos[voo1][voo2]--)
#define getVoosRota(voo1, voo2) (voos[voo1][voo2])
#define getSomaVoosRota(voo1, voo2) (voos[voo1][voo2] + voos[voo2][voo1])
#define setVoosRota(voo1, voo2, val) (voos[voo1][voo2] = val)

#include "aeroporto.c"



