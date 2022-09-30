#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define choix_invalid "choix invalid\n"
#define operation_invalide "invalid operation\n"
#define supprime "\n*** un produit supprimer ***\n"
#define ajoute "\n*** un produit ajoute ***\n"
#define cls system("cls")

// une structure qui s'appele produit
typedef struct {
	int code;
	char nom[25];
	int quantite;
	float prix;
} produit;

typedef struct {
	float TTC;
	char date[12];
	int quantite;	
} produit_achete;


// une fonction pour afficher le menu
void afficher_menu();
//une fonction pour afficher les deux choix de recherche
void afficher_recherche_choix();
//une fonction pour afficher les deux choix de tri
void afficher_tri_choix();
//une fonction qui jouter un produit
produit ajouter_produit();
//une fonction qui ajouter plusieur produits
void ajouter_n_produit();
//une fonction qui trier tous les produits par prix (order decroissant)
void trier_par_prix();
//une fonction qui trier les produits par nom (order croissant)
void trier_par_nom();
//une fonction pour acheter un produit
void acheter();
//une fonction qui rechercher un produit par code
void rechercher_par_code();
//une fonction qui rechercher un produit par quantite
void rechercher_par_quantite();
//une fonction pour afficher tous les produits
void afficher_produit();
//une fonction pour afficher tous les produits vendu
void afficher_produit_achete();
//etat de stock
void etat_stock();
//alimanter le stock
void alimanter_stock();
//une fonction pour supprimer un produit par code 
void supprimer();
//une fonction qui copie les prix * les quantites de tous les produits d'aujourd'hui
void copie_prix_produits_vendu_aujourdhui();
//une fonction pour retourner le max prix
float max_prix();
//une fonction pour retourner le min prix
float min_prix();


produit PRODUITS[1000];
produit_achete PRODUITS_ACHETES[400];
float PRIX_TTC[400];
int rnd = 7 , T1 = 0 , T2 = 0 , T3 = 0 , T1A , OPERATION_CHOIX , TRI_CHOIX , RECHERCHE_CHOIX , QUITTER;
char DATE[12];

int main(){

	float somme = 0;
       
	do{
		cls;
		afficher_menu();
		printf("\nchoisir une operation\n");
		printf(">> ");
		scanf("%d" , &OPERATION_CHOIX);
	switch(OPERATION_CHOIX){
		case 1:
			cls;
			PRODUITS[T1] = ajouter_produit();
			T1++;
			cls;
			printf(ajoute);
			break;
		case 2:
			cls;
			printf("enter le nombre de produits que vous voulez saisir\n");
        	scanf("%d" , &T1A);
			ajouter_n_produit();
			T1 += T1A;
			cls;
			break;
		case 3:
			cls;
			afficher_tri_choix();
			printf(">> ");
			scanf("%d" , &TRI_CHOIX);
			switch(TRI_CHOIX){
				case 1:
					cls;
					trier_par_prix();
					afficher_produit();
					break;
				case 2:
					cls;
					trier_par_nom();
					afficher_produit();
					break;
				default:
					printf(choix_invalid);
					break;
			}
			break;
		case 4:
			cls;
			acheter();
			T2++;
			break;
		case 5:
			cls;
			afficher_recherche_choix();
			printf(">> ");
			scanf("%d" , &RECHERCHE_CHOIX);
			switch(RECHERCHE_CHOIX){
				case 1:
					cls;
					rechercher_par_code();
					break;
				case 2:
					cls;
					rechercher_par_quantite();
					break;
				default:
					printf(choix_invalid);
					break;
			}
			break;
		case 6:
			cls;
			etat_stock();
			break;
		case 7:
			cls;
			alimanter_stock();
			break;
		case 8:
			cls;
			supprimer();
			cls;
			printf(supprime);
			T1--;
			break;
		case 9:
			cls;
			copie_prix_produits_vendu_aujourdhui();
			for(int i = 0 ; i < T3 ; i++){
				somme += PRIX_TTC[i];
			}
			cls;
			printf("Les Statistiques de Vente : \n\n");
			printf("Le prix total des produits est : %.2f\n" , somme);
			printf("La moyenne des prix des produits est : %.2f\n" , somme/T3);
			printf("Le max prix des produits est : %.2f\n" , max_prix());
			printf("Le min prix des produits est : %.2f\n" , min_prix());
			break;
		case 10:
			cls;
			afficher_produit();
			break;
		case 11:
			cls;
			afficher_produit_achete();
			break;
		default:
			cls;
			printf(operation_invalide);
			break;	
	}
	printf("\nQuitter => 0  |  Menu Principal => 1\n");
	printf(">> ");
	scanf("%d" , &QUITTER);
	}while(QUITTER != 0);

	return 0;
}


