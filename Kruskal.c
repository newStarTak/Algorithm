#include <stdio.h>
#include <stdlib.h>

int parent[7] = { 0, 1, 2, 3, 4, 5, 6 };
int lastVisitedArray[7] = { -1, -1, -1, -1, -1, -1, -1};

typedef struct Edgelist
{
  struct Edge* edges[9];
} edgeList;

typedef struct Edge
{
  int start;
  int end;
  int weight;
  struct Edge* link;
} edge;

int FindParent(int i)
{
  if(parent[i] == i)
  {
    return i;
  }
  else
  {
    return FindParent(parent[i]);
  }
}

int Kruskal(edgeList* el_t)
{
  int res = 0;
  int eCount = 0;

  for(int i = 0; i < 9; i++)
  {
    printf("정점 %d에서 %d 탐색\n", el_t->edges[i]->start, el_t->edges[i]->end);

    if(lastVisitedArray[el_t->edges[i]->end] != -1)
    {
      printf("사이클이 생길 수 있는 간선으로 확인 작업 중...\n");
      int lastVisited = FindParent(lastVisitedArray[el_t->edges[i]->end]);
      int nowVisit = FindParent(parent[el_t->edges[i]->start]);

      if(lastVisited != nowVisit)
      {
        res += el_t->edges[i]->weight;
        printf("가중치 %d가 더해집니다.\n", el_t->edges[i]->weight);
        eCount++;

        parent[el_t->edges[i]->start] = el_t->edges[i]->end;

        lastVisitedArray[el_t->edges[i]->end] = el_t->edges[i]->start;
      }
      else
      {
        printf("두 정점의 루트 노드가 같아 해당 간선은 버립니다.\n");
      }
    }
    else
    {
      res += el_t->edges[i]->weight;
      printf("가중치 %d가 더해집니다.\n", el_t->edges[i]->weight);
      eCount++;

      parent[el_t->edges[i]->start] = el_t->edges[i]->end;

      lastVisitedArray[el_t->edges[i]->end] = el_t->edges[i]->start;
    }

     if(eCount == 6)
    {
      break;
    }

    printf("\n");
  }
  printf("\n");

  return res;
}

void Compare(edgeList* el_t)
{
  int maxIndex;
  int temp;

  for(int max = 8; max > 0; max--)
  {
    maxIndex = 0;
    for(int i = 1; i <= max; i++)
    {
      if(el_t->edges[i]->weight > el_t->edges[maxIndex]->weight)
      {
        maxIndex = i;
      }
    }

    temp = el_t->edges[max]->start;
    el_t->edges[max]->start = el_t->edges[maxIndex]->start;
    el_t->edges[maxIndex]->start = temp;

    temp = el_t->edges[max]->end;
    el_t->edges[max]->end = el_t->edges[maxIndex]->end;
    el_t->edges[maxIndex]->end = temp;

    temp = el_t->edges[max]->weight;
    el_t->edges[max]->weight = el_t->edges[maxIndex]->weight;
    el_t->edges[maxIndex]->weight = temp;
  }

  for(int i = 0; i < 9; i++)
  {
    printf("%d번째:%6d%8d%6d\n", i + 1, el_t->edges[i]->start, el_t->edges[i]->end, el_t->edges[i]->weight);
  }
  printf("\n");
}

void Connect(edgeList* el_t, int s, int e, int w)
{
  edge* newEdge = (edge*)malloc(sizeof(edge));

  newEdge->start = s;
  newEdge->end = e;
  newEdge->weight = w;

  for(int i = 0; ; i++)
  {
    if(el_t->edges[i] == NULL)
    {
      el_t->edges[i] = newEdge;
      break;
    }
  }
}

int main(void)
{  
  edgeList* el = (edgeList*)malloc(sizeof(edgeList));

  Connect(el, 0, 1, 29);
  Connect(el, 0, 5, 10);
  Connect(el, 1, 2, 16);
  Connect(el, 1, 6, 15);
  Connect(el, 2, 3, 12);
  Connect(el, 3, 4, 22);
  Connect(el, 3, 6, 18);
  Connect(el, 4, 5, 27);
  Connect(el, 4, 6, 25);

  printf("%7s%10s%10s%10s\n", "간선", "시작점", "끝점", "가중치");
  for(int i = 0; i < 9; i++)
  {
    printf("%d번째:%6d%8d%6d\n", i + 1, el->edges[i]->start, el->edges[i]->end, el->edges[i]->weight);
  }
  printf("\n");

  printf("정렬 후\n\n%7s%10s%10s%10s\n", "간선", "시작점", "끝점", "가중치");
  Compare(el);

  printf("최소 신장 트리의 최소 가중치 합은 %d입니다.", Kruskal(el));
}
