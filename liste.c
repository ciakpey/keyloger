#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"
#include <time.h>
#include "main.h"


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
				(*maliste)=NULL;
			}
			else if (ptr->precedent==NULL){
				ptr->suivant->precedent=NULL;
				*maliste=ptr->suivant;
			}
			else if (ptr->suivant==NULL){
				ptr->precedent->precedent=NULL;
			}
			else{
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


time_t curtime;
//ne prend que des listes de longueur au moins2 et renvoie 0 si la liste n'est pas: lettre ->ALtgr|Shift
int est_lettres_combi(char keymap[][3][TAILLE_BUFF],struct liste *maliste){
	int m = keymap[maliste->elem][0][0]<='z' && keymap[maliste->elem][0][0]>='a'; //si le premier element est une lettre
	if ( m!= 0 && strncmp("Shift",keymap[maliste->suivant->elem][0],5)==0 ) return 1;
	else if (m!=0 && strncmp("ISO_Level3_Shift",keymap[maliste->suivant->elem][0],16)==0) return 2;
	else return 0;
}



void fprintliste(struct liste *maliste,FILE *fichier,char keymap[][3][TAILLE_BUFF]){ //fonctionne
	struct liste *ptr=maliste;
	int g;

	if (taille_liste(maliste)==1) 
		fprintf(fichier,"%s",keymap[ptr->elem][0]);

	else if (taille_liste(maliste)==2 && (g=est_lettres_combi(keymap,maliste)))
			fprintf(fichier,"%s",keymap[ptr->elem][g]);
	else{
		while(ptr!=NULL && ptr->suivant!=NULL){
			
				fprintf(fichier,"%s+",keymap[ptr->suivant->elem][0]);
				ptr=ptr->suivant;
		}
		fprintf(fichier,"%s",keymap[maliste->elem][0]);
	}
	time(&curtime);
	fprintf(fichier," %s\n",ctime(&curtime));
}

