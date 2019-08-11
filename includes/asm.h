/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:41:10 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/07 14:46:32 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"

# define LIVE 0x01
# define LD 0x02
# define ST 0x03
# define ADD 0x04
# define SUB 0x05
# define AND 0x06
# define OR 0x07
# define XOR 0x08
# define ZJMP 0x09
# define LDI 0x0A
# define STI 0x0B
# define FORK 0x0C
# define LLD 0x0D
# define LLDI 0x0E
# define LFORK 0x0F
# define AFF 0x10

# define COM 1
# define NAME 2

# define ISSEP 0
# define RET 1
# define NB 2
# define I 3
# define TMPRET 0
# define TMPI 2
# define J 4

typedef struct	s_file
{
	int		fdopen;
	int		fdwrite;
	char	*name;
}				t_file;

typedef struct	s_gnl
{
	int		nbline;
	char	*line;
}				t_gnl;

typedef struct	s_op
{
	char			*label;
	char			*searchlabel[3];
	int				size;
	int				addr;
	int				nbarg;
	char			inst;
	int				code[3];
	int				param[3];
	int				line;
	struct s_op		*next;
}				t_op;

typedef struct	s_asm
{
	t_op	*op;
	t_gnl	gnl;
	t_file	file;
	int		n_param;
	int		error;
}				t_asm;

/*
** FILE
*/

char			*ft_recupfile(char *name);
int				createfile(char *name);
int				ft_closeall(t_asm tasm);
int				start(char **av, t_file *file, int i);
int				ft_strok(char **trim, t_asm *tasm, t_gnl *gnl, int nbline);
int				ft_retmulterr(char **str, char **trim, char ***split);

/*
** HEADER
*/

int				printfile(t_header *header, t_asm *tasm);
int				ft_recup(t_header *header, t_asm *tasm, int *len, int type);
int				ft_nbquote(char *str);
char			*ft_strjoinfree1(char *s1, char *s2);
int				ft_multiline(t_asm *tasm, char **trim, char ***split);

/*
 ** ERROR
*/

int				ft_freecom(char ***tab, int err, char *str, t_gnl *gnl);
int				ft_free(char ***tab, int err, t_gnl *gnl, char **str);
int				ft_syntax(char **tab, t_asm *tasm, char c);
int				ft_errorparams(t_asm *tasm, char *s);

/*
** TOOLS
*/

int				ft_retgnl(t_asm *tasm, int i);
char			ft_opc(int code[3]);
int				ft_separator(char **str, int nb, t_asm *tasm);
unsigned long	ft_atui(const char *str);
int				ft_diffis(const char *s1, const char *s2);
int				ft_strclentab(const char *s1, char print, char *str, int occ);
void			ft_strprintspaces(const char *s1);
char			*ft_charwtspaces(char *str);
int				ft_passtab(char *line, int *i, int ret);
int				accept_d4(int inst);
int				ft_lentab2d(char **split);

/*
** INSTRUCTIONS & LABEL
*/

int				ft_filld(char **split, t_asm *tasm, int size);
int				ft_filli(char **split, t_asm *tasm);
int				ft_fillrg(char **split, t_asm *tasm);
void			ft_fillinstop(char *inst, t_op *op);
int				ft_idd(char **split, t_asm *tasm, int size);
int				ft_rgd(char **split, t_asm *tasm, int size);
int				ft_rgidd(char **split, t_asm *tasm, int size);
int				ft_rgid(char **split, t_asm *tasm);

int				ft_readinst(t_asm *tasm);
int				ft_readn(t_file file, char **line, int *ret);
int				ft_instructions(char **trim, t_asm *tasm);

int				ft_paramd(char **split, t_asm *tasm, int size);
int				ft_paramrg(char **split, t_asm *tasm);
int				ft_paramld(char **split, t_asm *tasm);
int				ft_paramst(char **split, t_asm *tasm);
int				ft_param3rg(char **split, t_asm *tasm);
int				ft_paramldi(char **split, t_asm *tasm);
int				ft_paramsti(char **split, t_asm *tasm);
int				ft_paramcomp(char **split, t_asm *tasm);

void			ft_fillparam1(t_asm *tasm, int size, int code,
		unsigned int param1);
void			ft_fillparam2(t_op *op, int size, int code,
		unsigned int param2);
void			ft_fillparam3(t_op *op, int size, int code,
		unsigned int param3);

unsigned int	ft_filllabel(t_asm *tasm, char **split);
int				ft_searchlabel(t_asm *tasm, int err);
void			write_code(t_file *file, t_op *op);
int				ft_label(char *trim, t_gnl *gnl, t_op *new);

#endif
