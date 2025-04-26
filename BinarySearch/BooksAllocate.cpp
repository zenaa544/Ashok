Problem statement
Given an array ‘arr’ of integer numbers, ‘arr[i]’ represents the number of pages in the ‘i-th’ book.



There are ‘m’ number of students, and the task is to allocate all the books to the students.



Allocate books in such a way that:

1. Each student gets at least one book.
2. Each book should be allocated to only one student.
3. Book allocation should be in a contiguous manner.


You have to allocate the book to ‘m’ students such that the maximum number of pages assigned to a student is minimum.



If the allocation of books is not possible, return -1.



  bool isPossibleToAllocate(vector<int>& arr, int maxStudents, int maxPages){

 int numStudents=1;
 int numPages=0;

 for(int i=0;i< arr.size();i++){
     if(numPages+arr[i]<=maxPages){
         numPages+=arr[i];
     }
     else{
         numPages=arr[i];
         numStudents++;
     }

     if(numStudents>maxStudents)return false;

    }

    return true;
}

int findPages(vector<int>& arr, int n, int m) {
    // Write your code here.

    if(n<m) return -1;

    int low= *max_element(arr.begin(), arr.end());
    
    int high = accumulate(arr.begin(),arr.end(),0);
    
    int ans =high;
    while(low<=high){
        int mid = low+(high-low)/2;
        if(isPossibleToAllocate(arr,m,mid)){
            ans=mid;
            high=mid-1;
        }
        else{
            low=mid+1;
        }
    }

    return ans;
}
