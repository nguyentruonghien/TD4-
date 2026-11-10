/* TD4, exercices 2 et 3 : squelette de lister_dossier() (a integrer dans votre mon_ls.c du TD 3) */
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

static int recursif = 0;                 /* option -R */

/* ETAPE A : construit "dossier/nom" dans out (taille octets) ; -1 si le resultat ne tient pas (snprintf !) */
static int joindre(char *out, size_t taille, const char *dossier, const char *nom)
{
	(void)out; (void)taille; (void)dossier; (void)nom;
	return -1;
}

static int comparer(const void *a, const void *b)
{
	return strcmp(*(char *const *)a, *(char *const *)b);
}

static int lister_dossier(const char *dossier)
{
	DIR *d = opendir(dossier);
	if (d == NULL) { perror(dossier); return -1; }

	/* ETAPE B : lire TOUS les noms (sauf ceux qui commencent par '.') dans un tableau dynamique
	             (realloc par doublement de capacite, strdup de chaque nom ; errno = 0 avant chaque readdir)  */
	char **noms = NULL;
	size_t nb = 0;

	/* ETAPE C : trier avec qsort(noms, nb, sizeof(*noms), comparer)  -- seulement si nb > 1 !               */
	(void)comparer;

	/* ETAPE D : pour chaque nom : joindre -> lstat -> afficher (votre print_stat du TD 3)                    */

	/* ETAPE E : si recursif, rappeler lister_dossier sur chaque sous-dossier (S_ISDIR apres lstat)           */
	(void)recursif;

	closedir(d);
	for (size_t i = 0; i < nb; i++) free(noms[i]);
	free(noms);
	return 0;
}

int main(int argc, char *argv[])
{
	/* ETAPE F : reconnaitre l'option -R (argv[1]) puis appeler lister_dossier sur chaque dossier */
	(void)argc; (void)argv; (void)lister_dossier;
	return EXIT_SUCCESS;
}
