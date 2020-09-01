#include <stdio.h>
#include <stdlib.h>
void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
int move(int *nums, int left, int right){
	int pivot = left, swapIdx=left;
	for(int i=left+1;i<=right;i++){
		if(nums[pivot] > nums[i]){
			swapIdx++;
			swap(nums+i,nums+swapIdx);
		}
	}
	swap(nums+left,nums+swapIdx);
	return swapIdx;
}
void partition(int *nums,int left, int right) {
	if(left<right){
		int pivot = move(nums,left,right);
		partition(nums,left,pivot-1);
		partition(nums,pivot+1,right);
	}
}
void quickSort(int *nums, int numsSize){
	int left = 0, right = numsSize - 1;
	partition(nums,left,right);
}
int main() {
	int array[10]={1,5,7,3,2,9,0,5,6,8};
	quickSort(array,10);

	for(int i=0; i<10; i++)
		printf("%d\n",array[i]);
	return 0;
}