/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachfenn <aachfenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:21:01 by aachfenn          #+#    #+#             */
/*   Updated: 2023/06/19 11:21:13 by aachfenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	here_doc_ext_2(char	*read, t_cmd	*cmd, t_prep	*prep)
{
	if (read == NULL || (ft_strncmp(read, cmd->eof[prep->j], \
	ft_strlen(read) + 1) == 0))
	{
		prep->j++;
		free(read);
		return (1);
	}
	return (0);
}
