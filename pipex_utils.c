#include "./libft/libft.h"
#include <sys/errno.h>
#include <string.h>
#include <stdio.h>

void print_error(char *error_message, char *info)
{
    ft_putstr_fd("pipex: ", 2);
    ft_putstr_fd(info, 2);
    ft_putstr_fd(": ", 2);
    ft_putendl_fd(error_message, 2);
}

char **free_matrix(char **m)
{
    int i;

    i = 0;
    if (!m)
        return (NULL);
    while (m[i])
    {
        free(m[i]);
        i++;
    }
    free(m);
    return NULL;
}

char **get_paths(char **envp)
{
    char **paths;
    int i;

    i = 0;
    while (ft_strnstr(envp[i], "PATH", 4) == NULL)
        i++;
    paths = ft_split(envp[i] + 5, ':');
    return (paths);
}
char *extract_path(char **paths, char *cmd)
{
    int i;
    char *r;

    i = 0;
    while (paths[i])
    {
        r = ft_strjoin(paths[i++], cmd);
        if (!r)
            return (free_matrix(paths), free(cmd), NULL);
        if (access(r, F_OK | X_OK) == 0)
            break;
        free(r);
    }
    if (paths[i] == NULL)
    {
        r = NULL;
    }
    return (free_matrix(paths), free(cmd), r);
}

int is_directory(char *s)
{
    if (!*s)
        return 0;
    if (ft_strlen(s) < 2)
        return (*s == '/');
    return (s[0] == '/' || (s[0] == '.' && s[1] == '/'));
}

char *get_path(char *args, char **envp)
{
    char **paths;
    char *r;
    char *cmd;
    int i;

    i = 0;
    if (!args)
        return NULL;
    if (is_directory(args))
        return ft_strdup(args);
    cmd = ft_strjoin("/", args);
    if (!cmd)
        return (NULL);
    while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
        i++;
    if (!envp[i])
        return (free(cmd), NULL);
    paths = ft_split(envp[i] + 5, ':');
    if (!paths)
        return (free(cmd), NULL);
    return (extract_path(paths, cmd));
}
