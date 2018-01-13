int minPatches(int* nums, int numsSize, int n) {
	long long int sum = 0;
	int index = 0;
	int i = 1;
	int count = 0;
	while(sum < n){
			if(sum >= nums[index]-1 && index < numsSize){
				sum+=(long long)nums[index];
				index++;
			}
			else{
				sum = 2*sum+1;
				count++;
			}
	}
	return count;
}