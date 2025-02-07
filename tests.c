#include <stdio.h>
#include "./libft/libft.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>

char *get_path(char *arg, char **envp);
void print_error(char *error_message, char *info);
char **free_matrix(char **m);

void handle_close(int fd[2], int in_out_fd, int exit_code)
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
	if (in_out_fd != -1)
		close(in_out_fd);
	if (exit_code != 0)
		exit(exit_code);
}

void child_process_1_helper(char **av, int fd[2], int infd)
{
	if (infd == -1)
	{
		print_error(strerror(errno), av[1]);
		handle_close(fd, infd, 1);
	}
	if (dup2(infd, STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
		(print_error(strerror(errno), av[1]), handle_close(fd, infd, 1));
}

void child_process_2_helper(char **av, int fd[2], int outfd)
{
	if (outfd == -1)
	{
		print_error(strerror(errno), av[4]);
		handle_close(fd, outfd, 1);
	}
	if (dup2(outfd, STDOUT_FILENO) == -1 || dup2(fd[0], STDIN_FILENO) == -1)
		(print_error(strerror(errno), av[4]), handle_close(fd, outfd, 1));
}

void child_process_1(char **av, char **env, int fd[2])
{
	int infd;
	char **args;
	char *path;

	infd = open(av[1], O_RDONLY);
	child_process_1_helper(av, fd, infd);
	args = ft_split(av[2], ' ');
	if (!args)
		handle_close(fd, infd, 1);
	path = get_path(args[0], env);
	if (!path)
	{
		print_error("command not found", args[0]);
		free_matrix(args);
		handle_close(fd, infd, 127);
	}
	close(fd[0]);
	execve(path, args, env);
	print_error(strerror(errno), args[0]);
	free_matrix(args);
	free(path);
	handle_close(fd, infd, 127);
}

void child_process_2(char **av, char **env, int fd[2])
{
	int infd;
	char **args;
	char *path;

	infd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	child_process_2_helper(av, fd, infd);
	args = ft_split(av[3], ' ');
	if (!args)
		handle_close(fd, infd, 1);
	path = get_path(args[0], env);
	if (!path)
	{
		print_error("command not found", args[0]);
		free_matrix(args);
		handle_close(fd, infd, 127);
	}
	close(fd[1]);
	execve(path, args, env);
	print_error(strerror(errno), args[0]);
	free_matrix(args);
	free(path);
	handle_close(fd, infd, 127);
}

void f()
{
	system("lsof -c pipex");
}

int main(int ac, char **av, char **env)
{
	int fd[2];
	pipe(fd);

	if (ac != 5)
		return 1;

	// atexit(f);

	int pid = fork();
	if (pid == 0)
		child_process_1(av, env, fd);
	int status;
	int pid2 = fork();
	if (pid2 == 0)
		child_process_2(av, env, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, &status, 0);
	waitpid(pid2, &status, 0);
	if (status == 0)
		return 0;
	return (WEXITSTATUS(status));
}
