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

class solution {
	//Question1
    vector<int> twoSum(vector<int>& nums, int target) {
    	vector<int> res;
        
        map<int,int> hash;
        map<int,int>::iterator it;
        
        for(int i =0;i<nums.size();i++){
            if((it=hash.find(target-nums[i]))!=hash.end()){
                res.push_back(it->second);
                res.push_back(i);
                return res;
            }
            else{
                hash[nums[i]]=i;
            }
        }
        /*
        int left = 0,right = nums.size()-1;
        sort(nums.begin(),nums.end());
        while(left<right){
            if(nums[left]+nums[right]==target){
                res.push_back(left);
                res.push_back(right);
                return res;
            }
            else{
                nums[left]+nums[right]<target?left++:right--;
            }
        }
        返回索引，不能用two points
        */
        return res;
    }
	//Question 2
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        //reverseList(l2);
        
        ListNode *root = l1;
        int flag = 0;
        while(1){
            
            int tmp = (l1->val+l2->val+flag)%10;
            flag = (l1->val+l2->val+flag)/10;
            l1->val = tmp;
            if(l1->next==NULL&&l2->next!=NULL)
                l1->next = new ListNode(0);
            else if(l1->next!=NULL&&l2->next==NULL)
                l2->next= new ListNode(0);
            else if(l1->next==NULL&&l2->next==NULL&&flag>0){
                l1->next= new ListNode(0);
                l2->next= new ListNode(0);
            }
            else if(l1->next==NULL&&l2->next==NULL&&flag==0) {
                break;
            } 
            l1 = l1->next;
            l2 = l2->next;
        }
        return root;
        /*
        ListNode *root;
        long count = 1, a=0,b=0;
        while(l1!=NULL){
            a += l1->val*count;
            count *= 10;
            l1 = l1->next;
        }
        count = 1;
        while(l2!=NULL){
            b += l2->val*count;
            count *=10;
            l2 = l2->next;
        }
        count = 10;
        long c = a+b;
        
        root = new ListNode(c%10);
        ListNode *res = root;
        while((c/count)!=0){
            root->next = new ListNode((c/count)%10);
            root = root->next;
            count *=10;
        }
        return res;\
        */
    }
    void reverseList(ListNode *&root){
        
        ListNode *pre = root;
        root = root->next;
        pre->next = NULL;
        while(root!=NULL){
           ListNode *tmp = root->next; 
           root->next = pre;
           pre = root;
           root = tmp;
        }
        root = pre;
    }

    //Question 3
	int lengthOfLongestSubstring(string s) {
        map<char,int> hash;
        //map<char,int> mapp;
        int count = 0;
        int maxium = 0;
        for(int i=0;i<s.size();i++){
            
            hash[s[i]] = -1;
        }
        for(int i=0;i<s.size();i++){
            
            if(hash[s[i]]<(i-count)){
                //mapp[s[i]] =1;
                hash[s[i]] = i;
                count++;
            }
            else{
                count = i-hash[s[i]];
                hash[s[i]] = i;
            }
            maxium = max(maxium,count);
            
        }
        return maxium;
    }
 
   //Quesition 4
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        
        vector<int> m,n;
        if(nums1.size()<nums2.size()){
            m = nums1;
            n = nums2;
        }
        else{
            m = nums2;
            n = nums1;
        }
        int len1 = m.size();
        int len2 = n.size();
        int k = (len1+len2+1)/2;
        int left = 0,right = len1;
        int mid1,mid2;
        int leftmax;
        int rightmin;
        while(left<=right){
            mid1 = left+(right-left)/2;
            mid2 = k - mid1;
            
            if(mid1>0&&m[mid1-1]>n[mid2]){
                right = mid1-1;
            }
            else if(mid1<len1&&n[mid2-1]>m[mid1]){
                left = mid1+1;
            }
            else{
                if(mid1==0) leftmax = n[mid2-1];
                else if(mid2==0) leftmax = m[mid1-1];
                else leftmax = max(n[mid2-1],m[mid1-1]);
                if((len1+len2)%2==1) return leftmax;
                if(mid1==len1) rightmin = n[mid2];
                else if(mid2==len2) rightmin = m[mid1];
                else rightmin = min(m[mid1],n[mid2]);
                
                return (leftmax+rightmin)/2.0;
            }
        }
        return 0;

    }
    
    int findKth(){
    	return 0;   
    }

    //Question 5
	string longestPalindrome(string s) {
        bool dp[s.size()][s.size()];
        for(int i=0;i<s.size();i++){
            for(int j=0;j<s.size();j++){
                if(i==j)
                    dp[i][j] = true;
                else
                    dp[i][j] = false;
            }
        }
        int maxium = 1,pre = 0 ;
        for(int i=0;i<s.size();i++){
            for(int j = 0;j<i;j++){
                if(s[i]==s[j]&&(dp[j+1][i-1]||(i-j)<=2)){
                    dp[j][i] = true;
                    if((i-j+1)>maxium){
                        maxium = (i-j+1);
                        pre = j;
                    }
                }
                else{
                    dp[j][i] = false;
                }
                    
            }
        }
        return s.substr(pre,maxium);      
    }

	//Question 6
	string convert(string s, int numRows) {
        if(numRows==1) return s;
        string res = s;
        //if() return res;
        int count = 0;
        int v=0;
        for(int i=numRows;i>=1;i--){
            v = numRows-i;
            if(i==1||i==numRows){
               while(v<s.size()&&count<s.size()){
                   res[count++] = s[v];
                   v += 2*numRows-2;
               } 
            }
            else{
                bool flag = true;
                while(v<s.size()&&count<s.size()){
                    res[count++] = s[v];
                    if(flag){
                        v += 2*i-2;
                        flag = false;
                    }
                    else{
                        v += 2*(numRows-i);
                        flag = true;
                    }
               }
            }
        }
        return res;    
    }

	//Question 7
	int reverse(int x) {
        long res =0;
        long n = 1;
        int flag = 1;
        if(x<0) {
          flag = -1;
          x = abs(x);
        }
        while(x/n!=0){
          
            n *=10;
        }
        n /=10;
        long m=1;
        while(x/m!=0){
            res += (x/m)%10*n;
            n /=10;
            m *=10;
        }
        if(res>INT_MAX||res<INT_MIN)
          return 0;
        else
          return res*flag;
      }

	//Question

	int myAtoi(string str) {
    	if(str=="") return 0;
    	long long res = 0;
    	while(str[0]==' ')
        	str = str.erase(0,1);
    	int sign = 1;
    	if(str[0]=='-'){
        	sign = -1;
        	str = str.erase(0,1);
   	 	}
    	else if(str[0]=='+'){
        	str = str.erase(0,1);
    	}
    
    	for(int i=0;i<str.size();i++){
        	if(!((str[i]-'0')>=0&&(str[i]-'0')<=9))
            	break;
        	else{
            	res = res*10 +(str[i]-'0');
            	if(res*sign>INT_MAX)
                	return INT_MAX;
            	else if(res*sign<INT_MIN)
                	return INT_MIN;
       	 	}
    	}
    	return int(res*sign);
    }

	//Question 9
	bool isPalindrome(int x) {
        int res = 0;
        int t = x;
        if(x<0) return false;
        while(x!=0){
            res = res*10 +x%10;
            x = x/10;
        }
        if(res == t)
            return true;
        else
            return false;
    }

	//Question 10
	//....
}

