#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#define BLOCK_SIZE 512
void copy_stdin2stdout();
//------------------------------------------------------------------------------

int main(void) {
  // copy_stdin2stdout();
  grafo *g = le_grafo(stdin);

  if ( !g )

    return 1;

  escreve_grafo(stdout, g);

  return ! destroi_grafo(g);
}

void copy_stdin2stdout()
{
    char buffer[BLOCK_SIZE];
    for(;;) {
        size_t bytes = fread(buffer,  sizeof(char),BLOCK_SIZE,stdin);
        fwrite(buffer, sizeof(char), bytes, stdout);
        fflush(stdout);
        if (bytes < BLOCK_SIZE)
            if (feof(stdin))
                break;
    }

}