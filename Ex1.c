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
	int* t =  calloc(dimension,sizeof(int));
	//si l'allocation mémoire a échoué, on arrète le programme
	if(t == NULL){
		exit(0);
	}
	for(int i=0; i<dimension; i++){
		t[i]=val;
	}
	return t;
}

void liberer_tableau(int *tab){
	free(tab);
	tab=NULL;
}

int *lire_n_entiers(int n){
	int nb;
	int *t = allouer_tableau(n,0);
	for(int i=0; i<n; i++){
		printf("entrez un nb\n");
		scanf("%d",&nb);
		t[i]=nb;
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

int *lire_entiers(void){
	int nb=1;
	int cpt=0;
	int* t=allouer_tableau(4,0);
	while(nb!=0){
		printf("entrez un nb ou terminez par 0\n");
		scanf("%d",&nb);
		t[cpt]=nb;
		cpt++;
		if(cpt%3 >= 3){
			//le tableau contenait cpt-1 éléments donc on fait 2*(cpt-1) pour doubler sa taille
			//en multipliant par sizeof(int) pour donner la taille en octets
			t= realloc(t, 2*(cpt-1)*sizeof(int));
		}
	}
	afficher_tableau(t,cpt-1);
	return t;
}

int **allouer_matrice(int lignes, int colonnes, int val){
	int **mat = malloc(lignes * sizeof(int *));
	for(int i=0; i<lignes; i++){
		mat[i]=allouer_tableau(colonnes,val);
	}return mat;
}

void liberer_matrice(int **mat, int lignes){
	for(int i=lignes-1; i>=0; i--){
		liberer_tableau(mat[i]);
	}free(mat);
	mat=NULL;
}

void afficher_matrice(int **mat, int lignes, int colonnes){
	for(int i=0;i<lignes;i++){
		afficher_tableau(mat[i],colonnes);
	}
}

int main(){
	int taille = 10;
	int* t = lire_entiers();
	liberer_tableau(t);
	afficher_tableau(t,taille);
//	int** mat = allouer_matrice(10,10,8);
//	afficher_matrice(mat,10,10);
//	liberer_matrice(mat,10);
//	afficher_matrice(mat,10,10);

}

