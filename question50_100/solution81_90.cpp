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
    //question 81
    bool search(vector<int>& nums, int target) {
        int key = -1;
        for(int i =0;i<nums.size()-1;i++){
            if(nums[i+1]<nums[i])
                key = i;
        }
        int low,high,mid;
        if(key == -1){
            low = 0;
            high = nums.size()-1;
            
        }
        else if(target>=nums[0]){
            low = 0;
            high = key;
        }
        else{
            low = key + 1;
            high = nums.size()-1;
        }
        while(low<=high){
            mid = (low+high)/2;
            if(target == nums[mid])
                return true;
            else if(target<nums[mid]){
                high = mid-1;
                while(nums[high]==nums[high-1]&&high>0)
                    high--;
            }
            else{
                low = mid +1;
                while(nums[low]==nums[low+1]&&low<(nums.size()-1))
                    low++;
            }
        }
        return false;
            
    }
    
    //question 82
    ListNode* deleteDuplicates(ListNode* head) {
        if(head==NULL||head->next==NULL)
            return head;
        ListNode *ppre = new ListNode(-1);
        ppre->next = head;
        ListNode *pre = ppre;
        ListNode *cur = head;
        while(cur!=NULL){
            bool flag = false;;
            while(cur->next!=NULL&&cur->val==cur->next->val){
                flag = true;
                cur = cur->next;  
            }
            if(flag){
                pre->next = cur->next;
                cur = cur->next; 
            }
            else{
                pre = cur;
                cur = cur->next;
            }
        }
        return ppre->next;
        
    }


    //question 83
    ListNode* deleteDuplicates(ListNode* head) {
        if(head==NULL) return head;
        ListNode *res = head;
        map<int,int> as;
        as[head->val]=1;
        while(head->next!=NULL){
            
            if(as[head->next->val]==1){
                head->next = head->next->next;
            }
            else{
                as[head->next->val] = 1;
                head = head->next;
            }       
        }
        return res;
        
    }

    //question 84
    int largestRectangleArea(vector<int>& heights) {
        stack<int> s;
        heights.push_back(0);
        int pre = 0;
        int maxium = 0;
        for(int i=0;i<heights.size();i++){
            while(!s.empty()&&heights[s.top()]>=heights[i]){
                int height = heights[s.top()];
                s.pop();
                int wid = s.empty()?-1:s.top();
                maxium = max(maxium,height*(i-wid-1));
            }
            s.push(i);
        }
        return maxium;
    }

    //question 85
    int maximalRectangle(vector<vector<char>>& matrix) {
        int res = 0;
        if(matrix.empty()) return res;
        int len = matrix.size();
        int lem = matrix[0].size();
        int height[lem+1];
        for(int i=0;i<=lem;i++)
            height[i] = 0;
        stack<int> s;
        for(int i=0;i<len;i++){
            for(int j=0;j<=lem;j++){
                if(j<lem&&matrix[i][j]=='1') height[j] = height[j]+1;
                else height[j] = 0;
                while(!s.empty()&&height[j]<=height[s.top()]){
                    int h = height[s.top()];
                    s.pop();
                    int wid = s.empty()?-1:s.top();
                    res = max(res,h*(j-wid-1));
                }
                s.push(j);
            }
            while(!s.empty()) s.pop();
        }
        return res;
        
    }

    //question 86
    ListNode* partition(ListNode* head, int x) {
        if(head==NULL||head->next==NULL) return head;
        /*
        ListNode *first = new ListNode(-1);
        ListNode *last = first;
        first->next = head;
        while(head!=NULL&&head->val<x){
            last = head;
            head = head->next;
        }
        ListNode *cur = head;
        ListNode *pre = first;
        while(cur!=NULL){
            if(cur->val<x){
                pre->next = cur->next;
                ListNode *tmp = last->next;
                last->next = cur;
                last = cur;
                cur->next = tmp;
                cur = pre->next;
            }
            else{
                pre = cur;
                cur = cur->next;
            }
        }
        return first->next;
        */
        ListNode *left = new ListNode(-1);
        ListNode *right = new ListNode(-1);
        ListNode *leftend = left;
        ListNode *rightend = right;
        while(head!=NULL){
            if(head->val<x){
                leftend->next = head;
                leftend = leftend->next;
            }
            else{
                rightend->next = head;
                rightend = rightend->next;
            }
            head = head->next;
        }
        leftend->next = right->next;
        rightend->next = NULL;
        return left->next;
        
    }

    //question 87
    map<pair<string,string>,bool> mp;
    bool isScramble(string s1, string s2) {
        if(s1.size()!=s2.size()) return false;
        pair<string,string> tmp(s1,s2);
        if(mp.find(tmp)!=mp.end())
            return mp[tmp];
        if(s1==s2){
           return true; 
        }

        for(int j=1;j<s1.size();j++){
            if(isScramble(s1.substr(0,j),s2.substr(0,j))&&isScramble(s1.substr(j,s1.size()-j),s2.substr(j,s2.size()-j))){
                mp[tmp] = true;
                return true;
            }
            if(isScramble(s1.substr(0,j),s2.substr(s2.size()-j,j))&&isScramble(s1.substr(j,s1.size()-j),s2.substr(0,s2.size()-j))){
                mp[tmp] = true;
                return true;
            }
        }
        mp[tmp] = false;
        return false;
    }

    //question 88
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int left=m-1,right=n-1;
        int count = m+n-1;
        while(count>=0){
            if(left<0)
                nums1[count--] = nums2[right--];
            else if(right<0)
                nums1[count--] = nums1[left--];
            else{
                nums1[count--] = nums1[left]>nums2[right]?nums1[left--]:nums2[right--];
            }
        }
    }

    //question 89
    vector<int> grayCode(int n) {
        int count = 0;
        vector<int> res;
        if(n==0) {
            res.push_back(0);
            return res;
        }
        else{
            vector<int> tmp = grayCode(n-1);
            int len = pow(2,n);
            for(int i=0;i<len;i++){
                if(i<len/2)
                    res.push_back(tmp[i]);
                else
                    res.push_back(tmp[len-1-i]+len/2);
            }
            return res;
        }
        
        
    }

    //question 90
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        vector<int> tmp;
        return dfs(res,tmp,nums,0);
        
    }
    
    vector<vector<int>> dfs(vector<vector<int>>&res,vector<int> &tmp,vector<int> &nums,int level){
        res.push_back(tmp);
        for(int i=level;i<nums.size();i++){
            if(i>level)
                if(nums[i]==nums[i-1])
                continue;
            tmp.push_back(nums[i]);
            res = dfs(res,tmp,nums,i+1);
            tmp.pop_back();
        }
        return res;
    }

};


