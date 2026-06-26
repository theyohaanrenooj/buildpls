#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    // main directory
    char *homedir = getpwuid(getuid())->pw_dir;
    char *main = "/.buildpls/";
    char *mainpath = malloc(strlen(homedir) + strlen(main) + 1);
    strcpy(mainpath,homedir);
    strcat(mainpath,main);

    struct dirent *listing;
    DIR *maindr;
    maindr = opendir(mainpath);
    if (maindr!=NULL) {
        // checking all language listings
        while ((listing = readdir(maindr)) != NULL) {
            if (argc > 2 && strcmp(argv[1], listing->d_name)==0) {

                // allocating memory for string operations
                char *res = malloc(strlen("cp -r ") + strlen(mainpath) + strlen(listing->d_name) + strlen(" ") + strlen(argv[2]) + 1);

                strcpy(res, "cp -r ");
                strcat(res, mainpath);
                strcat(res, listing->d_name);
                strcat(res, " ");
                strcat(res, argv[2]);

                // copying the files over
                system(res);
                printf("All good, project %s made successfully!\n", argv[2]);

                // freeing memory
                free(res);
                free(mainpath);
                res = NULL;
                mainpath = NULL;
            }
        }
        closedir(maindr);
    } else {
        printf("Main Directory not found\n");
    }
    return 0;
}
