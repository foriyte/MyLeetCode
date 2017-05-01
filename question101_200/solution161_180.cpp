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
    //question 162
    int findPeakElement(vector<int>& nums) {
        int left = 0 ;
        int right = nums.size()-1;
        int mid;
        if(nums.size()==1) return 0;
        while(left<=right){
            mid = (left+right)/2;
            if(mid==0){
                if(nums[mid]>nums[mid+1])
                    return mid;
                else
                    left = mid+1;
            }
            else if(mid==nums.size()-1){
                if(nums[mid]>nums[mid-1])
                    return mid;
                else 
                    right = mid-1;
            }
            else if(nums[mid]>nums[mid-1]&&nums[mid]>nums[mid+1]){
                return mid;
            }
            else if(nums[mid]>nums[mid-1]&&nums[mid]<nums[mid+1])
                left = mid+1;
            else
                right = mid-1;
            
        }
        return mid;
    }

    //question
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> res;
        int left = 0;
        int right = numbers.size()-1;
        int value = numbers[left]+numbers[right];
        while(value!=target){
            if(value>target)
                right--;
            else
                left++;
            value = numbers[left]+numbers[right];
        }
        res.push_back(left+1);
        res.push_back(right+1);
        return res;
    }

    //question
    string convertToTitle(int n) {
        int lv=1;
        int nn = n;
        while(nn>pow(26,lv)){
            nn -= pow(26,lv++);
        }
        int len = lv;
        lv = len-1;
        string res = "";
        for(int i=0;i<len;i++){
            int tmp = nn/pow(26,lv);
            nn -= tmp*pow(26,lv--);
            tmp =  (tmp+26-((nn==0)?1:0))%26;
            res += (char)('A'+tmp);
        }
        return res;
    }

    //question 169
    int majorityElement(vector<int>& nums) {
        int m=-1;
        int count = 0;
        for(auto p:nums){
            if(count==0)
                m=p;
            if(m==p)
                count++;
            else
                count--;
        }
        return m;
    }

    //question 171
    int titleToNumber(string s) {
        int len = s.size();
        int res=0;
        for(int i=1;i<len;i++){
            res+=pow(26,i);
        }
        
        for(int i =0;i<len;i++){
            int tmp = s[i]-'A';
            res+=tmp*pow(26,len-i-1);
            
        }
        return res+1;
        
    }

    //question 172
    int trailingZeroes(int n) {
        int count = 0;
        long base = 5;
        while(n/base!=0){
            cout<<base<<endl;
            count += n/base;
            base = base*5;
        }
        return count;
    }

    //question 179
    bool cmp(const string &a,const string &b){
        string aa = a+b;
        string bb = b+a;
        
        return aa>bb;
    }
    bool comp(int i,int j){
        string a = to_string(i);
        string b = to_string(j);
        string aa = a+b;
        string bb = b+a;
        return aa>bb;
    }
    string largestNumber(vector<int>& nums) {
        vector<string> hehe;
        sort(nums.begin(),nums.end(),comp);
        
        //for(auto p:nums)
         //   hehe.push_back(to_string(p));
        //sort(hehe.begin(),hehe.end(),cmp);
        string res = "";
        for(auto p:nums){
            if(res==""&&p==0) continue;
            res += to_string(p);
        }
        if(res=="") return "0";
        return res;
    }

};

//question 173
class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        cur = -1;
        dfs(root);
    }
    void dfs(TreeNode* root){
        if(root==NULL) return;
        if(root->left!=NULL)
            dfs(root->left);
        nums.push_back(root->val);
        if(root->right!=NULL)
            dfs(root->right);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        if(nums.empty()||cur==(int)(nums.size()-1)) return false;
        return true;
    }

    /** @return the next smallest number */
    int next() {
        if(hasNext())
            return nums[++cur];
        return -1;
    }
private:
    vector<int> nums;
    int cur;
};


