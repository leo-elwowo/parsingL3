#!/bin/bash

# ==============================================================================
# SCRIPT DE TEST POUR PROJET TPC IA IA IA IA IA :DDD
# ==============================================================================

# 1. Configuration
# ----------------
TPCAS="./bin/tpcas"
DIR_GOOD="test/good"
DIR_BAD="test/syn-err"

# Couleurs pour l'affichage
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color
BOLD='\033[1m'

# Compteurs
TOTAL=0
PASSED=0

# 2. Vérification de l'exécutable
# -------------------------------
if [ ! -f "$TPCAS" ]; then
    echo -e "${RED}Erreur : L'exécutable $TPCAS n'existe pas.${NC}"
    echo "Veuillez compiler avec 'make' d'abord."
    exit 1
fi

echo -e "${BOLD}Lancement des tests sur l'analyseur syntaxique TPC...${NC}\n"

# 3. Fonction de test
# -------------------
run_test() {
    local file=$1
    local expected_code=$2
    local type_test=$3
    
    # On incrémente le total
    ((TOTAL++))

    # Exécution du parser (On cache la sortie standard et d'erreur)
    # On utilise < pour rediriger le fichier comme demandé dans le sujet
    $TPCAS < "$file" > /dev/null 2>&1
    local ret=$?

    # Vérification du résultat
    if [ "$type_test" == "GOOD" ]; then
        if [ $ret -eq 0 ]; then
            echo -e "[${GREEN}OK${NC}] $file (Retour: $ret)"
            ((PASSED++))
        else
            echo -e "[${RED}KO${NC}] $file (Attendu: 0, Reçu: $ret)"
        fi
    elif [ "$type_test" == "BAD" ]; then
        if [ $ret -eq 1 ]; then
            echo -e "[${GREEN}OK${NC}] $file (Retour: $ret)"
            ((PASSED++))
        elif [ $ret -eq 0 ]; then
             echo -e "[${RED}KO${NC}] $file (Erreur non détectée ! Attendu: 1, Reçu: 0)"
        else
             # Cas où le code est différent de 0 et 1 (Crash, SegFault, etc)
             echo -e "[${RED}KO${NC}] $file (Crash ou code incorrect ? Attendu: 1, Reçu: $ret)"
        fi
    fi
}

# 4. Exécution des tests valides (Doivent renvoyer 0)
# ---------------------------------------------------
echo -e "${BLUE}=== TESTS VALIDES (Attendu : 0) ===${NC}"
# Vérifie si des fichiers existent pour éviter une erreur de boucle
shopt -s nullglob
files_good=($DIR_GOOD/*.tpc)
if [ ${#files_good[@]} -eq 0 ]; then
    echo "Aucun fichier trouvé dans $DIR_GOOD"
else
    for file in "${files_good[@]}"; do
        run_test "$file" 0 "GOOD"
    done
fi

echo ""

# 5. Exécution des tests invalides (Doivent renvoyer 1)
# -----------------------------------------------------
echo -e "${BLUE}=== TESTS ERRONÉS (Attendu : 1) ===${NC}"
files_bad=($DIR_BAD/*.tpc)
if [ ${#files_bad[@]} -eq 0 ]; then
    echo "Aucun fichier trouvé dans $DIR_BAD"
else
    for file in "${files_bad[@]}"; do
        run_test "$file" 1 "BAD"
    done
fi

# 6. Bilan et Score
# -----------------
echo -e "\n${BOLD}=== RÉSULTATS ===${NC}"
echo -e "Tests passés : $PASSED / $TOTAL"

if [ $TOTAL -gt 0 ]; then
    SCORE=$(( 100 * PASSED / TOTAL ))
    if [ $PASSED -eq $TOTAL ]; then
        echo -e "Score Global : ${GREEN}$SCORE%${NC} 🎉"
    else
        echo -e "Score Global : ${RED}$SCORE%${NC}"
    fi
else
    echo "Aucun test n'a été exécuté."
fi

# Retourner 0 si tout est OK, 1 sinon (pour l'intégration continue si besoin)
if [ $PASSED -eq $TOTAL ] && [ $TOTAL -gt 0 ]; then
    exit 0
else
    exit 1
fi