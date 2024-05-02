#include <stdio.h>
#include<stdbool.h>

void merge(int job[], int deadline[], int profit[], int low, int mid, int high)
{
  int i = low;
  int j = mid + 1;
  int k, t = low;
  int task[high+1], dead[high+1], p[high+1];
  while(i <= mid && j <= high)
  {
    if(profit[i] <= profit[j])
    {
      task[t] = job[j];
      dead[t] = deadline[j];
      p[t] = profit[j];
      t++;
      j++;
    }
    else
    {
      task[t] = job[i];
      dead[t] = deadline[i];
      p[t] = profit[i];
      t++;
      i++;
    }
  }

  while(i <= mid)
  {
    task[t] = job[i];
    dead[t] = deadline[i];
    p[t] = profit[i];
    t++;
    i++;
  }

  while(j <= high)
  {
    task[t] = job[j];
    dead[t] = deadline[j];
    p[t] = profit[j];
    t++;
    j++;
  }

  for(k=low; k<=high; k++)
  {
    job[k] = task[k];
    deadline[k] = dead[k];
    profit[k] = p[k];
  }
}

void mergesort(int job[], int deadline[], int profit[], int low, int high)
{
  if(low < high)
  {
    int mid = (low + high) / 2;
    mergesort(job, deadline, profit, low, mid);
    mergesort(job, deadline, profit, mid+1, high);
    merge(job, deadline, profit, low, mid, high);
  }
}

int min (int a, int b)
{
  return (a <= b) ? a : b;
}

void schedule(int job[], int deadline[], int profit[], int n)
{
  int assigned[n], sum = 0;
  bool slot[n];
  for(int i=0; i<n; i++)
  {
    slot[i] = false;
    assigned[i] = -1;
  }
  mergesort(job, deadline, profit, 0, n-1);

  for(int i=0; i<n; i++)
  {
    for(int j = min(n, deadline[i]) - 1; j >= 0; j--)
    {
      if(slot[j] == false)
      {
        assigned[j] = job[i];
        slot[j] = true;
        sum += profit[i];
        break;
      }
    }
  }

  printf("The scheduled jobs are : \n");
  for(int i=0; i<n; i++)
  {
    if(assigned[i] != -1)
      printf("%d\t",assigned[i]);
  }
  printf("Max profit is Rs. %d\n",sum);
}

int main ()
{
  int n;
  printf("Enter the no. of jobs : \n");
  scanf("%d", &n);
  int job[n], deadline[n], profit[n];
  printf("Enter the deadlines and profits : \n");
  for(int i=0; i<n; i++)
  {
    job[i] = i + 1;
    printf("\nEnter the deadline and profit for job %d : ", i+1);
    scanf("%d %d",&deadline[i],&profit[i]);
  }
  schedule(job, deadline, profit, n);
  return 0;
}