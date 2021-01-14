#include "list.h"
#include "list.c"
#include <stdlib.h>
#include <stdio.h>

 static bool searchCase(void* pItem, void* pComparisonArg){
     if(*(int *)pItem == *(int *) pComparisonArg){
         return 1;
     }
     return 0;
 }

 static void complexTestFreeFn(void* pItem){
     pItem = NULL;
 }

int main()
{
    // List_create();
    // Creating 11 lists to see if an error is thrown on the 11th list creation
    List* list1 = List_create();
    List* list2 = List_create();
    List* list3 = List_create();
    List* list4 = List_create();
    List* list5 = List_create();
    List* list6 = List_create();
    List* list7 = List_create();
    List* list8 = List_create();
    List* list9 = List_create();
    List* list10 = List_create();
    List* list11 = List_create();
    printf("\n");


    // List_free(List* pList, FREE_FN pItemFreeFn);
    // Freeing all 10 lists
    List_free(list1, complexTestFreeFn);
    List_free(list2, complexTestFreeFn);
    List_free(list3, complexTestFreeFn);
    List_free(list4, complexTestFreeFn);
    List_free(list5, complexTestFreeFn);
    List_free(list6, complexTestFreeFn);
    List_free(list7, complexTestFreeFn);
    List_free(list8, complexTestFreeFn);
    List_free(list9, complexTestFreeFn);
    List_free(list10, complexTestFreeFn);
    printf("\n");


    // List_count(List* pList);
    // creating new list
    List* l1 = List_create();

    // Testing List_count with empty and non empty lists
    // counting nodes in and empty list
    int num = List_count(l1);
    printf("%d is the length (empty list)\n", num);

    // counting nodes after appending values to list
    int x0 = 64;
    List_append(l1, &x0);
    printf("%d is the length after appending 64\n", List_count(l1));

    int x1 = 89;
    List_append(l1, &x1);
    printf("%d is the length after appending 89\n\n", List_count(l1));

    List_free(l1, complexTestFreeFn);


    // List_first(List* pList); List_curr(List* pList); and List_last(List* pList);
    List* l2 = List_create();
    // getting first item in an empty list
    void *f0 = List_first(l2);
    if(f0 == NULL) {
        printf("Returned NULL!\n");
    } else {
        printf("The first element is %d\n", *(int *) f0);
    }

    // getting current item in an empty list
    void *f1 = List_curr(l2);
    if(f1 == NULL) {
        printf("Returned NULL!\n");
    } else {
        printf("The current element is %d\n", *(int *)f1);
    }

    // getting last item in an empty list
    void *f2 = List_last(l2);
    if(f2 == NULL) {
        printf("Returned NULL!\n\n");
    } else {
        printf("The last element is %d\n\n", *(int *) f2);
    }


    // prepending values to list
    int x2 = 46;
    List_prepend(l2, &x2);
    // getting first item in a list with size 1
    void *f3 = List_first(l2);
    if(f3 == NULL) {
        printf("Returned NULL!\n");
    } else {
        printf("The first element is %d\n", *(int *) f3);
    }

    // getting current item in a list with size 1
    void *f4 = List_curr(l2);
    if(f4 == NULL) {
        printf("Returned NULL!\n");
    } else {
        printf("The current element is %d\n", *(int *)f4);
    }

    // getting last item in a list with size 1
    void *f5 = List_last(l2);
    if(f5 == NULL) {
        printf("Returned NULL!\n\n");
    } else {
        printf("The last element is %d\n\n", *(int *) f5);
    }


    // prepending values to list
    int x3 = 2;
    int x4 = 53;
    int x5 = 92;
    List_prepend(l2, &x3);
    List_prepend(l2, &x4);
    List_prepend(l2, &x5);
    // getting first item in a list with size >1
    void *f6 = List_first(l2);
    if(f6 == NULL) {
        printf("Returned NULL!\n");
    } else {
        printf("The first element is %d\n", *(int *) f6);
    }

    // getting current item in a list with size >1
    void *f7 = List_curr(l2);
    if(f7 == NULL) {
        printf("Returned NULL!\n");
    } else {
        printf("The current element is %d\n", *(int *)f7);
    }

    // getting last item in a list with size >1
    void *f8 = List_last(l2);
    if(f8 == NULL) {
        printf("Returned NULL!\n");
    } else {
        printf("The last element is %d\n\n", *(int *) f8);
    }

    printList(l2);


    // List_next(List* pList); List_prev(List* pList);
    List_first(l2);
    List_prev(l2);

    // moving to the next node in the list when current node is before the start of the list
    void *f10 = List_next(l2);
    if(f10 == NULL) {
        printf("Returned NULL!\n");
    } else {
        printf("The next element is %d\n", *(int *) f10);
    }

    List_next(l2);
    // moving to the next node in the list
    void *f11 = List_next(l2);
    if(f11 == NULL) {
        printf("Returned NULL!\n");
    } else {
        printf("The next element is %d\n", *(int *) f11);
    }

    List_next(l2);
    // moving to the next node in the list when current node is the tail
    void *f12 = List_next(l2);
    if(f12 == NULL) {
        printf("Returned NULL!\n");
    } else {
        printf("The next element is %d\n", *(int *) f12);
    }

    // moving to the next node in the list when current node is beyond the tail of the list
    void *f13 = List_next(l2);
    if(f13 == NULL) {
        printf("Returned NULL!\n\n");
    } else {
        printf("The next element is %d\n\n", *(int *) f13);
    }


    // moving to the previous node in the list when current node is beyond the end of the list
    void *f14 = List_prev(l2);
    if(f14 == NULL) {
        printf("Returned NULL!\n");
    } else {
        printf("The previous element is %d\n", *(int *) f14);
    }

    List_prev(l2);
    // moving to the next node in the list
    void *f15 = List_prev(l2);
    if(f15 == NULL) {
        printf("Returned NULL!\n");
    } else {
        printf("The previous element is %d\n", *(int *) f15);
    }

    List_prev(l2);
    // moving to the next node in the list when current node is the tail
    void *f16 = List_prev(l2);
    if(f16 == NULL) {
        printf("Returned NULL!\n");
    } else {
        printf("The previous element is %d\n", *(int *) f16);
    }

    // moving to the next node in the list when current node is beyond the tail of the list
    void *f17 = List_prev(l2);
    if(f17 == NULL) {
        printf("Returned NULL!\n\n");
    } else {
        printf("The previous element is %d\n", *(int *) f17);
    }

    List_free(l2, complexTestFreeFn);
    printf("\n");


    // List_add(List* pList, void* pItem);
    List* l3 = List_create();

    // Adding an item to an empty list
    int r0 = 77;
    int xyz0 = List_add(l3, &r0);
    if(xyz0 == 0) {
        printf("Item added successfully\n");
    } else {
        printf("Item could not be added\n");
    }
    printList(l3);

    // Adding an item to a list when the current node is before the start of the list
    List_prev(l3);
    int r1 = 3;
    int xyz1 = List_add(l3, &r1);
    if(xyz1 == 0) {
        printf("Item added successfully\n");
    } else {
        printf("Item could not be added\n");
    }
    printList(l3);

    // Adding an item to a list when the current node is after the end of the list
    List_next(l3);
    List_next(l3);
    int r2 = 4;
    int xyz2 = List_add(l3, &r2);
    if(xyz2 == 0) {
        printf("Item added successfully\n");
    } else {
        printf("Item could not be added\n");
    }
    printList(l3);

    // Adding an item to a list when the current node is somewhere in the middle of the list
    List_prev(l3);
    int r4 = 15;
    int xyz4 = List_add(l3, &r4);
    if(xyz4 == 0) {
        printf("Item added successfully\n");
    } else {
        printf("Item could not be added\n");
    }
    printList(l3);

    List_free(l3, complexTestFreeFn);
    printf("\n");



    // List_insert(List* pList, void* pItem);
    List* l4 = List_create();

    // Inserting an item to an empty list
    int r5 = 77;
    int xyz5 = List_insert(l4, &r5);
    if(xyz5 == 0) {
        printf("Item inserted successfully\n");
    } else {
        printf("Item could not be inserted\n");
    }
    printList(l4);

    // Inserting an item to a list when the current node is before the start of the list
    List_prev(l4);
    int r6 = 3;
    int xyz6 = List_insert(l4, &r6);
    if(xyz6 == 0) {
        printf("Item inserted successfully\n");
    } else {
        printf("Item could not be inserted\n");
    }
    printList(l4);

    // Inserting an item to a list when the current node is after the end of the list
    List_next(l4);
    List_next(l4);
    int r7 = 4;
    int xyz7 = List_insert(l4, &r7);
    if(xyz7 == 0) {
        printf("Item inserted successfully\n");
    } else {
        printf("Item could not be inserted\n");
    }
    printList(l4);

    // Inserting an item to a list when the current node is somewhere in the middle of the list
    List_prev(l4);
    int r8 = 15;
    int xyz8 = List_insert(l4, &r8);
    if(xyz8 == 0) {
        printf("Item inserted successfully\n");
    } else {
        printf("Item could not be inserted\n");
    }
    printList(l4);

    List_free(l4, complexTestFreeFn);
    printf("\n");



    // List_append(List* pList, void* pItem);
    List* l5 = List_create();

    // Appending an item to an empty list
    int r9 = 77;
    int xyz9 = List_append(l5, &r9);
    if(xyz9 == 0) {
        printf("Item appended successfully\n");
    } else {
        printf("Item could not be appended\n");
    }
    printList(l5);

    // Appending an item to a list when the current node is before the start of the list
    List_prev(l5);
    int r10 = 3;
    int xyz10 = List_append(l5, &r10);
    if(xyz10 == 0) {
        printf("Item appended successfully\n");
    } else {
        printf("Item could not be appended\n");
    }
    printList(l5);

    // Appending an item to a list when the current node is after the end of the list
    List_next(l5);
    List_next(l5);
    int r11 = 4;
    int xyz11 = List_append(l5, &r11);
    if(xyz11 == 0) {
        printf("Item appended successfully\n");
    } else {
        printf("Item could not be appended\n");
    }
    printList(l5);

    // Appending an item to a list when the current node is somewhere in the middle of the list
    List_prev(l5);
    int r12 = 15;
    int xyz12 = List_append(l5, &r12);
    if(xyz12 == 0) {
        printf("Item appended successfully\n");
    } else {
        printf("Item could not be appended\n");
    }
    printList(l5);

    List_free(l5, complexTestFreeFn);
    printf("\n");



    // List_prepend(List* pList, void* pItem);
    List* l6 = List_create();

    // Prepending an item to an empty list
    int r13 = 77;
    int xyz13 = List_append(l6, &r13);
    if(xyz13 == 0) {
        printf("Item prepended successfully\n");
    } else {
        printf("Item could not be prepended\n");
    }
    printList(l6);

    // Prepending an item to a list when the current node is before the start of the list
    List_prev(l6);
    int r14 = 3;
    int xyz14 = List_append(l6, &r14);
    if(xyz14 == 0) {
        printf("Item prepended successfully\n");
    } else {
        printf("Item could not be prepended\n");
    }
    printList(l6);

    // Prepending an item to a list when the current node is after the end of the list
    List_next(l6);
    List_next(l6);
    int r15 = 4;
    int xyz15 = List_append(l6, &r15);
    if(xyz15 == 0) {
        printf("Item prepended successfully\n");
    } else {
        printf("Item could not be prepended\n");
    }
    printList(l6);

    // Prepending an item to a list when the current node is somewhere in the middle of the list
    List_prev(l6);
    int r16 = 15;
    int xyz16 = List_append(l6, &r16);
    if(xyz16 == 0) {
        printf("Item prepended successfully\n");
    } else {
        printf("Item could not be prepended\n");
    }
    printList(l6);

    List_free(l6, complexTestFreeFn);
    printf("\n");



    // List_concat(List* pList1, List* pList2);
    // creating 2 new lists
    List* l7 = List_create();
    List* l8 = List_create();

    // concatenating 2 empty lists
    List_concat(l7, l8);
    printf("concatenating 2 empty lists\n");
    printList(l7);
    printf("\n");

    List* l9 = List_create();
    // concatenating 2 non empty lists
    List_append(l7, &r13);
    List_append(l7, &r14);
    List_append(l9, &r15);
    List_append(l9, &r16);
    List_concat(l7, l9);
    printf("concatenating 2 non empty lists\n");
    printList(l7);
    printf("\n");

    List* l10 = List_create();
    // concatenating an empty list with a non empty lists
    List_concat(l10, l7);
    printf("concatenating an empty list with a non empty lists\n");
    printList(l10);
    printf("\n");


    // List_remove(List* pList);
    // removing an element from before the head of the list
    void *t0 = List_remove(l10);
    if(t0 == NULL) {
        printf("Returned NULL!\n");
    } else {
        printf("The removed element is %d\n", *(int *) t0);
    }
    printList(l10);

    // removing an element from middle of the list
    List_next(l10);
    List_next(l10);
    void *t1 = List_remove(l10);
    if(t1 == NULL) {
        printf("Returned NULL!\n");
    } else {
        printf("The removed element is %d\n", *(int *) t1);
    }
    printList(l10);



    return 0;
}