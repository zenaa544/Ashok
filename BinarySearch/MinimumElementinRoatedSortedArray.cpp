int findMin(vector<int>& arr)
{
	// Write your code here.
    
	int n = arr.size();
    if(n==0) return -1;
	if(n==1) return arr[0];
	int left = 0;
	int right =n-1;
    int ans = INT_MAX;
	while(left<=right){
     
	 int mid = (left+right)/2;
     
	 if(arr[left]<=arr[mid]){
		 ans=min(arr[left], ans);
		 left=mid+1;
	 }
	 else{
		 
		 ans=min(arr[mid],ans);
		 right = mid-1;
	 }

	}
   return ans;

}
