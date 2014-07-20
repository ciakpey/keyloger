#include <stdio.h>
#include <stdlib.h>


int main(){
	
	/* recuperer la correspondance numero, valeur avec xmodmap -pke*/
	FILE *sortie;
	sortie = popen("xinput test 11","r");
	while (1) {
		char maison[100];
		fgets(maison,99,sortie);
		printf("%s", maison);
	}
	pclose(sortie);
	return 0;
}