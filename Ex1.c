#include <stdio.h>
#include <stdlib.h>
/*
int *creer_tableau(int n) {
	int tab[n];
	return tab;
}

int main() {
	int *t = creer_tableau(100);
	return 0;
}


Q1/
la fonction creer_tableau renvoie un pointeur vers tab qui est une variable locale à cette fonction
dans la fonction main cette adresse ne sera donc pas celle du tableau
*/

int *allouer_tableau(int dimension, int val){
	int *t =  calloc(dimension,4);
	for(int i=0; i<dimension; i++){
		t[i]=val;
	}
	return t;
}

void liberer_tableau(int *tab){
	free(tab);
}

int *lire_n_entiers(int n){
	int nb;
	int *t = allouer_tableau(n,0);
	for(int i=0; i<n; i++){
		printf("entrez un nb\n");
		scanf("%d",&nb);
		t[i]=nb;
		printf("i=%d\n",i);

	}
	return t;
}

void afficher_tableau(int *tab, int dimension){
	printf("[%d",tab[0]);
	for(int i=1; i<dimension; i++){
                printf(";%d",tab[i]);
        }
	printf("]\n");
}

int main(){
	int taille = 3;
	int *t = lire_n_entiers(taille);
	afficher_tableau(t,taille);
	liberer_tableau(t);
	printf("%d",t[0]);
}

