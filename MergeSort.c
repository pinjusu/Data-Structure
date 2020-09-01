#include <string.h>
#include <stdio.h>
#include <stdlib.h>
void mergeSort(int *nums, int numsSize){
	int *numsTemp = (int *)malloc(sizeof(int) * numsSize);
	memcpy(numsTemp,nums,sizeof(int) * numsSize);
	for(int i=1; i<numsSize; i=i<<1){
		for(int j=0; j<numsSize;){
			int left = j, right = j + i, leftlimit = j + i, rightlimit = j + 2 * i;
			leftlimit = leftlimit>numsSize ? numsSize : leftlimit;
			rightlimit = rightlimit>numsSize ? numsSize : rightlimit;
			while(left<leftlimit || right<rightlimit){
				if( left < leftlimit && (nums[left] < nums[right] || right >= rightlimit) )
					numsTemp[j++] = nums[left++];
				else
					numsTemp[j++] = nums[right++];
			}
		}
		memcpy(nums,numsTemp,sizeof(int)*numsSize);
	}
	free(numsTemp);
}
int main() {
	int array[10]={1,5,7,3,2,9,0,5,6,8};
	mergeSort(array,10);
	for(int i=0; i<10; i++)
		printf("%d\n",array[i]);
	return 0;
}