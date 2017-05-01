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
    //question 61
    ListNode* rotateRight(ListNode* head,int k){
        if(head==NULL||k==0) return head;
        ListNode* left = head;
        ListNode* right = head;
        int len = 0;
        while(left!=NULL){
            left=left->next;
            len++;
        }
        k = k%len;  
        left = head;
        if(k==0) return head;
        int count = 0;
        while(count<k){
            if(right==NULL) return head;
            right = right->next;
            count++;
        }
        if(right==NULL) return head;
        while(right->next!=NULL){
            left = left->next;
            right = right->next;
        }
        right->next = head;
        head = left->next;
        left->next = NULL;
        return head;
        
    }

    //question 62
    int uniquePaths(int m, int n) {
        int dp[m][n];
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                dp[i][j] = 0;
        for(int i=0;i<m;i++)
            dp[i][0] = 1;
        for(int j=0;j<n;j++)
            dp[0][j] = 1;
  
        for(int i=1;i<m;i++){
            for(int j=1;j<n;j++){
                dp[i][j] = dp[i-1][j]+dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }

    //question 63
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        //int count = 0;
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        int dp[m][n];
        
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                dp[i][j] = 0;
        if(obstacleGrid[0][0]==0) dp[0][0] =1 ;
        int all = min(m,n);
        for(int i = 0;i<all;i++){
            for(int j=i;j<n;j++){
                if(obstacleGrid[i][j]==1)
                    dp[i][j]=0;
                else{
                    if(i>0)
                        dp[i][j] +=dp[i-1][j];
                    if(j>0)
                        dp[i][j] +=dp[i][j-1];
                }
            }
            for(int j=i+1;j<m;j++){
                if(obstacleGrid[j][i]==1)
                    dp[j][i]=0;
                else{
                    if(i>0)
                        dp[j][i] +=dp[j][i-1];
                    if(j>0)
                        dp[j][i] +=dp[j-1][i];
                }
            }
                
        }
        return dp[m-1][n-1];
    }

    //question 64
    int minPathSum(vector<vector<int>>& grid) {
        //vector<vector<int>> value;
        int m = grid.size(),n=grid[0].size();
        int all = min(m,n);
        int v = grid[m-1][n-1];
        //value = grid;
        for(int i=0;i<all;i++){
            for(int j =i;j<n;j++){
                int a=100000,b=100000;
                if(i>0)
                    a = grid[i-1][j];
                if(j>0)
                    b = grid[i][j-1];
                if(i!=0||j!=0)
                    grid[i][j] = grid[i][j]+min(a,b);
            }
            for(int j = i+1;j<m;j++){
                int a=100000,b=100000;
                if(j>0)
                    a = grid[j-1][i];
                if(i>0)
                    b = grid[j][i-1];
                if(i!=0||j!=0)
                    grid[j][i] = grid[j][i]+min(a,b);
            }
        }
        return grid[m-1][n-1];
    }

    //question 65
    bool isNumber(string s) {
        if(s=="") return false;
        while(s[0]==' ') s.erase(0,1);
        if(s=="") return false;
        while(s[s.size()-1]==' ') s.erase(s.size()-1,1);
        if(s=="") return false;
        if(s[0]=='+'||s[0]=='-') s.erase(0,1);
        if(s=="") return false;
        for(char p:s){
            if((p<'0'||p>'9')&&p!='e'&&p!='E'&&p!='.'&&p!='+'&&p!='-')
                return false;
        }
        map<char,int> mp;
        for(char p:s){
            if(p=='e'||p=='E'||p=='.'||p=='+'||p=='-')
                mp[p]++;
        }
        if((mp['e']+mp['E'])>1||mp['.']>1||mp['+']>1||mp['-']>1) return false;
        if(s=="."||s=="e"||s=="E") return false;
        for(int i=0;i<s.size();i++){
            if(s[i]=='e'||s[i]=='E'){
                if(i==0||i==s.size()-1||(s[i-1]=='.'&&i==1)||(s[i-1]=='+')||s[i-1]=='-'||s[i+1]=='.') return false;
            }
        }
        bool flag = false;
        for(int i=0;i<s.size();i++){
            if(s[i]=='e'||s[i]=='E') flag = true;
            if(s[i]=='.'){
                if(flag) return false;
                if((i>0&&(s[i-1]<'0'||s[i-1]>'9'))||(i<s.size()-1&&(s[i+1]<'0'&&s[i+1]>'9'&&s[i+1]!='e'&&s[i+1]!='E')))
                    return false;
            }
        }
        for(int i=0;i<s.size();i++){
            if(s[i]=='+'||s[i]=='-')
                if((s[i-1]!='e'&&s[i-1]!='E')||i==s.size()-1) return false;
        }
        return true;
        
    }
 
    //question 66
    vector<int> plusOne(vector<int>& digits) {
        for(int i = digits.size()-1;i>=0;i--){
            if(digits[i]!=9){
                digits[i]++;
                return digits;
            }
            else{
                digits[i]=0;
                if(i==0){
                    vector<int> res;
                    res.push_back(1);
                    for(int p:digits)
                        res.push_back(p);
                    return res;
                }
            }
        }
        return digits;
    }

    //question 67
    string addBinary(string a, string b) {
        int na = a.size(),nb = b.size();
        int c = min(na,nb);
        string  res;
        int flag = 0;
        for(int i=0;i<c;i++){
            if(a[na-i-1]!=b[nb-i-1]){
                res.append(to_string(!flag));
            }
            else{
                res.append(to_string(flag));
                if(a[na-i-1]=='1'&&b[nb-i-1]=='1')
                    flag =1;
                else
                    flag = 0;
            }
        }
        if(na!=nb){
            string cc = na>nb?a:b;
            
            int nc = cc.size();
            //int cha = abs(na-nb);
            for(int i = 0;i<nc-c;i++){
                if(cc[nc-c-1-i]=='1'){
                    if(flag)
                        res.append("0");
                    else
                        res.append("1");
                }
                else{
                    res.append(to_string(flag));
                    flag = 0;
                }
            }
        }
        if(flag)
            res.append("1");
        string hehe = res;
        bool h = false;
        if(res.size()==1)
            return res;
        int count = 0;
        for(int i=0;i<res.size();i++){
            if(res[res.size()-1-i]!='0')
                h = true;
            if(h)
                hehe[count++] = res[res.size()-1-i];
        }
        
        return hehe;     
    }

    //question 68
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int idx = 0;
        vector<string> res;
        while(idx<words.size()){
            int count = 0;
            int sum = 0;
            while(idx<words.size()&&(sum+words[idx].size())<=maxWidth){
                sum+=words[idx].size();
                idx++;
                count++;
                sum++;
            }
            if(count ==0){
                string s = words[idx].substr(0,maxWidth);
                res.push_back(s);
                words[idx] = words[idx].substr(maxWidth,words[idx].size()-maxWidth);
            }
            else if(count==1){
                sum--;
                idx--;
                string s = words[idx];
                int spacecount = maxWidth - sum;
                for(int i=0;i<spacecount;i++)
                    s+=" ";
                res.push_back(s);
            }
            else{
                sum--;
                idx--;
                string s = "";
                int max = maxWidth;
                if(idx==words.size()-1)
                    max = sum;
                int cha = max -sum;
                int duoyu = cha/(count-1);
                vector<int> tmp(count-1,1+duoyu);
                int shengyu = cha - duoyu*(count-1);
                for(int i=0;i<shengyu;i++)
                    tmp[i]++;
                for(int i=0;i<count;i++){
                    s += words[idx-count+i+1];
                    if(i<count-1){
                        for(int j=0;j<tmp[i];j++)
                            s += " ";
                    }
                }
                if(idx==words.size()-1){
                    int len = s.size();
                    for(int i=0;i<maxWidth-len;i++)
                        s+=" ";
                }
                res.push_back(s);
            }
            idx++;
        }
        return res;
    }

    //question 69
    int mySqrt(int x) {
        if(x == 1) return 1;
        else if(x == 0) return 0;
        else if (x<0) return -1;
        else{
            int low = 1;
            int high = x/2;
            int mid = (low+high)/2;
            while(high>=low){
                if((x/mid)>=mid&&(mid+1)>(x/(mid+1)))
                    return mid;
                else if((x/mid)<mid){
                    high = mid-1;
                    mid = (low+high)/2;

                }
                else{
                    low = mid+1;
                    mid = (low+high)/2;
                }
            }
        }
        return 0;
    }

    //question 70
    int climbStairs(int n) {

        if(n==1) return 1;
        else if(n==2) return 2;
        else if(n==3) return 3;
        else{
            int half = n/2;
            return climbStairs(half)*climbStairs(n-half)+climbStairs(half-1)*climbStairs(n-(half+1));
        }
    }


};



