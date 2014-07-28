#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "main.h"
#include "liste.h"



/* poour la gestion du presse papier, voir la fonction gtk_clipboard_wait_for_text */

int main(int argc, char *argv[]){

	if (argc < 3 ){
		printf("Usage : %s id_du_clavier fichier_d_enregistrement -> xinput\n",argv[0]);
		return 0;
	}

	time_t curtime;
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
	int nomb_touche_aligne=0;


		/* recuperation du keymap du clavier*/
	char keymap[256][TAILLE_BUFF][3];
	if(get_keymap(keymap)==-1){
		perror("Erreur dans la lecture du keymap");
		return (-1);
	}


	
	while (fgets(sortie_xinput,TAILLE_BUFF,sortie) != NULL) {
			time(&curtime);
		if(sscanf(sortie_xinput,"key press %d", &num)==1){
			ajoute(liste_interuptions,num);
			/*fprintf(enregistrement,"press %s %s\n",keymap[num][0],ctime(&curtime));*/
		}
		else if (sscanf(sortie_xinput,"key release %d", &num)==1){
				fprintliste(liste_interuptions,enregistrement);
				supprime(liste_interuptions,num);
			/*fprintf(enregistrement,"release %s %s\n", keymap[num][0],ctime(&curtime));*/
			}
		fflush(enregistrement);
	}
	fclose(enregistrement);
	pclose(sortie);
	return 0;
}



int get_keymap(char keymap[][TAILLE_BUFF][3]){/* keymap[i]="string"*/
	FILE *map;
	map=popen("xmodmap -pke","r");
	int num;
	char attente[5*TAILLE_BUFF];
	char attent[TAILLE_BUFF];
	char shift_attent[TAILLE_BUFF];
	char shit1[TAILLE_BUFF];
	char shit2[TAILLE_BUFF];
	char altgr_attent[TAILLE_BUFF];


	if(map==NULL){
		perror("Can't launch the command");
		return (-1);
	}
	
	while (fgets(attente,5*TAILLE_BUFF,map)!=NULL) {
		if (sscanf(attente,"keycode %d = %s %s %s %s %s",&num,attent,shift_attent,shit1,shit2,altgr_attent)>=1 && num<256 && num>0){
			memcpy(keymap[num][3],attent,TAILLE_BUFF);
		}
	}
		
	pclose(map);
	return 0;
	}