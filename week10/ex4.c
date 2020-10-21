#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

const char *directory;
unsigned long long dir_length;

// This method is called only when the number of links is more than or equal to 2.
void printAllFilesLinkedTo(char* file, int i_node, int num_links){
    printf("The file '%s', whose inode is %d, is linked with %d files: ", file, i_node, num_links);

    DIR *dirp1 = opendir(directory);

    char file_path[300];
    strcpy(file_path, directory);
    file_path[dir_length] = '/';

    struct dirent *dp;
    struct stat stat_struct;
    while((dp = readdir(dirp1)) != NULL){
        if(strcmp(dp->d_name, ".") == 0) continue;
        if(strcmp(dp->d_name, "..") == 0) continue;
        strcpy(file_path + dir_length + 1, dp->d_name);
        int ok = stat(file_path, &stat_struct);
        if (ok == -1){
            printf("Error!");
            continue;
        }

        // We should only consider files which have the i-node value as the given file.
        if(stat_struct.st_ino == i_node){
            printf("%s ", dp->d_name);
        }
    }
    printf("\n");
}

int main() {
    directory = "/home/hash/week10/tmp";
    dir_length = strlen(directory);

    unsigned long long max_size = dir_length + 1 + NAME_MAX;
    char file_path[max_size];
    struct stat stat_struct;
    struct dirent *dp;

    strcpy(file_path, directory);
    file_path[dir_length] = '/';
    DIR *dirp = opendir(directory);

    while ((dp = readdir(dirp)) != NULL){

        // If the name of the file is "." or "..", we shouldn't consider it.
        if(strcmp(dp->d_name, ".") == 0) continue;
        if(strcmp(dp->d_name, "..") == 0) continue;

        // We modify the file_path to make it equal to our current file's path.
        strcpy(file_path + dir_length + 1, dp->d_name);

        // Then we read the file stats and store it in stat_struct.
        int ok = stat(file_path,&stat_struct);

        // If the value is equal to -1, then some error occurred.
        if (ok == -1){
            printf("Error!");
            continue;
        }

        // We need only files which have two or more links.
        if(stat_struct.st_nlink < 2){
            continue;
        }

        // Now (again) we iterate over all files to search for files with inode equal to the current file's.
        printAllFilesLinkedTo(dp->d_name, stat_struct.st_ino, stat_struct.st_nlink);
    }
}
