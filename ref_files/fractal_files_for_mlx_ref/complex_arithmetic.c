/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_arithmetic.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 00:05:07 by pamatya           #+#    #+#             */
/*   Updated: 2025/07/04 18:18:57 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_cmplx	c_sqr_plus_const(t_cmplx z, t_cmplx c);
t_cmplx	c_sqr_plus_const_abs(t_cmplx z, t_cmplx c);
double	c_dist_sqr(t_cmplx z);
double	ft_abs(double num);

t_cmplx	c_sqr_plus_const(t_cmplx z, t_cmplx c)
{
	t_cmplx	res;

	res.rl = z.rl * z.rl - z.im * z.im + c.rl;
	res.im = 2 * z.rl * z.im + c.im;
	return (res);
}

t_cmplx	c_sqr_plus_const_abs(t_cmplx z, t_cmplx c)
{
	t_cmplx	res;

	res.rl = ft_abs((z.rl * z.rl - z.im * z.im) + c.rl);
	res.im = - (2 * ft_abs(z.rl) * ft_abs(z.im)) + c.im;
	return (res);
}

double	c_dist_sqr(t_cmplx z)
{
	return (z.rl * z.rl + z.im * z.im);
}

double	ft_abs(double num)
{
	if (num < 0)
		num = -num;
	return (num);
}
