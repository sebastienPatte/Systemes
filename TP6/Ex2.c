
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int *initialiser_tableau_v1(int n, int valeur) {
	int len = 1;
	int *tab = malloc(sizeof(int));
	tab[0]=valeur;
	while (2 * len <= n) {
		int dest = *tab+len*sizeof(int);
		int src = *tab;
		memcpy(tab+len*sizeof(int), tab, len*sizeof(int));
		len = len*2;
		printf("dest : %d\nsrc : %d\n",dest,src);
	}
	tab = realloc(tab, len*sizeof(int));
	return tab;
}

void print_tab(int* t, int n){
	for(int i = 0; i<n; i++){
		printf("%d", t[i]);
	}printf("\n");
}

int main(){
	int* tab = initialiser_tableau_v1(4,2);
	print_tab(tab,4);
}
