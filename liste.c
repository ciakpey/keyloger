#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"
#include <time.h>
/* ptr->|....|...|precedent|element|suivant|....*/

extern void ajoute(struct liste **maliste,int elem){//fonctionne
	
	struct liste *newliste = (struct liste *) malloc(sizeof(struct liste));
		newliste->elem=elem; 
		newliste->suivant=*maliste; 
		newliste->precedent=NULL;

	if (*maliste != NULL){
		(*maliste)->precedent=newliste;
		*maliste=newliste;
			if ((*maliste)->suivant==NULL) printf("aa");
			fflush(stdout);
	}
	else 
		*maliste=newliste;
}

extern void supprime(struct liste **maliste,int elem){
	struct liste *ptr=*maliste;
	while(ptr!=NULL){
		if (elem==ptr->elem){
			if (ptr->precedent==NULL && ptr->suivant==NULL){
				(*maliste)=NULL;printf("0");
			}
			else if (ptr->precedent==NULL){
				ptr->suivant->precedent=NULL;
				*maliste=ptr->suivant;
				printf("1");
			}
			else if (ptr->suivant==NULL){
				ptr->precedent->precedent=NULL;printf("2");
			}
			else{printf("3");
				ptr->precedent->suivant=ptr->suivant;
				ptr->suivant->precedent=ptr->precedent;
			}
			fflush(stdout);
			break;
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

void fprintliste(struct liste *maliste,FILE *fichier){ //fonctionne
	struct liste *ptr=maliste;
	while(ptr!=NULL){
		if (ptr->suivant==NULL){
			fprintf(fichier,"%d",ptr->elem);
			ptr=ptr->suivant;
		}
		else{
			fprintf(fichier,"%d+",ptr->elem);
			ptr=ptr->suivant;
		}
	}
	time(&curtime);
	fprintf(fichier," %s\n",ctime(&curtime));
}

