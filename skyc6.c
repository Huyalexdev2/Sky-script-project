#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VARS 100
#define MAX_FUNCS 100
#define MAX_LINES 1000

// Struct to hold variable and value pairs
typedef struct {
    char var_name[50];
    char value[50];
} Variable;

Variable variables[MAX_VARS];
int var_count = 0;

// Struct to hold function definitions
typedef struct {
    char func_name[50];
    char func_body[MAX_LINES][100];
    int line_count;
} Function;

Function functions[MAX_FUNCS];
int func_count = 0;

// Function prototypes
void assign_variable(char* line);
void show(char* line);
void define_function(char* lines[], int* i);
void handle_if(char* lines[], int* i);
void handle_for(char* lines[], int* i);
void handle_while(char* lines[], int* i);
void input_variable(char* line);
void call_function(char* line);
void interpret(char* lines[], int line_count);
void run_sky_code(const char* file_path);
void print(char* line); // Prototype for the print function

// Additional prototypes for new features
void handle_try_except(char* lines[], int* i);
void handle_loop_control(char* lines[], int* i);
void handle_list_and_string_methods(char* line);
void handle_dict_methods(char* line);
void handle_object_and_class(char* line);
void handle_async_await(char* line);
void handle_file_operations(char* line);
void handle_datetime_operations(char* line);
void handle_byte_operations(char* line);
void handle_special_methods(char* line);
void handle_data_types(char* line);

void interpret(char* lines[], int line_count) {
    for (int i = 0; i < line_count; i++) {
        char* line = lines[i];
        if (strncmp(line, "va ", 3) == 0) {
            assign_variable(line);
        } else if (strncmp(line, "show ", 5) == 0) {
            show(line);
        } else if (strncmp(line, "func ", 5) == 0) {
            define_function(lines, &i);
        } else if (strncmp(line, "if ", 3) == 0) {
            handle_if(lines, &i);
        } else if (strncmp(line, "for ", 4) == 0) {
            handle_for(lines, &i);
        } else if (strncmp(line, "while ", 6) == 0) {
            handle_while(lines, &i);
        } else if (strncmp(line, "input ", 6) == 0) {
            input_variable(line);
        } else if (strncmp(line, "print ", 6) == 0) {
            print(line);
        } else if (strncmp(line, "try ", 4) == 0) {
            handle_try_except(lines, &i);
        } else if (strncmp(line, "loop ", 5) == 0) {
            handle_loop_control(lines, &i);
        } else if (strncmp(line, "list_method ", 12) == 0 || strncmp(line, "string_method ", 14) == 0) {
            handle_list_and_string_methods(line);
        } else if (strncmp(line, "dict_method ", 12) == 0) {
            handle_dict_methods(line);
        } else if (strncmp(line, "class ", 6) == 0) {
            handle_object_and_class(line);
        } else if (strncmp(line, "async ", 6) == 0) {
            handle_async_await(line);
        } else if (strncmp(line, "file_op ", 8) == 0) {
            handle_file_operations(line);
        } else if (strncmp(line, "datetime ", 9) == 0) {
            handle_datetime_operations(line);
        } else if (strncmp(line, "byte_op ", 8) == 0) {
            handle_byte_operations(line);
        } else if (strncmp(line, "special_method ", 15) == 0) {
            handle_special_methods(line);
        } else if (strncmp(line, "data_type ", 10) == 0) {
            handle_data_types(line);
        } else {
            call_function(line);
        }
    }
}

void assign_variable(char* line) {
    char var_name[50], value[50];
    if (sscanf(line, "va %s to %s", var_name, value) == 2) {
        strcpy(variables[var_count].var_name, var_name);
        strcpy(variables[var_count].value, value);
        var_count++;
    } else {
        printf("Error in variable assignment.\n");
    }
}

void show(char* line) {
    char var_name[50];
    if (sscanf(line, "show %s", var_name) == 1) {
        for (int i = 0; i < var_count; i++) {
            if (strcmp(variables[i].var_name, var_name) == 0) {
                printf("%s\n", variables[i].value);
                return;
            }
        }
        printf("Variable %s not found.\n", var_name);
    } else {
        printf("Error in show command.\n");
    }
}

