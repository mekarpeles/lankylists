#include <stdio.h>
#include <stdlib.h>

#define LST_SIZE (4)

struct _Node {
  int car;
  struct _Node *cdr;
};

typedef struct _Node Node;

Node* Nodify(int value) {
  Node *n;
  n = (Node*)malloc(sizeof(Node));
  n->car = value;
  n->cdr = NULL;
  return n;
}

Node* List(int* values, int len) {  
  Node *car, *current, *next;
  car = (Node*)malloc(sizeof(Node));
  current = car;
  current->car = values[0];
  int ii=1;
  for (ii; ii<len; ii++) {
    next = Nodify(values[ii]);
    current->cdr = next;
    current = next;
  }
  return car;
}

Node* merge(Node* lst_a, Node* lst_b, int len_a, int len_b) {
  Node *head, *tail, *next;
  int a = 1;
  int b = 1;

  // Point head at lesser first element of lst_a, lst_b
  if(lst_a->car <= lst_b->car) {
    head = lst_a;
    lst_a = lst_a->cdr;
  } else {
    head = lst_b;
    lst_b = lst_b->cdr;
  }
  head->cdr = NULL;
  tail = head;

  // Compare heads of lst_a and lst_b:
  // Pop() the lower of the two and append() to tail
  while(a<=len_a && b<=len_b) {
    if (lst_a->car <= lst_b->car) {
      next = lst_a;
      lst_a = lst_a->cdr;
      tail->cdr = next;
      tail = next;
      a++;
    } else {
      next = lst_b;
      lst_b = lst_b->cdr;
      tail->cdr = next;
      tail = next;
      b++;
    }
    tail->cdr = NULL;
  }

  // Append remainder
  if(a<len_a) {
    tail->cdr = lst_a;
  } else if(b<len_b) {
    tail->cdr = lst_b;
  }
  return head;
}

int main(int argc, char *argv[]) {
  /*
  if(!argv[1] || !argv[2]) {
    puts("2 csv lists were not provided.");
    return 0;
  }
  int arr_a[] = str2int_arr(argv[1]);
  int arr_b[] = str2int_arr(argv[2]);
  */

  // Setup pre-sorted linked lists
  int arr_a[] = {3, 4, 6, 8};
  int arr_b[] = {2, 5, 7, 9};

  Node *lst_a = List(arr_a, LST_SIZE);
  Node *lst_b = List(arr_b, LST_SIZE);

  Node *lst = merge(lst_a, lst_b, LST_SIZE, LST_SIZE);
  Node *tmp = lst;

  printf("[");
  while(tmp) {
    printf("%d", tmp->car);
    if (tmp->cdr)
      printf(", "); 
    tmp = tmp->cdr;
  }
  printf("]\n");

  return 1;
}
