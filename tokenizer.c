#include "shell.h"

/**
 * **split_string_words - will split a string into words. Repeated delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

/// @brief
/// @param str
/// @param d
/// @return
char **split_string_words(char *str, char *d)
{
	int A, B, C, E, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (A = 0; str[A] != '\0'; A++)
		if (!check_delimeter(str[A], d) && (check_delimeter(str[A + 1], d) || !str[A + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (A = 0, B = 0; B < numwords; B++)
	{
		while (check_delimeter(str[A], d))
			A++;
		C = 0;
		while (!check_delimeter(str[A + C], d) && str[A + C])
			C++;
		s[B] = malloc((C + 1) * sizeof(char));
		if (!s[B])
		{
			for (C = 0; C < B; C++)
				free(s[C]);
			free(s);
			return (NULL);
		}
		for (E = 0; E < C; E++)
			s[B][E] = str[A++];
		s[B][E] = 0;
	}
	s[B] = NULL;
	return (s);
}

/**
 * **split_string_words_2 - will split a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */

/// @brief
/// @param str
/// @param d
/// @return
char **split_string_words_2(char *str, char d)
{
	int A, B, C, E, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (A = 0; str[A] != '\0'; A++)
		if ((str[A] != d && str[A + 1] == d) ||
		    (str[A] != d && !str[A + 1]) || str[A + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (A = 0, B = 0; B < numwords; B++)
	{
		while (str[A] == d && str[A] != d)
			A++;
		C = 0;
		while (str[A + C] != d && str[A + C] && str[A + C] != d)
			C++;
		s[B] = malloc((C + 1) * sizeof(char));
		if (!s[B])
		{
			for (C = 0; C < B; C++)
				free(s[C]);
			free(s);
			return (NULL);
		}
		for (E = 0; E < C; E++)
			s[B][E] = str[A++];
		s[B][E] = 0;
	}
	s[B] = NULL;
	return (s);
}
