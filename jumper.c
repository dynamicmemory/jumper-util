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

    for (size_t i = 0; i < directory.count; i++) 
        printf("%s", directory.items[i]);

    free_list(&directory);
    return 0;
}


//
// def main() -> None:
//     if len(sys.argv) != 2:
//         print(f"Usage: {sys.argv[0]} <directory_name>", file=sys.stderr)
//         sys.exit(1)
//
//     jump_to = sys.argv[1]
//     directory_options = []
//
//     for root, dirs, files in os.walk("/"):
//         for d in dirs:
//             if d == jump_to:
//                 directory_options.append(os.path.join(root,d))
//
//     if not directory_options:
//         print(f"No directories named '{jump_to}' found.", file=sys.stderr)
//         sys.exit(1)
//
//     if len(directory_options) == 1:
//         print(directory_options[0])
//         return 
//
//     print("Pick which directory you want:", file=sys.stderr)
//     for idx, option in enumerate(directory_options, 1):
//         print(f"{idx}) {option}", file=sys.stderr)
//
//     while True:
//         try:
//             print("Enter selection: ", end='', file=sys.stderr)
//             choice = input()
//             index = int(choice) - 1
//             if 0 <= index < len(directory_options):
//                 print(directory_options[index])
//                 return 
//             else:
//                 print(f"Invalid selection. Enter a number between 1 and {len(directory_options)}.", file=sys.stderr)
//         except ValueError:
//             print("Please enter a vliad number.", file=sys.stderr) 
