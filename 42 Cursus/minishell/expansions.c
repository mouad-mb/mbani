/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbani <mbani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 11:34:53 by mbani             #+#    #+#             */
/*   Updated: 2020/12/03 14:17:23 by mbani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		char_count(char **str, int i, int *j)
{
	while (str[0][i])
	{
		if (((str[0][i] >= 'a' && str[0][i] <= 'z') ||
		(str[0][i] >= 'A' && str[0][i] <= 'Z')) ||
		(str[0][i] >= '0' && str[0][i] <= '9') || str[0][i] == '_')
			*j += 1;
		else
			break ;
		i++;
	}
	return (*j);
}

void	dolar_check(char **str)
{
	int		i;
	int		j;
	t_expan	expan;

	expan.sng = 0;
	expan.dbl = 0;
	i = 0;
	j = 0;
	while (str[0][i])
	{
		quote_check(&expan.sng, &expan.dbl, str[0], i);
		if (expan.sng == 1)
		{
			i++;
			continue;
		}
		else
		{
			if (str[0][i] == '$' && not_escaped(str[0], i))
				i += char_count(str, i + 1, &j);
			if (j)
			{
				if ((search_and_replace(str, i, j)) == 0)
				{
					replace(str, "", j, i);
					i -= j;
				}
				j = 0;
			}
		}
		i++;
	}
}

void	param_expansion(t_cmd *tmp)
{
	while (tmp->next)
	{
		dolar_check(&(tmp->string));
		quote_removal(&(tmp->string));
		tmp = tmp->next;
	}
	dolar_check(&(tmp->string));
	quote_removal(&(tmp->string));
}


// void	dolar_check(char **str)
// {
// 	int		i;
// 	int		j;
// 	t_expan	expan;

// 	expan.sng = 0;
// 	expan.dbl = 0;
// 	i = 0;
// 	j = 0;
// 	while (str[0][i])
// 	{
// 		quote_check(&expan.sng, &expan.dbl, str[0], i);
// 		if (expan.sng == 1)
// 		{
// 			i++;
// 			continue;
// 		}
// 		else
// 		{
// 			if (str[0][i] == '$' && not_escaped(str[0], i))
// 				i += char_count(str, i + 1, &j);
// 			if (j)
// 			{
// 				if ((search_and_replace(str, i, j)) == 0)
// 				{
// 					replace(str, "", j, i);
// 					i -= j;
// 				}
// 				j = 0;
// 			}
// 		}
// 		i++;
// 	}
// }