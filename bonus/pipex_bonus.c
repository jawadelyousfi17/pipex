#include "../libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
char *get_path(char *arg, char **envp);

void child_process(char *path, char *arg, char **env, int fdin[2], int fdout[2])
{
	close(fdin[0]);
	close(fdout[1]);
	fdin[0] = dup(0);
	fdout[1] = dup(1);
    fprintf(stderr , "fdin = %d\nfdout = %", fdin[0]);
	execve(path, ft_split(arg, ' '),env);
	exit(0);
}

int main(int ac, char **av, char **env)
{
	int i = 2;
	int pid;
	int fd[2][2];

	
	i = 2;
	while (i < ac - 1)
	{
		int pid = fork();
		pipe(fd[(i % 2) ^ 1]);
		if (pid == 0)
		{
			if (i == 2) fd[0][0] = open(av[2], O_RDONLY);
			else if (i == ac - 1 ) fd[(i % 2) ^ 1][1] = open(av[ac - 1], O_RDWR);
			child_process(get_path(av[i], env), av[i], env, fd[i % 2] ,fd[(i % 2) ^ 1]);
		}
		waitpid(pid, NULL, 0);
		i++;
	}
}