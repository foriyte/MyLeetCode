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
    //question21
    ListNode* mergeTwoLists(ListNode* l, ListNode* r) {
       if(l==NULL) return r;
       if(r==NULL) return l;
       ListNode* res;
       if(l->val<r->val){
           res = l;
           res->next = mergeTwoLists(l->next,r);
           return res;
       } 
       else{
           res = r;
           res->next = mergeTwoLists(l,r->next);
           return res;
       }
        /*
        ListNode* pre = new ListNode(0);
        ListNode* last;
        ListNode* cur;
        cur = l;
        last = r->next;
        pre->next = l;
        if(l->val>r->val){
            l = r;
            l->next = cur;
            r = last;
            pre = l;
        }
        
        while(r!=NULL){
            if(cur==NULL){
                pre->next = r;
                break;
            }
            if(r->val>=cur->val){
                cur = cur->next;
                pre = pre->next;
            }
            else{
                pre->next = r;
                last = r->next;
                r->next = cur;
                pre = r;
                r = last;
            }
        }
        return l;
        */
    }
    //question 22
    vector<string> generateParenthesis(int n) {
        
        vector<string> res;
        if(n==0) return res;
        else if(n==1){
            res.push_back("()");
            return res;
        }
        else{
            vector<string> tmp = dfs(n-1,n,1);
            for(string p :tmp)
                res.push_back("("+p);
           
            
        }
        return res;
        
    }
    
    vector<string> dfs(int left,int right,int p){
        
        vector<string> res;
        if(right==0){ 
            res.push_back("");
            return res;
        }
        else{
            if(p==0){
                vector<string> tmp = dfs(left-1,right,1);
                for(string p:tmp){
                    res.push_back("("+p);
                }
            }
            else if(p>0&&left>0){
                vector<string> tmp = dfs(left-1,right,p+1);
                for(string p:tmp){
                    res.push_back("("+p);
                }
                vector<string> tmp2 = dfs(left,right-1,p-1);
                for(string p:tmp2){
                    res.push_back(")"+p);
                }
            }
            else if(p>0&&left==0){
                vector<string> tmp = dfs(left,right-1,p-1);
                for(string p:tmp){
                    res.push_back(")"+p);
                }
            }
        }
        return res;
        
        
    }
    
     //question 23
     ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = lists.size();
        if(n==0) return NULL;
        /*
        else if(n==1) return lists[0];
        else if(n==2) return merge(lists[0],lists[1]);
        else if(n==3) return merge(merge(lists[0],lists[1]),lists[2]);
        else
            return mergeLists(lists,0,(lists.size()-1)/2,(lists.size()-1)/2+1,lists.size()-1);
            */
        else{
            while(lists.size()>1){
                lists.push_back(merge(lists[0],lists[1]));
                lists.erase(lists.begin());
                lists.erase(lists.begin());
            }
            return lists[0];
        }
    }
    
    ListNode* mergeLists(vector<ListNode*> lists,int l1,int r1,int l2,int r2){
        ListNode* left;
        ListNode* right;
        if(r1-l1==1) left = merge(lists[l1],lists[r1]);
        else if(r1-l1==2){
           left = merge(merge(lists[l1],lists[l1+1]),lists[r1]); 
        }
        else{
            left = mergeLists(lists,l1,l1+(r1-l1)/2,l1+(r1-l1)/2+1,r1);
        }
        if(r2-l2==1) right = merge(lists[l2],lists[r2]);
        else if(r2-l2==2){
           right = merge(merge(lists[l2],lists[l2+1]),lists[r2]); 
        }
        else{
            right = mergeLists(lists,l2,l2+(r2-l2)/2,l2+(r2-l2)/2+1,r2);
        }
        return merge(left,right);
    }
    
    ListNode* merge(ListNode* l,ListNode* r){
        if(l==NULL) return r;
        if(r==NULL) return l;
        ListNode* pre = new ListNode(0);
        ListNode* last;
        ListNode* cur;
        cur = l;
        last = r->next;
        pre->next = l;
        if(l->val>r->val){
            l = r;
            l->next = cur;
            r = last;
            pre = l;
        }
        
        while(r!=NULL){
            if(cur==NULL){
                pre->next = r;
                break;
            }
            if(r->val>=cur->val){
                cur = cur->next;
                pre = pre->next;
            }
            else{
                pre->next = r;
                last = r->next;
                r->next = cur;
                pre = r;
                r = last;
            }
        }
        return l;
    }

    //question24
    ListNode* swapPairs(ListNode* head) {
        if(head==NULL||head->next==NULL) return head;
        ListNode* pre = NULL;
        ListNode* cur = head;
        ListNode* last = NULL;
        ListNode* right=NULL;
        bool flag = true;
        while(cur!=NULL){
            
            right = cur->next;
                
            if(pre==NULL){
                pre = cur;
                last = right;
                cur = last->next;
                last->next = pre;
                pre->next = NULL;
            }
            else{
                if(right==NULL){
                    pre->next = cur;
                    break;
                }
                else{
                    pre->next = right; 
                    ListNode* tmp = cur;
                    cur = right->next;
                    right->next = tmp;
                    pre = tmp;
                    pre->next = NULL;//防止末尾成循环，检测超时
                }
            }       
        }
        return last;
    }

    //question 25
    ListNode* reverseKGroup(ListNode* head, int k) {
        /*
        if(k==1||head==NULL||head->next==NULL) return head;
        int count = 1;
        ListNode* cur = head;
        ListNode* pre = NULL;
        ListNode* first = head;
        ListNode* last = head;
        ListNode* left = NULL;
        ListNode* right = NULL;
        while(cur!=NULL){
            if(count==k){
                right = cur->next;
                cur->next = left;
                if(pre!=NULL){
                    pre->next = cur;
                    pre = first;
                    first->next = right;
                }
                else{
                    pre = first;
                    last = cur;
                    pre->next = NULL;
                }
                count=1;
                cur=right;
            }
            else{
                if(count==1) {
                    ListNode* tmp = cur;
                    while(count<k&&tmp!=NULL) {
                        tmp = tmp->next;
                        count++;
                    }
                    if(tmp==NULL) {
                        if(pre!=NULL&&pre->next==NULL)
                            pre->next = cur;
                        break;
                    }
                    else count = 1;
                    first = cur;
                    left = cur;
                    cur = cur->next;
                }
                else{
                    right = cur->next;
                    cur->next = left;
                    left = cur;
                    cur = right;
                }
                count++;
            }
        }
        return last;
        */
        if(k==1||head==NULL||head->next==NULL) return head;
        int count = 1;
        ListNode *cur = head;
        while(count<k&&cur!=NULL){
            cur = cur->next;
            count++;
        }
        if(cur==NULL){
            return head;
        }
        else{
            ListNode *pre = head;
            ListNode *last;
            cur = head->next;
            count =1;
            while(count<k){
                last = cur->next;
                cur->next = pre;
                pre = cur;
                cur = last;
                count++;
            }
            head->next = reverseKGroup(cur,k);
            return pre;
        }
 
    }

    //question 26
    int removeDuplicates(vector<int>& nums) {
        if(nums.size()<2) return nums.size();
        int pre = nums[0];
        for(vector<int>::iterator it = nums.begin()+1;it!=nums.end();++it){
        
            if(*it==pre){
                nums.erase(it);
                it--;
            }
            else{
                pre = *it;
            }
        }
        return nums.size();
    }

    //question 24
    int removeElement(vector<int>& nums, int val) {
        vector<int>::iterator it = nums.begin();
        for(;it!=nums.end();++it){
            if(*it==val){
                nums.erase(it);
                it--;
            }
        }
        return nums.size();
    }

    //question 28
    int strStr(string haystack, string needle) {
        int res;
        if(haystack==needle||needle.size()==0) return 0;
        if(haystack.size()<needle.size()) return -1;
        
        vector<int> next = kmpNext(needle);
        int i=0,j=0;
        while(i<haystack.size()&&j<needle.size()){
            if(haystack[i]==needle[j]){
                i++;
                j++;
            }
            else if(j>0){
                j=next[j];
            }
            else{
                i++;
            }
        }
        if(j==needle.size()) return i-needle.size();
        return -1;
    }
    
    vector<int> kmpNext(string s){
        
        vector<int> next(s.size(),0);
        next[0] =0;
        if(s.size()==1) return next;
        next[1] = 0;
        for(int i=1;i<s.size()-1;i++){
            int j = next[i];
            while(j>0&&s[j]!=s[i]) j = next[j];
            if(s[j]==s[i]) next[i+1] = j+1;
            
        }
        return next;
    }

    //question 29
    int divide(int dividend, int divisor) {
        if(dividend==0) return 0;
        
        if(dividend==INT_MIN&&divisor==-1||divisor==0) return INT_MAX;
        if(divisor==1) return dividend;
        if(divisor==-1) return -dividend;
        int sign = (dividend^divisor)<0?-1:1;
        long divd = labs(dividend);
        long divs = labs(divisor);
        long res = 0;
        while(divd>=divs){
            long tmp = divs;
            long tmpres = 1;
            while(divd>(tmp<<1)){
                tmp <<=1;
                tmpres <<=1;
            }
            divd-=tmp;
            res+=tmpres;
        }
        
        return sign>0?res:-res;
        
    }

    //question 30
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        int m = words[0].size();
        int n = words.size();
        int len = m*n;
        if(s.size()<len) return res;
        unordered_map<string,int> wmap;
        for(string word:words)
            wmap[word]++;
        //vector<int>::iterator itin;
        
        for(int i = 0;i<=s.size()-len;i++){
            string tmp = s.substr(i,len);
            unordered_map<string,int> tmap;
            int left = 0,right = tmp.size()-m;
            bool flag = true;
            while(left<=right){
                string l = tmp.substr(left,m);
                string r = tmp.substr(right,m);
                tmap[l]++;
                if(tmap[l]>wmap[l]) {
                    flag = false;
                    break;
                }
                if(left==right) break;
                tmap[r]++;
                if(tmap[r]>wmap[r]){
                    flag = false;
                    break; 
                } 
                left+=m;
                right-=m;
            }
            if(flag){
                res.push_back(i);
            }
        }
        
        return res;
    }


};





