/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:55:23 by hberger           #+#    #+#             */
/*   Updated: 2019/10/15 16:50:29 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**              <----- Description ----->
**
** Alloue et retourne un tableau de chaines de caractères "fraiches"
** (toutes terminées par un ’\0’, le tableau également donc)
** résultant de la découpe de s selon le caractère c.
** Si l’allocation echoue, la fonction retourne NULL.
**
** Exemple : ft_split("*salut*les***etudiants*", ’*’)
** renvoie le tableau ["salut", "les", "etudiants"].
*/

#include "./libft.h"

static int		check(char c, char charset)
{
	if (c == charset)
		return (1);
	return (0);
}

static int		ft_word_nbr(char *str, char charset)
{
	int i;
	int nbr;
	int last_is_sep;

	i = -1;
	nbr = 0;
	last_is_sep = 1;
	while (str[++i])
		if (check(str[i], charset))
			last_is_sep = 1;
		else if (last_is_sep)
		{
			last_is_sep = 0;
			nbr++;
		}
	return (nbr);
}

static char		*ft_create_word(char *str, char charset)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && !(check(str[i], charset)))
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (str[i] && !(check(str[i], charset)))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int		ft_create_strs(char **strs, char *str, char charset)
{
	int i;
	int nbr;
	int last_is_sep;

	i = -1;
	nbr = 0;
	last_is_sep = 1;
	while (str[++i])
		if (check(str[i], charset))
			last_is_sep = 1;
		else if (last_is_sep)
		{
			last_is_sep = 0;
			strs[nbr] = ft_create_word(str + i, charset);
			if (strs[nbr] == NULL)
			{
				while (nbr-- > 0)
					free(strs[nbr]);
				return (1);
			}
			nbr++;
		}
	return (0);
}

char			**ft_split(char const *s, char c)
{
	char	**strs;
	char	*tmp;

	tmp = (char *)s;
	strs = malloc(sizeof(char *) * (ft_word_nbr(tmp, c) + 1));
	if (strs == 0)
		return (0);
	if (ft_create_strs(strs, tmp, c))
	{
		free(strs);
		return (NULL);
	}
	strs[ft_word_nbr(tmp, c)] = 0;
	return (strs);
}
