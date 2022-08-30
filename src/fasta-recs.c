#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
 * 'slurp' reads the file identified by 'path' into a character buffer
 * pointed at by 'buf', optionally adding a terminating NUL if
 * 'add_nul' is true. On success, the size of the file is returned; on
 * failure, -1 is returned and ERRNO is set by the underlying system
 * or library call that failed.
 *
 * WARNING: 'slurp' malloc()s memory to '*buf' which must be freed by
 * the caller.
 */
long slurp(char const* path, char **buf, bool add_nul)
{
    FILE  *fp;
    size_t fsz;
    long   off_end;
    int    rc;

    /* Open the file */
    fp = fopen(path, "rb");
    if( NULL == fp ) {
        return -1L;
    }

    /* Seek to the end of the file */
    rc = fseek(fp, 0L, SEEK_END);
    if( 0 != rc ) {
        return -1L;
    }

    /* Byte offset to the end of the file (size) */
    if( 0 > (off_end = ftell(fp)) ) {
        return -1L;
    }
    fsz = (size_t)off_end;
    printf("a\n");

    /* Allocate a buffer to hold the whole file */
    *buf = malloc( fsz+(int)add_nul );
    if( NULL == *buf ) {
        return -1L;
    }
    printf("a\n");

    /* Rewind file pointer to start of file */
    rewind(fp);

    /* Slurp file into buffer */
    if( fsz != fread(*buf, 1, fsz, fp) ) {
        free(*buf);
        return -1L;
    }
    
    /* Close the file */
    if( EOF == fclose(fp) ) {
        free(*buf);
        return -1L;
    }

    if( add_nul ) {
        /* Make sure the buffer is NUL-terminated, just in case */
        buf[fsz] = '\0';
    }

    /* Return the file size */
    return (long)fsz;
}

int main(int argc, char const *argv[])
{
    printf("Holis\n");
    if (argc != 2)
    {
        fprintf(stderr, "Usage: fasta-recs fasta-file\n");
        return 1;
    }

    const char *fasta_fname = argv[1];
    char **pContent;
    printf("Holis\n");
    long fileSize = slurp(fasta_fname, pContent, 1);
    printf("Holis\n");
    if(fileSize<0){
        fprintf(stderr, "Error while reading the file\n");
        exit(2);
    }
    char *content = *pContent;

    //Parsing into DNA chains
    int pos = 0;

    char c = content[pos];

    // Find every chain
    while(c!='\0'){
        //First we have to find '>'
        while(c!='\0' && c!='>'){
            pos++;
            c = content[pos];
        }

        // Skip spaces
        while(c!='\0' && c!=' '){
            pos++;
            c = content[pos];
        }

        // Find the name
        int nameBegin = pos;
        while(c!='\0' && c!=' ' && c!='\n'){
            pos++;
            c = content[pos];
        }

        char *name;
        free(name);
        name = malloc(pos-nameBegin);
        memcpy(name, &content[nameBegin], pos);

        // Find the chain
        int nChain = 0;
        int chainBegin = pos;
        while(c!='\0' && c!='>'){
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

    free(pContent);

    return 1;
}