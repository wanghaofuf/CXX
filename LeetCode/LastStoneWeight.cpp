#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class LastStoneWeight
{
public:
    int lastStoneWeight(vector<int>& stones) {
        if(stones.size()==0) return 0;
        if(stones.size()==1){
            return stones[0];
        }
        std::sort(stones.begin(),stones.end());
        stones[stones.size()-2] = stones[stones.size()-1] - stones[stones.size()-2];
        stones.erase(stones.begin()+stones.size()-1,stones.end());
        return lastStoneWeight(stones);
    }
};





int main(int argc, char **argv){

    
    return 0;
}