#include "aeroporto.h"

void ajustarCod(char s[])
{
	strncpy(s, s, 3);
	s[3] = '\0';
	
}

int main()
{
	
	char comando[MAX_LEN_COMANDO], arg1[MAX_LEN_COMANDO], arg2[MAX_LEN_COMANDO];
	char opcao;
	int id_arg1, id_arg2;
	
	do
	{
		fgets(comando, sizeof(comando), stdin);
		sscanf(comando, "%c %s %s", &opcao, arg1, arg2);
		
				
	
		switch (opcao)
		{
			case 'A':	ajustarCod(arg1);
						adicionaAeroporto(arg1, atoi(arg2)); break;
			
			case 'I':	ajustarCod(arg1);
						alteraCapacidade(arg1, atoi(arg2)); break;
			
			case 'F':	ajustarCod(arg1); ajustarCod(arg2);
						adicionarVooIdaVolta(getIdOrdemByCodigo(arg1), getIdOrdemByCodigo(arg2)); break;
			
			case 'G':	ajustarCod(arg1); ajustarCod(arg2);
						id_arg1 = getIdOrdemByCodigo(arg1);
						id_arg2 = getIdOrdemByCodigo(arg2);
				
						if (((id_arg1 == -1) || (id_arg2 == -1)) || ((!estaAberto(id_arg1) || !estaAberto(id_arg2)) || (estaLotado(id_arg1) || (estaLotado(id_arg2)))))
							printf("*Impossivel adicionar voo %s %s\n", arg1, arg2);
						else adicionaRota(getIdOrdemByCodigo(arg1), getIdOrdemByCodigo(arg2));
				
						break;
						
			case 'R':	ajustarCod(arg1); ajustarCod(arg2);
						removeVoo(getIdOrdemByCodigo(arg1), getIdOrdemByCodigo(arg2));		break;
			
			case 'S':	ajustarCod(arg1); ajustarCod(arg2);
						removerVooIdaVolta(getIdOrdemByCodigo(arg1), getIdOrdemByCodigo(arg2)); break;
			
			case 'N':	ajustarCod(arg1); ajustarCod(arg2);
						numerodeVoos(getIdOrdemByCodigo(arg1), getIdOrdemByCodigo(arg2)); break;
			
			case 'P':	AeroportoMaiorNvoos();	break;
			
			case 'Q':	AeroportoMaisConectado(); break;
			
			case 'V':	vooMaisPopular();	break;
			
			case 'C':	ajustarCod(arg1);
						id_arg1 = getIdOrdemByCodigo(arg1);
						if (id_arg1 == -1)
							printf("*Aeroporto %s inexistente\n", arg1);
						else encerraAeroporto(getIdOrdemByCodigo(arg1)); break;
			
			case 'O':	ajustarCod(arg1);
						id_arg1 = getIdOrdemByCodigo(arg1);
						if (id_arg1 == -1)
							printf("*Aeroporto %s inexistente\n", arg1);
						else reabreAeroporto(getIdOrdemByCodigo(arg1)); break;
			
			case 'L':	listar(atoi(arg1));	break;
			
			case 'X':	printf("%d:%d\n", numeroTotalVoos(), numeroAeroportos);	break;
			case 'a': 
			
			id_arg1 = getIdOrdemByCodigo(arg1);
				printf("Codigo: %s \n", arg1);
				printf("Max Capacidade: %d \n", getMaxCapacidade(id_arg1));
				printf("Estado: %d \n", estaAberto(id_arg1));
				printf("Id_ordem: %d \n", id_arg1);
				printf("Voos out: %d >0 %d\n", getVoosOUT(id_arg1), getVoosOUT(id_arg1)-1>0);
				printf("Voos in: %d >0 %d\n", getVoosIN(id_arg1), getVoosIN(id_arg1)-1>0);
				printf("Voos Total: %d \n", getVoosAeroportoTotal(id_arg1));
				printf("how m Voos IN: %d \n", howManyVoosIncoming(id_arg1));
				printf("how m Voos OUT: %d \n", howManyVoosOutcoming(id_arg1));
			 break;
			
			case 'b':
			for(id_arg1 = 0; id_arg1 < numeroAeroportos; id_arg1++)
				for(id_arg2 = 0; id_arg2 < numeroAeroportos; id_arg2++)
					printf("[%d][%d] = %d\n", id_arg1, id_arg2, getVoosRota(id_arg1,id_arg2));
			
			
			break;
			
		}	
		
		
		
	}
	while (opcao != 'X');




	return 0;
}
