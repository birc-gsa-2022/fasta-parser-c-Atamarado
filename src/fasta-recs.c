#include <stdio.h>

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: fasta-recs fasta-file\n");
        return 1;
    }

    const char *fasta_fname = argv[1];
    printf("I should be parsing %s now, but someone forgot to implement that.\n",
           fasta_fname);

    return 1;
}