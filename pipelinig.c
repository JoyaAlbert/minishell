/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelinig.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:12:53 by copito            #+#    #+#             */
/*   Updated: 2025/07/25 17:51:31 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils/utils.h"

/*
 * Actualiza los comandos eliminando el carácter pipe '|' al final
 * Recorre cada comando en la matriz y trunca el símbolo pipe si está al final
 * Prepara los comandos para ser procesados por las funciones de ejecución
 */
void	update_cmd(char **cmds)
{
	int	i;
	int	len;

	i = 0;
	while (cmds[i] != NULL)
	{
		len = ft_strlen(cmds[i]);
		if (len > 0 && cmds[i][len - 1] == '|')
			cmds[i][len - 1] = '\0';
		i++;
	}
}

/*
 * Procesa comandos que contienen redirecciones (<, >, >>, <<)
 * Identifica el tipo de redirección presente en el comando
 * Ejecuta el comando con las redirecciones configuradas adecuadamente
 * Proporciona soporte para múltiples redirecciones en un solo comando
 */
void	do_redirections(char **cmd_parts, char **envp,
	t_dir_info *dir, t_envp *envp_d)
{
	t_exec_ctx	ctx;

	handle_redirections(cmd_parts);
	if (cmd_parts[0])
	{
		ctx.envp = envp;
		ctx.dir = dir;
		ctx.envp_d = envp_d;
		builtin_exec(cmd_parts[0], cmd_parts, &ctx);
		parse_path(ft_strndup(cmd_parts[0], ft_strlen(cmd_parts[0]) + 1),
			cmd_parts, envp);
	}
	matrixfree(cmd_parts);
	exit(0);
}

/*
 * Función auxiliar para procesar una secuencia de comandos conectados por 
 * tuberías
 * Configura los descriptores de archivo para las tuberías entre procesos
 * Crea procesos hijos para cada comando en la secuencia
 * Espera a que todos los procesos hijos terminen
 */
void	pipeaux(char **cmds, char **envp, t_dir_info *dir, t_envp *envp_d)
{
	pid_t			pid;
	int				i;
	int				prev_fd;
	t_pipe_params	params;

	params.envp = envp;
	params.dir = dir;
	params.envp_d = envp_d;
	prev_fd = 0;
	i = -1;
	while (cmds[++i + 1] != NULL)
		prev_fd = pipe_process(&cmds[i], &params, prev_fd);
	pid = fork();
	fork_fail(cmds, pid);
	if (pid == 0)
		handle_last_command(prev_fd, cmds[i], &params);
	else
		close(prev_fd);
	while (wait(NULL) > 0)
		;
}

/*
 * Maneja el último comando en una tubería (proceso hijo final)
 * Configura la entrada desde la tubería anterior si existe
 * Ejecuta el comando final con las redirecciones apropiadas
 */
void	handle_last_command(int prev_fd, char *cmd, t_pipe_params *params)
{
	char	**cmd_parts;

	if (prev_fd != 0)
	{
		dup2(prev_fd, 0);
		close(prev_fd);
	}
	cmd_parts = ft_split(cmd, ' ');
	do_redirections(cmd_parts, params->envp, params->dir, params->envp_d);
}

/*
 * Función principal para manejar comandos con tuberías
 * Verifica la sintaxis del comando (por ejemplo, no puede comenzar con '|')
 * Divide la entrada en comandos separados por el operador '|'
 * Actualiza los comandos y los envía a la función auxiliar de tuberías
 * Libera la memoria utilizada al finalizar
 * 
 * Explicación técnica:
 * 1. Primero verifica si el comando comienza con un pipe, lo que sería un
  error de sintaxis
 * 2. Utiliza ft_split para dividir la entrada en un array de comandos usando 
 '|' como delimitador
 * 3. Llama a update_cmd para eliminar cualquier carácter '|' residual al final 
 de cada comando
 * 4. Envía el array de comandos a pipeaux, que realiza el procesamiento real 
 de las tuberías:
 *    - Crea procesos hijo para cada comando usando fork()
 *    - Conecta la salida de cada comando con la entrada del siguiente
 *    - Maneja las redirecciones dentro de cada comando
 * 5. Espera a que todos los procesos hijo terminen
 * 6. Finalmente libera la memoria utilizada por el array de comandos
 */
void	pipeline(char *cmd, char **envp, t_dir_info *dir, t_envp *envp_d)
{
	char	**cmds;
	int		i;

	i = 0;
	if (lookinenv(envp, "PATH=/") == NULL)
	{
		printf("Command not found\n");
		return ;
	}
	if (!ft_strncmp(cmd, "echo", 4) && echo_quotes(cmd) == 1)
		return ;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		i++;
	if (cmd[i] == '|')
	{
		printf("Syntax error\n");
		return ;
	}
	cmds = split_outside_quotes(cmd, '|');
	update_cmd(cmds);
	pipeaux(cmds, envp, dir, envp_d);
	matrixfree(cmds);
}
