

/* ptr->|....|...|precedent|element|suivant|....*/
struct liste{
	char *elem;
	struct liste *suivant;
	struct liste *precedent;
};

void ajoute(struct liste *maliste,char  *elem){
	char *new=(char *) malloc(strlen(elem) *sizeof(char));
	struct liste newliste = {new,NULL,maliste};
	*maliste=newliste;
	maliste->precedent = maliste;
}

void supprime(struct liste *maliste,char *elem){
	struct liste *ptr=maliste;
	while(ptr!=NULL){
		if (strcmp(elem,ptr->elem)==0){
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