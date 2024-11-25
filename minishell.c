#include "minishell.h"

int main(int argc, char **argv, char **envp)
{

    (void)argv;
    if (argc != 1)
        msg("\033[31mNO arguments accepted");
    if (envp == NULL)
        msg("\033[31mNO Envp variable");
    if (getpatharray(envp) == NULL)
        msg("\033[31mNO Path variable on Envp");
    if (lookinenv(envp, "PWD=/") == NULL)
        msg("\033[31mNO PWD variable on Envp");
    while(prompt(envp) == 0)
        ;

}