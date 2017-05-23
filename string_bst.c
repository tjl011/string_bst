/**
 * Example of a Binary Search Tree (BST) for strings in C89.
 * I like to make keys in the binary search tree to be unique.
 * I chose to use include a parent pointer to allow us to perform
 * in order traversal of all keys in the tree using constant memory.
 */

#include "string_bst.h"

#include <stdlib.h>
#include <string.h>

/**
 * Instantiate a new BST node.
 *
 * @param s - input string that acts as the 'key' for this BST node.
 * @return NULL on error (malloc failure or input s is NULL, otherwise
 *	   return instance 
 */
struct str_bst *str_bst_init(const char *s, size_t len)
{
	struct str_bst *n = NULL;

	if (!s)
		goto exit_error;

	n = malloc(sizeof(*n));
	if (!n)
		goto exit_error;

	n->str = malloc(sizeof(char) * (len + 1));
	if (!n->str)
		goto exit_error;

	memcpy(n->str, s, len);
	n->str[len] = '\0';
	n->len = len;

	n->parent = NULL;
	n->left = NULL;
	n->right = NULL;

	return n;

exit_error:
	free(n);

	return NULL;
}

/**
 * Deallocates all dynamic memory associated with node 'n'.
 */
void str_bst_destroy(struct str_bst *n)
{
	if (n) {
		free(n->str);
		free(n);
	}
}

int str_bst_insert(struct str_bst **root, struct str_bst *node)
{
	int ret;
	size_t len;
	if (!(*root)) {
		*root = node;
		return 0;
	}

	while (*root) {
		len = node->len > (*root)->len ? (*root)->len : node->len;
		ret = strncmp((*root)->str, node->str, len);

		if (ret == 0) {
			if (node->len > (*root)->len)
				ret = -1;
			else if (node->len < (*root)->len)
				ret = 1;
		}

		if (ret < 0) {
			if ((*root)->right) {
				root = &(*root)->right;
			} else {
				(*root)->right = node;
				node->parent = *root;
				return 0;
			}
		} else if (ret > 0) {
			if ((*root)->left) {
				root = &(*root)->left;
			} else {
				(*root)->left = node;
				node->parent = *root;
				return 0;
			}
		} else {
			return -1;
		}
	}
	return -1;
}

struct str_bst *
str_bst_find(const struct str_bst *tree, const char *str, size_t slen)
{
	int cmp;
	size_t len;

	while (tree) {
		len = tree->len > slen ? slen : tree->len;
		cmp = strncmp(tree->str, str, len);
		if (cmp < 0) {
			tree = tree->right;
		} else if (cmp > 0) {
			tree = tree->left;
		} else {
			if (tree->len > slen)
				tree = tree->left;
			else if (tree->len < slen)
				tree = tree->right;
			else
				break;
		}
	}

	return (struct str_bst *)tree;
}

static void
update_parent_ref(struct str_bst **root, struct str_bst *node, struct str_bst *succ)
{
	struct str_bst *par = node->parent;
	if (par) {
		if (par->left == node)
			par->left = succ;
		else
			par->right = succ;
	}
	if (succ)
		succ->parent = par;
	
	/* check if root is going to be replaced */
	if (*root == node)
		*root = succ;
}

void str_bst_delete(struct str_bst **root, const char *str, size_t len)
{
	struct str_bst *n, *succ;
	n = str_bst_find(*root, str, len);
	if (!n) {
		return;
	}

	while (n) {
		/* node to delete has no children */
		if (!n->left && !n->right) {
			succ = NULL;
			update_parent_ref(root, n, succ);
			str_bst_destroy(n);
			break;
		}
		/* node only has left child */
		else if (n->left && !n->right) {
			succ = n->left;
			update_parent_ref(root, n, succ);
			str_bst_destroy(n);
			break;
		}
		/* node only has right child */
		else if (!n->left && n->right) {
			succ = n->right;
			update_parent_ref(root, n, succ);
			str_bst_destroy(n);
			break;
		}
		/* node has two children */ 
		else {
			succ = str_bst_get_min(n->right);
			free(n->str);
			n->str = succ->str;
			n->len = succ->len;
			succ->str = NULL;
			n = succ;
		}
	}
}

struct str_bst *str_bst_get_min(const struct str_bst *root)
{
	if (!root)
		return NULL;
	
	while (root->left)
		root = root->left;

	return (struct str_bst *)root;
}

struct str_bst *str_bst_inorder_succ(const struct str_bst *root)
{
	struct str_bst *par;

	if (!root)
		return NULL;

	if (root->right)
		return str_bst_get_min(root->right);
	
	par = root->parent;
	while (par && par->left != root) {
		root = par;
		par = par->parent;
	}
	return (struct str_bst *)par;
}
