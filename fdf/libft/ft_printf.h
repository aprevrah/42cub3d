/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:18:41 by aprevrha          #+#    #+#             */
/*   Updated: 2023/09/27 20:52:22 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>

int	ft_printf(const char *s, ...);
int	ft_put_i(int nb);
int	ft_put_hex(unsigned int nb, char *b);
int	ft_put_p(const void	*p);
int	ft_put_u(unsigned int nb);
int	ft_put_s(char *s);
int	ft_put_c(char c);

#endif