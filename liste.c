#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"

/* ptr->|....|...|precedent|element|suivant|....*/

extern void ajoute(struct liste *maliste,int elem){
	
	struct liste *newliste = (struct liste *) malloc(sizeof(struct liste));
	newliste->elem=elem; newliste->suivant=maliste; newliste->precedent=NULL;/*={elem,NULL,maliste};*/
	maliste=newliste;
	maliste->precedent = maliste;
}

extern void supprime(struct liste *maliste,int elem){
	struct liste *ptr=maliste;
	while(ptr!=NULL){
		if (elem==ptr->elem){
			if (ptr->precedent==NULL && ptr->precedent==NULL){
				maliste=NULL;
			}
			else if (ptr->precedent==NULL){
				ptr->suivant->precedent=NULL;
				maliste=ptr->suivant;
			}
			else if (ptr->suivant==NULL){
				ptr->precedent->suivant=NULL;
			}
			else{
				ptr->precedent->suivant=ptr->suivant;
				ptr->suivant->precedent=ptr->precedent;
			}
		}
		else 
			ptr=ptr->suivant;
	}
}

int taille_liste(struct liste *maliste){
	int accu = 0 ;
	struct liste *ptr=maliste;
	while(ptr!=NULL){
		accu++;
		ptr=ptr->suivant;
	}
	return accu;
}

/*struct liste *new_liste(int elem){
	struct liste *essai = (struct liste *) malloc(sizeof(struct liste));
	essai->elem = elem;
	return essai;
}*/

time_t curtime;

void fprintliste(struct liste *maliste,FILE *fichier){
	struct liste *ptr=maliste;
	while(ptr!=NULL){
		fprintf(fichier,"%d+",ptr->elem);
		ptr=ptr->suivant;
	}
	time(&curtime);
	fprintf(fichier," %s\n",ctime(&curtime));
}