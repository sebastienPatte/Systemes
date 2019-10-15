
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int *initialiser_tableau_v1(int n, int valeur) {
	int len = 1;
	int *tab = malloc(sizeof(int));
	tab[0]=valeur;
	//on met le pointeur source sur le premier élément du tableau
	long unsigned int src = (long unsigned int)&(tab[0]);
	long unsigned int dest ;

	while (2 * len <= n) {
		//calcul du pointeur vers la destination
		dest = (long unsigned int)&tab[0]+len*sizeof(int);
		int size = (len)*sizeof(int);
		//on double la mémoire allouée au tableau
		tab = realloc(tab,len*sizeof(int));
		//copie des éléments du tableau à la mémoire qu'on viens de lui ré-allouer
		memcpy( (int*)dest, (int*)src, size);
		len = len*2;
//		printf("dest : %lu\nsrc : %lu\nsize: %d\n",dest%100,src%100,size);
	}

	//ajustement pour les tableaux de taille impaire 
	tab = realloc(tab,n*sizeof(int));
	/*on récupère la valeur du pointeur vers la destination 
	(la dernière valeur étant dans le while au dessus, donc inaccessible)*/
	dest = (long unsigned int)&tab[0]+len*sizeof(int);
	/*on copie autant d'éléments qu'il en manque à la fin du tableau pour les y placer
	le nombre d'éléments manquants est n-(len-1) 
	(on met len-1 car len commence à 1 alors que l'indice minimal dans ce tableau est 0)*/
	memcpy( (int*)  dest, (int*)src, (n-(len-1))*sizeof(int));

	return tab;
}

void print_tab_int(int* t, int n){
	for(int i = 0; i<n; i++){
		printf("%d;", t[i]);
	}
	printf("\n");
}


char *initialiser_tableau_char(int dimension, char c){
		int *tab = malloc(dimension*sizeof(int));
		memset(tab, c, dimension);
}

void print_tab_char(char* t, int n){
	for(int i = 0; i<n; i++){
		printf("%c;", t[i]);
	}
	printf("\n");
}

void copier_chaine(char *tab, int s1, int taille, int s2){
	//on utilise memove car la sources et la destination de la copie peuvent se chevaucher
	memmove((char*)&tab[s2], (char*)&tab[s1], taille*sizeof(char));
}

int main(){
	
	printf("initialiser_tableau_v1(8,2) : \n");
	int* tabInt = initialiser_tableau_v1(7,2);
	print_tab_int(tabInt,8);

	printf("\ninitialiser_tableau_char(10,'x') : \n");
	char* tabChar = initialiser_tableau_char(10,'x');
	print_tab_char(tabChar,10);

	printf("\ntabChar[0]='A'\ntabChar[1]='V'\ntabChar[2]='Z'\n");
	tabChar[0]='A';
	tabChar[1]='V';
	tabChar[2]='Z';
	print_tab_char(tabChar,10);
	
	printf("\ncopier_chaine(tabChar, 0, 3, 2) : \n");
	copier_chaine(tabChar, 0, 3, 2);
	print_tab_char(tabChar,10);
}
