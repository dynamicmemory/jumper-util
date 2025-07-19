#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAXPATH 4096

typedef struct {
    char **items;
    size_t count;
    size_t capacity;
} PathList;

void init_list(PathList *list) {
    list->count = 0;
    list->capacity = 10;
    list->items = malloc(sizeof(char*) * list->capacity);
}

void add_to_list(PathList *list, const char *path) {
    if (list->count >= list->capacity) {
        list->capacity *= 2;
        list->items = realloc(list->items, sizeof(char*) * list->capacity);
    }
    list->items[list->count++] = strdup(path);
}

void free_list(PathList *list) {
    for (size_t i = 0; i < list->count; i++) {
         free(list->items[i]);
    }
    free(list->items);
}


void walk_dir(const char *base_path, const char *jump_to, PathList *results) {
    DIR *dir = opendir(base_path);
    if (!dir) {
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char path[MAXPATH];
        snprintf(path, sizeof(path), "%s/%s", base_path, entry->d_name);
        
        struct stat statbuf;
        if (stat(path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
            if (strcmp(entry->d_name, jump_to) == 0) 
                add_to_list(results, path);
            walk_dir(path, jump_to, results);
        }
    }
    closedir(dir);
}


int main(int argc, char *argv[]) {
    
    if (argc != 2)
        fprintf(stderr, "Usage: %s <directory_name>\n", argv[0]);

    char *jump_to = argv[1];
    PathList directory;
    init_list(&directory);

    walk_dir("/home/lenny", jump_to, &directory);

    if (directory.count == 0) {
        printf("No directories named %s found.", jump_to);
        free_list(&directory);
        return 0;
    }

    if (directory.count == 1) {
        printf("%s", directory.items[0]);
        free_list(&directory);
        return 0;
    }

    fprintf(stderr, "Pick which directory you want:\n");
    for(size_t i = 0; i < directory.count; i++){
        fprintf(stderr, "%zu) %s\n", i + 1, directory.items[i]);
    }

    while (1) {
        fprintf(stderr, "Enter selection: ");
        char buf[16];
        if (!fgets(buf, sizeof(buf), stdin)) {
            fprintf(stderr, "Error reading input.\n");
            continue;
        }
        char *endptr;
        long choice = strtol(buf, &endptr, 10);
        if (endptr == buf || *endptr != '\n') {
            fprintf(stderr, "please enter a valid number.\n");
            continue;
        }
        if (choice >= 1 && choice <= (long)directory.count) {
            printf("%s", directory.items[choice - 1]);
            break;
        }
        else 
            fprintf(stderr, "Invalid selection. Enter a number between 1 and %zu.\n", directory.count);
    }

    free_list(&directory);
    return 0;
}
