bool isPossibleToPartition(vector<int>& arr, int maxPartitions, int partitionSumLimit){

 int numPartitions=1;
 int partitionSum=0;;

 for(int i=0;i< arr.size();i++){
     if(partitionSum+arr[i]<=partitionSumLimit){
         partitionSum+=arr[i];
     }
     else{
         partitionSum=arr[i];
         numPartitions++;
     }

     if(numPartitions>maxPartitions)return false;

    }

    return true;
}
    int splitArray(vector<int>& arr, int k) {
    
     int n = arr.size();
     if(n<k) return -1;

    int low= *max_element(arr.begin(), arr.end());
    
    int high = accumulate(arr.begin(),arr.end(),0);
    
    int ans =high;
    while(low<=high){
        int mid = low+(high-low)/2;
        if(isPossibleToPartition(arr,k,mid)){
            ans=mid;
            high=mid-1;
        }
        else{
            low=mid+1;
        }
    }
        return ans;
    }
