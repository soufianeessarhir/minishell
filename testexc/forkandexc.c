


#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    pid_t mypid;
    pid_t childpid;

    childpid = fork();
    if (childpid == -1)
    {
        perror("fork");
        return 1;
    }
    mypid = getpid();
    if (childpid > 0)
    {
        wait(NULL);
        printf("i am in parent\n");
        printf("parent pid = %d\n", mypid);
    }
    if (childpid == 0)
    {
        sleep(5);
        printf("i am childpid\n");
        printf("childpid = %d\n", mypid);
        sleep(5);
        return 0;
    }
    

    
}
