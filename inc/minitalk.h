/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:14:52 by cycolonn          #+#    #+#             */
/*   Updated: 2026/01/28 12:14:55 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H

# define MINITALK_H

# include "../inc/ft_printf.h"
# include "../inc/libft.h"
# include <signal.h>
# include <unistd.h>

typedef struct s_sent
{
	char	cur_char;
	int		count_bits;
	int		pid;
}			t_sent;

#endif
