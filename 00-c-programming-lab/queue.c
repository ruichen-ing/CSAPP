/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  (queue_t*)malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if(q){
      q->head = NULL;
      q->tail = NULL;
      q->list_size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    while(q && q->head){
      list_ele_t *temp = q->head->next;
      free(q->head->value);
      free(q->head);
      q->head = temp;
      q->list_size -= 1;
    }
    /* Free queue structure */
    if(q){
      free(q);
    }
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{   
    /* What should you do if the q is NULL? */
    if(!q){
      return false;
    }
    list_ele_t *newh;
    newh = (list_ele_t*)malloc(sizeof(list_ele_t));
    /* What if either call to malloc returns NULL? */
    if(!newh){
      return false;
    }
    // strlen + 1 accounts for the null terminator \0 at the end of string, as this terminator is not counted when calling strlen
    char *newS = (char*)malloc((strlen(s) + 1) * sizeof(char));
    // why do we check if malloc returns NULL seperately for newS and newh?
    // Because we need to avoid memory leakage, that means if newS is NULL then we need to free the space of newh
    if(!newS){
      free(newh);
      return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    strcpy(newS, s);
    newh->value = newS;
    // head insertion
    newh->next = q->head;
    q->head = newh;
    if(!q->tail){
      q->tail = newh;
    }
    q->list_size += 1;
    return true;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if(!q){
      return false;
    }
    list_ele_t *newt = (list_ele_t*)malloc(sizeof(list_ele_t));
    if(!newt){
      return false;
    }
    char *newS = (char*)malloc((strlen(s) + 1) * sizeof(char));
    if(!newS){
      free(newt);
      return false;
    }
    strcpy(newS, s);
    newt->value = newS;
    // tail insertion
    newt->next = NULL;
    if(q->tail){
      q->tail->next = newt;
    }
    q->tail = newt;
    if(!q->head){
      q->head = newt;
    }
    q->list_size += 1;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if(!q || !q->head){
      return false;
    }
    list_ele_t *removed = q->head;
    q->head = q->head->next;
    if(q->tail == removed){
      q->tail = NULL;
    }
    q->list_size -= 1;
    if(sp){
      // no need to allocate space for sp as the space has been created for it in the caller function
      strncpy(sp, removed->value, bufsize - 1); // strncpy: copy at most bufsize - 1 characters from target to dest
      sp[bufsize - 1] = '\0';   // set the last character to \0, specifically when the target string is truncated
    }
    free(removed->value);
    free(removed);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q? q->list_size : 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if(!q || !q->head){
      return;
    }
    list_ele_t *curr = q->head->next;
    list_ele_t *pre = q->head;
    list_ele_t *temp = NULL;
    pre->next = NULL;
    while(curr){
      temp = curr->next;
      curr->next = pre;
      pre = curr;
      curr = temp;
    }
    temp = q->head;
    q->head = q->tail;
    q->tail = temp;
}