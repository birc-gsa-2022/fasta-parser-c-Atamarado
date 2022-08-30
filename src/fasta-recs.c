#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    //Parsing into DNA chains
    int pos = 0;
    const int length = strlen(content);

    // Find every chain
    while(pos<length){
        //First we have to find '>'
        char c = content[pos];
        while(pos < length && c!='>'){
            pos++;
            c = content[pos];
        }

        // Skip spaces
        while(pos < length && c!=' '){
            pos++;
            c = content[pos];
        }

        // Find the name
        int nameBegin = pos;
        while(pos<length && c!=' ' && c!='\n'){
            pos++;
            c = content[pos];
        }

        char *name = calloc(pos-nameBegin, sizeof(char));
        memcpy(name, &content[nameBegin], pos);

        // Find the chain
        int nChain = 0;
        int chainBegin = pos;
        while(pos<length && c!='>'){
            if(c!=' ' && c!='\n'){
                nChain++;
            }

            pos++;
            c = content[pos];
        }

        printf("%s ",name);

        for(int i=0; i<pos-chainBegin && nChain>0; i++){
            char c = content[chainBegin+i];
            if(c!=' ' && c!='\n'){
                printf("%c", c);
                nChain--;
            }
        }

        printf("\n");
    }


    return 1;
}