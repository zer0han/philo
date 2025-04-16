/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:50:36 by rdalal            #+#    #+#             */
/*   Updated: 2025/04/16 20:52:50 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <strings.h>
# include <pthread.h>

// void	*print_number()
// {
// 	int	i = 0;

// 	while (i < 5)
// 	{
// 		printf("thread 1: %d\n", i);
// 		i++;
// 		sleep(1);
// 	}
// 	return (NULL);
// }

// void	*print_letters()
// {
// 	char	letter[] = "ABCDE";
// 	int		i = 0;

// 	while (i < 5)
// 	{
// 		printf("thread 2: %c\n", letter[i]);
// 		i++;                                                   
// 		sleep(1);
// 	}
// 	return (NULL);
// }

// void	show_basic_threading()
// {
// 	printf("\n=== Basic threading ex ===\n");
// 	pthread_t	thread1;
// 	pthread_t	thread2;

// 	pthread_create(&thread1, NULL, print_number, NULL);
// 	pthread_create(&thread2, NULL, print_letters, NULL);

// 	pthread_join(thread1, NULL);
// 	pthread_join(thread2, NULL);
// }

// int	main()
// {
// 	show_basic_threading();
// 	return (0);	
// }

int bal = 0;

void	write_balance(int new_bal)
{
	usleep(250000);
	bal = new_bal;
}

int	read_balance()
{
	usleep(250000);
	return (bal);
}

void	*deposit(void *amt)
{
	int	account_bal = read_balance();
	account_bal += *((int *) amt);
	write_balance(account_bal);
	return (NULL);
}

int	main()
{
	int	before = read_balance();
	printf("before: %d\n", before);
	pthread_t	thread1;
	pthread_t	thread2;
	int			dep1 = 200;
	int			dep2 = 300;
	
	pthread_create(&thread1, NULL, deposit, (void *) &dep1);
	pthread_create(&thread2, NULL, deposit, (void *) &dep2);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	int	after = read_balance();
	printf("after: %d\n", after);
	return(0);
}
