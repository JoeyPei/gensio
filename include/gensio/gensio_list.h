/*
 *  gensio - A library for abstracting stream I/O
 *  Copyright (C) 2018  Corey Minyard <minyard@acm.org>
 *
 *  SPDX-License-Identifier: LGPL-2.1-only
 */

#ifndef GENSIO_LIST_H
#define GENSIO_LIST_H

#include <gensio/gensio_dllvisibility.h>
#include <stddef.h>

#define gensio_container_of(ptr, type, member)		\
    ((type *)(((char *) ptr) - offsetof(type, member)))

/*
 * Generic doubly-linked list operations.
 */
struct gensio_list;
struct gensio_link {
    struct gensio_list *list;
    struct gensio_link *next;
    struct gensio_link *prev;
};

struct gensio_list {
    struct gensio_link link;
};

GENSIO_DLL_PUBLIC
void gensio_list_rm(struct gensio_list *list, struct gensio_link *link);
GENSIO_DLL_PUBLIC
void gensio_list_add_head(struct gensio_list *list, struct gensio_link *link);
GENSIO_DLL_PUBLIC
void gensio_list_add_tail(struct gensio_list *list, struct gensio_link *link);
GENSIO_DLL_PUBLIC
void gensio_list_add_next(struct gensio_list *list, struct gensio_link *curr,
			  struct gensio_link *link);
GENSIO_DLL_PUBLIC
void gensio_list_add_prev(struct gensio_list *list, struct gensio_link *curr,
			  struct gensio_link *link);
GENSIO_DLL_PUBLIC
void gensio_list_init(struct gensio_list *list);
GENSIO_DLL_PUBLIC
bool gensio_list_empty(struct gensio_list *list);

#define gensio_list_first(list) ((list)->link.next)
#define gensio_list_last(list) ((list)->link.prev)
/* Go to the next entry, returning NULL if at the end. */
#define gensio_list_next(list, linkv) ((linkv)->next == &(list)->link ? \
				       NULL : (linkv)->next)
/* Go to the next entry, wrapping around to the first entry if at end. */
#define gensio_list_next_wrap(list, linkv) ((linkv)->next == &(list)->link ? \
					    (list)->link.next : (linkv)->next)

#define gensio_list_for_each(list, l)					\
    for ((l) = (list)->link.next; (l) != &(list)->link; l = l->next)

#define gensio_list_for_each_safe(list, l, l2) \
    for ((l) = (list)->link.next, (l2) = (l)->next; \
	 (l) != &(list)->link; (l) = (l2), (l2) = (l)->next )

#endif /* GENSIO_LIST_H */
