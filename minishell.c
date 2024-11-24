#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    argv++;
    if (argc != 1)
        msg("\033[31mNO arguments accepted");
    if (envp == NULL)
        msg("\033[31mNO Envp variable");
    if (getpatharray(envp) == NULL)
        msg("\033[31mNO Path variable on Envp");
    while(prompt(envp) == 0)
        ;

}