#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
int removeDuplicates(vector<int>& nums) 
{
    int k;
    unordered_set<int> seen;
    int i = 0;
    while (i < nums.size())
    {
        if(seen.find(nums[i]) != seen.end())
        {
            nums.erase(nums.begin() + i);
        } 
        else
        {
            seen.insert(nums[i]);
            i++;
        }
    }
    return k = i;
}
};