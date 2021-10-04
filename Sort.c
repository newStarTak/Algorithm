#include <stdio.h>

int Partition(int list[], int left, int right, int max)
{
  int leftmost = left + 1;
  int rightmost = right;
  int pivot = list[left];
  int temp;

  do
  {
    while(leftmost <= right && list[leftmost] < pivot)
    {
      leftmost++;
    }
    
    while(rightmost >= left && list[rightmost] > pivot)
    {
      rightmost--;
    }

    if (leftmost < rightmost)
    {
      temp = list[leftmost];
      list[leftmost] = list[rightmost];
      list[rightmost] = temp;
    }
  } while(leftmost < rightmost);

  temp = list[left];
  list[left] = list[rightmost];
  list[rightmost] = temp;

  printf("피벗 %d 기준 정렬 후 배열: ", pivot);
  for(int i = 0; i < max; i++)
  {
    printf("%d ", list[i]);
  }
  printf("\n");

  return rightmost;
}

void Quick(int list[], int left, int right, int max)
{
  int movedPivotIndex;

  if (right - left > 0)
  {
    movedPivotIndex = Partition(list, left, right, max);

    Quick(list, left, movedPivotIndex - 1, max);
    Quick(list, movedPivotIndex + 1, right, max);
  }
}

void Merge(int list[], int left, int mid, int right)
{
  int l = left;
  int r = mid + 1;
  int t = left;

  int temp[10] = { 0, };

  while(l <= mid && r <= right)
  {
    if(list[l] < list[r])
    {
      temp[t++] = list[l++];
    }
    else
    {
      temp[t++] = list[r++];
    }
  }

  if(l > mid)
  {
    for(; r <= right; r++, t++)
    {
      temp[t] = list[r];
    }
  }
  else
  {
    for(; l <= mid; l++, t++)
    {
      temp[t] = list[l];
    }
  }

  for(t = left; t <= right; t++)
  {
    list[t] = temp[t];
  }

  printf("합      병: ");
  for(t = left; t <= right; t++)
  {
    printf("%d ", list[t]);
  }
  printf("\n");
}

void Cut(int list[], int left, int right, int level)
{
  int mid;

  if(level < 1)
  {
    printf("초기  배열: ");
  }
  else
  {
    printf("분할 %d단계: ", level);
  }
  for(int t = left; t <= right; t++)
  {
    printf("%d ", list[t]);
  }
  printf("\n");

  if(right - left > 0)
  {
    level++;
    mid = (left + right) / 2;
    Cut(list, left, mid, level);
    Cut(list, mid + 1, right, level);
    Merge(list, left, mid, right);
  }
}

int main(void)
{
  int sortKind;
  int list[10];
  
  // 선택 정렬 전용 변수
  int minIndex;
  int temp;
  int max;

  // 합병 정렬 전용 변수
  

  // 퀵 정렬 전용 변수

  do
  {
    printf("출력하고 싶은 정렬 방식의 숫자를 입력하세요. (선택_1 합병_2 퀵_3): ");
    scanf("%d", &sortKind);
  } while (!(1 <= sortKind && sortKind <= 3));

  do
  {
    printf("배열의 크기를 입력하세요. (2 이상 10 이하): ");
    scanf("%d", &max);
  } while (!(2 <= max && max <= 10));

  for (int n = 0; n < max; n++)
  {
    printf("배열의 %d번째 자리에 넣을 정수를 입력하세요.: ", n + 1);
    scanf("%d", &list[n]);
  }
  printf("\n");

  if(sortKind == 1)
  {
    printf("초  기      배  열: ");
    for(int k = 0; k < max; k++)
    {
      printf("%d ", list[k]);
    }
    printf("\n");

    for(int i = 0; i < max - 1; i++)
    {
      minIndex = i;

      for(int j = i + 1; j < max; j++)
      {
        if(list[j] < list[minIndex])
        {
          minIndex = j;
        }
      }

      temp = list[minIndex];
      list[minIndex] = list[i];
      list[i] = temp;

      printf("%d회차 정렬 후 배열: ", i + 1);
      for(int k = 0; k < max; k++)
      {
        printf("%d ", list[k]);
      }
      printf("\n");
    }
  }
  else if(sortKind == 2)
  {
    Cut(list, 0, max - 1, 0);
  }
  else if(sortKind == 3)
  {
    Quick(list, 0, max - 1, max);
  }

  return 0;
}

