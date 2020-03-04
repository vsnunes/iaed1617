#include "arvore.h"

link NEW(Item item, link l, link r)
{
	link x = (link)malloc(sizeof(struct STnode));
	x->item = item;
	x->l = l;
	x->r = r;
	return x;	
}

void STinit(link* head)
{
	*head = NULL;	
}

link insertR(link h, Item item)
{
	if (h == NULL)
		return NEW(item, NULL, NULL);
	if(greater(key(item), key(h->item)))
		h->l = insertR(h->l, item);
	else
		h->r = insertR(h->r, item);
	return h;
	
}



void STinsert(link* head, Key d, Item* mais_popular)
{
	
	Item t = STsearch_byKey(*head, d);
	if (t == NULL) //se nao existe adiciona-se
		{
			Item novo = NEWItem(d,1);
			//Atualiza o elemento mais popular
			update_most_popular(novo, mais_popular);
			*head = insertR(*head, novo);
			
			
		}
	else { //Caso o elemento exista e dado controlo ao procedimento funcCasoExista
		 //Que trata o elemento de forma diferente se este ja existir na arvore
		 //Esta funcao pode ser redefinida em item.h
		funcCasoExista(t);
		update_most_popular(t, mais_popular);
	}
	
	
}

Item searchR(link h, Key v)
{
	if (h == NULL)
		return NULLitem;
	if (eq(v, key(h->item)))
		return h->item;
	if (greater(v,key(h->item)))
		return searchR(h->l, v);
	else return searchR(h->r, v);
	
}

Item STsearch_byKey(link head, Key v)
{
	Key k = ++v; //retira o primeiro caracter
	return searchR(head, k);	
}


link max(link h)
{
	if (h == NULL || h->r == NULL) return h;
	else return max(h->r);	
}

int count(link h)
{
	if (h == NULL) return 0;
	else return count(h->r)+count(h->l)+1;
}

int sum(link h)
{
	if (h == NULL) return 0;
	else return getHashtagOco(h->item) + sum(h->r)+ sum(h->l);
	
}

int height (link h)
{
	int u, v;
	if (h == NULL) return 0;
	u = height(h->l);
	v = height(h->r);
	if (u > v) 	return u+1;
	else 		return v+1;

}

void visit(Item it)
{
	escreveItem(it);	
}

void traverse(link h, void (*visit)(Item))
{	
	if (h == NULL)
		return;
	
	traverse(h->l, visit);
	visit(h->item);
	traverse(h->r, visit);

}


int STcount(link head)
{
	return count(head);
	
}

link deleteR(link h, Key k)
{
	if (h==NULL) return h;
	else if(greater(k, key(h->item))) h->l=deleteR(h->l,k);
	else if(greater(key(h->item),k)) h->r=deleteR(h->r,k);
	else {
		if (h->l != NULL && h->r != NULL){
			link aux=max(h->l);
			Item x; x=h->item; h->item=aux->item; aux->item=x;
			h->l = deleteR(h->l, key(aux->item));
			
		}
		else {
			link aux=h;
			if (h->l == NULL && h->r == NULL) h = NULL;
			else if (h->l==NULL) h=h->r;
			else h=h->l;
			deleteItem(&(aux->item));
			
			free(aux);
			
		}
		
	}
	
	return h;
}

void sortR(link h, void (*visit)(Item))
{
	if (h == NULL)
		return;
	sortR(h->l, visit);
	visit(h->item);
	sortR(h->r, visit);
}

void STsort(link head, void (*visit)(Item))
{
	sortR(head, visit);
}

link freeR(link h)
{
	if (h == NULL)
		return h;
	h->l=freeR(h->l);
	h->r=freeR(h->r);
	return deleteR(h, key(h->item));
	
}

void STfree(link*head)
{
	*head =freeR(*head);
	free(*head);
}

void mostra_totais(link tree)
{
	printf("%d %d\n", count(tree), sum(tree));
}


int tree_to_array(link tree, Item it[], int i)
{
	if (tree == NULL)
		return i;
	
	
	if (tree->l != NULL)
		i = tree_to_array(tree->l, it, i);
	
	it[i] = tree->item;
	i++;	
	
	if (tree->r != NULL)
		i = tree_to_array(tree->r, it, i);
	
	return i;
}

int compara(const void *p, const void *q)
{
	int x = *((int *)p);
	int y = *((int *)q);
	return (getHashtagOco(items[x]) > getHashtagOco(items[y]));
	
}

void mostra_ordenado(link tree, Item maior)
{
	if (tree == NULL) return;
	
	int nos = count(tree); 
	int i;
	
	items = (Item*)calloc(nos, sizeof(Item)); //crio um vetor de Items e reservo espaco para o numero de items da arvore
	tree_to_array(tree, items, 0); //items contem a arvore
	
	int *ordena = (int *)calloc(nos, sizeof(int));
	for (i = 0; i < nos; i++)
		ordena[i] = i;
		
	
	
	qsort(ordena, nos, sizeof(int), compara);
	
	//radixsort(items, nos, maior);

	
	for (i = nos - 1; i >= 0; i--)
		escreveItem(items[ordena[i]]);
	
	free(items);
	free(ordena);
}

void adicionaHashtags(link *tree, char *line, Item* mais_popular)
{
	
	int i,j,k;
	char buffer[MSG_BUFFER];

	for(i = 0, k = 0; line[i] != '\0'; i++, k++) {
		buffer[k] = tolower(line[i]);
		for (j = 0; j < NUMSEP; j++) {
			if (line[i] == separators[j]) {
				if (k != 0) {
					buffer[k] = '\0';
					
					if (buffer[0] == '#') //se comecar com cardinal
						if (allowed_char(buffer[1]) && (buffer[1] != '#')) //apenas insere se o primeiro caracter da hashtag nao for um separador
							STinsert(tree, buffer, mais_popular);
							 
				}
				
				k = -1;
			}
			
		}
		
		
	}
	

	
}
