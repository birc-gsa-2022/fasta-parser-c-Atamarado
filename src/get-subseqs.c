#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    if (argc < 2 || argc > 3)
    {
        fprintf(stderr, "Usage: fasta-recs fasta-file [coordinates]\n");
        return 1;
    }

    const char *fasta_fname = argv[1];
    printf("I should be parsing %s now, but someone forgot to implement that.\n",
           fasta_fname);

    FILE *coordf = (argc < 3 || (strcmp(argv[2], "-") == 0))
                       ? stdin
                       : fopen(argv[2], "r");
    if (!coordf)
    {
        fprintf(stderr, "Couldn't open coordinates file.\n");
        perror("Open error");
        return 1;
    }
    printf("I was supposed to read coordinates now, but I forgot.\n");

    fclose(coordf);

    return 1;
}