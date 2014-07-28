#include <stdio.h>

struct liste{
	int elem;
	struct liste *suivant;
	struct liste *precedent;
};

void ajoute(struct liste *maliste,int elem);

void supprime(struct liste *maliste,int elem);

int taille_liste(struct liste *maliste);

void fprintliste(struct liste *maliste,FILE *fichier);