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
    //question 141
    bool hasCycle(ListNode *head) {
        if(head==NULL||head->next==NULL) return false;
        if(head->next==head) return true;
        
        ListNode *flag = head;
        ListNode *pre = NULL;
        while(head->next!=NULL){
            ListNode *tmp = head;
            head = head->next;
            tmp->next = pre;
            pre = tmp;
            if(head == flag)
                return true;
        }
        return false;
        
    }

    //question 142
    ListNode *detectCycle(ListNode *head) {
        set<ListNode*> ss;
        while(head){
            if(ss.find(head)!=ss.end()) return head;
            ss.insert(head);
            head = head->next;
        }
        return NULL;
    }

    //question 143
    void reorderList(ListNode* head) {
    
    ListNode *ts = head;
	ListNode *res = head;
	int size = 0;
    while(ts!=NULL){
        size++;
		ts = ts->next;
	}
	if(size==1||size==2||size==0) return;
	int num = size/2;
    while(num>0){

		head = head->next;
		num--;
	}
	num = size/2;											             
	ts = head->next;
	while(ts!=NULL){
		ListNode *tmp = ts;
		ts = ts->next;
		tmp->next = head;
		head = tmp;
	}
	ListNode *r = res;
	while(num>0){
		ListNode *tmp = res->next;
	    res->next = head;
	    head = head->next;
		res->next->next = tmp;
		res = tmp;
		num--;
	}
	res->next = NULL;
	/*
	while(r!=NULL){
		printf("%d\n",r->val);
		r = r->next;
	}
	*/
        
    }
    
    //question 144
    vector<int> preorderTraversal(TreeNode* root) {
         stack<TreeNode*> s;
         TreeNode * p =root;
         vector<int> res;
         while(!s.empty()||p){
             while(p){
                 res.push_back(p->val);
                 s.push(p);
                 p = p->left;
             }
             
            p = s.top();
            s.pop();
            p = p->right;
             
             
             
         }
         return res;
        
    }

    //question 145
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        map<TreeNode*,bool> flag;
        stack<TreeNode*> s;
        TreeNode *p;
        p = root;
        while(!s.empty()||p){
            while(p){
                s.push(p);
                p=p->left;
            }
            
            p = s.top();
            while(p->right==NULL||flag[p->right]){
                res.push_back(p->val);
                flag[p] = true;
                s.pop();
                if(!s.empty())
                    p = s.top();
                else 
                    return res;
            }
            p = p->right;
            
        }
        return res;
    }

    //question 147
    ListNode* insertionSortList(ListNode* head) {
        if(head==NULL) return NULL;
        if(head->next==NULL) return head;
        ListNode *k = head->next;
        ListNode *pre = head;
       // ListNode *res;
        while(k!=NULL){
            
            ListNode *tmp = k->next;
            if(k->val<=head->val){
                
                pre->next = tmp;
                k->next = head;
                head = k;
                k = tmp;
                
            }
            else if(k->val>=pre->val){
                pre = k;
                k = tmp;
            }
            else
            {
                ListNode *p = head;
                ListNode *t;
                while(k->val>p->val){
                    t = p;
                    p = p->next;
                }
                pre->next = tmp;
                t->next = k;
                k->next = p;
                k = tmp;
            }
            
        }
        return head;
    }

    //question 148
    ListNode* Merge(ListNode *s1,ListNode *s2){
        if(s1 == NULL) return s2;
        if(s2 == NULL) return s1;
        ListNode *res;
        ListNode *p;
        
        ListNode *q;
        if(s1->val<s2->val){
            p = s1;
            q = s2;
            res = s1;
        }
        else{
            p = s2;
            q = s1;
            res = s2;
        }
        ListNode *pre;
        while(q!=NULL){
            if(q->val>=p->val){
                pre = p;
                p = p->next;
                if(p == NULL){
                    pre->next = q;
                    return res;
                }
                
            }
            else{
                pre->next = q;
                ListNode *t = q->next;
                q->next = p;
                pre = q;
                q = t;
                
            }
        }
        return res;
    }
    
    ListNode* getMid(ListNode *head){
        ListNode *slow = head;
        ListNode *fast = head;
        ListNode *pre;
        while(1){
            pre = slow;
            slow = slow->next;
            fast = fast->next->next;
            
            if(fast==NULL||fast->next == NULL){
                pre->next = NULL;
                return slow;
            }
        }
        return slow;
    }
    
    ListNode* sortList(ListNode* head) 
    {
        //归并排序
        if(head ==NULL||head->next == NULL) return head;
        else{
            ListNode *mid = getMid(head);
            ListNode *h1 = sortList(head);
            ListNode *h2 = sortList(mid);
            return Merge(h1,h2);
        }
    }

    //question 149
    int maxPoints(vector<Point>& points) {
        
        map<pair<pair<int,int>,int>,vector<int>> mp;
        int res = 0;
        if(points.empty()) return res;
        if(points.size()==1) return 1;
        res = 1;
        for(int i=0;i<points.size()-1;i++){
            bool flag = false;
            for(int j=i+1;j<points.size();j++){
                pair<pair<int,int>,int> tmp = getline(points[i],points[j]);
                auto it = mp.find(tmp);
                if(it!=mp.end()){
                    if(find(mp[tmp].begin(),mp[tmp].end(),i)==mp[tmp].end())
                        mp[tmp].push_back(i);
                    if(find(mp[tmp].begin(),mp[tmp].end(),j)==mp[tmp].end())
                        mp[tmp].push_back(j);
                    res = max(res,(int)mp[tmp].size());
                    //if((int)mp[tmp].size()==21)
                    //cout<<tmp.first<<"  "<<tmp.second<<"   "<<(int)mp[tmp].size()<<endl;
                }
                else{
                    vector<int> temp;
                    temp.push_back(i);
                    temp.push_back(j);
                    mp[tmp] = temp;
                    res = max(res,(int)mp[tmp].size());
                    //cout<<tmp.first<<"  "<<tmp.second<<"   "<<(int)mp[tmp].size()<<endl;
                }
            }
        }
        return res;
        
        
        
    }
    
    pair<pair<int,int>,int> getline(Point a,Point b){
        
        if(b.x==a.x){
            pair<int,int> k(INT_MAX,INT_MAX);
            pair<pair<int,int>,int> hehe(k,b.x);
            return hehe;
        }
        else{
            int g = gcd(b.y-a.y,b.x-a.x);
            int i = (b.y-a.y)/g;
            int j = (b.x-a.x)/g;
            pair<int,int> k(i,j);
            double kk = (b.y-a.y)*1.0/(b.x-a.x);
        
            int d = b.y*1.0 - kk*b.x;
            pair<pair<int,int>,int> hehe(k,d);
            return hehe;
        }
    }
    
    int gcd(int a,int b){
        if(b==0) return a;
        else
            return gcd(b,a%b);
    }


    //question 150
    int evalRPN(vector<string>& tokens) {
        stack<int> s;
        //int res;
        for(auto n:tokens){
            if(n=="+"){
                int a = s.top();
                s.pop();
                int b = s.top();
                s.pop();
                s.push(a+b);
            }
            else if(n=="-"){
                int a = s.top();
                s.pop();
                int b = s.top();
                s.pop();
                s.push(b-a);
            }
            else if(n=="*"){
                int a = s.top();
                s.pop();
                int b = s.top();
                s.pop();
                s.push(a*b);
            }
            else if(n=="/"){
                int a = s.top();
                s.pop();
                int b = s.top();
                s.pop();
                s.push(b/a);
            }
            else{
                int tmp = atoi(n.c_str());
                s.push(tmp);
            }
        }
        return s.top();
    }

    //question 151
    void reverseWords(string &s) {
        string res;
        if(s=="") return;
        while(s[0]==' ') s.erase(0,1);
        if(s=="") return;
        while(s[s.size()-1]==' ') s.erase(s.size()-1,1);
        stack<char> temp;
        cout<<s<<endl;
        for(int i=s.size()-1;i>=0;i--){
            //if((s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z')||(s[i]>='0'&&s[i]<='9')){
            if(s[i]!=' '){
                temp.push(s[i]);
            }
            else{
                string tmp;
                while(!temp.empty()){
                    tmp += temp.top();
                    temp.pop();
                }
                res+=tmp;
                if(res[res.size()-1]!=' ')
                    res+=s[i];
            }
        }
        string tmp;
        while(!temp.empty()){
            tmp += temp.top();
            temp.pop();
        }
        res+=tmp;
        s= res;
    }

    //question 152
    int maxProduct(vector<int>& nums) {
        int length = nums.size();
        int maxx[length];
        int minn[length];
        
        int maxium = nums[0];
        maxx[0] = maxium;
        minn[0] = maxium;
        for(int i=1;i<nums.size();i++){
            minn[i] = min(nums[i],min(nums[i]*minn[i-1],nums[i]*maxx[i-1]));
            maxx[i] = max(nums[i],max(nums[i]*maxx[i-1],nums[i]*minn[i-1]));
            if(maxx[i]>maxium)
                maxium = maxx[i];
        }
        return maxium;
        
    }


    //question 153
    int findMin(vector<int>& nums) {
        int current = nums[0];
        if(nums.size()==1||current<nums[nums.size()-1]) return current;
        
        int left = 0;
        int right = nums.size()-1;
        int mid;
        while(left<=right){
            mid = (left+right)/2;
            if(nums[mid]<current){
                right = mid-1;
                current = nums[mid];
            }
            else
                left = mid+1;
                
            
           
        }
        return current;
    }

    //question 160
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA==NULL||headB==NULL) return NULL;
        ListNode *curA = headA;
        ListNode *curB = headB;
        int lenA = 1;
        int lenB = 1;
        
        while(curA->next!=NULL){
            lenA++;
            curA = curA->next;
        }
        while(curB->next!=NULL){
            lenB++;
            curB = curB->next;
        }
        if(curA!=curB) return NULL;
        curA = lenA>lenB?headA:headB;
        curB = lenA>lenB?headB:headA;
        int cha = abs(lenA-lenB);
        while(cha>0){
            curA = curA->next;
            cha--;
        }
        while(curA!=curB){
            curA = curA->next;
            curB = curB->next;
        }
        return curA;
        
        
    }

};

