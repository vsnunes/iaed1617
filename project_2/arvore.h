#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef ARVORE_H
#define ARVORE_H
#include "item.h"

typedef struct STnode* link;
struct STnode {Item item; link l, r;};

#define NULLitem NULL
#define NUMSEP 11
static const char separators[] = {' ','\t',',',';','.','?','!','"','\n',':','\0'};
#define allowed_char(c) (!strchr(separators, c))

//Variavel necessaria para a ordenacao
Item *items;


link NEW(Item item, link l, link r);
void STinit(link* head);
link insertR(link h, Item item);
void STinsert(link* head, Key d, Item* mais_popular);
Item searchR(link h, Key v);
Item STsearch_byKey(link head, Key v);
link max(link h);
int count(link h);
int sum(link h);
int height (link h);
void visit(Item it);
void traverse(link h, void (*visit)(Item));
int STcount(link head);
link deleteR(link h, Key k);
//void STdelete_desc(link*head, Description k);
void sortR(link h, void (*visit)(Item));
void STsort(link head, void (*visit)(Item));
link freeR(link h);
void STfree(link*head);
void mostra_totais(link tree);
int tree_to_array(link tree, Item it[], int i);
void radixsort(Item vetor[], int tamanho, Item maior);
int compara(const void *p, const void *q);
void mostra_ordenado(link tree, Item maior);
void adicionaHashtags(link *tree, char *line, Item* mais_popular);


#endif /* ARVORE_H */
