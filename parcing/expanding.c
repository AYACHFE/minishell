/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarraji <rarraji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:18:58 by rarraji           #+#    #+#             */
/*   Updated: 2023/06/09 22:32:33 by rarraji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr1(char const *s, unsigned int start, size_t len)
{
	int			i;
	int			l;
	size_t		len_s;
	const char	*ss;
	char		*p;
	int deuble = 0;
	int single = 0;

	if (!s)
		return (0);
	ss = s;
	len_s = ft_strlen(s);
	i = 0;
	if (start >= len_s)
		return (ft_strdup(""));
	if (len > len_s)
		len = len_s - start;
	p = malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	l = (int)len;
 
	while (l > i)
	{
		if (ss[start] == '\"' && ((single % 2) == 0))
		{
			deuble++;
			start++;
		}
		else if (ss[start] == '\'' && ((deuble % 2) == 0))
		{
			single++;
			start++;
		}
		else
		{
			p[i] = ss[start];
			start++;
			i++;
		}
	}
	p[i] = '\0';
	return (p);
}



int ft_strlenn(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] == '\"' || str[i] == '$' || str[i] == '\'')
	{
		j++;
		i++;   
	}
	while(str[i] != '$' && str[i] != '\0' && str[i] != '\"' && str[i] != '\'')
	{
		if (str[i] == '\"')
			j++;
		i++;   
	}
	return(i - j);
}

int ft_hsb(char *s)
{
	char c;
	int  i = 0;
	int j = 0;
	int deuble = 0;
	int single = 0;

	c = '\'';
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if(s[i] == '\"' && ((single % 2) == 0))
			{
				deuble++;
				j++;
			}
			if(s[i] == '\'' && ((deuble % 2) == 0))
			{
				single++;
				j++;
			}
		}
		i++;
	}
	return (i - j);           
}

int ft_strlennn(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	
	while(str[i] != '\0' && str[i] != '\"' && str[i] != '$')
	{
		i++;   
	}
	return(i);
}



char *ft_change_var(char *str, t_minishell *mini, int tmp)
{
	int i;
	int j;
	int d;
	int n;
	char *s;
	char *str_jn = NULL;
	 
	j = 0;
	i = 0;
	n = 0;
	while (tmp && str[n])
	{
		while(str[n] == '\"' )
			n++;
		if (str[n] == '$')
		{
			j = n;
			j++;
			while (str[j] != '$' && str[j] != '\0' && ft_isdigit(str[j]) == 0 && str[j] != '-' && str[j] != '@')
				j++;
			s = ft_substr(str, n+1 , j);
			i = 0;
			while (mini->my_env[i])
			{
				d = 0;
				if (ft_strncmp(mini->my_env[i], s, ft_cnt(mini->my_env[i])) == 0)
				{
					d = 0;   
					while (mini->my_env[i][d])
					{
						if (mini->my_env[i][d] == '=')
							break; 
						d++;            
					}    
				}
				if (mini->my_env[i][d] == '=')
					break;
				else
					i++;
			}
			tmp--;    
			// free (s);
			if(mini->my_env[i] == '\0')
            {
                if (ft_strncmp(s, "?", 1) == 0)
                {
                    s = ft_itoa(mini->exit_code);
                    str_jn = ft_strjoin(str_jn, s);
                    while (str[n] != '$' && str[n] != '\"' && str[n] != '\0' && ft_isalpha(str[n]) == 0)
                        n++;
                }
                else if(ft_strchr(str, '\'') != NULL)
				{
					s = ft_substr1(str, n, ft_hsb(str));
                    str_jn = ft_strjoin(str_jn, s);
                    while (str[n] != '$' && str[n] != '\"' && ft_isdigit(str[n]) == 0 && str[n] && str[n] != '-' && str[n] != '@')
                        n++;
				}
                else
                {
					n++;
                    while (str[n] != '$' && str[n] != '\"' && ft_isdigit(str[n]) == 0 && str[n] && str[n] != '-' && str[n] != '@')
                        n++;
                }
            }
			else if (mini->my_env[i] == '\0' && str[0] == '\"' && str[1] == '$'  && str[2] == '\'')
			{
				n = n + 1;
				s = ft_substr(str, n, ft_strlennn(str));
				str_jn = ft_strjoin(str_jn, s);
				while (str[n] != '\'' && str[n])
					n++;
			}
			// else if(mini->my_env[i] == '\0')
			// {
			// 	// s = "@";
			// 	// str_jn = ft_strjoin(str_jn, s);
			// 	while (str[n] != '$' && str[n] != '\"' && ft_isdigit(str[n]) == 0 && str[n] && str[n] != '-' && str[n] != '@')
			// 		n++;
			// }
			if (mini->my_env[i] != '\0')
			{
				s = ft_substr(mini->my_env[i], d + 1, ft_strlen(mini->my_env[i]));
				str_jn = ft_strjoin(str_jn, s); 
				free(s);
				while (str[n] != '$' && str[n] != '\"' && ft_isdigit(str[n]) == 0 && str[n] && str[n] != '-' && str[n] != '@')
					n++;
			}
			n = j;

		}
		else if(mini->my_env[i] != '\0' && str[0] == '\'')
		{
		    s = ft_substr(str, n, ft_strlennn(str));
		    str_jn = ft_strjoin(str_jn, s);
		    while (str[n] != '\'' && str[n] != '\0')
		        n++;   
		    n++;
		    n = j;    
		}
		// else if(mini->my_env[i] != '\0' && str[0] == '\'')
		// {
		//     s = ft_substr(str, n, ft_strlennn(str));
		//     str_jn = ft_strjoin(str_jn, s);
		//     while (str[n] != '\'' && str[n] != '\0')
		//         n++;
		//     printf("---->%d\n", n);    
		//     n++;
		//     n = j;    
		// }
		else
		{
			j = n;
			if (str[n] == '\"')
				n++;
			while (str[j] != '$' && str[j] != '\0')
				j++;       
			s = ft_substr(str, n, ft_strlenn(str));
			str_jn = ft_strjoin(str_jn, s);
			n = j;
		} 
	}
	return (str_jn);   
}

void    ft_check_dollar(t_minishell *mini)
{
	int i;
	int j;
	int d;
	int tmp;
	int single;
	int deuble;
	int k;
	int	s;
	// char *check = NULL;

	k = 0;
	
	i = 0;
	j = 0;
	d = 0;
	s = 0;
	single = 0;
	tmp = 0;
	deuble = 0;
	mini->tmp_cmd = malloc(sizeof(char *) * (mini->cmd_nb + 1));
	while (mini->cmd[i])
    {
        d = 0;
        while(mini->cmd[i][s])
        {
            if(mini->cmd[i][s] == '$')
            {
                s++;
            }
            else
              break;     
        }
        if(mini->cmd[i][s] == '\0')
        {
            mini->tmp_cmd[j] = ft_strdup("$");
            j++;
        }

        if (mini->cmd[i][d] == '\'')
        {
            d++;
            single = 1;
        }
        if (mini->cmd[i][d] == '\"' && single != 1)
        {
            deuble =1;
            d++;
        }
        while(mini->cmd[i][d] && single != 1 )
        {
            if (mini->cmd[i][d] == '$')
                tmp++;
            d++;    
        }
        if (tmp > 0 && mini->cmd[i][s] != '\0')
        {
            // printf("-->%s\n", mini->cmd[i]);
            mini->tmp_cmd[j] = ft_change_var(mini->cmd[i], mini, tmp);
            j++;
        }
        else if (mini->cmd[i][s] != '\0')
        {
            if (deuble == 0 && single != 1)
            {
                mini->tmp_cmd[j] = ft_substr(mini->cmd[i], 0, ft_strlen(mini->cmd[i]));
                j++;
            }
            else
            {
                k = 0;
                if (deuble == 1 && mini->cmd[i][k + 1] == '\"' && mini->cmd[i][k + 2] == '\0')
                    break;
                // if (single == 0)
                // {
                //     puts("bngb");
                //     while(mini->cmd[i][k] == '\"')
                //         k++;
                // }        
                mini->tmp_cmd[j] = ft_substr1(mini->cmd[i], k, ft_hsb(mini->cmd[i]));
                j++;    
            }
                
        }
        s = 0;
        tmp = 0;
        i++;
    }
    mini->tmp_cmd[j] = NULL;
    // i = 0;
    // while(mini->tmp_cmd[i])
    //     i++;
    // check = malloc(i + 1);
    // i = 0;
    // while(mini->tmp_cmd[i])
    // {
    //     check = ft_strjoin(mini->tmp_cmd[i], check);
    //     i++;
    // }
    // ft_error(check, 1);
}
