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
    //question 91
    int numDecodings(string s) {
        if(s.empty()) return 0;
        int dp[s.size()+1];
        dp[0] = 1;
        if(s[0]=='0')
            dp[1] = 0;
        else
            dp[1] = 1;
        for(int i =1 ;i<s.size();i++){
            int c =0;
            if(s[i]!='0')
                c += dp[i];
            
            string tmp = s.substr(i-1,2);
            int count = atoi(tmp.c_str());
            if(tmp[0]!='0'&&count<27)
                c+=dp[i-1];
            dp[i+1] = c;
        }
        return dp[s.size()];
    }

    //question 92
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        int count = 1;
        if(m==n) return head;
        
        ListNode *first = new ListNode(-1);
        first->next = head;
        ListNode *pre = first;
        ListNode *cur = head;
        while(count<m){
            pre = cur;
            cur = cur->next;
            count++;
        }
        int k=0;
        ListNode *right = cur;
        ListNode *left = pre;
        while(k<=(n-m)){
            ListNode *tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
            k++;
        }
        left->next = pre;
        right->next = cur;
        return first->next;
    }

    //question 93
    vector<string> res;
    vector<string> restoreIpAddresses(string s) {
        dfs(s,0,"",1);
        return res;
    }
    
    void dfs(string s,int i,string tmp,int level){
        
        if(level==4){
            if(i>=s.size()||s.size()-i>3) return;
            string hehe = s.substr(i,s.size()-i);
            if(hehe[0]=='0'&&hehe.size()>1) return;
            int ip = atoi(hehe.c_str());
            if(ip>=0&&ip<=255){
                tmp += hehe;
                res.push_back(tmp);
            }
        }
        else{
            if(s[i]=='0'){
                string tmp2 = tmp+"0.";
                dfs(s,i+1,tmp2,level+1);
            }
            else{
                for(int j=1;j<=3;j++){
                    if((i+j)>=s.size()||s.size()-i>3*(4-level+1)) return;
                    string hehe = s.substr(i,j);
                    int ip = atoi(hehe.c_str());
                    if(ip>0&&ip<=255){
                        string tmp2 = tmp+hehe+".";
                        dfs(s,i+j,tmp2,level+1);
                    }
                }
            }    
            
        }
    }


    //question 94
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> s;
        while(!s.empty()||root){
            while(root){
                s.push(root);
                root = root->left;
            }
           
                root=s.top();
                res.push_back(root->val);
                s.pop();
                
                root = root->right;
    
        }
        return res;
        
    }

    //question 95
    vector<TreeNode*> generateTrees(int n) {
        return dfs(1,n);
    }
    
    vector<TreeNode*> dfs(int left,int right){
        vector<TreeNode*> res;
        if(left>right) return res;
        for(int i=left;i<=right;i++){
            vector<TreeNode*> leftres = dfs(left,i-1);
            vector<TreeNode*> rightres = dfs(i+1,right);
            if(!leftres.empty()&&!rightres.empty()){
                for(TreeNode* l:leftres){
                    for(TreeNode* r:rightres){
                        TreeNode *root = new TreeNode(i);
                        root->left = l;
                        root->right = r;
                        res.push_back(root);
                    }
                }
            }
            else if(leftres.empty()&&!rightres.empty()){
                for(TreeNode* r:rightres){
                    TreeNode *root = new TreeNode(i);
                    root->right = r;
                    res.push_back(root);
                }
            }
            else if(!leftres.empty()&&rightres.empty()){
                for(TreeNode* l:leftres){
                    TreeNode *root = new TreeNode(i);
                    root->left = l;
                    res.push_back(root);
                }
            }
            else{
                TreeNode *root = new TreeNode(i);
                res.push_back(root);
            }
        }
        return res;
    }

    //question 96
    int numTrees(int n){
        if(n==0) return 1;
        if(jilu[n]!=0) return jilu[n];
        int res = 0;
        for(int i=1;i<=n;i++){
            res += numTrees(i-1)*numTrees(n-i);
        }
        jilu[n] = res;
        return res;
    }


    //question 97
    int dp[1000][1000];
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.size()+s2.size()!=s3.size()) return false;

        for(int i=0;i<=s1.size();i++)
            for(int j=0;j<=s2.size();j++)
                dp[i][j] = -1;
        return judge(s1,s2,s3);

    }
    
    bool judge(string s1,string s2,string s3){

            if(s1.empty()&&s2.empty()&&s3.empty()) return true;
            if(dp[s1.size()][s2.size()]==0) return false;
            if(dp[s1.size()][s2.size()]==1) return true;
            if(!s1.empty()&&!s3.empty()&&s1[s1.size()-1]==s3[s3.size()-1])
                if(judge(s1.empty()?"":s1.substr(0,s1.size()-1),s2,s3.empty()?"":s3.substr(0,s3.size()-1)))
                    return true;
            if(!s2.empty()&&!s3.empty()&&s2[s2.size()-1]==s3[s3.size()-1])
                if(judge(s1,s2.empty()?"":s2.substr(0,s2.size()-1),s3.empty()?"":s3.substr(0,s3.size()-1)))
                    return true;
            dp[s1.size()][s2.size()] = 0;
            return false;
    }

    //question 98
    vector<int> hehe;
    bool isValidBST(TreeNode* root) {
        if(root==NULL) return true;
        if(root->left){
            if(!isValidBST(root->left))
                return false;
        }
        if(hehe.size()>0&&root->val<=hehe[hehe.size()-1]) return false;
        hehe.push_back(root->val);
        if(root->right){
            if(!isValidBST(root->right))
                return false;
        }
        return true;
    }

    //question 99
    vector<TreeNode*> in;
    void recoverTree(TreeNode* root) {
        inorderTree(root);
        TreeNode* left = NULL;
        TreeNode* right = NULL;
        for(int i =0;i<in.size()-1;i++){
            if(in[i]->val>in[i+1]->val){
                left = in[i];
                break;
            }
        }
        for(int i =in.size()-1;i>0;i--){
            if(in[i]->val<in[i-1]->val){
                right = in[i];
                break;
            }
        }
        int tmp = left->val;
        left->val = right->val;
        right->val = tmp;
    }
    
    void inorderTree(TreeNode* root){
        if(root==NULL) return;
        inorderTree(root->left);
        in.push_back(root);
        inorderTree(root->right);
    }

    //question 100
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p==NULL&&q==NULL)
            return true;
        if((p==NULL&&q!=NULL)||(p!=NULL&&q==NULL))
            return false;
            
        if(p->val!=q->val)
            return false;
        if(!isSameTree(p->left,q->left))
            return false;
        if(!isSameTree(p->right,q->right))
            return false;
        return true;
    }

};



