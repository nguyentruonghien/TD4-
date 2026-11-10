/* Exemple guide : parcours recursif d'une arborescence (affichage indente, sans suivre les liens symboliques) */
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

static void parcourir(const char *dossier, int niveau)
{
	DIR *d = opendir(dossier);

	if (d == NULL) {
		perror(dossier);               /* on signale et on CONTINUE (le parcours n'est pas interrompu) */
		return;
	}
	for (struct dirent *e = readdir(d); e != NULL; e = readdir(d)) {
		if (strcmp(e->d_name, ".") == 0 || strcmp(e->d_name, "..") == 0)
			continue;                  /* sinon : boucle infinie */
		char chemin[PATH_MAX + 1];
		if (snprintf(chemin, sizeof(chemin), "%s/%s", dossier, e->d_name) >= (int)sizeof(chemin)) {
			fprintf(stderr, "chemin trop long : %s/%s\n", dossier, e->d_name);
			continue;
		}
		printf("%*s%s\n", 2 * niveau, "", e->d_name);
		struct stat st;
		if (lstat(chemin, &st) == 0 && S_ISDIR(st.st_mode))   /* lstat : un lien vers un dossier n'est PAS suivi */
			parcourir(chemin, niveau + 1);                    /* appel recursif */
	}
	closedir(d);
}

int main(int argc, char *argv[])
{
	parcourir((argc > 1) ? argv[1] : ".", 0);
	return EXIT_SUCCESS;
}
