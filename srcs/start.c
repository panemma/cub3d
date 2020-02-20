/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-banv <ede-banv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:06:49 by ede-banv          #+#    #+#             */
/*   Updated: 2020/02/20 16:43:51 by ede-banv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void     ft_free(char *res, int e, int n)
{
    if (res)
    {
        free (res);
        res = NULL;
    }
    ft_exit(e, n);
}

void    ft_tri(char *res, t_pars *pars, t_all *all) //intialiser la structure pour faire erreurs de doublons
{
    static char *instances = NULL;

    if (!instances)
        instances = (char[]){0,0,0,0,0,0,0,0};
    skipspace(&res, 2);
    ft_putstr_fd("tri\n", 1);
    if (*res == 'R')
    {
        if (ft_resolution(pars, &res, instances) == -1)
            ft_free(res, 2, 1);
    }
    else if (*res == 'N'|| *res == 'S' || *res == 'W' || *res == 'E') //possibilite d'erreur
    {
        if (ft_textures(pars, &res, instances, all) == -1)
            ft_free(res, 2, 2);
    }
    else if (*res == 'F' || *res == 'C')
    {
        if (ft_colors(pars, &res, instances) == -1)
            ft_free(res, 2, 3);
    }
    else if (*res == '\n')
        return ;
    else
        return ft_free(res, 2, 7); 
    return ;
}

int     ft_checkline(char *data, char *pars)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (data[i])
    {
        if (ft_strchr(pars, (int)data[i]))
            i++;
        else
            return (0);
    }
    return (1);
}

void    parsing(t_all *all, int fd)
{
    char    *data;
    int     n;
    
    n = 1;
    while (n == 1)
    {
        ft_putstr_fd("lol\n", 1);
        n = get_next_line(fd, &data);
        ft_tri(data, &all->pars, all);
        if (ft_checkline(data, "1 "))
        {
            ft_map(all, fd, data);
        }
        free(data);
        data = NULL;
    }
}

void    startprogram(char *file, int n)
{
    t_all   *all;
    int     fd;

    if (!(all = (t_all *)malloc(sizeof(t_all))))
        ft_exit(3, 0);
    if ((fd = open(file, O_RDONLY)) == -1)
        ft_exit(1, 4);
    if (!(all->win.mlx_ptr = mlx_init()))
        ft_exit(3, 4);
    parsing(all, fd);
    close(fd);
    (void)n;
    //this should return a fully malloqued & filled pars structure OR just exit by itself.
    //as well as the player info partially filled.
    //so next to do:
    // create a window & image if n == 1 save
    // do calculs lol

}