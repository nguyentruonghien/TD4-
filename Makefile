# Makefile des TD : « make nom » compile nom.c en l'executable nom, avec les options strictes du cours.
# (regle implicite de make : $(CC) $(CFLAGS) nom.c -o nom)
CC     = gcc
CFLAGS = -std=c11 -D_XOPEN_SOURCE=700 -Wall -Wextra -Werror -pedantic -g

# « make clean » supprime les executables (tout fichier .c qui a un executable du meme nom)
clean:
	rm -f $(basename $(wildcard *.c))
