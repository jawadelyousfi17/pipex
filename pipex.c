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

void child_process(char **argv, char **envp, t_args *args, int fd[2])
{
    int fd_in;

    if (!args->path || !args->cmd_args)
        exit(127);
    fd_in = open(argv[1], O_RDWR);
    if (fd_in < 0)
    {
        ft_printf("pipex: %s: %s\n", strerror(errno), argv[1]);
        close(fd[0]);
        close(fd[1]);
        exit(2);
    }
    close(fd[0]);
    if (dup2(fd[1], STDOUT_FILENO) == -1 || dup2(fd_in, STDIN_FILENO) == -1)
    {
        perror("pipex");
        close(fd[0]);
        close(fd[1]);
        exit(2);
    }
    if (execve(args->path, args->cmd_args, envp) == -1)
    {
        perror("pipex");
        close(fd[0]);
        close(fd[1]);
        exit(127);
    }
}

void child_process_1(char **argv, char **envp, t_args *args, int fd[2])
{
    int fd_out;

    if (!args->path || !args->cmd_args)
        exit(127);
    fd_out = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (fd_out < 0)
    {
        ft_printf("pipex: %s: %s\n", strerror(errno), argv[4]);
        (close(fd[0]), close(fd[1]), exit(2));
    }
    close(fd[1]);
    if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(fd_out, STDOUT_FILENO) == -1)
    {
        (perror("pipex"), close(fd[0]), close(fd[1]));
        exit(2);
    }
    if (execve(args->path, args->cmd_args, envp) == -1)
    {
        perror("pipex");
        close(fd[0]);
        close(fd[1]);
        exit(127);
    }
}

void init_args(char *cmd, t_args *args, char **envp, int fd[2])
{
    args->path = get_path(cmd, envp);
    if (!args->path)
    {
        if (errno != ENOENT)
            ft_printf("pipex: %s\n%d", strerror(errno));
        args->cmd_args = NULL;
        clean_all(args, 1);
            close(fd[0]);
            close(fd[1]);
        return;
    }
    args->cmd_args = ft_split(cmd, ' ');
    if (!args->cmd_args)
    {
        ft_printf("pipex: %s\n", strerror(errno));
        clean_all(args, 1);
        if (fd[0] != -1)
            close(fd[0]);
        if (fd[1] != -1)
            close(fd[1]);
        return;
    }
}

void f()
{
    // system("leaks a.out");
}

void clean_all(t_args *args, int code)
{
    free(args->path);
    free_matrix(args->cmd_args);
}
void ff()
{
    system("lsof -c a.out");
}
int main(int argc, char **argv, char **envp)
{
    int pid1;
    int pid2;
    t_args args[2];
    int fd[2];


    pipe(fd);

    init_args(argv[2], &args[0], envp, fd);

    pid1 = fork();
    if (pid1 == 0)
    {
        child_process(argv, envp, &args[0], fd);
    }

    init_args(argv[3], &args[1], envp, fd);
    pid2 = fork();
    if (pid2 == 0)
    {
        child_process_1(argv, envp, &args[1], fd);
    }

    if (fd[0] != -1)
            close(fd[0]);
        if (fd[1] != -1)
            close(fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    clean_all(&args[0], 1);
    clean_all(&args[1], 1);

    return 0;
}
