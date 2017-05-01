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
    //question 101
    bool isSymmetric(TreeNode* root) {
        if(root==NULL) return true;
        return dfs(root->left,root->right);
        
    }
    bool dfs(TreeNode* left,TreeNode* right){
        if(left==NULL^right==NULL)
            return false;
        else if(left==NULL&&right==NULL)
            return true;
        else{
            if(left->val!=right->val)
                return false;
            else{
                return dfs(left->left,right->right)&&dfs(left->right,right->left);
            }
        }
    }

    //question 102
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(!root) return res;
        queue<pair<TreeNode*,int>> que;
        pair<TreeNode*,int> first(root,1);
        que.push(first);
        vector<int> hehe;
        int last = 1;
        while(!que.empty()){
            pair<TreeNode*,int> tmp = que.front();
            if(tmp.second==last){
                hehe.push_back(tmp.first->val);
            }
            else{
                res.push_back(hehe);
                hehe.clear();
                hehe.push_back(tmp.first->val);
                last = tmp.second;
            }
            if(tmp.first->left!=NULL){
                pair<TreeNode*,int> left(tmp.first->left,tmp.second+1);
                que.push(left);
            }
            if(tmp.first->right!=NULL){
                pair<TreeNode*,int> right(tmp.first->right,tmp.second+1);
                que.push(right);
            }
            que.pop();
            
        }
        if(!hehe.empty())
            res.push_back(hehe);
        return res;
    }

    //question 103
    tor<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(!root) return res;
        stack<TreeNode*> left;
        stack<TreeNode*> right;
        right.push(root);
        vector<int> hehe;
        hehe.push_back(root->val);
        res.push_back(hehe);
        hehe.clear();
        while(!left.empty()||!right.empty()){
                while(!right.empty()){
                    TreeNode* tmp = right.top();
                    if(tmp->right){
                        left.push(tmp->right);
                        hehe.push_back(tmp->right->val);
                    }
                    if(tmp->left){
                        left.push(tmp->left);
                        hehe.push_back(tmp->left->val);
                    }
                    right.pop();
                }
                if(!hehe.empty()){
                    res.push_back(hehe);
                    hehe.clear();
                }
                while(!left.empty()){
                    TreeNode* tmp = left.top();
                    if(tmp->left){
                        right.push(tmp->left);
                        hehe.push_back(tmp->left->val);
                    }
                    if(tmp->right){
                        right.push(tmp->right);
                        hehe.push_back(tmp->right->val);
                    }
                    left.pop();
                }
                if(!hehe.empty()){
                    res.push_back(hehe);
                    hehe.clear();
                }
            
            
        }
        return res;
    }


    //question 104
    int maxDepth(TreeNode* root) {
        if(root==NULL)
            return 0;
        else
            return max(maxDepth(root->left),maxDepth(root->right))+1;
    }


TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return build(preorder,0,preorder.size()-1,inorder,0,inorder.size()-1);
    }
    
    //question 105
    TreeNode* build(vector<int>& preorder,int prestart,int preend,vector<int>& inorder,int instart,int inend){
        TreeNode *root = NULL;
        if(prestart>preend||instart>inend){
            return root;
        }
        else{
            root = new TreeNode(preorder[prestart]);
            int leftcount = 0,rightcount = 0;
            bool flag = true;
            int rootnumber = -1;
            for(int i = instart;i<=inend;i++){
                if(inorder[i]==preorder[prestart]){
                    flag = false;
                    rootnumber = i;
                    continue;
                }
                flag?leftcount++:rightcount++;
            }
            root->left = build(preorder,prestart+1,prestart+leftcount,inorder,instart,rootnumber-1);
            root->right = build(preorder,prestart+leftcount+1,preend,inorder,rootnumber+1,inend);
            return root;
        }
        
    }

    //question 106
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
         return build(postorder,0,postorder.size()-1,inorder,0,inorder.size()-1);
    }
    
    TreeNode* build(vector<int>& postorder,int poststart,int postend,vector<int>& inorder,int instart,int inend){
        TreeNode *root = NULL;
        if(poststart>postend||instart>inend){
            return root;
        }
        else{
            root = new TreeNode(postorder[postend]);
            int leftcount = 0,rightcount = 0;
            bool flag = true;
            int rootnumber = -1;
            for(int i = instart;i<=inend;i++){
                if(inorder[i]==postorder[postend]){
                    flag = false;
                    rootnumber = i;
                    continue;
                }
                flag?leftcount++:rightcount++;
            }
            root->left = build(postorder,poststart,poststart+leftcount-1,inorder,instart,rootnumber-1);
            root->right = build(postorder,poststart+leftcount,postend-1,inorder,rootnumber+1,inend);
            return root;
        }
        
    }

    //question 107
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        stack<vector<int>> st;
        vector<vector<int>> res;
        if(root==NULL) return res;
        int last = 1;
        queue<pair<TreeNode*,int>> que;
        pair<TreeNode*,int> hehe(root,1);
        que.push(hehe);
        vector<int> temp;
        while(!que.empty()){
            pair<TreeNode*,int> tmp = que.front();
            if(tmp.second==last){
                if(tmp.first->left){
                    hehe = make_pair(tmp.first->left,last+1);
                    que.push(hehe);
                }
                if(tmp.first->right){
                    hehe = make_pair(tmp.first->right,last+1);
                    que.push(hehe);
                }
                temp.push_back(tmp.first->val);
                que.pop();
            }
            else{
                st.push(temp);
                temp.clear();
                last++;
            }
        }
        if(!temp.empty())
            st.push(temp);
        while(!st.empty()){
            res.push_back(st.top());
            st.pop();
        }
        return res;
    }

    //question 108
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if(nums.empty()) return NULL;
        return build(nums,0,nums.size()-1);
    }
    TreeNode* build(vector<int>& nums,int x,int y){
        TreeNode *root;
        if(y==x)
            root = new TreeNode(nums[x]);
        else if((y-x)==1){
            root = new TreeNode(nums[(x+y)/2]);
            root->right = new TreeNode(nums[(x+y)/2+1]);
        }
        else{
            root = new TreeNode(nums[(x+y)/2]);
            root->left = build(nums,x,(x+y)/2-1);
            root->right = build(nums,(x+y)/2+1,y);
        }
        return root;
    }


    //question 109
    TreeNode* sortedListToBST(ListNode* head) {
        int count = 0;
        ListNode *cur = head;
        TreeNode* root;
        while(cur!=NULL){
            count++;
            cur = cur->next;
        }
        if(count==0)
            return NULL;
        else if(count==1){
            root = new TreeNode(head->val);
        }
        else{
            ListNode *pre;
            cur = head;
            count /=2;
            while(count>0){
                count--;
                pre = cur;
                cur = cur->next;
            }
            pre->next = NULL;
            root = new TreeNode(cur->val);
            root->left = sortedListToBST(head);
            root->right = sortedListToBST(cur->next);
        }
        return root;
    }

    //question 110
    bool isBalanced(TreeNode* root) {
        if(root==NULL) return true;
        if(!isBalanced(root->left)||!isBalanced(root->right)) return false;
        int l = getHeight(root->left);
        int r = getHeight(root->right);
        if(abs(l-r)>1) return false;
        else return true;
    }
    int getHeight(TreeNode* root){
        if(root==NULL) return 0;
        return max(getHeight(root->left),getHeight(root->right))+1;
    }

    //question 111
    int minDepth(TreeNode* root) {
        if(root==NULL) return 0;
        else {
            int a = minDepth(root->left);
            int b = minDepth(root->right);
            if((a*b)==0) return (a^b)+1;
            else return 1+min(a,b);
        }
    }

    //question 112
    bool hasPathSum(TreeNode* root, int sum) {
        if(root==NULL) return false;
        if(!root->left&&!root->right&&sum==root->val) return true;
        if(root->left&&hasPathSum(root->left,sum-root->val))
            return true;
        if(root->right&&hasPathSum(root->right,sum-root->val))
            return true;
        return false;
        
    }

    //question 113
    vector<vector<int>> res;
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        if(root==NULL) return res;
        vector<int> tmp;
        dfs(root,tmp,sum);
        return res;
    }
    
    void dfs(TreeNode* root,vector<int> tmp,int sum){
            if(!root->left&&!root->right&&sum==root->val){
                tmp.push_back(root->val);
                res.push_back(tmp);
                return;
            }
            if(root->left){
                tmp.push_back(root->val);
                dfs(root->left,tmp,sum-root->val);
                tmp.pop_back();
            }
            if(root->right){
                tmp.push_back(root->val);
                dfs(root->right,tmp,sum-root->val);
                tmp.pop_back();
            }
        
    }

    //question 114
    void flatten(TreeNode* root) {
        
        root = dfs(root);
        
    }
    TreeNode* dfs(TreeNode* root){
        
        if(!root) return root;
        TreeNode* right = root->right;
        TreeNode* left = root->left;
        flatten(left);
        flatten(right);
        root->left = NULL;
        if(left){
            root->right = left;
            while(left->right!=NULL){
                left = left->right;
            }
            left->right = right;
        }
        else{
            root->right = right;
        }
        return root;
    }

    //question 115
    map<pair<string,string>,int> mp;
    int numDistinct(string s, string t) {
        /*
        if(t.empty()) return 1;
        if(s.empty()) return 0;
        pair<string,string> hehe(s,t);
        if(mp.find(hehe)!=mp.end())
            return mp[hehe];
        int count = 0;
        for(int i=0;i<s.size();i++){
            if(t[0]==s[i]){
                count+=numDistinct(s.substr(i+1,s.size()-i),t.substr(1,t.size()-1));
            }
        }
        
        mp[hehe] = count;
        return count;
        */
        int dp[s.size()+1][t.size()+1];
        memset(dp[0],0,sizeof(dp[0]));
        for(int i=0;i<=s.size();i++)
            dp[i][0] = 1;
        
        for(int i=1;i<=t.size();i++){
            for(int j=1;j<=s.size();j++){
                if(s[j-1]==t[i-1]){
                    
                    dp[j][i] = dp[j-1][i-1]+dp[j-1][i];
 
                }
                else{
                    dp[j][i] = dp[j-1][i];
                }
            }
        }
        return dp[s.size()][t.size()];
    }

   //question 116
    void connect(TreeLinkNode *root) {
        
        root = dfs(root);
    }
    
    TreeLinkNode* dfs(TreeLinkNode* root){
        if(!root) return root;
        root->next = NULL;
        if(root->left){
            root->left = dfs(root->left);
            root->right = dfs(root->right);
            TreeLinkNode* left = root->left;
            TreeLinkNode* right = root->right;
            while(left){
                left->next = right;
                left = left->right;
                right = right->left;
            }
            
        }
        return root;
    }

    //question 117
    void connect(TreeLinkNode *root) {
        if(root==NULL) return;
        queue<TreeLinkNode*> q;
        q.push(root);
        q.push(NULL);
        TreeLinkNode *pre = NULL;
        while(!q.empty()){
            TreeLinkNode *cur = q.front();
            if(cur==NULL){
                pre->next = NULL;
                pre = NULL;
                q.pop();
                if(q.empty()) return;
                q.push(NULL);
            }
            else{
                if(cur->left!=NULL) q.push(cur->left);
                if(cur->right!=NULL) q.push(cur->right);
                if(pre!=NULL)
                    pre->next = cur;
                pre = cur;
                q.pop();
                
            }
        }
    }

    //question 118
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        if(numRows==0) return res;
        vector<int> tmp;
        tmp.push_back(1);
        res.push_back(tmp);
        while(numRows-->1){
            vector<int> hehe = tmp;
            tmp.clear();
            tmp.push_back(hehe[0]);
            for(int i=1;i<hehe.size();i++){
                tmp.push_back(hehe[i-1]+hehe[i]);
            }
            tmp.push_back(hehe[hehe.size()-1]);
            res.push_back(tmp);
        }
        return res;
    }

    //question 119
    vector<int> getRow(int rowIndex) {
        vector<int> res;
        if(rowIndex==0){
            res.push_back(1);
            return res;
        }
        vector<int> hehe = getRow(rowIndex-1);
        res.push_back(hehe[0]);
        for(int i=1;i<hehe.size();i++)
            res.push_back(hehe[i-1]+hehe[i]);
        res.push_back(hehe[0]);
        return res;
    }

    //question 120
    int minimumTotal(vector<vector<int>>& triangle) {
        vector<vector<int>> path;
        for(int i =0;i<triangle.size();i++){
                vector<int> tmp;
            for(int j = 0;j<triangle[i].size();j++){
                if(i==0)
                    tmp.push_back(triangle[i][j]);
                else{
                    if(j==0)
                        tmp.push_back(triangle[i][j]+path[i-1][j]);
                    else if(j==triangle[i].size()-1)
                        tmp.push_back(triangle[i][j]+path[i-1][j-1]);
                    else
                        tmp.push_back(triangle[i][j]+min(path[i-1][j],path[i-1][j-1]));
                    
                }
                
            }
            path.push_back(tmp);
        }
        int min=10000000;
        for(auto p:path[path.size()-1]){
            if(p<min)
                min = p;
        }
        return min;
    }

};






