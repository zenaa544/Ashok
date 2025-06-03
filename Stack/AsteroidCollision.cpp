We are given an array asteroids of integers representing asteroids in a row. 
The indices of the asteriod in the array represent their relative position in space.

For each asteroid, the absolute value represents its size, and the sign represents its direction 
(positive meaning right, negative meaning left). Each asteroid moves at the same speed.

Find out the state of the asteroids after all collisions. 
If two asteroids meet, the smaller one will explode. If both are the same size, 
both will explode. Two asteroids moving in the same direction will never meet.

vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> ans;

        for(int i=0;i<asteroids.size();i++){
           
           if(asteroids[i]>0){
            ans.push_back(asteroids[i]);
           }

           else{
              while(!ans.empty() && ans.back()>0 && ans.back()<abs(asteroids[i])){                    
                    ans.pop_back();
              }
              if(!ans.empty() && ans.back()>0 && ans.back()==abs(asteroids[i])){
                ans.pop_back();continue;
              }
              if(ans.empty()|| ans.back()<0)
                  ans.push_back(asteroids[i]);
           }

        }

        return ans;
    }
