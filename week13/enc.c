#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_KEY 100
#define MAX_INPUT 256

int main(int argc, const char** argv) {

    char key[MAX_KEY];
    char input[MAX_INPUT];

    int read_bytes = 0;
    int key_index = 0;

    if(argc < 2) {
        printf("no input key\n");
        return 1;
    }
    int key_size = strlen(argv[1]);
    strncpy(key, argv[1], MAX_KEY);

    // while there is input
    while(read_bytes = read(STDIN_FILENO, input, MAX_INPUT)) {

        for(int i = 0; i < read_bytes; i++) {

            // xor input with key
            input[i] = input[i] ^ key[key_index];

            // circular advance
            key_index = (key_index + 1) % key_size;
        }

        write(STDOUT_FILENO, input, read_bytes);
    }

    return 0;
}