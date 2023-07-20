/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthiruma <pthiruma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:50:14 by pthiruma          #+#    #+#             */
/*   Updated: 2023/07/13 11:00:59 by pthiruma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	msg(char *err)
{
	write (2, err, ft_strlen(err));
	return (1);
}

void	msg_error(char *err)
{
	perror (err);
	exit (1);
}
