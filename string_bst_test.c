/**
 * Test file for string_bst source code.
 */

#include "string_bst.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static const char *test_data[] = {
	"a",
	"aabc"
	"b",
	" ",
	"12345",
	"qwerty",
	"tom",
	"testfail",
	"c",
	"d",
	"e",
	"f",
	"g",
	"h",
	"i",
	"j",
	"k",
	"l",
	"m"
};

void inorder_print(const struct str_bst *tree)
{
	if (!tree)
		return;
	inorder_print(tree->left);
	printf("%s\n", tree->str);
	inorder_print(tree->right);
}

int main(void)
{
	struct str_bst *tree = NULL;
	struct str_bst *n = NULL;
	size_t i;

	for (i = 0; i < sizeof(test_data) / sizeof(*test_data); i++) {
		n = str_bst_init(test_data[i], strlen(test_data[i]));
		if (!n) {
			printf("%s(): error insertion failed for \"%s\"\n", __func__, test_data[i]);
		}
		if (str_bst_insert(&tree, n) < 0) {
			printf("%s(): error insertion failed for \"%s\"\n", __func__, test_data[i]);
		}
	}

	printf("printing in order\n");
	inorder_print(tree);

	printf("\n\nfind each node!\n");
	for (i = 0; i < sizeof(test_data) / sizeof(*test_data); i++) {
		n = str_bst_find(tree, test_data[i], strlen(test_data[i]));
		if (!n) {
			printf("error failed to find '%s' in tree!\n", test_data[i]);
		}
		else if (strcmp(n->str, test_data[i])) {
			printf("error returned node '%s' != '%s'\n", n->str, test_data[i]);
		}
	}

	return 0;
}