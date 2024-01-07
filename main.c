#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Piece {
    float valeur;
    int quantite;
};

struct Produit {
    char nom[50];
    float prix;
    int quantite;
};

int verifierMotDePasse(char motDePasse[]) {
    char motDePasseAttendu[] = "MAXIMD";
    return strcmp(motDePasse, motDePasseAttendu) == 0;
}

void afficherStockProduits(struct Produit produits[], int nbProduits) {
    printf("Stock de produits disponibles :\n");
    for (int i = 0; i < nbProduits; i++) {
        printf("%s: %d\n", produits[i].nom, produits[i].quantite);
    }
}

void afficherMenu(struct Produit produits[], int nbProduits) {
    afficherStockProduits(produits, nbProduits);
    printf("Menu des articles:\n");
    for (int i = 0; i < nbProduits; i++) {
        printf("%s: %.2f euros\n", produits[i].nom, produits[i].prix);
    }
}

void afficherCaisse(struct Piece pieces[], int nbPieces, char motDePasse[]) {
    if (verifierMotDePasse(motDePasse)) {
        printf("Contenu de la caisse:\n");
        for (int i = 0; i < nbPieces; i++) {
            printf("%.2f euro(s): %d\n", pieces[i].valeur, pieces[i].quantite);
        }
    } else {
        printf("Mot de passe incorrect.\n");
    }
}

void initialiserCaisse(struct Piece caisse[], int nbPieces) {
    printf("Initialisation de la caisse au démarrage du programme:\n");
    for (int i = 0; i < nbPieces; i++) {
        printf("Nombre de pièces de %.2f euro(s): ", caisse[i].valeur);
        scanf("%d", &caisse[i].quantite);
    }
}

void initialiserStock(struct Produit produits[], int nbProduits) {
    printf("Initialisation du stock de produits au démarrage du programme:\n");
    for (int i = 0; i < nbProduits; i++) {
        printf("Nombre de %s: ", produits[i].nom);
        scanf("%d", &produits[i].quantite);
    }
}

float calculerSommePanier(struct Produit produits[], int nbProduits, int quantites[]) {
    float somme = 0;
    for (int i = 0; i < nbProduits; i++) {
        somme += produits[i].prix * quantites[i];
    }
    return somme;
}

void rendreMonnaie(struct Piece caisse[], int nbPieces, float monnaieDue) {
    for (int i = 0; i < nbPieces; i++) {
        while (caisse[i].quantite > 0 && monnaieDue >= caisse[i].valeur) {
            printf("Rendre %.2f euro(s)\n", caisse[i].valeur);
            monnaieDue -= caisse[i].valeur;
            caisse[i].quantite--;
        }
    }
}

int main() {
    struct Piece caisse[] = {{2, 0}, {1, 0}, {0.5, 0}, {0.2, 0}, {0.1, 0}, {0.05, 0}};
    int nbPieces = sizeof(caisse) / sizeof(caisse[0]);

    struct Produit produits[] = {{"baguette", 1.5, 10}, {"pain_long", 2, 8}, {"pizza", 5, 5},
                                 {"pissaladiere", 3, 3}, {"pain_chocolat", 1.2, 12}, {"croissant", 1, 15}};
    int nbProduits = sizeof(produits) / sizeof(produits[0]);

    char motDePasse[50];

    initialiserCaisse(caisse, nbPieces);
    initialiserStock(produits, nbProduits);

    while (1) {
        printf("\nMenu principal:\n");
        printf("1. Afficher le menu\n");
        printf("2. Afficher le contenu de la caisse\n");
        printf("3. Effectuer un achat\n");
        printf("9. Quitter\n");

        int choix;
        printf("Choisissez une option: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                afficherMenu(produits, nbProduits);
                break;
            case 2:
                printf("Entrez le mot de passe: ");
                scanf("%s", motDePasse);
                afficherCaisse(caisse, nbPieces, motDePasse);
                break;
            case 3: {
                afficherStockProduits(produits, nbProduits);

                printf("Entrez le numéro du produit que vous souhaitez acheter: ");
                int numProduit;
                scanf("%d", &numProduit);
                if (numProduit >= 0 && numProduit < nbProduits) {
                    printf("Produit sélectionné: %s\n", produits[numProduit].nom);
                    printf("Prix: %.2f euros\n", produits[numProduit].prix);
                    printf("Stock disponible: %d\n", produits[numProduit].quantite);

                    int quantite;
                    printf("Entrez la quantité que vous souhaitez acheter: ");
                    scanf("%d", &quantite);

                    if (quantite <= produits[numProduit].quantite) {
                        float sommeDue = produits[numProduit].prix * quantite;
                        printf("La somme due est de %.2f euros.\n", sommeDue);

                        float monnaieVerse = 0;
                        printf("Entrez la somme que vous donnez: ");
                        scanf("%f", &monnaieVerse);

                        if (monnaieVerse < sommeDue) {
                            printf("Somme insuffisante. Rendre les pièces.\n");
                        } else {
                            float monnaieDue = monnaieVerse - sommeDue;
                            if (monnaieDue > 0) {
                                rendreMonnaie(caisse, nbPieces, monnaieDue);
                                produits[numProduit].quantite -= quantite;
                                printf("Transaction réussie. Rendre la monnaie.\n");
                            } else {
                                produits[numProduit].quantite -= quantite;
                                printf("Transaction réussie. Pas de monnaie à rendre.\n");
                            }
                        }
                    } else {
                        printf("Stock insuffisant pour le produit sélectionné.\n");
                    }
                } else {
                    printf("Numéro de produit invalide.\n");
                }
                break;
            }
            default:
                printf("Option invalide. Veuillez réessayer.\n");
        }

        // Ajouter une pause pour laisser le temps à l'utilisateur de lire avant de nettoyer la console
        printf("\nAppuyez sur Entrée pour continuer...");
        getchar();  // Attendre l'entrée de l'utilisateur
        getchar();  // Attendre une autre entrée pour continuer
    }

    return 0;
}


