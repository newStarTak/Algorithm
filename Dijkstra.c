#include <stdio.h>
#include <stdlib.h>

#define inf 99999

int VisitedArray[7] = { 0, };
int dist[7] = { inf, inf, inf, inf, inf, inf, inf };

typedef struct Edge
{
  int end;
  int weight;
} edge;

typedef struct EdgeStart
{
  struct Edge* edges[7];
} edgeStart;

typedef struct EdgeList
{
  struct EdgeStart* edgeStarts[7];
} edgeList;

void Dijkstra(edgeList* el_t, int index)
{
  VisitedArray[index] = 1;

  int minIndex = -1;
  int minWeight = -1;

  edge* min;

  printf("= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n");
  printf("현재 정점: %d\n\n", index);

  for(int i = 0; el_t->edgeStarts[index]->edges[i] != NULL; i++)
  {
    if(VisitedArray[el_t->edgeStarts[index]->edges[i]->end] == 0)
    {
      printf("인접한 간선의 가중치 %d + 지금까지의 거리 %d와 끝점 %d의 distance 값 %d 대소 비교 중...\n", el_t->edgeStarts[index]->edges[i]->weight, dist[index], el_t->edgeStarts[index]->edges[i]->end, dist[el_t->edgeStarts[index]->edges[i]->end]);
      if(el_t->edgeStarts[index]->edges[i]->weight + dist[index] < dist[el_t->edgeStarts[index]->edges[i]->end])
      {
        printf("간선의 가중치 + 지금까지의 거리가 더 작습니다. distance 값을 %d로 변경합니다.\n\n", el_t->edgeStarts[index]->edges[i]->weight + dist[index]);
        dist[el_t->edgeStarts[index]->edges[i]->end] = el_t->edgeStarts[index]->edges[i]->weight + dist[index];
      }
    }
  }

  printf("변경된 dist 값\n");
  for(int i = 0; i < 7; i++)
  {
    printf("%d ", dist[i]);
  }
  printf("\n\n");

  for(int i = 0; i < 7; i++)
  {
    if(VisitedArray[i] == 0)
    {
      if(minIndex == -1 || dist[i] < dist[minIndex])
      {
        minIndex = i;
        printf("다음 정점 후보 %d로 임시 결정\n", minIndex);
      }
    }
  }
  printf("\n");

  if(minIndex != -1)
  {
    Dijkstra(el_t, minIndex);
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

  Connect(el0, 1, 7);
  Connect(el0, 4, 3);
  Connect(el0, 5, 10);
  Connect(el1, 2, 4);
  Connect(el1, 3, 10);
  Connect(el1, 4, 2);
  Connect(el1, 5, 6);
  Connect(el2, 3, 2);
  Connect(el3, 4, 11);
  Connect(el3, 5, 9);
  Connect(el3, 6, 4);
  Connect(el4, 6, 5);

  Connect(el1, 0, 7);
  Connect(el4, 0, 3);
  Connect(el5, 0, 10);
  Connect(el2, 1, 4);
  Connect(el3, 1, 10);
  Connect(el4, 1, 2);
  Connect(el5, 1, 6);
  Connect(el3, 2, 2);
  Connect(el4, 3, 11);
  Connect(el5, 3, 9);
  Connect(el6, 3, 4);
  Connect(el6, 4, 5);

  dist[0] = 0;
  Dijkstra(el, 0);

  return 0;
}
