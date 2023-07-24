#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>



int poweroften(int power);



typedef struct ListNode {
      int val;
      struct ListNode *next;
}ListNode;




int addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    int counterl1 = 0;
    int counterl2 = 0;
    int l1Value = 0;
    int l2Value = 0;
    int l3Value = 0;
    for (ListNode *tmp = l1; tmp != NULL; tmp = tmp->next)
    {
        l1Value = l1Value + tmp->val * poweroften(counterl1);
        counterl1++;
    }

    for (ListNode *tmp = l2; tmp != NULL; tmp = tmp->next)
    {
        l2Value = l2Value + tmp->val * poweroften(counterl2);
        counterl2++;
    }

    l3Value = l1Value + l2Value;
    return l3Value;


}
int main()
{
      ListNode *l1 = NULL;
      ListNode *n = malloc(sizeof(ListNode));

      if (n == NULL)
      {
          return 1;
      }
      n->val = 2;
      n->next = NULL;

      l1 = n;

      n = malloc(sizeof(ListNode));
      if (n == NULL)
      {
          free(l1);
          return 1;
      }
      n->val = 4;
      n->next = NULL;
      l1->next = n;


      n = malloc(sizeof(ListNode));
      if (n == NULL)
      {
          free(l1->next);
          free(l1);
          return 1;
      }


      n->val = 3;
      n->next = NULL;
      l1->next->next = n;


      for (ListNode *tmp = l1; tmp != NULL; tmp = tmp->next)
      {
          printf("%i\n", tmp->val);
      }







}


int poweroften(int power)
{
    int base = 1;
    for (int i = 0; i < power; i++ )
    {
        base= base* 10;
    }
    return base;
}





