#include <stdio.h>
void get_noof_ways(int *arr, int arr_len, int limit,int curr,int *count,int start)
{
	if (curr == limit){
		*count = *count + 1;
		return;
	}
	if (curr < limit){
		for (int i = start; i < arr_len&&curr < limit; i++)
		{
			curr += arr[i];
			get_noof_ways(arr, arr_len, limit, curr, count,i);
			curr -= arr[i];
		}
	}
}
int steps_main()
{
	int arr[] = { 1,2,3,4,5,6,7,8,9,10};
	int noofsteps = 20;
	int count = 0;
	get_noof_ways(arr, 7, noofsteps,0,&count,0);
	printf("%d", count);
	return 0;
}