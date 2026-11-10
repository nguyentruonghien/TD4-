/* Exemple guide : lire la cible d'un lien symbolique avec lstat() et readlink() */
#include <limits.h>   /* PATH_MAX */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	struct stat st;
	char cible[PATH_MAX + 1];            /* +1 : place du '\0', que readlink n'ecrit PAS */

	if (argc != 2) {
		fprintf(stderr, "usage : %s lien\n", argv[0]);
		return EXIT_FAILURE;
	}
	if (lstat(argv[1], &st) == -1) {     /* lstat : decrit le lien lui-meme (stat decrirait sa cible) */
		perror(argv[1]);
		return EXIT_FAILURE;
	}
	if (!S_ISLNK(st.st_mode)) {
		printf("%s n'est pas un lien symbolique\n", argv[1]);
		return EXIT_SUCCESS;
	}
	ssize_t n = readlink(argv[1], cible, sizeof(cible) - 1);
	if (n == -1) {
		perror("readlink");
		return EXIT_FAILURE;
	}
	cible[n] = '\0';                     /* on termine la chaine nous-memes */
	printf("%s -> %s\n", argv[1], cible);
	return EXIT_SUCCESS;
}
