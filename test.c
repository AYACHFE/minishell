void ft_unste(t_minishell *mini) {
	int i;
	int j;
	int l;

	i = 1;
	l = 0;
	while (i < mini->count_str) {
		j = 0;
		while (mini->my_env[j]) {
			if (ft_strncmp(mini->str[i], mini->my_env[j], ft_cnt(mini->my_env[j])) != 0)
				j++;
			else {
				j++;
				l++;
				break;
			}
		}
		i++;
	}
	ft_rem_var(mini, l);
}

void ft_rem_var(t_minishell *mini, int l) {
	int i;
	int j;
	int d;
	int n;
	char **my_tmp;

	j = 0;
	n = 0;
	while (mini->my_env[j])
		j++;
	my_tmp = malloc(sizeof(char *) * (j - l + 1)); // Ajout de +1 pour le NULL final
	d = 0;
	j = 0;
	while (mini->my_env[d]) {
		i = 1;
		while (mini->str[i]) {
			if (ft_strncmp(mini->my_env[d], mini->str[i], ft_cnt(mini->my_env[d])) == 0)
				i++;
			else {
				my_tmp[n] = ft_strdup(mini->my_env[d]);
				n++;
				i++;
			}
		}
		d++;
	}
	my_tmp[n] = NULL; // Assigner NULL à la dernière position du tableau
	i = 0;
	while (my_tmp[i]) {
		printf("%s\n", my_tmp[i]);
		i++;
	}

	// Libérer la mémoire allouée pour mini->my_env
	i = 0;
	while (mini->my_env[i]) {
		free(mini->my_env[i]);
		i++;
	}
	free(mini->my_env);

	mini->my_env = my_tmp;
}