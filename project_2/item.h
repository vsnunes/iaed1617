#ifndef ITEM_H
#define ITEM_H
#include "hashtag.h"
typedef Hashtag Item;

//A chave pela qual as procuras serao feitas sera pela palavra
typedef char* Key;

#define key(it) (it->palavra)
#define less(a,b) (strcmp(a,b)<0)
#define greater(a,b) (strcmp(a,b)>0)
#define eq(a,b) (!strcmp(a,b))

#define comparaItemKey(hashtag, k) comparaHashtags_palavra(hashtag, k)
#define NEWItem(h,oc) cria_nova_hashtag(h,oc)

#define funcCasoExista(h) incOcorrencias(h)


void escreveItem(Item it);
void deleteItem(Item* a);
void update_most_popular(Item h, Item* mais_popular);
void escreve_mais_popular(Item mais_popular);

#endif /* ITEM_H */
