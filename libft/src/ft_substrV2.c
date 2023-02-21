/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substrV2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:54:39 by ngriveau          #+#    #+#             */
/*   Updated: 2023/02/18 11:29:52 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*str;

	i = 0;
	if (((size_t) ft_strlen(s)) <= start)
		return (ft_strdup(""));
	if (((size_t) ft_strlen(s)) <= len)
		str = malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (len > 0 && s[start] != '\0')
	{
		str[i] = s[start];
		i++;
		start++;
		len--;
	}
	str[i] = '\0';
	return (str);
}

// int main (void)
// {
// 	char *test = "iNanrxz RV39lUH 6toz9g0mnpx AJH vEjTzhr06dLxFZS58 MGRzPblKZUv16neJj 63J0";
// 	int start = 6;
// 	int len = 1;
// 	printf("z = %s\n",ft_substr(test,start,len));
// 	test = "HtADw5hrZiI2 r1q5HfGchZDXdPU rY97U jL17xQT3Sti xuHDgKcVCnv Kdz XEHsmNcRGZlK1Vabq RQVc4aPsOF VyE IGB0Sj";
// 	start = 7;
// 	len = 1;
// 	printf("r = %s\n",ft_substr(test,start,len));
// 	test = "4hm X8Dz5lWN47hrVS 3gwlU5046dcYfnP7V PlU0voEp epD aZAYFEvnT1 fp4ensuO ucoV83fF2DwEaOY";
// 	start = 8;
// 	len = 4;
// 	printf("5lWN = %s\n",ft_substr(test,start,len));
// 	test = "je9oz 3awnKd2R j2zwfxTy Xvo MnIdTJ SaymFOJi 3ZealS47Ni tI6eV HTgQheCJF uQTgJo k90Qj4xZyUd1wc2Ml GHsDJ4 fgPGeAkJx";
// 	start = 6;
// 	len = 4;
// 	printf("3awn = %s\n",ft_substr(test,start,len));
// 	test = "fjlQTOvR MpQUWLRBeAlrstP2f 5eIEwP2M0vH3zrRxm SW4Dgzi5Je ytigWr0 VZFWPRydUbDep5w TJ8DH0yVgiYF4R2Z EhH5n uI3O1S6n PHU47ct2 qwWoHsTy6tUR UYFTljEbZA diN7 eYVZpzgS RbVKUlpB aCu8oNDHr7fJ 3DpRKudgYw";
// 	start = 8;
// 	len = 6;
// 	printf("MpQUW = %s\n",ft_substr(test,start,len));
// 	test = "ULaNjy Kiz 93vtOqKon0Ja Opedn1YGDZ";
// 	start = 7;
// 	len = 1;
// 	printf("K = %s\n",ft_substr(test,start,len));
// 	test = "ULaNjy Kiz 93vtOqKon0Ja Opedn1YGDZ";
// 	start = 30;
// 	len = 0;
// 	printf("= %s\n",ft_substr(test,start,len));
// }
