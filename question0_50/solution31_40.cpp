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
    //question 31
    void nextPermutation(vector<int>& nums) {
        int minium = 9999999;
        int pre = -1;
        vector<int>::iterator it = nums.end()-2;
        for(int i=nums.size()-2;i>=0;i--){
            
            if(nums[i]<nums[i+1]){
                for(int j = nums.size()-1;j>i;j--)
                    if((minium>nums[j])&&(nums[j]>nums[i])){
                        minium = nums[j];
                        pre = j;
                    }
                nums[pre] = nums[i];
                nums[i] = minium;
                sort(it+1,nums.end());
                return;
            }
            it--;
        }
        for(int left=0,right=nums.size()-1;left<right;left++,right--)
            swap(nums[left],nums[right]);
    }

    //question 32
    int longestValidParentheses(string s) {
        vector<int> ss(s.size(),0);
        int res = 0;
        for(int i=1;i<s.size();i++){
            if(s[i]==')'){
                if(s[i-1]=='('){
                    ss[i] = ss[i-2]+2;
                }
                else{
                    if(s[i-1-ss[i-1]]=='(')
                        ss[i]=ss[i-1-ss[i-1]-1]+ss[i-1]+2;
                }
            }
            res = max(res,ss[i]);
        }
        return res;
    }

    //question 33
    int search(vector<int>& nums, int target) {
        
        int low=0,high = nums.size()-1;
        if(target == nums[0]) return 0;
        int mid;
        while(low<=high){
            mid = (low+high)/2;
            if(target == nums[mid])
                return mid;
            else if(target>=nums[0]&&target<=nums[mid])
                high = mid-1;
            else if(target<nums[0]&&target>nums[mid])
                low = mid +1;
            else{
                if(nums[mid]>=nums[0])
                    low = mid+1;
                else
                    high = mid-1;
            }
        }
        
        return -1;
    }

    //question 34
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();
        int pre = 0;
        int last = n-1;
        int mid = (pre+last)/2;
        int start = 0;
        int end = 0;
        vector<int> res;
        while(last>=pre){
            if(nums[mid] == target){
                start = mid;
                end = mid;
                while(nums[start-1]==target&&start>0)
                    start--;
                while(nums[end+1]==target&&end<(n-1))
                    end++;
                res.push_back(start);
                res.push_back(end);
                return res;
            }
            else if(nums[mid]<target){
                pre = mid+1;
                mid = (pre+last)/2;
            }
            else if(nums[mid]>target){
                last = mid-1;
                mid = (pre+last)/2;
            }
            
        }
        res.push_back(-1);
        res.push_back(-1);
        return res;
    }

    //question 35
    int searchInsert(vector<int>& nums, int target) {
        int low,high,mid;
        low = 0;
        high = nums.size()-1;
        if(target<=nums[0]) return 0;
        if(target>nums[high]) return high+1;
        while(low<=high){
            mid = (low+high)/2;
            if(nums[mid]==target){
                while(nums[mid-1]==target)
                    mid--;
                return mid;
            }
            else if(nums[mid]<target)
                low = mid+1;
            else
                high = mid-1;
            
                
        }
        return low;
    }

    //question 36
    bool isValidSudoku(vector<vector<char>>& board) {
        for(int i=0;i<9;i++){
            unordered_map<char,int> tmp;
            for(int p:board[i]){
                if(p>'0'&&p<='9'){
                    tmp[p]++;
                    if(tmp[p]>1)
                        return false;
                }
            }
        }
        for(int i =0;i<9;i++){
            unordered_map<char,int> tmp;
            for(int j=0;j<9;j++){
                char p = board[j][i];
                if(p>'0'&&p<='9'){
                    tmp[p]++;
                    if(tmp[p]>1)
                        return false;
                }
            }
        }
        for(int i=0;i<7;i+=3){
            for(int k=0;k<7;k+=3){
                unordered_map<char,int> tmp;
                for(int j=0;j<3;j++){
                    for(int m =0;m<3;m++){
                        char p = board[i+j][k+m];
                        if(p>'0'&&p<='9'){
                            tmp[p]++;
                            if(tmp[p]>1)
                                return false;
                        }
                    }
                }
                
            }
        }
        return true;
    }

    //question 37
    void solveSudoku(vector<vector<char>>& board) {
         solved(board);
    }
    
    bool solved(vector<vector<char>>& board){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(board[i][j]=='.'){
                    int k;
                    for(k=1;k<10;k++){
                        board[i][j] = char('0'+k);
                        if(duplicate(board,i,j)) {
                            continue;
                        }
                        if(solved(board))
                            return true;
                    }
                    if(k==10){
                        board[i][j]='.';
                        return false;
                    }
                }
            }
        }
        return true;
    }
    
    bool duplicate(vector<vector<char>> board,int m,int n){
        char p = board[m][n];
        for(int i=0;i<9;i++){
            if(p==board[m][i]&&i!=n)
                return true;
        }
        for(int i=0;i<9;i++){
            if(p==board[i][n]&&i!=m)
                return true;
        }
        
        int i = m-m%3,j=n-n%3;
        for(int ii=0;ii<3;ii++){
            for(int jj=0;jj<3;jj++){
                if(p==board[i+ii][j+jj]&&m!=(i+ii)&&n!=(j+jj))
                    return true;
            }
        }
        return false;
    }

    //question 38
    string countAndSay(int n) {
        if(n==1) return "1";
        string s="1";
        string tmp = "1";
        while(n>1){
            s  = tmp;
            tmp="";
            for(int i=0;i<s.size();i++){
                int count = 1;
                while((i+1)<s.size()&&s[i+1]==s[i]){
                    i++;
                    count++;
                }
                tmp += to_string(count)+s.substr(i,1);
            }
            n--;
        }
        return tmp;
    }

    //question 39
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(),candidates.end());
        vector<vector<int>> res;
        vector<int> tmp;
        dfs(candidates,res,tmp,0,0,target);
        return res;
    }
    
    void dfs(vector<int> &nums,vector<vector<int>> &res,vector<int> &tmp,int level,int sum ,int target){
        if(sum==target){
            res.push_back(tmp);
            return;
        }
        else if(sum>target)
            return;
        else if(level>=nums.size())
            return;
        else{
            int count =0;
            if(level>0)
                if(nums[level]==nums[level-1])
                    dfs(nums,res,tmp,level+1,sum,target);
            while(count*nums[level]<=target){
                for(int i =0;i<count;i++)
                    tmp.push_back(nums[level]);
                dfs(nums,res,tmp,level+1,sum+count*nums[level],target);
                for(int i =0;i<count;i++)
                    tmp.pop_back();
                count++;
            }
        }
    }

    //qeestion 40
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(),candidates.end());
        vector<vector<int>> res;
        vector<int> tmp;
        dfs(candidates,res,tmp,0,0,target);
        return res;
    }
    
    void dfs(vector<int> &nums,vector<vector<int>> &res,vector<int> &tmp,int level,int sum ,int target){
        if(sum==target){
            res.push_back(tmp);
            return;
        }
        else if(sum>target)
            return;
        else if(level>=nums.size())
            return;
        else{
            
            for(int i =level;i<nums.size();i++){
                if(nums[i]==nums[i-1]&&i!=level) continue;
                tmp.push_back(nums[i]);
                dfs(nums,res,tmp,i+1,sum+nums[i],target);
                tmp.pop_back();
            }
            
        }
    }
};







