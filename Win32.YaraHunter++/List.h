#pragma once
#include <malloc.h>
#include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}t_list;

extern "C" void	lst_free(t_list *lst);
extern "C" t_list	*lstlast(t_list *lst);
extern "C" void	lstadd_back(t_list **lst, t_list *new_node);
extern "C" t_list	*lstnew(void *content);
