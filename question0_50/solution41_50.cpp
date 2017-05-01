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
    //question 41
    int firstMissingPositive(vector<int>& nums) {
        unordered_map<int,int> um;
        for(int num:nums){
            um[num]++;
        }
        for(int i =1;i<INT_MAX;i++)
            if(um[i]==0) return i;
        return 1;
    }
    
    //question 42
    int trap(vector<int>& h) {
        if(h.size()<3) return 0;
        vector<int> point;
        vector<int> height;
        height.push_back(0);
        for(int p:h) height.push_back(p);
        height.push_back(0);
        int res = 0;
        for(int i=1;i<height.size()-1;i++){
            if(height[i]>=height[i-1]&&height[i]>height[i+1])
                point.push_back(i);
        }
        if(point.size()<2) return res;
        bool flag = true;
        while(flag){
            flag = false;
            for(vector<int>::iterator it = point.begin()+1;it!=point.end()-1;it++){
                if(height[*it]<=height[*(it-1)]&&height[*it]<=height[*(it+1)]){
                    point.erase(it--);
                    flag = true;
                }
            }
        }
        for(int i=0;i<point.size()-1;i++){
            int left=point[i];
            int right = point[i+1];
            int mid = min(height[left],height[right]);
            for(int j=left+1;j<right;j++)
                res += max(0,mid-height[j]);
        }
        return res;
    }

    //question 43
    string multiply(string num1, string num2) {
        while(num1[0]=='0') num1.erase(0,1);
        while(num2[0]=='0') num2.erase(0,1);
        if(num1==""||num2=="") return "0";
        vector<char> tmpres;
        string res = "";
        int duo = 0;
        string t1 = num1.size()>num2.size()?num1:num2;
        string t2 = num1.size()>num2.size()?num2:num1;
        int len = t1.size()+t2.size()-1;
        for(int i=0;i<len;i++){
            int k = 0;
            while(k<t2.size()){
                int j = i-k;
                if(j>=0&&j<t1.size()){
                    duo += (t2[t2.size()-1-k]-'0')*(t1[t1.size()-1-j]-'0');
                }
                k++;   
            }
            tmpres.push_back(char('0'+duo%10));
            duo /=10;
        }
        while(duo!=0){
            tmpres.push_back(char('0'+duo%10));
            duo /=10;
        }
        for(int i=tmpres.size()-1;i>=0;i--)
            res += tmpres[i];
        return res;
        
    }

    //question 45
    int jump(vector<int>& nums) {
        if(nums.size()<2) return 0;
        vector<int> jump(nums.size(),nums.size());
        jump[0] = 0;
        for(int i=0;i<nums.size();i++){
            if(nums[i]>=(nums.size()-i-1)) return jump[i]+1;
            int count = i+nums[i];
            int flag = i+1;
            for(int j=1;j<=nums[i]&&(i+j)<nums.size();j++){
                jump[i+j] = min(jump[i+j],jump[i]+1);
                if(i+j==nums.size()-1) return jump[i+j];
                if((i+j+nums[i+j])>=count){
                    count = i+j+nums[i+j];
                    flag = i+j;
                } 
            }
            i = flag-1;
        }
        return jump[jump.size()-1];
    }

    //question 46
    vector<vector<int>> permute(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        if(nums.size()==1){
            res.push_back(nums);
            return res;
        }
        for(vector<int>::iterator it = nums.begin();it!=nums.end();it++){
            vector<int> tmp = nums;
            vector<int>::iterator itt = find(tmp.begin(),tmp.end(),*it);
            tmp.erase(itt);
            vector<vector<int>> hehe = permute(tmp);
            for(int i=0;i<hehe.size();i++){
                hehe[i].push_back(*it);
                res.push_back(hehe[i]);
            }
            
        }
        return res;
    }

    //question 47
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        if(nums.size()==1){
            res.push_back(nums);
            return res;
        }
        for(vector<int>::iterator it = nums.begin();it!=nums.end();it++){
            if(it>nums.begin()&&*it==*(it-1)) continue;
            vector<int> tmp = nums;
            vector<int>::iterator itt = find(tmp.begin(),tmp.end(),*it);
            tmp.erase(itt);
            vector<vector<int>> hehe = permuteUnique(tmp);
            for(int i=0;i<hehe.size();i++){
                hehe[i].push_back(*it);
                res.push_back(hehe[i]);
            }
            
        }
        return res;
    }
    
    //question 48
    void rotate(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        int sq = min(m,n);
        int all = sq/2;
        
        
        for(int i =0;i<all;i++){
            for(int j = i;j<sq-1-i;j++){
                lunzhuan(matrix,i,j,sq);
            }
        }
        /*
        if(m<n){
            for(int i=m;i<n;i++){
                vector<int> row;
                for(int j = m-1;j>=0;j--)
                    row.push_back(matrix[i][j]);
                matrix.push_back(row);
            }
            for(int i = 0;i<m;i++){
                for(int j = m-1;j>=n;j--){
                    matrix[i].pop_back();
                }
            }
        }
        else if(m>n){
            for(int i=0;i<n;i++){
                for(int j =n;j<m;j++){
                    matrix[i].push_back(-1);
                }
                for(int jj=0;jj<n;jj++){
                    matrix[i][jj+m-n] = matrix[i][jj];
                }
            }
            for(int i=m-1;i>=n;i--){
                for(int j = 0;j<n;j++){
                    matrix[j][m-i] = matrix[i][j];
                }
                matrix[i].pop_back();
            }
            
        }
        */
    
    }
    void lunzhuan(vector<vector<int>>& matrix,int x,int y,int sq){
        int tmp = matrix[x][y];
        for(int i=0;i<3;i++){
            int p = sq-y-1;
            int q = x;
            matrix[x][y] = matrix[p][q];
            x = p;
            y = q;
        }
        matrix[x][y] = tmp;
        
    }
    //question 49
    vector<vector<string>> groupAnagrams(vector<string>& strs){
        
        vector<vector<string>> res;
        unordered_map<string,vector<string> >m;
        for(string str:strs){
            string tmp =str;
            sort(tmp.begin(),tmp.end());
            m[tmp].push_back(str);
        }
        for(auto p:m){
            res.push_back(p.second);
        }
        return res;
    }

    //question 50
    double myPow(double x, int n) {
        if(n==0) return 1;
        if(n==1) return x;
        double m = pow(x,n/2);
        return m*m*pow(x,n%2);
        
        
    }

};





