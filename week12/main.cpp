#include <stdio.h>
#include <string.h>

void print_p_and_x(char* p, int x) {
    printf("p is \"%s\" and x is %i\n", p, x);
}

int main() {

    const char hello_str[] = "Hello";
    const char world_str[] = "World!";

    // minus 2 \0 null sentinel chars plus the ' ' char and a \0 sentinel so 0 in total
    char concatenated[sizeof(hello_str) + sizeof(world_str)];
    strcpy(concatenated, hello_str);

    char* end = concatenated + sizeof(hello_str) - 1;
    *end = ' ';
    strcpy(end + 1, world_str);
    
    // print final string
    printf("%s\n", concatenated);
    print_p_and_x("test", 5);

    return 0;
}