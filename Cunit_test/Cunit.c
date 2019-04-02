#include "CUnit/Basic.h"
#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ************************** PRIORITY QUEUE **************************
typedef struct _node {
  unsigned char item;
  int priority;
  struct _node *next, *left, *right;
} node;

typedef struct _priority_queue {
  node *head;
} priority_queue;

priority_queue *create_priority_queue() {
  priority_queue *new_pq = (priority_queue *)malloc(sizeof(priority_queue));
  new_pq->head = NULL;
  return new_pq;
}

int is_empty_pq(priority_queue *pq) { return (pq->head == NULL); }

void enqueue(priority_queue *pq, char i, int p) {
  node *new_node = (node *)malloc(sizeof(node));
  new_node->item = i;
  new_node->priority = p;

  if ((is_empty_pq(pq)) || (p <= pq->head->priority)) {
    new_node->next = pq->head;
    pq->head = new_node;
  } else {
    node *current = pq->head;

    while ((current->next != NULL) &&
           (current->next->priority < new_node->priority)) {
      current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
  }
}

node *dequeue(priority_queue *pq) {
  if (is_empty_pq(pq)) {
    printf("Priority Queue underflow");
    return NULL;
  } else {
    node *node = pq->head;
    pq->head = pq->head->next;
    node->next = NULL;
    return node;
  }
}

// ************************************************************************

int init_suite(void) { return 0; }

int clear_suite(void) { return 0; }

void test_enqueue() {
  priority_queue *test = create_priority_queue();

  int item1 = 5;
  int item2 = 4;
  int item3 = 3;
  int item4 = 2;
  int item5 = 1;

  enqueue(test, item3, 10);
  enqueue(test, item1, 15);
  enqueue(test, item4, 5);
  dequeue(test);

  CU_ASSERT_EQUAL(test->head->item, item3);

  enqueue(test, item5, 1);
  enqueue(test, item2, 4);

  CU_ASSERT(test->head->left == NULL);
  CU_ASSERT(test->head->right == NULL);
}

int main() {
  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry()) {
    return CU_get_error();
  }

  /* add a suite to the registry */
  pSuite = CU_add_suite("Basic_Test_Suite", init_suite, clear_suite);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if (NULL == CU_add_test(pSuite, "test enqueue", test_enqueue)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
