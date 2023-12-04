/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmartir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 20:48:39 by grmartir          #+#    #+#             */
/*   Updated: 2023/07/07 20:48:41 by grmartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	err(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}

void	perror_error(char *err)
{
	perror(err);
	exit (1);
}
