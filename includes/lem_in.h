/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:37:00 by dapinto           #+#    #+#             */
/*   Updated: 2019/10/04 11:26:00 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# define PREERROR "ERROR: There can be only comments before Antsnb."
# define ANTERROR "ERROR: Ant nb must be a positive int below INT_MAX, ONLY."
# define LINERROR "ERROR: Ant nb must be followed by comments or valid rooms."
# define MODERROR "ERROR: Modifiers are duplicated, null or have invalid room."
# define FMTERROR "ERROR: Room format invalid or empty line found."
# define FETERROR "ERROR: Fetcher couldn't return room node address."
# define MEMERROR "ERROR: Failed to allocate memory for input. Is file empty ?"
# define STRERROR "ERROR: Failed to initialize data structure."
# define MMLERROR "ERROR: Failed to allocate memory during linkage."
# define SEPERROR "ERROR: Failed to separate rooms in linkage."
# define HASERROR "ERROR: Failed to find links or to hash rooms."
# define MALLOCER "ERROR: Malloc failed to allocate memory."
# define WAYERROR "ERROR: No possible path."
# define START "##start"
# define END "##end"

typedef struct		s_stock
{
	int				io;
	int				room;
	int				max;
	int				ant;
	int				flow;
	int				ref;
	int				f;
	int				size;
	int				stop;
	int				verbose;
	int				i;
	int				j;
	int				*tab;
	int				*abp;
	int				turn;
	int				besturn;
	int				cprev;
	int				fourmi;
	int				first;
	int				malloc;
	struct s_wait	*update;
	struct s_list	*find;
	struct s_list	*final;
	struct s_wait	*free;
	struct s_list	*sat;
	struct s_list	*real_begin;
	struct s_final	*temp;
	char			prevsaturated;
	char			**matrix;
	char			**output;
	int				node;
}					t_stock;

typedef struct		s_paths
{
	char			*n;
	int				nu;
	int				io;
	int				saturated;
	struct s_paths	*next;
	struct s_list	*room;
}					t_paths;

typedef struct		s_list
{
	int				nu;
	char			*n;
	int				start;
	int				end;
	int				mark;
	int				saturated;
	long			ant_nb;
	struct s_list	*next;
	struct s_list	*find;
	struct s_paths	*path;
	struct s_list	*prev;
	struct s_list	*fpath;
	struct s_list	*pfpath;
	struct s_list	*pfnext;
	struct s_list	*fnext;
	struct s_list	*p;
}					t_list;

typedef struct		s_hash
{
	char			*room;
	int				startend;
	struct s_hash	*next_col;
}					t_hash;

typedef struct		s_wait
{
	struct s_list	*point;
	struct s_wait	*next;
	int				io;
}					t_wait;

typedef struct		s_parse_container
{
	long			ant_nb;
	int				room_nb;
	int				link_i;
	int				room_i;
	int				ants_i;
	int				verbose;
	char			*room1;
	char			*room2;
	t_hash			*room_ids;
	char			**output;
	char			**input;
}					t_parse;

void				max_flow(t_stock *stock, t_list *begin);
void				apply_flow(t_stock *stock);
void				apply_stock(t_stock *stock);
int					reverse_list(t_list *begin, t_stock *stock);
t_list				*anthill_info_parser(int fd, t_parse *container,
		t_stock *stk);
int					input_check(t_parse *box);
int					checknofeed(t_parse *box, int i);
int					is_room(char *line);
int					assert_validity(t_parse *box, int i);
int					assert_no_duplicate(t_parse *box, char *line, int i);
int					assert_room_existence(t_parse *box, char *room_name);
int					assert_correct_node(char *lst_node_name, char *target);
int					assert_no_multiple_modifiers(t_parse *box, int mod_i,
		char *mod, int lim);
int					room_description(t_parse *box);
int					link_description(t_parse *box, t_list *head);
t_list				*init_data_structure(t_parse *box);
t_list				*create_list(void);
void				free_list(t_list **head);
void				free_parser(t_parse **box);
void				printlst(t_list *head);
void				printhash(t_parse *box);
void				errout(int fg, char *mess);
void				free_hashtable(t_parse **box);
int					comment_clean(t_parse *box, int com);
int					hashtable(t_parse *box, char *room, int i);
int					rot_hash(t_parse *box, char *room, size_t len);
int					karp(t_stock *stock, t_list *begin);
void				create_malloc(t_stock *stock);
void				first_link(t_stock *stock, t_paths *curr);
void				current_saturated(t_stock *stock, t_paths *curr);
void				node_saturated(t_stock *stock, t_paths *curr);
void				opti_path(t_stock *stock, t_list *begin);
void				opti_path_next(t_stock *stock, t_list *begin,
		t_paths *curr, int i);
void				check_turn(t_stock *stock, int i);
void				sort_int_tab(t_stock *stock, int i);
void				max_flow(t_stock *stock, t_list *begin);
int					get_flow(t_stock *stock, t_list *begin, t_paths *curr);
t_wait				*add_list(t_stock *stock, t_list *elem, t_wait *list,
		int io);
t_list				*get_first_elem(t_stock *stock, t_wait *list);
t_wait				*check_add(t_stock *stock, t_list *begin, t_paths *curr,
		t_wait *list);
t_wait				*dispatch(t_stock *stock, t_list *begin, t_paths *curr,
		t_wait *list);
void				change_io(t_stock *stock);
char				check_sat(t_stock *stock, int a, int b);
void				init(t_stock *stock, t_list *begin);
void				remove_flow(t_stock *stock);
void				check_turn_next(t_stock *stock, int fourmi, int i, int j);
t_wait				*add_list_next(t_wait *begin, t_wait *list, t_wait *box);
void				init_get_flow(t_stock *stock, t_list *begin);
void				get_abp_next(t_stock *stock, int fourmi);
void				get_abp(t_stock *stock);
void				change_positions(t_stock *stock, t_list *curr,
		t_list *prev);
void				sort_list(t_stock *stock, t_list *begin);
void				cut_paths(t_stock *stock, t_list *begin);
void				prepare_path(t_stock *stock, t_list *begin, t_list *path,
		int i);
void				get_in_line(t_stock *stock, t_list *begin);
void				ft_put_tab(char **tab);
void				printer(t_stock *stk);
void				reverse_paths(t_list *begin);
void				aff(t_stock *stock);
void				set_to(t_list *path);
void				aff_next(t_stock *stock, t_list *begin, t_list *path);
void				set_start(t_stock *stock, t_list *prev);
void				free_wait(t_stock *stock);
void				free_all(t_stock *stock);
void				error(t_stock *stock);
int					direct_path(t_list *begin, t_stock *stock);
void				print_direct_path(t_list *begin, t_paths *curr);
void				add_another_path(t_list *begin, t_paths *curr);
int					error_msg(t_stock *stock);
char				**ft_feedsplit(char const *s, char c);
#endif
