/* Exemple guide : lire les noms contenus dans un repertoire avec opendir/readdir */
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	const char *dossier = (argc > 1) ? argv[1] : ".";
	DIR *d = opendir(dossier);

	if (d == NULL) {
		perror(dossier);
		return EXIT_FAILURE;
	}
	for (;;) {
		errno = 0;                        /* readdir retourne NULL a la fin ET en cas d'erreur : errno les distingue */
		struct dirent *e = readdir(d);
		if (e == NULL)
			break;
		printf("%s\n", e->d_name);        /* contient aussi "." et ".." */
	}
	if (errno != 0)
		perror(dossier);
	closedir(d);
	return EXIT_SUCCESS;
}
