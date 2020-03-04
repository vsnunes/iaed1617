#include <stdio.h>
#include <ctype.h>
#include "hashtag.h"
#include <string.h>



Hashtag cria_nova_hashtag(char *palavra, int ocorrencias)
{
	Hashtag nova;
	nova = (Hashtag)malloc(sizeof(struct hashtag_t));
	nova->ocorrencias = ocorrencias;
	nova->palavra = strdup(++palavra); //introduz apenas a palavra sem o #
	return nova;
}

int comparaHashtags_palavra(Hashtag h, char *word)
{
	char *only_word = ++word; //remove o primeiro caracter (#)
	return !strcmp(h->palavra, only_word);
	
}

void escreveHashtag(Hashtag h)
{
	if (h != NULL)
		printf("#%s %d\n", h->palavra, h->ocorrencias);
}

void libertaHashtag (Hashtag h)
{
	free(h->palavra);
	free(h);
	
}

