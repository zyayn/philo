/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:17:22 by zchia             #+#    #+#             */
/*   Updated: 2023/09/15 17:59:07 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countwords(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if ((i == 0) && (s[i] != c))
			count++;
		else if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static char	*getword(const char *s, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc(sizeof(char) * (finish - start + 1));
	while (start < finish)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		front;
	char	**results;

	results = (char **)malloc(sizeof(char *) * (countwords(s, c) + 1));
	if (!s || !results)
		return (NULL);
	i = 0;
	j = 0;
	front = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && front < 0)
			front = i;
		else if ((s[i] == c || i == ft_strlen(s)) && front >= 0)
		{
			results[j++] = getword(s, front, i);
			front = -1;
		}
		i++;
	}
	results[j] = NULL;
	return (results);
}
/*
int	main(void)
{
	char	**results;
	int		i;
	
	results = ft_split("          ", ' ');
	printf("Done split!\n");
	i = 0;
	while (results[i])
	{
		printf("%s\n", results[i]);
		i++;
	}
}
*/
