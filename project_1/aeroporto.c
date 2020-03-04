

/* Funcoes de manipulação da estrutura */

int getIdOrdemByCodigo (char id[])
{
	int i;
	for (i = 0; i < numeroAeroportos; i++)
	{
		if(!strcmp(getCodigoAeroporto(i),id))
			return i;
	}
	return -1;
	
	
}

void ordenarCods (char a[][MAX_LEN_ID_AEROPORTO])
{
	int i,j;
	char tmp[MAX_AEROPORTOS];
	for (i = 0; i < numeroAeroportos; i++)
		for(j=i+1; j < numeroAeroportos; j++) {
			if (strcmp(a[i], a[j])>0) {
				strcpy(tmp, a[i]);
				strcpy(a[i], a[j]);
				strcpy(a[j], tmp);				
			}
			
		}
}

void adicionaAeroporto(char id[], int capacidade)
{
	if (capacidade > 0)
	{
		setCodigoAeroporto(numeroAeroportos, id);
		setMaxCapacidade(numeroAeroportos, capacidade);
		setAberto(numeroAeroportos);
		setVoosInit(numeroAeroportos);
		numeroAeroportos++;
	}	
}

void alteraCapacidade(char arg[], int capacidade)
{
	int id_ordem = getIdOrdemByCodigo(arg);
	if ((id_ordem == -1) || (!estaAberto(id_ordem)))
	{
		printf("*Capacidade de %s inalterada\n", arg);
		
	}
	else {	
	
		int voos = getVoosAeroportoTotal(id_ordem);
		int capacidade_atual = getMaxCapacidade(id_ordem);
		
		int nova_capacidade = capacidade_atual + capacidade;
		
		if (nova_capacidade < voos)
			printf("*Capacidade de %s inalterada\n", arg);
		else
			setMaxCapacidade(id_ordem, nova_capacidade);
	}
}

void adicionarVooIdaVolta(int OUT_id_ordem, int IN_id_ordem)
{
	if ((!estaAberto(IN_id_ordem) || !estaAberto(OUT_id_ordem)) || (estaLotadoRT(IN_id_ordem) || (estaLotadoRT(OUT_id_ordem))))
		printf("*Impossivel adicionar voo RT %s %s\n", getCodigoAeroporto(OUT_id_ordem), getCodigoAeroporto(IN_id_ordem));
	else
		{
			incVoosRota(IN_id_ordem, OUT_id_ordem);
			incVoosRota(OUT_id_ordem, IN_id_ordem);
			incVoosIN(IN_id_ordem);
			incVoosOUT(IN_id_ordem);
			incVoosIN(OUT_id_ordem);
			incVoosOUT(OUT_id_ordem);

		}
}

void adicionaRota(int OUT_id_ordem, int IN_id_ordem)
{
	incVoosRota(OUT_id_ordem, IN_id_ordem);
	incVoosIN(IN_id_ordem);
	incVoosOUT(OUT_id_ordem);
		
}

void removeVoo(int OUT_id_ordem, int IN_id_ordem)
{
	if ((getVoosOUT(OUT_id_ordem)-1 >= 0) && (getVoosIN(IN_id_ordem)-1 >= 0) && (getVoosRota(OUT_id_ordem,IN_id_ordem)-1 >= 0))
	 {
		 decVoosIN(IN_id_ordem);
		 decVoosOUT(OUT_id_ordem);
		 decVoosRota(OUT_id_ordem, IN_id_ordem);
		 
	 }
	 else
		printf("*Impossivel remover voo %s %s\n", getCodigoAeroporto(OUT_id_ordem), getCodigoAeroporto(IN_id_ordem));
	
}

void removerVooIdaVolta(int id_origem, int id_destino)
{
	if ((getVoosOUT(id_origem)-1 >= 0) && (getVoosIN(id_destino)-1 >= 0) && (getVoosRota(id_origem,id_destino)-1 >= 0) && (getVoosRota(id_destino,id_origem)-1 >= 0))
		{
			decVoosRota(id_origem,id_destino);
			decVoosRota(id_destino,id_origem);
			decVoosIN(id_origem);
			decVoosOUT(id_origem);
			decVoosIN(id_destino);
			decVoosOUT(id_destino);
		}
	else
		printf("*Impossivel remover voo RT %s %s\n", getCodigoAeroporto(id_origem), getCodigoAeroporto(id_destino));
}

void numerodeVoos(int id_ordem1, int id_ordem2)
{
	if (id_ordem1 > numeroAeroportos)
		printf("*Aeroporto %s inexistente\n", getCodigoAeroporto(id_ordem1));
	else {
		if (id_ordem2 > numeroAeroportos)
			printf("*Aeroporto %s inexistente\n", getCodigoAeroporto(id_ordem2));
		else {
			/* Teste */
			int voos_incoming = getVoosRota(id_ordem2, id_ordem1);
			int voos_outcoming = getVoosRota(id_ordem1, id_ordem2);
			printf("Voos entre cidades %s:%s:%d:%d\n", getCodigoAeroporto(id_ordem1), getCodigoAeroporto(id_ordem2), voos_outcoming, voos_incoming);	

		}
		
	}
	
	
}

int getVoosIncoming(int id)
{
	int i = 0, nvoos = 0;
	for (i = 0; i < numeroAeroportos; i++)
		nvoos += getVoosRota(i, id);
		
	return nvoos;
	
}

