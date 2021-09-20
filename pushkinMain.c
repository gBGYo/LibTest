//https://rosettacode.org/wiki/Call_a_function_in_a_shared_library#C

#define _XOPEN_SOURCE 500
#include <dlfcn.h> 
#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>

int WalkThroughFileTree(const char *fpath, const struct stat *sb, 
                         int typeflag, struct FTW *ftwbuf)
{
    void *handle;
    char *(*pushkin)(char*);

    handle = dlopen("./libpushkin.so", RTLD_LAZY);
    if ( handle == NULL ) {
        fprintf(stderr, "Ошибка загрузки библиотеки: %s\n", dlerror());
        return -1;
    }
 
    pushkin = (char *(*)(char*)) dlsym(handle, "puskin");

    if ( pushkin != NULL ) {
        char *text = NULL;
	    text = pushkin(text);
    } else {
	    fprintf(stderr, "Ошибка получения функции: %s\n", dlerror());
    }
    
    dlclose(handle);
    return  ( pushkin == NULL ) ? (-1) : (0);
}

int main(int argc, char *argv[])
{
    if ( nftw(".", WalkThroughFileTree, 10, 0) == -1 ) {
        fprintf(stderr, "nftw -- error occured!\n");
        exit(1);
    }

    return EXIT_SUCCESS;
}
