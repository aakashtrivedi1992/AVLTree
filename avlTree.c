#include <stdio.h>
#include <stdlib.h>


typedef struct avlNode *avlPTR;

struct avlNode
{
   int element;
   avlPTR left;
   avlPTR right;
   avlPTR parent;
   int height;
} avlNode;

typedef avlPTR SEARCHTREE;


SEARCHTREE createTree(void)
{
   SEARCHTREE avlTree = (SEARCHTREE)malloc(sizeof(struct avlNode));

   if (avlTree == NULL)
   {
      printf("Out of space.\n");
   }

   return avlTree;
}

int maxHeight(int a, int b)
{
   if (a > b)
   {
      return a;
   }
   
   else
   {
      return b;
   }
}

int height(avlPTR p)
{
   if (p == NULL)
   {
      return -1;
   }
   
   else
   {
      return p->height;
   }
}

SEARCHTREE singleRotationRight(SEARCHTREE k2)
{
   SEARCHTREE k1;

   k1 = k2->right;
   k2->right = k1->left;
   k1->left = k2;
   k2->height = maxHeight(height(k2->left), height(k2->right)) + 1;
   k1->height = maxHeight(height(k1->right), k2->height) + 1;

   return k1;
}

avlPTR singleRotationLeft(avlPTR k2)
{
   avlPTR k1;

   k1 = k2->left;
   k2->left = k1->right;
   k1->right = k2;
   k2->height = maxHeight(height(k2->left), height(k2->right)) + 1;
   k1->height = maxHeight(height(k1->left), k2->height) + 1;

   return k1;
}

avlPTR doubleRotationLeft(avlPTR k3)
{
   k3->left = singleRotationRight(k3->left);

   return (singleRotationLeft(k3));
}

avlPTR doubleRotationRight(avlPTR k3)
{
   k3->right = singleRotationLeft(k3->right);

   return (singleRotationRight(k3));
}

SEARCHTREE insert(int x, SEARCHTREE T)
{
   if (T == NULL)
   {
      T = (SEARCHTREE)malloc(sizeof (struct avlNode));
   
      if (T == NULL)
      {
         printf("Out of space.\n");
      }
      
      else
      {
         T->element = x; T->height = 0;
         T->left = T->right = NULL;
      }
   }
   
   else
   {
      if (x < T->element)
      {
         T->left = insert(x, T->left);
      
         if ((height(T->left) - height(T->right)) == 2)
         {
            if (x < T->left->element)
            {
               T = singleRotationLeft(T);
            }
            
            else
            {
               T = doubleRotationLeft(T);
            }
         }
      }
      
      else if (x > T -> element)
      {
         T->right = insert(x, T->right);
      
         if ((height (T->right) - height(T->left)) == 2)
         {
            if (x > T->right->element)
            {
               T = singleRotationRight (T);
            }
            
            else
            {
               T = doubleRotationRight (T);
            }
         }
      }
   
      T->height = maxHeight(height(T->left), height(T->right)) + 1;
   }

   return T;
}

void inOrder(SEARCHTREE T)
{
   if (T != NULL)
   {
      inOrder(T->left);
      printf("%d ",T->element);
      inOrder(T->right);
   }
}

void preOrder(SEARCHTREE T)
{
   if (T != NULL)
   {
      printf("%d ",T->element);
      preOrder(T->left);
      preOrder(T->right);
   }
}

void postOrder(SEARCHTREE T)
{
   if(T != NULL)
   {
      postOrder(T->left);
      postOrder(T->right);
      printf("%d ",T->element);
   }
}

int main(int argc, char *argv[])
{
   SEARCHTREE avlTree = NULL;
   int a = 0;
   int i = 0;
   int inputValue = 0;
   int sortTreeSize;

   printf("Type in how many numbers you want to sort: ");
   scanf("%d", &sortTreeSize);

   printf("\n\nPlease type in each number you want to sort.\n");

   for (a = 0; a < sortTreeSize; a++)
   {
      scanf("%d", &inputValue);
      avlTree = insert(inputValue, avlTree);
   }

   printf("\nEnter the traversal you want\n");
   printf("1.Inorder.\n2.Preorder.\n3.Postorder.\n\n");
   scanf("%d",&i);

   switch(i)
   {
      case 1:
         {
            printf("\nThe inorder traversal is:\n");
            inOrder(avlTree);
         }
         break;
   
      case 2:
         {
            printf("\nThe preorder traversal is:\n");
            preOrder(avlTree);
         }
         break;
   
      case 3:
         {
            printf("\nThe postorder traversal is:\n");
            postOrder(avlTree);
         }
         break;
   }

   printf("\n\n");

   return 0;
}
