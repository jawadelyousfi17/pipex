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

    fd_in = open(argv[1], O_RDWR);
    if (fd_in < 0)
    {
        ft_printf("p1 pipex: %s: %s\n", strerror(errno), argv[1]);
        exit(2);
    }
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    dup2(fd_in, STDIN_FILENO);
    execve(args->path, args->cmd_args, envp);
}

void child_process_1(char **argv, char **envp, t_args *args, int fd[2])
{
    int fd_out;

    fd_out = open(argv[4], O_RDWR | O_CREAT, 0777);
    if (fd_out < 0)
    {
        ft_printf("p2 pipex: %s: %s\n", strerror(errno), argv[4]);
        exit(2);
    }
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    dup2(fd_out, STDOUT_FILENO);
    execve(args->path, args->cmd_args, envp);
}

void init_args(char *cmd, t_args *args, char **envp)
{
    args->path = get_path(cmd, envp);
    if (!args->path)
    {
        if (errno != ENOENT)
            ft_printf("pipex: %s\n", strerror(errno));
        args->cmd_args = NULL;
        exit(1);
    }
    args->cmd_args = ft_split(cmd, ' ');
    if (!args->cmd_args)
    {
        ft_printf("pipex: %s\n", strerror(errno));
        exit(1);
    }
}

void f()
{
    system("leaks a.out");
}

void clean_all(t_args *args, int code)
{
    free(args->path);
    free_matrix(args->cmd_args);
}

int main(int argc, char **argv, char **envp)
{
    t_args args[2];
    int pid1;
    int pid2;
    int fd[2];
    int retrun_value;

    if (argc != 5)
        return 1;
    pipe(fd);
    
    pid1 = fork();
    if (pid1 == -1)
    {
        ft_printf("pipex: %s\n", strerror(errno));
        exit(1);
    }
    init_args(argv[2], &args[0], envp);
    if (pid1 == 0)
    {
        child_process(argv, envp, &args[0], fd);
    }
    waitpid(pid1, NULL, 0);
    clean_all(&args[0], 1);

    pid2 = fork();
    if (pid2 == -1)
    {
        clean_all(&args[0], 2);
        clean_all(&args[1], 2);
        ft_printf("pipex: %s\n", strerror(errno));
        exit(2);
    }
    init_args(argv[3], &args[1], envp);
    if (pid2 == 0)
    {
        child_process_1(argv, envp, &args[1], fd);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid2, &retrun_value, 0);
    clean_all(&args[1], 1);

    if (retrun_value != 0)
        exit(2);
    return 0;
}
