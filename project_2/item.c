#include <string.h>
#include "item.h"

// if (less(getHashtagWord((*mais_popular)), getHashtagWord(h)))

void update_most_popular(Item h, Item* mais_popular)
{
	
	if (((*mais_popular) == NULL) || (getHashtagOco(h) > getHashtagOco((*mais_popular))))
		*mais_popular = h;
	else { 
		if (getHashtagOco(h) == getHashtagOco((*mais_popular))) //se as ocorrencias forem iguais entao comparo alfabeticamente
			if (less(getHashtagWord(h), getHashtagWord((*mais_popular)))) //Se h for menor alfabeticamente entao h sera o mais popular
				*mais_popular = h;
			
	}
}
void escreveItem(Item it)
{
	escreveHashtag(it);
}
void deleteItem(Item* a)
{
	free((*a)->palavra);
	free((*a));
	
}

void escreve_mais_popular(Item mais_popular)
{
	if (mais_popular != NULL)
		escreveItem(mais_popular);
}
