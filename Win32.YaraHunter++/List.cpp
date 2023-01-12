#include "List.h"

extern "C" void lst_free(t_list *lst) {
	t_list *aux;
	while (lst) {
		aux = lst->next;
		free(lst->content);
		free(lst);
		if (!aux)
			break;
		lst = aux;
	}
}

extern "C" t_list	*lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

extern "C" void	lstadd_back(t_list **lst, t_list *new_node)
{
	if (!lst || !new_node)
		return;
	if (*lst)
		lstlast(*lst)->next = new_node;
	else
		*lst = new_node;
}

extern "C" t_list	*lstnew(void *content)
{
	t_list	*lst;

	lst = (t_list*)malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}