/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:13:30 by copito            #+#    #+#             */
/*   Updated: 2025/07/23 23:49:18 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Normaliza las redirecciones en un comando
 * Divide la entrada en tokens separados para facilitar su procesamiento
 * Identifica correctamente operadores y argumentos
 * Maneja espacios y otros caracteres especiales
 * Retorna una matriz de cadenas con todos los tokens o NULL si hay error
 */
char	**normalize_redirections(char *cmd)
{
	char	**result;
	int		token_count;
	int		i;
	int		j;

	token_count = count_tokens(cmd);
	if (token_count == -1)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (token_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ')
		{
			i = extract_operator_or_token(cmd, i, result, j);
			j++;
		}
		else
			i++;
	}
	result[j] = NULL;
	return (result);
}

/*
 * Ejecuta un comando en un proceso hijo con soporte para redirecciones
 * Crea un nuevo proceso mediante fork()
 * En el proceso hijo, gestiona las redirecciones y ejecuta el comando
 * En el proceso padre, espera a que el hijo termine
 * Maneja los posibles errores de fork y ejecución
 */
void	son_proccess(char **cmds, char **envp, t_dir_info *dir, t_envp *envp_d)
{
	t_exec_ctx	ctx;

	handle_redirections(cmds);
	if (cmds[0])
	{
		ctx.envp = envp;
		ctx.dir = dir;
		ctx.envp_d = envp_d;
		builtin_exec(cmds[0], cmds, &ctx);
		parse_path(ft_strndup(cmds[0], ft_strlen(cmds[0]) + 1), cmds, envp);
	}
	matrixfree(cmds);
	exit(EXIT_SUCCESS);
}

/*
 * Prepara y ejecuta un comando que tiene redirecciones
 * Analiza la entrada para identificar las partes del comando y las redirecciones
 * Crea un proceso hijo para ejecutar el comando con las redirecciones
 * Proporciona soporte para comandos built-in y externos
 * 
 * Explicación técnica:
 * 1. Normaliza la entrada usando normalize_redirections:
 *    - Divide el comando en tokens independientes teniendo en 
 cuenta los operadores
 *    - Separa correctamente comandos, operadores de redirección y 
 nombres de archivos
 * 2. Verifica posibles errores de sintaxis en las redirecciones
 * 3. Crea un proceso hijo mediante fork() para ejecutar el comando:
 *    - Aísla el proceso de redirección para evitar afectar al shell principal
 *    - Si hay error en fork(), muestra mensaje y libera memoria
 * 4. En el proceso hijo, llama a son_proccess que:
 *    - Aplica todas las redirecciones usando handle_redirections
 *    - Ejecuta el comando con las redirecciones establecidas
 *    - Maneja tanto comandos built-in como externos
 * 5. El proceso padre espera con waitpid a que termine el hijo
 * 6. Finalmente libera la memoria del array de tokens
 */
void	execute_with_redirections(char *cmd, char **envp,
		t_dir_info *dir, t_envp *envp_d)
{
	char	**cmds;
	pid_t	pid;

	if (!ft_strncmp(cmd, "echo", 4) && echo_quotes(cmd) == 1)
		return ;
	cmds = normalize_redirections(cmd);
	if (!cmds)
	{
		printf("Syntax error\n");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		matrixfree(cmds);
		msg("Fork error");
		return ;
	}
	if (pid == 0)
		son_proccess(cmds, envp, dir, envp_d);
	else
		waitpid(pid, NULL, 0);
	matrixfree(cmds);
}

/*
 * Libera tokens extra que aparecen después de redirecciones
 */
void	free_extra_token(char **cmds, int i, int seen_redirection)
{
	if (cmds[i] && seen_redirection)
	{
		free(cmds[i]);
		cmds[i] = NULL;
	}
}

int	check_end_of_token(char *cmd, int i)
{
	if (cmd[i] != '\0')
		i++;
	return (i);
}