int getVoosOutcoming(int id)
{
	int i = 0, nvoos = 0;
	for (i = 0; i < numeroAeroportos; i++)
		nvoos += getVoosRota(id, i);
		
	return nvoos;
	
}

int howManyVoosIncoming(int id)
{
	int i = 0, nvoos = 0;
	for (i = 0; i < numeroAeroportos; i++)
		{
			if (getVoosRota(i, id) != 0)
				nvoos++;			
		}
		
	return nvoos;
	
}

int howManyVoosOutcoming(int id)
{
	int i = 0, nvoos = 0;
	for (i = 0; i < numeroAeroportos; i++)
		{
			if (getVoosRota(id, i) != 0)
				nvoos++;			
		}
		
	return nvoos;
	
}


void AeroportoMaiorNvoos()
{
	int i, maior = 0, id_maior, tmp;
	for (i = 0; i < numeroAeroportos; i++)
	{
		if (!estaAberto(i)) continue;
		tmp = getVoosAeroportoTotal(i);
		if (tmp > maior)
		{
			maior = tmp;
			id_maior = i;
			
		}
		
		
	}	
	printf("Aeroporto com mais rotas %s:%d:%d\n", getCodigoAeroporto(id_maior), getVoosOutcoming(id_maior), getVoosIncoming(id_maior));
	
}

void AeroportoMaisConectado()
{
	int i,j, maior = 0, id_maior, tmp = 0;
	for (i = 0; i < numeroAeroportos; i++, tmp=0)
	{
		if (!estaAberto(i)) continue;
		for (j = 0; j < numeroAeroportos; j++)
			if (getVoosRota(i,j) != 0 || getVoosRota(j,i) != 0)
				tmp++;
		if (tmp > maior)
		{
			maior = tmp;
			id_maior = i;
			
		}
	}
	printf("Aeroporto com mais ligacoes %s:%d\n", getCodigoAeroporto(id_maior), maior);
}

void vooMaisPopular()
{
	int i,j, maior = 0, id_maior_origem, id_maior_dest;
	
	for (i = 0; i < numeroAeroportos; i++)
	{
		for (j = 0; j < numeroAeroportos; j++)
			{
				if (getVoosRota(i,j) > maior)
					{
						maior = getVoosRota(i,j);
						id_maior_origem = i;
						id_maior_dest = j;
						
					}
				
			}
		
	}
	
	
	
	printf("Voo mais popular %s:%s:%d\n", getCodigoAeroporto(id_maior_origem), getCodigoAeroporto(id_maior_dest),maior);
	
	
	
}

int AeroportosComXVoos(int x)
{
	int i, naeroportos = 0;
	for (i = 0; i < numeroAeroportos; i++)
	{
		if (getVoosAeroportoTotal(i) == x)
			naeroportos++;
		
	}
	return naeroportos;
	
	
}

void listar(int opcao)
{
	int i;
	int indice, n;
	char id_ordenado [MAX_AEROPORTOS][MAX_LEN_ID_AEROPORTO];
	
	switch (opcao)
	{
		case 0:  
		for (i = 0; i < numeroAeroportos; i++)
			printf("%s:%d:%d:%d\n", getCodigoAeroporto(i), getMaxCapacidade(i), getVoosOutcoming(i), getVoosIncoming(i));
		
		break;
		case 1:
		
		for (i = 0; i < numeroAeroportos; i++)
			strcpy(id_ordenado[i], getCodigoAeroporto(i));
			
		ordenarCods(id_ordenado);
		for (i = 0; i < numeroAeroportos; i++)
			{
				int id = getIdOrdemByCodigo(id_ordenado[i]);
				printf("%s:%d:%d:%d\n", getCodigoAeroporto(id), getMaxCapacidade(id), getVoosOutcoming(id), getVoosIncoming(id));
			}
		break;
		
		case 2:
		
		
		for (indice = 0, i = 0; i < numeroAeroportos; indice++)
		{
			n = AeroportosComXVoos(indice);
			if (n != 0)
				printf("%d:%d\n", indice, n);
			i += n;
		}
		
		
		break;
		
		
	}
	
}

void limpaVoos(int id_ordem)
{
	int i;
	for (i = 0; i < numeroAeroportos; i++)
	{
		setVoosRota(id_ordem,i,0);
		setVoosRota(i,id_ordem,0);
		
	}
}

void encerraAeroporto(int id_ordem)
{
		setEncerrado(id_ordem);
		limpaVoos(id_ordem);
		setVoosInit(id_ordem); /* Ao ser encerrado o numero de voos fica a zero. */
		
		/* É necessário atualizar as variaveis que contem o numero de voos de partida e chegada. */
		int i;
		for (i = 0; i < numeroAeroportos; i++)
		{
			setVoosIN(i, getVoosIncoming(i));
			setVoosOUT(i, getVoosOutcoming(i));			
		}
	
}

void reabreAeroporto(int id_ordem)
{
		setAberto(id_ordem);
		/* Coloca os voos de partida e destino do aerporto a zero. */
		limpaVoos(id_ordem);

}

int numeroTotalVoos()
{
	int i, j, soma = 0;
	for (i = 0; i < numeroAeroportos; i++)
	{
		for (j = 0; j < numeroAeroportos; j++)
			soma += getVoosRota(i,j);				
	}
	return soma;
}
