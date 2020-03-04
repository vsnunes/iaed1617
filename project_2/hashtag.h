#include <stdio.h>
#include <stdlib.h>

#ifndef hashtag_h
#define hashtag_h

#define MSG_BUFFER 143

typedef struct hashtag_t {
	char *palavra;
	int ocorrencias;
} hashtag_t;

typedef struct hashtag_t *Hashtag;

#define getHashtagWord(h) (h->palavra)
#define getHashtagOco(h) (h->ocorrencias)

#define incOcorrencias(h) (h->ocorrencias++)


#define Hashtags_ocorrencias(h, oc) (h->ocorrencias > oc)

#define comparaHashtags_ocorrencias(h1, h2) (h1->ocorrencias > h2->ocorrencias)

/* Funcoes do tipo hashtag_t */
Hashtag cria_nova_hashtag(char *palavra, int ocorrencias);
int comparaHashtags_palavra(Hashtag h, char *word);
void escreveHashtag(Hashtag h);
void libertaHashtag (Hashtag h);


#endif /* hashtag_h */
