

// #include <stdlib.h>
// #include <stdio.h>

// //char *getenv(const char *name);
// // printenv PATH
// // get value from environment variable
// int main()
// {
//     char *str = getenv("PATH");
//     printf("%s\n",str);
//     return 0;
// }




//execve : execute new program in the current process  with newly initialize stack, heap, and data segment
// int execve(const char *pathname, char *const _Nullable argv[], char *const _Nullable envp[]);
#include <unistd.h>
#include <stdio.h>

int main()
{
    char *args[] = {"./test.sh", "+x","test.sh", NULL};
    char *envp[] = {"fin=foo", "fin2=baz", NULL};
    // if (execve("/usr/bin/chmod", args, NULL) == -1)
    // {
    //     perror("execve");
    //     return 1;
    // }
    if (execve(args[0], NULL, envp) == -1)
    {
        perror("execve");
        return 1;
    }
    printf("after execve \n");
    return 0;
}


// i need two arrays, one for arguments and one for environment variables