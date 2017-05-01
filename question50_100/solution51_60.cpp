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
struct Interval {
     int start;
     int end;
     Interval() : start(0), end(0) {}
     Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
    //question 51  
    vector<vector<int>> tmp;
    vector<vector<string>> solveNQueens(int n) {
        vector<int> q(n,0);
        buildQueen(q,0);
        vector<vector<string>> res;
        string temp;
        for(int i=0;i<n;i++)
            temp+=".";
        for(int i=0;i<tmp.size();i++){
            vector<string> tempres;
            for(int j=0;j<tmp[i].size();j++){
                string s = temp;
                s[tmp[i][j]] = 'Q';
                tempres.push_back(s);
            }
            res.push_back(tempres);
        }
        return res;
    }
    
    void buildQueen(vector<int>& q,int level){
        for(int i=0;i<q.size();i++){
            bool flag = true;
            for(int j=0;j<level;j++){
                if(q[j]==i||abs(level-j)==abs(q[j]-i)){
                   flag = false;
                   break;
                }
            }
            if(flag){
                q[level] = i;
                if(level==q.size()-1){
                    tmp.push_back(q);
                    return;
                }
                else{
                    buildQueen(q,level+1);
                }
            }
        }
    }

    //question 52
    int count;
    int totalNQueens(int n) {
        vector<int> q(n,0);
        count=0;
        buildQueen(q,0);
        return count;
    }
    
    void buildQueen(vector<int>& q,int level){
        for(int i=0;i<q.size();i++){
            bool flag = true;
            for(int j=0;j<level;j++){
                if(q[j]==i||abs(level-j)==abs(q[j]-i)){
                   flag = false;
                   break;
                }
            }
            if(flag){
                q[level] = i;
                if(level==q.size()-1){
                    count++;
                    return;
                }
                else{
                    buildQueen(q,level+1);
                }
            }
        }
    }
    
    //question 53
    int maxSubArray(vector<int>& nums) {
        
        int length = nums.size();
        int len[length];
        for (int i =0;i<length;i++)
            len[i] = -9999999;
        
        len[0] = nums[0];
        int maxium = len[0];
        for(int i = 1;i<length;i++){
            len[i] = max(nums[i],len[i-1]+nums[i]);
            if(len[i]>maxium)
                maxium = len[i];
        }
        return maxium;
    }

    //question 54
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        if(matrix.empty()) return res;
        int m = matrix.size(),n = matrix[0].size();
        int all = (min(m,n)+1)/2;
        
        for(int i=0;i<all;i++){
            for(int j=i;j<n-i;j++)
                res.push_back(matrix[i][j]);
            for(int j = i+1;j<m-i;j++)
                res.push_back(matrix[j][n-i-1]);
            for(int j = n-i-2;j>=i&&(m-i-1)!=i;j--)
                res.push_back(matrix[m-i-1][j]);
            for(int j =m-i-2;j>i&&i!=(n-i-1);j--)
                res.push_back(matrix[j][i]);
            
            }
        
        return res;
    }

    //question 55
    bool canJump(vector<int>& nums) {
        int p = nums.size()-1;
        if(p==0) return true;
        int flag[p+1];
        flag[0] = nums[0];
        for(int i =0;i<=p;i++){
            if(flag[i]<1)
                return false;
            flag[i+1] = nums[i]>(flag[i]-1)?nums[i]:(flag[i]-1);
        }
        return flag[p-1]>0;
    }

    //question 56
    static bool cmp(Interval a ,Interval b){
        return a.start<b.start;
    }
    vector<Interval> merge(vector<Interval>& intervals) {
        if(intervals.size()<2) return intervals;
        sort(intervals.begin(),intervals.end(),cmp);
        vector<Interval> res;
        int left = intervals[0].start;
        int right = intervals[0].end;
        for(int i=1;i<intervals.size();i++){
            if(intervals[i].start>right){
                Interval temp(left,right);
                res.push_back(temp);
                left = intervals[i].start;
                right = intervals[i].end;
            }
            else{
                right = max(intervals[i].end,right);
            }
        }
        Interval tmp(left,right);
        res.push_back(tmp);
        return res;
    }

    //question 57
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        int left = newInterval.start;
        int right = newInterval.end;
        for(vector<Interval>::iterator it=intervals.begin();it!=intervals.end();it++){
            if(left<(*it).start){
                if(right<(*it).start){
                    break;
                }
                else if(right>=(*it).start&&right<=(*it).end){
                    right = (*it).end;
                    intervals.erase(it);
                    break;
                }
                else
                    intervals.erase(it--);
            }
            
            else if(left<=(*it).end){
                if(right<=(*it).end)
                    return intervals;
                else{
                    left = (*it).start;
                    while(right>=(*it).start&&it!=intervals.end()){
                        right=max(right,(*it).end);
                        intervals.erase(it);
                    }
                    break;
                }
            }
        }
        Interval temp(left,right);
        intervals.push_back(temp);
        if(intervals.size()<2) return intervals;
        int i=0;
        for(i=0;i<intervals.size();i++){
            if(intervals[i].start>left)
                break;
        }
        int count = intervals.size()-1;
        while(count>i){
            intervals[count] = intervals[count-1];
            count--;
        }
        intervals[i] = temp;
        return intervals;
    }

   //question 58
    int lengthOfLastWord(string s) {
        int count=0;
        for(int i=s.size()-1;i>=0;i--){
            if((s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z'))
                count++;
            if(count>0&&s[i]==' ')
                break;
        }

        return count;
    }

    //question 59
    vector<vector<int>> generateMatrix(int n) {
        
        vector<vector<int>> res;
        for(int i =0;i<n;i++){
            vector<int> tmp;
            for(int j=0;j<n;j++)
                tmp.push_back(0);
            res.push_back(tmp);
        }
            
        
        int all = (n+1)/2;
        int count = 1;
        for(int i=0;i<all;i++){
            for(int j=i;j<n-i;j++)
                res[i][j] = count++;
            for(int j = i+1;j<n-i;j++)
                res[j][n-i-1] = count++;
            for(int j = n-i-2;j>=i&&(n-i-1)!=i;j--)
                res[n-i-1][j] = count++;
            for(int j =n-i-2;j>i&&(n-i-1)!=;j--)
                res[j][i] = count++;
            
            }
        
        return res;
    }

    //question 60
    string getPermutation(int n, int k) {
        vector<int> nums;
        string res;
        for(int i=1;i<=n;i++)
            nums.push_back(i);
        for(int i=1;i<n;i++){
            int tmp = jie(n-i);
            int v = k/tmp;
            int w = k%tmp;
            k = k-tmp*v;
            if(v==0)
                res += to_string(nums[v]);
            else if(v>0&&w==0){
                v--;
                res += to_string(nums[v]);
                
                while((v+1)<=(nums.size()-1)){
                    nums[v] = nums[v+1];
                    v++;
                }
                nums.pop_back();
                int t = nums.size()-1;
                while(t>=0)
                    res +=to_string(nums[t--]);
                return res;
            }
            else if(v>0&&w>0)
                res += to_string(nums[v]);
            while((v+1)<=(nums.size()-1)){
                nums[v] = nums[v+1];
                v++;
            }
            nums.pop_back();
        }
        return res+to_string(nums[0]);
        
    }
    
    int jie(int x){
        return (x?x*jie(x-1):1);
    }


};





