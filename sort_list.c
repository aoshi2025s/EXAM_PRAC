/*
 * typedef struct s_list
 * {
 *  int data;
 *  t_list *next;
 *  } t_list;
*/

#include "list.h"

void	swap_list_data(t_list *a, t_list *b)
{
	int swap = a->data;
	a->data = b->data;
	b->data = swap;
}

t_list *sort_list(t_list* lst, int (*cmp)(int, int))
{
	t_list *curr = lst;
	int swap_all_ok = 0;

	while (swap_all_ok == 0)
	{
		curr = lst;
		swap_all_ok = 1;
		while (curr && curr->next)
		{
			if ((cmp)(curr->data, curr->next->data) == 0)
			{
				swap_list_data(curr, curr->next);
				swap_all_ok = 0;
			}
			curr = curr->next;
		}
	}
	return (lst);
}
