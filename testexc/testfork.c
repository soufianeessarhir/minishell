#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

static char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		return (strdup(s1));
	if (!s1)
		return (strdup(s2));
	i = 0;
	j = 0;
	str = malloc(strlen(s2) + strlen(s1) + 1);
	if (!str)
		return (NULL);
	while (i < strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	while (j < strlen(s2))
		str[i++] = s2[j++];
	str[i] = '\0';
	return ((char *)str);
}

int main(int argc, char *argv[])
{
    pid_t childpid;

    if (argc != 2)
    {
        printf("error in argument\n");
        return 1;
    }
    (void)argc;
    childpid = fork();
    if (childpid == -1)
    {
        perror("fork");
        return 1;
    }
    char *args[] = {"/usr/bin/chmod", "+x", argv[1], NULL};
    char *envp[] = {"fin=foo", "fin2=baz", NULL};

    if (childpid > 0)
    {
        wait(NULL);
        if (execve(ft_strjoin("./",argv[1]), NULL, envp) == -1)
        {
            perror("execve");
            return 1;
        }
    }
    if (childpid == 0)
    {
        if (execve(args[0], args, NULL) == -1)
        {
            perror("execve");
            return 1;
        }
        sleep(5);
        return 0;
    }
    return 0;
}

