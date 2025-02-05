#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/errno.h>
#include <string.h>
#include "./libft/libft.h"
#include <sys/wait.h>

typedef struct s_args
{
    char *path;
    char **cmd_args;
    int fd[2];
} t_args;

char *extract_path(char *arg, char **envp);
char *get_path(char *arg, char **envp);
char **free_matrix(char **m);
void clean_all(t_args *args, int code);

void handle_error(int fdin_out, int fd[2], int exit_code)
{
    if (fdin_out != -1)
        close(fdin_out);
    close(STDOUT_FILENO);
    close(STDIN_FILENO);
    exit(exit_code);
}

void child_process_1(char **av, char **env, int fd[2])
{
    char *path;
    char **args;

    int fdin = open(av[1], O_RDONLY);
    if (fdin == -1)
    {
        ft_printf("pipex: %s: %s\n", strerror(errno), av[1]);
        handle_error(fdin, fd, 1);
    }
    if (dup2(fdin, STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
    {
        perror("pipex");
        handle_error(fdin, fd, 1);
    }
    close(fd[0]);
    path = get_path(av[2], env);
    if (!path)
        handle_error(fdin, fd, 127);
    args = ft_split(av[2], ' ');
    if (!args)
        (free(path), handle_error(fdin, fd, 1));
    execve(path, args, env);
    free(path);
    free_matrix(args);
    handle_error(fdin, fd, 1);
}

void child_process_2(char **av, char **env, int fd[2])
{
    char *path;
    char **args;

    int fdout = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    path = get_path(av[3], env);
    if (!path)
        handle_error(fdout, fd, 127);
    args = ft_split(av[2], ' ');
    if (!args)
        (free(path), handle_error(fdout, fd, 1));
    if (fdout == -1)
    {
        ft_printf("pipex: %s: %s\n", strerror(errno), av[4]);
        handle_error(fdout, fd, 1);
    }
    if (dup2(fdout, STDOUT_FILENO) == -1 || dup2(fd[0], STDIN_FILENO) == -1)
    {
        perror("pipex");
        handle_error(fdout, fd, 1);
    }
    close(fd[1]);
    execve(path, args, env);
    free(path);
    free_matrix(args);
    handle_error(fdout, fd, 1);
}

void f()
{
    system("lsof -c pipex");
}

int main(int ac, char **av, char **env)
{
    int fd[2];
    int pid;
    int r;

    // atexit(f);

    if (ac != 5 || pipe(fd) == -1)
        return (EXIT_FAILURE);
    pid = fork();
    if (pid == -1)
        return (EXIT_FAILURE);
    if (pid == 0)
        child_process_1(av, env, fd);
    int pid2 = fork();
    if (pid2 == -1)
        return (EXIT_FAILURE);
    if (pid2 == 0)
        child_process_2(av, env, fd);
    close(fd[0]);
    close(fd[1]);
    waitpid(pid2, &r, 0);
    waitpid(pid2, &r, 0);
    return (WEXITSTATUS(r));
}
