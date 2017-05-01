#include <string>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <unordered_map>
#include <map>
#include <time.h>
#include <set>
#include <utility>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    //question 187
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> res;
        if(s.size()<=10) return res;
        /*
        map<string,int> ss;
        //set<string> temp;
        for(int i=0;i<=s.size()-10;i++){
            string tmp = s.substr(i,10);
            auto it = ss.find(tmp);
            if(it==ss.end())
                ss[tmp] = 1;
            else{
                ss[tmp]++;
            }
        }
        for(auto i:ss)
            if(i.second>1)
                res.push_back(i.first);
        */
        
        map<int,int> mp;
        int cur = 0;
        map<char,int> dic;
        dic['A'] = 0;
        dic['C'] = 1;
        dic['G'] = 2;
        dic['T'] = 3;
        for(int i=0;i<10;i++)
            cur = cur<<2|dic[s[i]];
        mp[cur] = 0;
        for(int i=10;i<s.size();i++){
            cur = (cur&0x3ffff)<<2|dic[s[i]];
            if(mp.find(cur)==mp.end()) mp[cur] = 0;
            else
                if(mp[cur]++==0) res.push_back(s.substr(i-9,10));
        }
        return res;
    }
 
    //question 188
    int maxProfit(int k, vector<int>& prices) {
        int len = prices.size();
        if(len<2) return 0;
        if(k>len/2){
            int res = 0;
            for(int i=1;i<len;i++){
                res += max(prices[i]-prices[i-1],0);
            }
            return res;
        }
        //int dp[k+1][len];
        vector<vector<int>> dp(k+1,vector<int>(len,0));
        for(int i = 1;i<=k;i++){
            int tmp = dp[i-1][0]-prices[0];
            for(int j=1;j<len;j++){
                dp[i][j] = max(dp[i][j-1],prices[j]+tmp);
                tmp = max(tmp,dp[i-1][j]-prices[j]);
            }
            
        }
        return dp[k][len-1];
    }

    //question 189
    void rotate(vector<int>& nums, int k) {
        
        int len = nums.size();
        k = k%len;
        int j = len-k;
        for(int i=0;i<j/2;i++)
            swap(nums[i],nums[j-1-i]);
        for(int i =0;i<k/2;i++)
            swap(nums[j+i],nums[len-1-i]);
        for(int i =0;i<len/2;i++)
            swap(nums[i],nums[len-1-i]);
    }

    //question 190
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = n&1;
        for(int i=0;i<31;i++){
            res = res<<1;
            n = n>>1;
            res += n&0x00000001;
        }
        return res;
    }

    //question 191
    int hammingWeight(uint32_t n) {
        int count=0;
        while(n!=0){
            if(n%2==1) count++;
            n/=2;
        }
        return count;
    }

    //question 198
    int dp[1000];
    int rob(vector<int>& nums) {
        memset(dp,0,nums.size());
        //int lv = 0,tmp =0;
        //return dfs(nums,lv,tmp,false);
        if(nums.empty()) return 0;
        if(nums.size()==1) return nums[0];
        if(nums.size()==2) return max(nums[0],nums[1]);
        if(nums.size()==3) return max(nums[0]+nums[2],nums[1]);
        dp[0] = nums[0];
        dp[1] = nums[1];
        dp[2] = nums[0] + nums[2];
        for(int i=3;i<nums.size();i++){
            dp[i] = max(dp[i-2],dp[i-3])+nums[i];
        }
        return max(dp[nums.size()-1],dp[nums.size()-2]);
        
    }
    int dfs(vector<int>& nums,int lv,int tmp,bool flag){
        if(lv==nums.size()) {
            return tmp;
        }
        if(flag){
            return tmp+dfs(nums,lv+1,0,false);
        }
        else{
            if(dp[lv]==0)
                dp[lv] = dfs(nums,lv+1,nums[lv],true);
            return max(dp[lv],dfs(nums,lv+1,0,false))+tmp;
            
        }
        
    }

    //question 199
    queue<pair<TreeNode*,int>> layer;
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res ;
        if(root==NULL) return res;
        pair<TreeNode*,int> start(root,1);
        layer.push(start);
        int l = 0;
        while(!layer.empty()){
            pair<TreeNode*,int> tmp = layer.front();
            if(tmp.second>l){
                res.push_back(tmp.first->val);
                l++;
            }
            if(tmp.first->right){
                pair<TreeNode*,int> rnode(tmp.first->right,tmp.second+1);
                layer.push(rnode);
            }
            if(tmp.first->left){
                pair<TreeNode*,int> lnode(tmp.first->left,tmp.second+1);
                layer.push(lnode);
            }
            layer.pop();
        }
        return res;
        
    }

    //question 200
    bool vis[1000][1000];
    int numIslands(vector<vector<char>>& grid) {
        int res = 0;
        if(grid.empty()) return res;
        for(int i=0;i<grid.size();i++)
            for(int j=0;j<grid[i].size();j++)
                vis[i][j] = false;
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[i].size();j++){
                if(grid[i][j]=='1'&&!vis[i][j]){
                    res++;
                    dfs(grid,i,j);
                }
            }
        }
        return res;
    }
    
    void dfs(vector<vector<char>>& grid,int x,int y){
        vis[x][y] = true;
        if(x<grid.size()-1&&grid[x+1][y]=='1'&&!vis[x+1][y])
            dfs(grid,x+1,y);
        if(y<grid[x].size()-1&&grid[x][y+1]=='1'&&!vis[x][y+1])
            dfs(grid,x,y+1);
        if(x>0&&grid[x-1][y]=='1'&&!vis[x-1][y])
            dfs(grid,x-1,y);
        if(y>0&&grid[x][y-1]=='1'&&!vis[x][y-1])
            dfs(grid,x,y-1);
    }

};


