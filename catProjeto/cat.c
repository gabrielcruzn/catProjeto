#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
}

void print_stdin() {
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), stdin)) {
        printf("%s", buffer);
    }
}

void print_with_line_numbers(const char *filename, int include_blank) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char buffer[1024];
    int line_number = 1;
    while (fgets(buffer, sizeof(buffer), file)) {
        if (include_blank || strlen(buffer) > 1) { 
            printf("%6d  %s", line_number++, buffer);
        } else {
            printf("%s", buffer);
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    int line_number_mode = 0; 

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            line_number_mode = 1;
        } else if (strcmp(argv[i], "-b") == 0) {
            line_number_mode = 2;
        } else if (argv[i][0] == '-') {
            fprintf(stderr, "Opção desconhecida: %s\n", argv[i]);
            return 1;
        }
    }

    if (argc == 1 || (argc == 2 && (line_number_mode != 0))) {
        print_stdin();
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "-b") == 0) {
            continue; 
        }

        if (line_number_mode == 0) {
            print_file(argv[i]);
        } else {
            print_with_line_numbers(argv[i], line_number_mode == 2);
        }
    }

    return 0;
}
