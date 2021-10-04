#include <stdio.h>
#include <stdlib.h>

int visited[5] = { 0, };

typedef struct Node
{
  int vertex;
  struct Node* link;
} node;

typedef struct NodeList
{
  struct Node* nodes[5];
} nodeList;

node* Init(int v)
{
  node* n = (node*)malloc(sizeof(node));

  n->vertex = v;
  n->link = NULL;

  return n;
}

void Connect(nodeList* nl, node* n, int v)
{
  node* newNode = (node*)malloc(sizeof(node));
  node* temp;
  nodeList* temp2;

  newNode->vertex = v;
  newNode->link = NULL;

  for(temp = n; ; temp = temp->link)
  {
    if(temp->link == NULL)
    {
      temp->link = newNode;
      break;
    }
  }

  if(visited[n->vertex] == 0)
  {
    visited[n->vertex] = 1;
    nl->nodes[n->vertex] = n;
  }
}

void Visit(nodeList* nl, node* n)
{
  visited[n->vertex] = 1;
  printf("[ 정점 %d 방문 ] -> ", n->vertex);

  for(node* temp = n->link; temp != NULL; temp = temp->link)
  {
    printf("정점 %d 탐색 여부 파악 중... -> ", temp->vertex);

    if(visited[temp->vertex] == 0)
    {
      Visit(nl, nl->nodes[temp->vertex]);
    }
    else
    {
      printf("정점 %d 은/는 이미 탐색했습니다 ->  ", temp->vertex);
    }

    if(temp->link == NULL)
    {
      printf("깊이 우선 탐색 종료");

      for(int i = 0; i < 5; i++)
      {
        free(nl->nodes[i]);
      }
      free(nl);

      exit(0);
    }
  }
}

int main(void)
{
  nodeList *nl;
  nl = (nodeList*)malloc(sizeof(nodeList));

  node* n0 = Init(0);
  node* n1 = Init(1);
  node* n2 = Init(2);
  node* n3 = Init(3);
  node* n4 = Init(4);

  Connect(nl, n0, 1);
  Connect(nl, n0, 2);
  Connect(nl, n0, 4);
  Connect(nl, n1, 0);
  Connect(nl, n1, 2);
  Connect(nl, n2, 0);
  Connect(nl, n2, 1);
  Connect(nl, n2, 3);
  Connect(nl, n2, 4);
  Connect(nl, n3, 2);
  Connect(nl, n3, 4);
  Connect(nl, n4, 0);
  Connect(nl, n4, 2);
  Connect(nl, n4, 3);

  printf("정점 0과 연결된 정점: ");
  for(node* temp = n0->link; temp != NULL; temp = temp->link)
  {
    printf("%d ", temp->vertex);
  }
  printf("\n");

  printf("정점 1과 연결된 정점: ");
  for(node* temp = n1->link; temp != NULL; temp = temp->link)
  {
    printf("%d ", temp->vertex);
  }
  printf("\n");
  
  printf("정점 2와 연결된 정점: ");
  for(node* temp = n2->link; temp != NULL; temp = temp->link)
  {
    printf("%d ", temp->vertex);
  }
  printf("\n");
  
  printf("정점 3과 연결된 정점: ");
  for(node* temp = n3->link; temp != NULL; temp = temp->link)
  {
    printf("%d ", temp->vertex);
  }
  printf("\n");

  printf("정점 4와 연결된 정점: ");
  for(node* temp = n4->link; temp != NULL; temp = temp->link)
  {
    printf("%d ", temp->vertex);
  }
  printf("\n");

  printf("\n");
  for(int i = 0; i < 5; i++)
  {
    visited[i] = 0;
  }

  Visit(nl, n0);
}


