#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include <string.h>

int leLinha(char s[], int n)
{
	int c, i = 0;
	
	while((c=getchar()) != '\n' && c != EOF)
		s[i++] = c;
	
	s[i++] = '\n';
	s[i] = '\0';
	return i;
}

int main(int argc, char *argv[])
{
	char comando;
	char mensagem[MSG_BUFFER];
	
	link hashtag_tree = NULL;
	STinit(&hashtag_tree);
	Item mais_popular = NULL; //variavel que guardara o item mais frequente. Evitando procuras desnecessarias.
	
	
	
	do {
		comando = getchar();
		leLinha(mensagem, MSG_BUFFER);
		
		
		switch (comando)
		{
				case 'a': adicionaHashtags(&hashtag_tree, mensagem, &mais_popular); break;
				case 's': mostra_totais(hashtag_tree); break;
				case 'm': escreve_mais_popular(mais_popular); break;
				case 'l': mostra_ordenado(hashtag_tree, mais_popular); break;
				
				
		
		}
	}
	while(comando != 'x');
	
	STfree(&hashtag_tree);

	
	return 0;
}