// une fonction pour afficher le menu
void afficher_menu(){
	printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("\n\t\t\t\t\t\t\t====================\n");
	printf("\t\t\t\t\t\t\tGestion de Pharmacie\n");
	printf("\t\t\t\t\t\t\t====================\n\n");
	printf("\t\t\t\t     Ajouter un Produit => 1      -      Ajouter n Produit => 2\n");
	printf("\n");
	printf("\t\t\t\t     Lister les Produits => 3     -      Acheter un Produit => 4\n");
	printf("\n");
	printf("\t\t\t\t     Rechercher un Produit => 5   -      Etat de Stock => 6\n");
	printf("\n");
	printf("\t\t\t\t     Alimanter de Stock => 7      -      Supprimer un produit => 8\n");
	printf("\n");
	printf("\t\t\t\t     Statistique de vente => 9    -      Afficher les tous les produits => 10\n");
	printf("\n");
	printf("\t\t\t\t\t\t     Afficher les produits vendu => 11\n");
	printf("\n--------------------------------------------------------------------------------------------------------------------------------------\n");
}
//afficher les deux choix de recherche
void afficher_recherche_choix(){
    printf("1-par code \n");
	printf("2-par quantite \n");
}
//afficher les deux choix de tri
void afficher_tri_choix(){
    printf("1-par prix \n");
    printf("2-par nom \n");
}
//une fonction pour ajouter un produit
produit ajouter_produit(){
	produit p;
	printf("entrer les information de produit :\n");
	p.code = rnd;
	rnd = (rnd * 2) - 3;
	printf("nom : ");
    scanf("%s" , p.nom);
	printf("quantite : ");
    scanf("%d" , &p.quantite);
	printf("prix : ");
    scanf("%f" , &p.prix);
	return p;
}

//une fonction pour ajouter plusieur produits
void ajouter_n_produit(){
	for(int i = T1 ; i < T1 + T1A ; i++){
		PRODUITS[i] = ajouter_produit();
	}
}

//trier tous les produits par prix order decroissant
void trier_par_prix(){

	produit aide;
	int condition;

	do{
		condition = 0;
		for(int i = 0 ; i < T1 - 1 ; i++){
			if(PRODUITS[i].prix < PRODUITS[i+1].prix){
                condition = 1;
				aide = PRODUITS[i];
				PRODUITS[i] = PRODUITS[i+1];
				PRODUITS[i+1] = aide;
			}
		}
	}while(condition == 1);
}

//une fonction qui trier les produits par nom
void trier_par_nom(){
	produit aide;
	int condition;
	do{	
		condition = 0;
		for(int i = 0; i < T1 - 1; i++){
        	if(strcasecmp(PRODUITS[i].nom, PRODUITS[i+1].nom) > 0){
				condition = 1;
            	aide = PRODUITS[i];
				PRODUITS[i] = PRODUITS[i+1];
				PRODUITS[i+1] = aide;
        	}
		}
	}while(condition == 1);
}

//une fonction pour acheter un produit
void acheter(){
	int code , quantite , position = -1;
	printf("enter le code du produit que vous voulez acheter : ");
	scanf("%d" , &code);
	
	for(int i = 0 ; i < T1 ; i++){
		if(code == PRODUITS[i].code){
			position = 1;
			printf("enter le quantite du produit que vous voulez acheter : ");
			scanf("%d" , &quantite);
			if(quantite > 0 && quantite < PRODUITS[i].quantite){
				PRODUITS[i].quantite -= quantite;
				PRODUITS_ACHETES[T2].TTC = (PRODUITS[i].prix + PRODUITS[i].prix * 0.15);
				printf("entrer la date d'achat (ex: jj/mm/aaaa) : ");
				scanf("%s" , PRODUITS_ACHETES[T2].date);
				PRODUITS_ACHETES[T2].quantite = quantite;
			}else
				printf("quantite de stock insufuson\n"); 
		}
	}
	if(position == -1)
		printf("ce produit n'existe pas\n");
}

