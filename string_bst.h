#ifndef STRING_BST_H_
#define STRING_BST_H_

#include <stddef.h>

struct str_bst {
	char *str;
	size_t len;
	struct str_bst *left;
	struct str_bst *right;
	struct str_bst *parent;
};

struct str_bst *str_bst_init(const char *s, size_t len);
int str_bst_insert(struct str_bst **root, struct str_bst *node);
struct str_bst *
str_bst_find(const struct str_bst *tree, const char *str, size_t slen);
void str_bst_delete(struct str_bst **root, const char *str, size_t len);
struct str_bst *str_bst_get_min(const struct str_bst *root);
struct str_bst *str_bst_inorder_succ(const struct str_bst *root);
void str_bst_destroy(struct str_bst *n);

#endif /* STRING_BST_H_ */