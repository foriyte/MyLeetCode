
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
    //question 72
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        
        int dp[m+1][n+1];
        for(int i= 0;i<=m;i++)
            dp[i][0] = i;
        for(int i=0;i<=n;i++)
            dp[0][i] = i;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(word1[i-1]==word2[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else
                    dp[i][j] = min(min(dp[i-1][j]+1,dp[i-1][j-1]+1),dp[i][j-1]+1);
            }
        }
        return dp[m][n];
    }

    //question 73
    void setZeroes(vector<vector<int>>& matrix) {
        
        //vector<int> row(matrix.size(),0);
        //vector<int> col(matrix[0].size(),0);
        
        //int row[1000] = {0};
        //int col[1000] = {0};
        int row = 1;
        int col = 1;
        for(int i=0;i<matrix[0].size();i++)
            if(matrix[0][i]==0){
                row = 0;
                break;
            }
        for(int i=0;i<matrix.size();i++)
            if(matrix[i][0]==0){
                col = 0;
                break;
            }
                
        for(int i =1;i<matrix.size();i++){
            for(int j=1;j<matrix[0].size();j++){
                if(matrix[i][j]==0){
                    matrix[0][j]=0;
                    matrix[i][0]=0;
                }
            }
        }
        for(int i=1;i<matrix[0].size();i++)
            if(matrix[0][i]==0){
                for(int j=1;j<matrix.size();j++)
                    matrix[j][i]=0;
            }
        for(int i=1;i<matrix.size();i++)
            if(matrix[i][0]==0){
                for(int j=1;j<matrix[0].size();j++)
                    matrix[i][j]=0;
            }
        if(row==0)
            for(int i =0;i<matrix[0].size();i++)
                matrix[0][i] = 0;
        if(!col)
            for(int i =0;i<matrix.size();i++)
                matrix[i][0] = 0;   
    }


    //question 74
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if(m==0) return false;
        int n = matrix[0].size();
        if(n==0) return false;
        
        int midm = m/2;
        int prem = 0;
        int lastm = m-1;
        while(lastm>=prem){
            if(target>=matrix[midm][0]&&target<=matrix[midm][n-1]){
                int midn = n/2;
                int pren = 0;
                int lastn = n-1;
                while(lastn>=pren){
                    if(matrix[midm][midn]==target)
                        return true;
                    else if(matrix[midm][midn]>target){
                        lastn = midn-1;
                        midn = (pren+lastn)/2;
                    }
                    else if(matrix[midm][midn]<target){
                        pren = midn+1;
                        midn = (pren+lastn)/2;
                    }
                        
                }
                return false;
            }
            else if(target<matrix[midm][0]){
                lastm = midm-1;
                midm = (prem+lastm)/2;
            }
            else if(target>matrix[midm][n-1]){
                prem = midm+1;
                midm = (prem+lastm)/2;
            }
            
        }
        
        return false;
    }

    //question 75
    void sortColors(vector<int>& nums) {
        int left = 0,right = nums.size()-1;
        int i = 0;
        while(i<=right){
            if(nums[i]==0){
                if(left!=i){
                    int tmp = nums[left];
                    nums[left] = nums[i];
                    nums[i--] = tmp;
                }
                left++;
            }
            else if(nums[i]==2){
                if(right!=i){ 
                    int tmp = nums[right];
                    nums[right] = nums[i];
                    nums[i--] = tmp;
                }
                right--;
            }
            i++;
        }
    }

    //question 76
    string minWindow(string s, string t) {
        unordered_map<char,int> mp;
        for(char c:s)
            mp[c] = INT_MIN;
        for(char c:t){
            if(mp[c]!=INT_MIN)
                mp[c]++;
            else
                mp[c] = 1;
        }

        int left =0,right = 0;
        int count = 0;
        int len = INT_MAX;
        string res = "";
        for(;right<s.size();right++){
            if(mp[s[right]]!=INT_MIN) mp[s[right]]--;
            if(mp[s[right]]>=0)
                count++;
            while(count==t.size()){
                while(mp[s[left]]<0){
                    if(mp[s[left]]!=INT_MIN)
                        mp[s[left]]++;
                    left++;
                }
                    
                if(mp[s[left]]==0){
                    mp[s[left]]++;
                    count--;
                    if((right-left+1)<len){
                        len = right-left+1;
                        res = s.substr(left,len);
                    }
                    left++;
                }
            }
        }
        
        return res;
    }

    //question 77
    vector<vector<int>> res;
    vector<vector<int>> combine(int n, int k) {
        if(k>n) return res;

        vector<int> tmp;
        dfs(1,n,k,tmp);
        return res;
    }
    
    void dfs(int level,int n,int k,vector<int> tmp){
        if((n-level+1)<k) return;
        if(k==0){
            res.push_back(tmp);
            return;
        }
        for(int i=level;i<=n;i++){
            tmp.push_back(i);
            dfs(i+1,n,k-1,tmp);
            tmp.pop_back();
        }
        
    }

    //question 78
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> tmp;
        res = dfs(res,tmp,nums,0);
        return res;
    }
    
    vector<vector<int>> dfs(vector<vector<int>> &res,vector<int> &tmp,vector<int>& nums,int level){
        res.push_back(tmp);
        for(int i = level;i<nums.size();i++){
            tmp.push_back(nums[i]);
            res = dfs(res,tmp,nums,i+1);
            tmp.pop_back();
        }
        return res;
    }

    //question 79
    bool exist(vector<vector<char>>& board, string word) {
        int flag[100][100] = {0};
        for(int i =0;i<board.size();i++){
            for(int j=0;j<board[i].size();j++){
                if(dfs(board,word,0,i,j,flag))
                    return true;
                
            }
        }
        return false;
    }
    bool dfs(vector<vector<char>>& board,string word,int level,int x,int y,int flag[][100]){
        if(word[level]==board[x][y]&&flag[x][y]==0){
            flag[x][y] =1;
            if(level==word.size()-1)
                return true;
            else{
                if(y>0&&dfs(board,word,level+1,x,y-1,flag))
                    return true;
                if(y<(board[x].size()-1)&&dfs(board,word,level+1,x,y+1,flag))
                    return true;
                if(x>0&&dfs(board,word,level+1,x-1,y,flag))
                    return true;
                if(x<(board.size()-1)&&dfs(board,word,level+1,x+1,y,flag))
                    return true;
            }
            flag[x][y] = 0;
            return false;
        }
        else{
            return false;
        }
    }

    //question 80
    int removeDuplicates(vector<int>& nums) {
        int p = 0,count = 0 ;
        vector<int> res;
        if(nums.size()!=0){
            count++;
            res.push_back(nums[0]);
            for(int i=1;i<nums.size();i++){
                if(nums[i]==nums[i-1])
                    p++;
                else
                    p=0;
                if(p<=1) {
                    res.push_back(nums[i]);
                    count++;
                }
            }
        }
        nums = res;
        return count;
    }


};



