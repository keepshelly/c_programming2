#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>
#include "linked_list.h"

static void test_create_node(void **state) {
    (void)state;
    struct node* n = createNode(42);
    assert_non_null(n);
    assert_int_equal(n->data, 42);
    assert_null(n->next);
    assert_null(n->prev);
    free(n);
}

static void test_append_to_empty(void **state) {
    (void)state;
    struct node* head = NULL;
    append(&head, 10);
    assert_non_null(head);
    assert_int_equal(head->data, 10);
    assert_null(head->next);
    assert_null(head->prev);
    freeList(head);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_create_node),
        cmocka_unit_test(test_append_to_empty),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}