void define_function(char* lines[], int* i) {
    char func_name[50];
    if (sscanf(lines[*i], "func %s", func_name) == 1) {
        strcpy(functions[func_count].func_name, func_name);
        (*i)++;
        int line_count = 0;
        while (strcmp(lines[*i], "end") != 0) {
            strcpy(functions[func_count].func_body[line_count], lines[*i]);
            line_count++;
            (*i)++;
        }
        functions[func_count].line_count = line_count;
        func_count++;
    } else {
        printf("Error in function definition.\n");
    }
}

void handle_if(char* lines[], int* i) {
    char condition[50];
    if (sscanf(lines[*i], "if %s", condition) == 1) {
        // Just as an example, assume condition is always true
        (*i)++;
        while (strcmp(lines[*i], "end") != 0) {
            interpret(&lines[*i], 1);
            (*i)++;
        }
    } else {
        printf("Error in if statement.\n");
    }
}

void handle_for(char* lines[], int* i) {
    char var_name[50];
    int start, end;
    if (sscanf(lines[*i], "for %s in range(%d, %d)", var_name, &start, &end) == 3) {
        for (int j = start; j <= end; j++) {
            sprintf(variables[var_count].var_name, "%s", var_name);
            sprintf(variables[var_count].value, "%d", j);
            var_count++;
            (*i)++;
            while (strcmp(lines[*i], "end") != 0) {
                interpret(&lines[*i], 1);
                (*i)++;
            }
        }
    } else {
        printf("Error in for loop.\n");
    }
}

void handle_while(char* lines[], int* i) {
    char condition[50];
    if (sscanf(lines[*i], "while %s", condition) == 1) {
        // Assume condition is always true for simplicity
        (*i)++;
        while (strcmp(lines[*i], "end") != 0) {
            interpret(&lines[*i], 1);
            (*i)++;
        }
    } else {
        printf("Error in while loop.\n");
    }
}

void input_variable(char* line) {
    char var_name[50];
    if (sscanf(line, "input %s", var_name) == 1) {
        char value[50];
        printf("Enter value for %s: ", var_name);
        scanf("%s", value);
        strcpy(variables[var_count].var_name, var_name);
        strcpy(variables[var_count].value, value);
        var_count++;
    } else {
        printf("Error in input command.\n");
    }
}

void call_function(char* line) {
    char func_name[50];
    sscanf(line, "%s", func_name);
    for (int i = 0; i < func_count; i++) {
        if (strcmp(functions[i].func_name, func_name) == 0) {
            interpret(functions[i].func_body, functions[i].line_count);
            return;
        }
    }
    printf("Function %s not found.\n", func_name);
}

void print(char* line) {
    char var_name[50];
    if (sscanf(line, "print %s", var_name) == 1) {
        for (int i = 0; i < var_count; i++) {
            if (strcmp(variables[i].var_name, var_name) == 0) {
                printf("%s\n", variables[i].value);
                return;
            }
        }
        printf("Variable %s not found.\n", var_name);
    } else {
        printf("Error in print command.\n");
    }
}

void run_sky_code(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", file_path);
        return;
    }

    char* read_file(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if (!file) {
        printf("Error opening file: %s\n", file_path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = (char*)malloc(file_size + 1);
    if (!content) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // Null-terminate the string
    fclose(file);
    return content;
}

void free_memory() {
    // Giải phóng bộ nhớ cho các biến và hàm đã định nghĩa
    for (int i = 0; i < var_count; i++) {
        free(variables[i].var_name);
        free(variables[i].value);
    }
    for (int i = 0; i < func_count; i++) {
        free(functions[i].func_name);
        for (int j = 0; j < functions[i].line_count; j++) {
            free(functions[i].func_body[j]);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <sky_code_file>\n", argv[0]);
        return 1;
    }

    char* code_content = read_file(argv[1]);
    if (code_content == NULL) {
        return 1;
    }

    char* lines[MAX_LINES];
    char* line = strtok(code_content, "\n");
    int line_count = 0;

    while (line != NULL) {
        lines[line_count] = strdup(line);
        line_count++;

        // Kiểm tra xem số lượng dòng đã đạt đến giới hạn tối đa chưa
        if (line_count >= MAX_LINES) {
            printf("Error: Exceeded maximum line count of %d.\n", MAX_LINES);
            break; // Thoát khỏi vòng lặp nếu vượt quá giới hạn
        }

        line = strtok(NULL, "\n");
    }

    interpret(lines, line_count);

    // Giải phóng bộ nhớ đã cấp phát
    for (int i = 0; i < line_count; i++) {
        free(lines[i]);
    }
    free(code_content);
    free_memory();

    return 0;
}
