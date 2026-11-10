#!/bin/bash

echo "╔══════════════════════════════════╗"
echo "║  Logiciel de traitement d'image  ║"
echo "╚══════════════════════════════════╝"
echo ""


# demander le chemin 
read -p "Entrez le chemin de votre image PGM : " chemin 

#verification sécurité

if [ ! -f "$chemin" ]; then
    echo "╔══════════════════════════════════════════════╗"
    echo "║  Erreur : le fichier '$chemin' n'existe pas !║"
    echo "╚══════════════════════════════════════════════╝"
    exit 1
fi 

#verifier que c est un pgm 

if [[ "$chemin" != *.pgm ]]; then
    echo "╔══════════════════════════════════════════╗"
    echo "║  Erreur : le fichier doit etre un .pgm ! ║"
    echo "╚══════════════════════════════════════════╝"
    exit 1
fi

# Lancer le programme

echo ""
echo "╔══════════════════════════╗"
echo "║  Chargement de l'image   ║"
echo "╚══════════════════════════╝"
echo ""
./projet_image "$chemin"