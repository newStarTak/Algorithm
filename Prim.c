#include <stdio.h>
#include <stdlib.h>

#define inf 99999

int VisitedArray[7] = { 0, };
int key[7] = { inf, inf, inf, inf, inf, inf, inf };

typedef struct Tree
{
  int node[7];
} tree;

typedef struct Edge
{
  int end;
  int weight;
} edge;

typedef struct EdgeStart
{
  struct Edge* edges[6];
} edgeStart;

typedef struct EdgeList
{
  struct EdgeStart* edgeStarts[7];
} edgeList;

void Prim(tree* MST_t, edgeList* el_t, int index, int res, int eCount)
{
  VisitedArray[index] = 1;
  eCount++;
  res += key[index];

  for(int i = 1; ; i++)
  {
    if(MST_t->node[i] == 0)
    {
      MST_t->node[i] = index;
      break;
    }
  }

  int minIndex = -1;
  int minWeight = -1;

  printf("현재 정점: %d\n", index);

  if(eCount == 6)
  {
    printf("프림 알고리즘 - MST 완성\n");
    for(int i = 0; i < 7; i++)
    {
      if(i == 6)
      {
        printf("정점 %d", MST_t->node[i]);
      }
      else
      {
        printf("정점 %d -> ", MST_t->node[i]);
      }
    }
    printf("\n최소 가중치 합은 %d입니다.", res);
    
    exit(0);
  }

  for(int i = 0; el_t->edgeStarts[index]->edges[i] != NULL; i++)
  {
    if(VisitedArray[el_t->edgeStarts[index]->edges[i]->end] == 0)
    {
      printf("인접한 간선의 가중치 %d와 끝점 %d의 Key 값 %d 대소 비교 중...\n", el_t->edgeStarts[index]->edges[i]->weight, el_t->edgeStarts[index]->edges[i]->end, key[el_t->edgeStarts[index]->edges[i]->end]);
      if(el_t->edgeStarts[index]->edges[i]->weight < key[el_t->edgeStarts[index]->edges[i]->end])
      {
        printf("간선의 가중치가 더 작습니다. Key 값을 %d로 변경합니다.\n", el_t->edgeStarts[index]->edges[i]->weight);
        key[el_t->edgeStarts[index]->edges[i]->end] = el_t->edgeStarts[index]->edges[i]->weight;

        if(minIndex == -1)
        {
          minIndex = el_t->edgeStarts[index]->edges[i]->end;
          minWeight = el_t->edgeStarts[index]->edges[i]->weight;
          printf("다음 MST 후보: 정점 %d로 최초 임시 결정\n", minIndex);
        }
        else
        {
          printf("현재 MST 후보 정점 %d의 가중치 %d와 새로운 후보 정점 %d의 가중치 %d 대소 비교 중...\n", minIndex, minWeight, el_t->edgeStarts[index]->edges[i]->end, el_t->edgeStarts[index]->edges[i]->weight);
          if(el_t->edgeStarts[index]->edges[i]->weight < minWeight)
          {
            minIndex = el_t->edgeStarts[index]->edges[i]->end;
            printf("다음 MST 후보: 정점 %d로 임시 결정\n", minIndex);
          }
        }
      }
    }
  }

  printf("변경된 Key 값\n");
  for(int i = 0; i < 7; i++)
  {
    printf("%d ", key[i]);
  }
  printf("\n\n");

  if(minIndex != -1)
  {
    Prim(MST_t, el_t, minIndex, res, eCount);
  }
}

void Connect(edgeStart* elN, int e, int w)
{
  edge* newEdge = (edge*)malloc(sizeof(edge));

  newEdge->end = e;
  newEdge->weight = w;

  for(int i = 0; ; i++)
  {
    if(elN->edges[i] == NULL)
    {
      elN->edges[i] = newEdge;
      break;
    }
  }
}

int main(void)
{
  edgeList* el = (edgeList*)malloc(sizeof(edgeList));
  tree* MST = (tree*)malloc(sizeof(tree));

  edgeStart* el0 = (edgeStart*)malloc(sizeof(edgeStart));
  edgeStart* el1 = (edgeStart*)malloc(sizeof(edgeStart));
  edgeStart* el2 = (edgeStart*)malloc(sizeof(edgeStart));
  edgeStart* el3 = (edgeStart*)malloc(sizeof(edgeStart));
  edgeStart* el4 = (edgeStart*)malloc(sizeof(edgeStart));
  edgeStart* el5 = (edgeStart*)malloc(sizeof(edgeStart));
  edgeStart* el6 = (edgeStart*)malloc(sizeof(edgeStart));

  el->edgeStarts[0] = el0;
  el->edgeStarts[1] = el1;
  el->edgeStarts[2] = el2;
  el->edgeStarts[3] = el3;
  el->edgeStarts[4] = el4;
  el->edgeStarts[5] = el5;
  el->edgeStarts[6] = el6;

  Connect(el0, 1, 29);
  Connect(el0, 5, 10);
  Connect(el1, 2, 16);
  Connect(el1, 6, 15);
  Connect(el2, 3, 12);
  Connect(el3, 4, 22);
  Connect(el3, 6, 18);
  Connect(el4, 5, 27);
  Connect(el4, 6, 25);

  Connect(el1, 0, 29);
  Connect(el5, 0, 10);
  Connect(el2, 1, 16);
  Connect(el6, 1, 15);
  Connect(el3, 2, 12);
  Connect(el4, 3, 22);
  Connect(el6, 3, 18);
  Connect(el5, 4, 27);
  Connect(el6, 4, 25);

  key[0] = 0;
  Prim(MST, el, 0, 0, -1);

  return 0;
}
