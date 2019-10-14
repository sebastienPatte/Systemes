
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int *initialiser_tableau_v1(int n, int valeur) {
	int len = 1;
	int *tab = malloc(sizeof(int));
	tab[0]=valeur;
	while (2 * len <= n) {
		long unsigned int dest = (long unsigned int)&tab[0]+len*sizeof(int);
		long unsigned int src = (long unsigned int)&(tab[0]);
		int size = (len)*sizeof(int);
		tab = realloc(tab,len*sizeof(int));
		memcpy( (int*)dest, (int*)src, size);
		len = len*2;
		printf("dest : %lu\nsrc : %lu\nsize: %d\n",dest%100,src%100,size);
	}
//	tab = realloc(tab, len*sizeof(int));
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
	int* tabInt = initialiser_tableau_v1(8,2);
	print_tab_int(tabInt,8);
	char* tabChar = initialiser_tableau_char(10,'x');
	print_tab_char(tabChar,10);
	tabChar[0]='A';
	tabChar[1]='V';
	tabChar[2]='Z';
	copier_chaine(tabChar, 0, 3, 2);
	print_tab_char(tabChar,10);
}
