
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// set up buffer

typedef struct {
    char * buffer;
    size_t buffer_length; // size_t is used to represent the size of an allocated block of memory
    ssize_t input_length; //ssize_t is the same size_t but signed, we can represent the number -1
} InputBuffer;

// read a line of input
ssize_t getline(char**lineptr, size_t * n, FILE *stream);

void print_prompt() {  printf("database>");}

void read_input(InputBuffer* input_buffer) {
    ssize_t bytes_read = getline(&(input_buffer -> buffer), &(input_buffer -> buffer_length), stdin); // standard input

    if(bytes_read <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    input_buffer -> input_length = bytes_read -1;
    input_buffer -> buffer[bytes_read -1] = 0;

}

void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer -> buffer);
    free(input_buffer);
}

InputBuffer * new_input_buffer() {
    InputBuffer * inputBuffer = (InputBuffer*) malloc(sizeof(InputBuffer));
    inputBuffer->buffer = NULL;
    inputBuffer->buffer_length = 0;
    inputBuffer->input_length = 0;

    return inputBuffer;
}



int main(int argc, char* argv[]) {
    InputBuffer* input_buffer = new_input_buffer();
    while(true) {
        print_prompt();
        read_input(input_buffer);

        if(strcmp(input_buffer -> buffer, ".exit") == 0) {
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        }  else {
            printf("Unrecognized command '%s' .\n", input_buffer-> buffer);;
        }
    }
}



