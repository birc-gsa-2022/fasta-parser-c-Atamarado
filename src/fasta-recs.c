#include <stdio.h>
#include <stdlib.h>

// Reads a file and puts in a buffer, in an allocated memory space
// https://stackoverflow.com/questions/3747086/reading-the-whole-text-file-into-a-char-array-in-c
char* readFile(const char* filename){
    
    FILE *fp;
    fp = fopen(filename, "r");
    if( !fp ) perror("blah.txt"),exit(1);

    fseek( fp , 0L , SEEK_END);
    long lSize = ftell( fp );
    rewind( fp );

    /* allocate memory for entire content */
    char *buffer = calloc( 1, lSize+1 );
    if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

    /* copy the file into the buffer */
    if( 1!=fread( buffer , lSize, 1 , fp) )
    fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);

    /* do your work here, buffer is a string contains the whole text */

    fclose(fp);
    free(buffer);

    return buffer;

}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: fasta-recs fasta-file\n");
        return 1;
    }

    const char *fasta_fname = argv[1];

    char *content = readFile(fasta_fname);

    printf("%s",content);

    return 1;
}