//question 146
class LRUCache {
public:
    LRUCache(int capacity) {
        vol = capacity;
    }
    
    int get(int key) {
        if(mp.find(key)!=mp.end()){
            pri.erase(find(pri.begin(),pri.end(),key));
            pri.push_back(key);
            return mp[key];
        }
        else return -1;
    }
    
    void put(int key, int value) {
        if(mp.find(key)!=mp.end()){
            mp[key] = value;
            pri.erase(find(pri.begin(),pri.end(),key));
            pri.push_back(key);
        }
        else{
            if(vol>0){
                mp[key] = value;
                pri.push_back(key);
                vol--;
            }
            else{
                mp[key] = value;
                pri.push_back(key);
                mp.erase(mp.find(pri[0]));
                pri.erase(pri.begin());
            }
        }
    }
    
private:
    map<int,int> mp;
    vector<int> pri;
    int vol;
};

//question 155
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        minium = INT_MAX;
    }
    
    void push(int x) {
        nums.push_back(x);
        minium = min(minium,x);
    }
    
    void pop() {
        int tmp = nums[nums.size()-1];
        nums.erase(nums.end()-1);
        if(tmp==minium){
            minium = INT_MAX;
            for(auto p:nums)
                minium = min(minium,p);
        }
    }
    
    int top() {
        return nums[nums.size()-1];
    }
    
    int getMin() {
        return minium;
    }
    private:
        vector<int> nums;
        int minium;
};
