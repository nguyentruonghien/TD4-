#!/bin/sh
# Arborescence de test : sous-dossiers, liens (dont un lien vers un dossier parent : piege de la recursivite), nom long
set -eu
rm -rf td-test
mkdir -p td-test/dir/a td-test/dir/b td-test/vide
cd td-test
echo "contenu" > fichier
touch dir/a/filea dir/b/fileb
ln -s fichier lien
ln -s inexistant lien_casse
ln -s .. dir/boucle                    # boucle : dir/boucle -> td-test (suivre ce lien ferait boucler indefiniment)
ln -s dir lien_dossier
mkfifo fifo
touch .cache                            # fichier cache : ls -l ne l'affiche pas
NOM=$(printf 'n%.0s' $(seq 1 200)); touch "dir/$NOM"
mkdir -m 000 interdit 2>/dev/null || true     # dossier sans droits : le programme doit continuer apres l'erreur
echo "arborescence creee dans $(pwd)"
