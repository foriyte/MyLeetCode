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
    //question 11
    int maxArea(vector<int>& height) {
        int n = height.size();
        int left = 0,right = n-1;
        int maxium = 0;
        while(left<right){
            maxium = max(maxium,(right-left)*min(height[left],height[right]));
            if(height[left]>height[right])
                right--;
            else
                left++;
        }
        return maxium;
    }
    //question12
    string intToRoman(int num) {
        char* c[4][10]={
            {"","I","II","III","IV","V","VI","VII","VIII","IX"},
            {"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"},
            {"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"},
            {"","M","MM","MMM"}
        };
        string res = "";
        res.append(c[3][num/1000%10]);
        res.append(c[2][num/100%10]);
        res.append(c[1][num/10%10]);
        res.append(c[0][num%10]);
        return res;
    }
    //question13
    int romanToInt(string s) {
        int i =0;
        int res = 0;
        char c[3][3] = {
            {'I','X','V'},
            {'X','C','L'},
            {'C','M','D'}
        };
        
        while(s[i]=='M'){
            res +=1000;
            i++;
        }
        
        for(int j = 2;j>=0;j--){
            
            if(s[i]==c[j][0]){
                if(s[i+1]==c[j][1]){
                    res +=9*pow(10,j);
                    i +=2;;
                }
                else if(s[i+1]==c[j][2]){
                    res +=4*pow(10,j);
                    i+=2;
                }
                else if(s[i+1]==c[j][0]){
                    res+=pow(10,j);
                    i++;
                    while(s[i]==c[j][0]){
                        res+=pow(10,j);
                        i++;
                    }
                }
                else{
                    res+=pow(10,j);
                    i++;
                }
            }
            else if(s[i]==c[j][2]){
                res += 5*pow(10,j);
                i++;
                while(s[i]==c[j][0]){
                    res +=pow(10,j);
                    i++;
                }
            }
        }
        return res;
    }

    //question14
    string longestCommonPrefix(vector<string>& strs) {
        int i =0;
        string res="";
        if(strs.empty())
            return res;
        int maxlen = 0;
        for(auto p:strs)
            maxlen = max(maxlen,int(p.size()));
        while(i<maxlen){
            char p = strs[0][i];
            bool flag = true;
            
            for(int j =1;j<strs.size();j++){
                if(strs[j][i]!=p){
                    flag = false;
                    break;
                }
            }
            if(flag)
                res +=p;
            else
                break;
            i++;
        }
        return res;
    }

    //question 15
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int target = -123456;
        vector<vector<int>> res;
        if(nums.size()<3) return res;
        /*
        for(int i=0;i<nums.size()-2;i++){
            if(i>0)
                if(nums[i]==nums[i-1]&&!res.empty()){
                    int count = 0;
                    for(auto p :res[res.size()-1]){
                        if(p==nums[i])
                            count++;
                    }
                    if(count==1||count==3)
                        continue;
                    else{
                        while(nums[i]==nums[i-1])
                            i++;
                        i--;
                    }
                }
            target = 0-nums[i];
            
            vector<vector<int>> tmp = find(nums,target,i+1);
            if(tmp.empty())
                continue;
            else{
                for(int j=0;j<tmp.size();j++){
                    tmp[j].push_back(nums[i]);
                    res.push_back(tmp[j]);
                }
            }
        }
        */
        //target = -nums[0];
        int left,right;
        for(int i=0;i<nums.size()-2;i++){
            /*
            if(nums[i]==nums[i-1]&&!res.empty()){
                int count = 0;
                for(auto p :res[res.size()-1]){
                    if(p==nums[i])
                        count++;
                }
                if(count==1||count==3)
                    continue;
                else{
                    while(nums[i]==nums[i-1])
                        i++;
                    i--;
                }
            }
            */
            target = -nums[i];
            left = i+1;
            right = nums.size()-1;
            while(left<right){
                if(nums[left]+nums[right]==target){
                    vector<int> tmp;
                    tmp.push_back(nums[i]);
                    tmp.push_back(nums[left++]);
                    tmp.push_back(nums[right--]);
                    res.push_back(tmp);
                    while(nums[left]==nums[left-1]&&left<nums.size()) left++;
                    while(nums[right]==nums[right+1]&&right>=0) right--;
                }
                else{
                    nums[left]+nums[right]<target?left++:right--;
                }
            }
            while(i+1<nums.size()&&nums[i+1]==nums[i]) i++;
        }
        return res;
    }
    vector<vector<int>> find(vector<int>&nums,int target,int level){
        vector<vector<int>> res;
        int left,right;
        left = level;right = nums.size()-1;
        while(left<right){
            if((nums[left]+nums[right])==target){
                vector<int> tmp;
                tmp.push_back(nums[left]);
                tmp.push_back(nums[right]);
                res.push_back(tmp);
                left++;
                right--;
                while(nums[left]==nums[left-1]&&nums[right]==nums[right+1]&&left<right){
                    left++;
                    right--;
                }
                
                
            }
            else if((nums[left]+nums[right])>target)
                right--;
            else
                left++;
            
        }
        return res;
    }

    //question16
    int threeSumClosest(vector<int>& nums, int target) {
        
        if(nums.size()==3) {
            return accumulate(nums.begin(),nums.end(),0);
        }
        else{
            int res = 100000000;
            sort(nums.begin(),nums.end());
            for(int i =0;i<nums.size()-2;i++){
                int tmp = find(nums,target-nums[i],i+1)+nums[i];
                res = abs(res-target)<abs(tmp-target)?res:tmp;
            }
            return res;
        }
    }
    
    int find(vector<int>&nums,int target,int level){
        int left=level,right = nums.size()-1;
        /*
        if(nums[left]>=target){
            return nums[left]+nums[left+1];
        }
        else{
        */
            int res = 1000000;
            while(left<right){
                if((nums[left]+nums[right])==target)
                    return nums[left]+nums[right];
                else if((nums[left]+nums[right])>target){
                    int tmp = nums[left]+nums[right]-target;
                    res = tmp<abs(res-target)?nums[left]+nums[right]:res;
                    right--;
                }
                else if((nums[left]+nums[right])<target){
                    int tmp = target-(nums[left]+nums[right]);
                    res = tmp<abs(res-target)?nums[left]+nums[right]:res;
                    left++;
                }
            }
            return res;
        
    }
    //question 17
    string c[8][5] = {
            {"a","b","c"},
            {"d","e","f"},
            {"g","h","i"},
            {"j","k","l"},
            {"m","n","o"},
            {"p","q","r","s"},
            {"t","u","v"},
            {"w","x","y","z"}
        };
    int a[8] = {3,3,3,3,3,4,3,4};

    vector<string> letterCombinations(string digits) {
        
        vector<string> res;
        if(digits.size()==0) return res;
        int tmp = digits[0]-'2';
        for(int j = 0;j<a[tmp];j++){
            vector<string> temp = letterCombinations(digits.substr(1,digits.size()-1));
            if(temp.empty()){
                string hehe="";
                hehe.append(c[tmp][j]);
                res.push_back(hehe);
            }
            else{
                 for(int i=0;i<temp.size();i++){
                    string hehe="";
                    hehe.append(c[tmp][j]);
                    hehe.append(temp[i]);
                    res.push_back(hehe);
                }
            }
        }
        return res;
        
    }

    //question 18
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int> > res;
        if(nums.size()<4) return res;
        sort(nums.begin(),nums.end());
        int left,right;
        
        for(int i=0;i<nums.size()-3;i++){
            int targ = target - nums[i];
            for(int j=i+1;j<nums.size()-2;j++){
                left = j+1;
                right = nums.size()-1;
                int sum = targ -nums[j];
                while(left<right){
                    if(nums[left]+nums[right]==sum){
                        vector<int> tmp;
                        tmp.push_back(nums[i]);
                        tmp.push_back(nums[j]);
                        tmp.push_back(nums[left]);
                        tmp.push_back(nums[right]);
                        res.push_back(tmp);
                        while(left<right&&nums[left]==nums[left+1]) left++;
                        while(right>left&&nums[right]==nums[right-1]) right--;
                        left++;
                        right--;
                    }
                    else{
                        nums[left]+nums[right]<sum?left++:right--;
                    }
                }
                while(j<nums.size()-3&&nums[j]==nums[j+1]) j++;
                
            }
            while(i<nums.size()-4&&nums[i]==nums[i+1]) i++;
        }
        return res;
        
    }
    
    //question 19
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *p = head;
        ListNode *q = head;;
        for(int i=0;i<n;i++)
            q = q->next;
        if(q==NULL) return head->next;
        while(q->next!=NULL){
            p = p->next;
            q = q->next;
        }
        
        p->next = p->next->next;
        return head;
    }

    //question 20
    bool isValid(string s) {
        stack<char> queue;
        
        for(char c:s){
            if(c=='('||c=='['||c=='{')
                queue.push(c);
            else if(c==')'){
                if(!queue.empty()&&queue.top()=='(')
                    queue.pop();
                else
                    return false;
            }
            else if(c==']'){
                if(!queue.empty()&&queue.top()=='[')
                    queue.pop();
                else
                    return false;
            }
            else if(c=='}'){
                if(!queue.empty()&&queue.top()=='{')
                    queue.pop();
                else
                    return false;
            }
            
        }
        if(queue.empty()) return true;
        else
            return false;
    }

};
