#include "./libft/libft.h"
#include <sys/errno.h>
#include <string.h>

char **free_matrix(char **m)
{
    int i;

    i = 0;
    while (m[i])
    {
        free(m[i]);
        i++;
    }
    free(m);
    return NULL;
}

char *get_cmd(char *str)
{
    int i;
    int start;
    char *r;
    char *tmp;

    i = 0;
    while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
    start = i;
    while (str[i] && str[i] != ' ' && str[i] != '\t')
        i++;
    tmp = ft_substr(str, start, i - start);
    if (!tmp)
        return NULL;
    r = ft_strjoin("/", tmp);
    return (free(tmp), r);
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
        ft_printf("pipex: command not found: %s\n", cmd + 1);
        r = NULL;
    }
    return (free_matrix(paths), free(cmd), r);
}

int get_first_word_index(char *s)
{
    int i;

    i = 0;
    while (s[i] && (s[i] == ' ' || s[i] == '\t'))
    {
        i++;
    }
    while (s[i] && s[i] != ' ' && s[i] != '\t')
    {
        i++;
    }
    return i;
}

char *get_path(char *arg, char **envp)
{
    char **paths;
    char *r;
    char *cmd;
    int i;
    char *sub;

    sub = ft_substr(arg, 0, get_first_word_index(arg));
    if (!sub)
        return (NULL);
    if (*arg == '/')
    {
        if (access(sub, F_OK | X_OK) == 0)
            return (arg);
        else
            return (ft_printf("pipex: %s: %s\n",strerror(errno), sub), NULL);
    }
    cmd = get_cmd(arg);
    if (!cmd)
        return (NULL);
    paths = get_paths(envp);
    if (!paths)
        return (free(cmd), NULL);
    return (extract_path(paths, cmd));
}
