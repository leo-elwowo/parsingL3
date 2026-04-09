#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "symb.h"

HashTable *global_table = NULL;
HashTable *local_table = NULL;
int current_offset = 0; 

void analyze_semantics(Node *node) {
    if (node == NULL) return;

    // 1. Action spécifique selon le type de nœud
    switch (node->label) {
        case T_PROG:
            // Racine du programme : on initialise la table globale
            init_table(&global_table);
            break;

        case T_FUNC:
            // On rentre dans une nouvelle fonction : on crée sa table locale
            init_table(&local_table);
            
            // On réinitialise l'offset pour la nouvelle fonction
            // (le cours indique d'utiliser l'offset pour l'emplacement disponible)
            current_offset = 0; 
            break;

        case T_DECL_VARS:
            // Déclaration de variable(s) (globale ou locale)
            // À FAIRE : Récupérer le type depuis le fils (T_TYPE)
            // À FAIRE : Parcourir les identifiants (T_IDENT) déclarés
            // À FAIRE : Les insérer avec insert_value() et mettre à jour current_offset
            break;

        case T_PARAM:
            // Paramètre d'une fonction (se comporte comme une variable locale)
            // À FAIRE : L'insérer dans local_table et mettre à jour current_offset
            break;

        case T_IDENT:
            // Utilisation d'une variable (dans une instruction, calcul, etc.)
            // À FAIRE : Vérifier si la variable existe.
            // On cherche d'abord dans local_table. Si pas trouvée, on cherche dans global_table.
            // Si elle n'est nulle part -> Erreur sémantique (variable non déclarée) !
            break;

        default:
            break;
    }

    // 2. Parcours récursif des enfants
    // On visite tous les fils de gauche à droite
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling) {
        analyze_semantics(child);
    }

    // 3. Action à la "remontée" (post-ordre)
    if (node->label == T_FUNC) {
        // On a fini d'analyser la fonction. 
        // Optionnel pour le moment : on pourrait libérer la table locale ou la sauvegarder 
        // pour la génération de code assembleur plus tard.
        // free_table(local_table); 
        // local_table = NULL;
    }
}