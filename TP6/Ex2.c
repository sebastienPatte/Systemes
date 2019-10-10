
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

void print_tab(int* t, int n){
	for(int i = 0; i<n; i++){
		printf("%d", t[i]);
	}printf("\n");
}

int main(){
	int* tab = initialiser_tableau_v1(8,2);
	print_tab(tab,8);
}