//rechercher un produit par code
void rechercher_par_code(){
	int code , position = -1;
	printf("entrer le code du produit : ");
	scanf("%d" , &code);
	for(int i = 0 ; i < T1 ; i++){
		if(code == PRODUITS[i].code){
			position = i;
		}
	}
	if(position != -1){
		printf("\ncode : %d | nom : %s | quantite : %d | prix : %.2f\n" , PRODUITS[position].code , PRODUITS[position].nom , PRODUITS[position].quantite , PRODUITS[position].prix);
	}else
		printf("\nce produit n'existe pas \n");
}

//rechercher un produit par quantite
void rechercher_par_quantite(){
	int quantite , existe = 1;
		printf("entrer la quantite du produit : ");
		scanf("%d" , &quantite);
		for(int i = 0 ; i < T1 ; i++){
                if(quantite == PRODUITS[i].quantite){
                        printf("\ncode : %d | nom : %s | quantite : %d | prix : %.2f\n" , PRODUITS[i].code , PRODUITS[i].nom , PRODUITS[i].quantite , PRODUITS[i].prix);
                }else
					existe = 0;
		}
		if(existe == 0){
			printf("\nle produit que vous cherchez n'existe pas \n");
		}
}

//une fonction pour afficher tous les produits
void afficher_produit(){
	printf("La Liste des Produits : \n\n");
	for(int i = 0 ; i < T1 ; i++){
        printf("\ncode : %d | nom : %s | quantite : %d | prix : %.2f\n" , PRODUITS[i].code , PRODUITS[i].nom , PRODUITS[i].quantite , PRODUITS[i].prix);
	}
}

void afficher_produit_achete(){
	for(int i = 0 ; i < T2 ; i++){
        printf("\nPrix TTC : %.2f | Date : %s | Quantite : %d\n" , PRODUITS_ACHETES[i].TTC , PRODUITS_ACHETES[i].date , PRODUITS_ACHETES[i].quantite);
	}
}

//etat de stock
void etat_stock(){
	int existe;
	printf("Etat de Stock :\n");
	for(int i = 0 ; i < T1 ; i++){
		if(PRODUITS[i].quantite < 3){
			printf("\ncode : %d - nom : %s - quantite : %d - prix : %.2f\n" , PRODUITS[i].code , PRODUITS[i].nom , PRODUITS[i].quantite , PRODUITS[i].prix);
		}else{
			existe = 0;
		}
	}
	if(existe == 0){
		printf("\nN'existe pas des produits ont une quantite inferieur de 3\n");
	}
}

//alimanter le stock
void alimanter_stock(){
	int code , quantite , position = -1;
	printf("entrer le code du produit : ");
	scanf("%d" , &code);

	for(int i = 0 ; i < T1 ; i++){
		if(code == PRODUITS[i].code){
			position = i;
		}
	}
	if(position != -1){
		printf("entrer la quantite : ");
		scanf("%d" , &quantite);
			if(quantite > 0){
				PRODUITS[position].quantite += quantite;
			}else
				printf("quantite doit être superieure à 0\n");
	}else{
		printf("ce produit n'existe pas\n");
	}
}
//une fonction pour supprimer un produit par code 
void supprimer(){
	int code , position = -1;
	printf("entrer le code du produit que vous voulez supprimer : ");
	scanf("%d" , &code);

	for(int i = 0 ; i < T1 ; i++){
		if(code == PRODUITS[i].code){
			position = i;
		}
	}
	if(position != -1){
		for(int i = position ; i < T1-1 ; i++){
			PRODUITS[i] = PRODUITS[i+1];
		}
	}
}

//une fonction qui copie les prix * les quantites de tous les produits d'aujourd'hui
void copie_prix_produits_vendu_aujourdhui(){
	printf("entrer la date du journnee courante : ");
	scanf("%s" , DATE);
	for(int i = 0 ; i < T2 ; i++){
		if(strcmp(DATE , PRODUITS_ACHETES[i].date) == 0){
			PRIX_TTC[T3] = PRODUITS_ACHETES[i].TTC * PRODUITS_ACHETES[i].quantite;
			T3++;
		}
	}
}
//une fonction pour retourner le max prix
float max_prix(){
	float max = PRIX_TTC[0];
	for(int i = 1 ; i < T3 ; i++){
		if(max < PRIX_TTC[i]){
			max = PRIX_TTC[i];
		}
	}
	return max;
}

//une fonction pour retourner le min prix
float min_prix(){
	float min = PRIX_TTC[0];
	for(int i = 1 ; i < T3 ; i++){
		if(min > PRIX_TTC[i]){
			min = PRIX_TTC[i];
		}
	}                                                   
    return min;
}