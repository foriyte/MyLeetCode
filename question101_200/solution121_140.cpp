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
struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};


class Solution {
public:
    //question 121
    int maxProfit(vector<int>& prices) {
        int length = prices.size();
        if(length==0) return 0;
        int min = prices[0];
        int value=-9999;
        for(auto p:prices){
            if(p<min){
                min = p;
            }
            else
                value = max(value,p-min);
        }
        return value;
    }
    
    //question 122 
    int maxProfit(vector<int>& prices) {
        /*
        int length = prices.size();
        if(length==0) return 0;
        int value[length];
        value[0] = 0;
        for(int i=1;i<length;i++){
            if(prices[i]>prices[i-1]){
                value[i] = value[i-1]+prices[i]-prices[i-1];
            }
            else{
                value[i] = value[i-1];
            }
        }
        return value[length-1];
        */
        
        int minium = INT_MAX;
        int res = 0;
        for(auto p :prices){
            if(p>minium){
                res += p-minium;
                minium = p;
            }
            minium = p;
        }
        return res;
    }

    //question 123
    int maxProfit(vector<int>& prices) {
        int n = prices.size(), num = 2;
        if (n <= 1) return 0;
        vector<vector<int> > dp(num + 1, vector<int>(n, 0));
        for (int k = 1; k <= num; k++) {
            int temp = dp[k - 1][0] - prices[0];
            for (int i = 1; i < n; i++) {
                dp[k][i] = max(dp[k][i - 1], prices[i] + temp);
                temp = max(temp, dp[k - 1][i] - prices[i]);
            }
        }
        return dp[num][n - 1];
        
    }

    //question 124
    map<TreeNode*,int> mp;
    int maxPathSum(TreeNode* root) {
        if(!root) return 0;
        int leftlen = maxLen(root->left);
        int rightlen = maxLen(root->right);
        int len = max(leftlen+rightlen+root->val,max(leftlen+root->val,rightlen+root->val));
        len = max(len,root->val);
        if(root->left){
            int left = maxPathSum(root->left);
            len = max(len,left);
        }
        if(root->right){
            int right = maxPathSum(root->right);
            len = max(len,right);
        }
        
        return len;
    }
    int maxLen(TreeNode* root){
        if(!root) return 0;
        if(mp.find(root)!=mp.end()) return mp[root];
        int res = root->val+max(0,max(maxLen(root->left),maxLen(root->right)));
        mp[root] = res;
        return res;
    }

    //question 125
    bool isPalindrome(string s){
        string ss;
        //if(s.empty()) return true;
        for(auto p :s){
            if(p>='A'&&p<='Z'){
                p = p+32;
                ss +=p;
            }
            else if((p>='a'&&p<='z')||(p>='0'&&p<='9')){
                ss +=p;
            }
            
        }
        int len = ss.size();
        for(int i=0;i<len/2;i++){
            if(ss[i]!=ss[len-1-i])
                return false;
        }
        return true;
    }

    //question 126
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> final;
        set<string> words;
        set<string> left,right,*cur,*other;
        for(auto p:wordList)
            words.insert(p);
        left.insert(beginWord);
        right.insert(endWord);
        auto tt = words.find(endWord);
        if(tt==words.end()) return final;
        words.erase(tt);
        tt = words.find(beginWord);
        if(tt!=words.end())
            words.erase(tt);
        map<string,set<string>> pre;
        
        while(!left.empty()&&!right.empty()){
            if(left.size()<=right.size()){
                cur = &left;
                other = &right;
            }
            else{
                cur = &right;
                other = &left;
            }
            
            set<string> temp;
            bool flag = false;
            for(auto it = cur->begin();it!=cur->end();it++){
                string curstr = *it;
                string dupstr = curstr;
                for(int i = 0;i<curstr.size();i++){
                    
                    for(char j = 'a';j<='z';j++){
                        curstr[i] = j;
                        auto res = other->find(curstr);
                        if(res!=other->end()){
                            flag = true;
                            vector<vector<string> > res1;
                            vector<vector<string> > res2;
                            vector<string> o;
                            dfs(pre,res1,o,curstr);
                            dfs(pre,res2,o,dupstr);
                            if(res2[0][res2[0].size()-1] == beginWord)
                                swap(res1,res2);
                            for(auto i:res1){
                                vector<string> tt;
                                for(int j= i.size()-1;j>=0;j--){
                                    tt.push_back(i[j]);
                                }
                                for(auto ii:res2){
                                    vector<string> tmptt = tt;
                                    for(int jj=0;jj<ii.size();jj++)
                                        tt.push_back(ii[jj]);
                                    final.push_back(tt);
                                    tt = tmptt;
                                }
                                
                            }
                            
                        }
                            
                        auto ress = words.find(curstr);
                        if(ress!=words.end()){
                            //words.erase(ress);
                            temp.insert(curstr);
                            if(pre.find(curstr)!=pre.end()){
                                pre[curstr].insert(dupstr);
                            }
                            else{
                                set<string> pretemp;
                                pretemp.insert(dupstr);
                                pre[curstr] = pretemp;
                            }
                        }
                    }
                    curstr = dupstr;
                }
                
            }
            if(flag) break;
            for(auto p:temp){
                auto pp = words.find(p);
                if(pp!=words.end())
                    words.erase(pp);
            }
            swap(*cur,temp);
        }
        return final;
        
    }
    
    void dfs(map<string,set<string>> &pre,vector<vector<string>> &res,vector<string> &tmp,string start){
        auto it = pre.find(start);
        tmp.push_back(start);
        if(it==pre.end()) {
            res.push_back(tmp);
            tmp.pop_back();
            return;
        }
        else{
            set<string> parents = pre[start];
            for(auto p:parents){
                dfs(pre,res,tmp,p);               
            }
            tmp.pop_back();
        }
    }

    //question 127
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        //vector speed of find is so slow thus using set
        if(find(wordList.begin(),wordList.end(),endWord)==wordList.end()) return 0;
        unordered_set<string> left;
        unordered_set<string> right;
        unordered_set<string> words;
        for(auto p:wordList)
            words.insert(p);
        left.insert(beginWord);
        right.insert(endWord);
        unordered_set<string> *cur,*other;
        int res = 1;
        while(!left.empty()&&!right.empty()){
            if(left.size()<=right.size()){
                cur = &left;
                other = &right;
            }
            else{
                cur = &right;
                other = &left;
            }
            res++;
            unordered_set<string> temp;
            
            for(auto it = cur->begin();it!=cur->end();++it){
                string start = *it;
                for(int i=0;i<start.size();i++){
                    char tmp = start[i];
                    for(char j = 'a';j<='z';j++){
                        start[i] = j;
                        auto hehe = other->find(start);
                        if(hehe!=other->end()){
                           return res;
                        }
                        auto he = words.find(start);
                        if(he!=words.end()){
                            temp.insert(start);
                            words.erase(he);
                        }
                    }
                    start[i] = tmp;
                }
            }
            swap(*cur,temp);
        }
        return 0;
    }

    //question 128
    int longestConsecutive(vector<int>& nums) {
        map<int,int> tree;
        map<int,int> sum;
        for(auto p:nums){
            tree[p] = INT_MIN;
            sum[p] = 1;
        }
        for(auto p:nums){
            if(tree[p]==p-1) continue;
            int c=0;
            if(tree.find(p-1)!=tree.end()){
                tree[p] = p-1;
                int h = p-1;
                while(tree[h]!=INT_MIN)
                    h = tree[h];
                sum[h] += sum[p];
            }
        }
        int res = 0;
        for(auto p:tree){
            if(p.second = INT_MIN){
                res = max(res,sum[p.first]);
            }
        }
        return res;
        
    }

    //question 129
    int sumNumbers(TreeNode* root) {
        int sum=0;
        if(root==NULL) return 0;
        preorder(root,sum,0);
        return sum;
    }
    void preorder(TreeNode *root,int& sum,int last){
        int tmp = last*10+root->val;
        if(root->left==NULL&&root->right==NULL){
            sum += tmp;
        }
        if(root->left!=NULL)
            preorder(root->left,sum,tmp);
        if(root->right!=NULL)
            preorder(root->right,sum,tmp);
    }

     //question 130
    void solve(vector<vector<char>>& board) {
        if(board.empty()) return;
        /*
        for(int i=0;i<board.size();i++){
            dfs(board,i,0);
            dfs(board,i,board[0].size()-1);
        }
        for(int j=1;j<board[0].size()-1;j++){
            dfs(board,0,j);
            dfs(board,board.size()-1,j);
        }
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[i].size();j++){
                if(board[i][j]=='A')
                    board[i][j] = 'O';
                else if(board[i][j]=='O')
                    board[i][j] = 'X';
            }
        }
        */
        
        int row = board.size(),col = board[0].size();
        
        
    }
    
    void dfs(vector<vector<char>>& board,int i,int j){
        
        if(board[i][j]=='O'){
            board[i][j] = 'A';
            if(i>1) dfs(board,i-1,j);
            if(i<(int)(board.size()-2)) dfs(board,i+1,j);
            if(j>1) dfs(board,i,j-1);
            if(j<(int)(board[0].size()-2)) dfs(board,i,j+1);
        }
       
    }

    //question 131
    vector<vector<string>> partition(string s) {
        vector<vector<string> > res;
        vector<string> tmp;
        dfs(res,tmp,s);
        return res;
    }
    
    void dfs(vector<vector<string>>& res,vector<string> &tmp,string s){
        if(s==""){
            res.push_back(tmp);
        }
        else{
            for(int i=1;i<=s.size();i++){
                string temp = s.substr(0,i);
                if(judge(temp)){
                    tmp.push_back(temp);
                    dfs(res,tmp,s.substr(i,s.size()-i));
                    tmp.pop_back();
                }
            }
        }
    }
    
    bool judge(string s){
        for(int i=0;i<(int)s.size()/2;i++){
            if(s[i]!=s[s.size()-i-1])
                return false;
        }
        return true;
    }

    //question 132
    int minCut(string s) {
        if(s=="") return 0;
        int len = s.size();
        bool dp[len][len];
        dp[0][0] = 1;
        for(int i=1;i<len;i++){
            for(int j=0;j<=i;j++){
                dp[j][i] = (s[i]==s[j]&&((i-j<2)||dp[j+1][i-1]));
            }
        }
        int cut[len];
        cut[0] = 0;
        for(int i=1;i<len;i++){
            cut[i] = INT_MAX;
            if(dp[0][i]) cut[i] = 0;
            else{
                for(int j =1;j<=i;j++){
                    if(dp[j][i]){
                        if((cut[j-1]+1)<cut[i])
                            cut[i] = cut[j-1]+1;
                    }
                }
            }
        }
        return cut[len-1];
    }

    //question 133
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(node==NULL) return NULL;
        queue<UndirectedGraphNode*> parent;
        queue<UndirectedGraphNode*> q;
        map<UndirectedGraphNode*,UndirectedGraphNode*> mp;
        q.push(node);
        q.push(NULL);
        UndirectedGraphNode *pre = NULL;
        UndirectedGraphNode *res = NULL;
        while(!q.empty()){
            UndirectedGraphNode *cur = q.front();
            q.pop();
            if(cur==NULL){
                if(parent.empty()) return res;
                else{
                    pre = parent.front();
                    parent.pop();
                }
            }else{
                auto it = mp.find(cur);
                UndirectedGraphNode *tmp = NULL;
                if(it==mp.end()){
                    tmp = new UndirectedGraphNode(cur->label);
                    mp[cur] = tmp;
                    parent.push(tmp);
                    for(auto p:cur->neighbors)
                        q.push(p);
                    q.push(NULL);
                }
                else
                    tmp = mp[cur];
                if(cur==node) res = tmp;
                if(pre!=NULL)
                    pre->neighbors.push_back(tmp);
            }
        }
        return res;
    }

    //question 134
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int len = gas.size();
        
        for(int i=0;i<len;i++){
            bool flag = true;
            int temp = 0;
            int pre = 0 ;
            for(int j=i;j<len;j++){
                temp = pre+gas[j]-cost[j];
                pre = temp;
                if(temp<0){
                    flag = false;
                    break;
                }
            }
            if(!flag) continue;   kkk
            for(int j=0;j<i;j++){
                temp = pre+gas[j]-cost[j];
                pre = temp;
                if(temp<0){
                    flag = false;
                    break;
                }
            }
            if(!flag) continue;
            return i;
            
        }
        return -1;
    }

    //question 135
    int candy(vector<int>& ratings) {
        int len = ratings.size();
        int preindex = 0;
        int pre = 1;
        int premax = 1;
        int res = 1;
        for(int i=1;i<len;i++){
            if(ratings[i]>ratings[i-1]){
                pre++;
                res += pre;
                preindex = i;
                premax = pre;
            }
            else if(ratings[i]<ratings[i-1]){
                if(pre>1){
                    pre = 1;
                    res += pre;
                }
                else{
                    res += (i-preindex);
                    if((i-preindex)==premax){
                        premax++;
                        res++;
                    }
                }
            }
            else{
                res++;
                premax = 1;
                preindex = i;
                pre = 1;
            }
        }
        return res;
    }

    //question 136
    int singleNumber(vector<int>& nums) {
       
        int res=0;
        vector<int>::iterator it;
        for(it=nums.begin();it!=nums.end();++it){
            
            res^=*it;
        }

        return res;
        
    }

    //question 137
    int singleNumber(vector<int>& nums) {
        int jilu[32];
        for(int i=0;i<32;i++)
            jilu[i] = 0;
        for(auto n:nums){
            for(int i=0;i<32;i++){
                jilu[i] += (n>>(31-i))&0x00000001;
                if(jilu[i]==3) jilu[i] = 0;
            }
        }
        int res = 0;
        for(int i=0;i<32;i++){
            res += jilu[i]<<(31-i);
        }
        return res;
    }

    //question 138
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(head==NULL) return NULL;
        RandomListNode *cur = head;
        while(cur!=NULL){
            RandomListNode *dup = new RandomListNode(cur->label);
            RandomListNode *tmp = cur->next;
            cur->next = dup;
            dup->next = tmp;
            cur = tmp;
        }
        cur = head;
        RandomListNode *res = cur->next;
        while(cur!=NULL){
            RandomListNode *tmp = cur->next;
            //RandomListNode *temp = tmp->next;
            if(cur->random!=NULL)
                tmp->random = cur->random->next;
            else
                tmp->random = NULL;
            cur = tmp->next;
        }
        cur = head;
        while(cur!=NULL){
            RandomListNode *tmp = cur->next;
            RandomListNode *temp = tmp->next;
            cur->next = temp;
            if(temp){
                tmp->next = temp->next;
            }
            else
                tmp->next = NULL;
            cur = temp;
        }
        return res;
    }

    //question 139
    bool wordBreak(string s, vector<string>& wordDict) {
        
        int dp[s.size()];
        //if(find(wordDict.begin(),wordDict.end(),s.substr(0,1))!=wordDict.end()) dp[0] = 1;
        //else dp[0] = 0;
        for(int i=0;i<s.size();i++){
            if(find(wordDict.begin(),wordDict.end(),s.substr(0,i+1))!=wordDict.end()){
                dp[i] = 1;
                continue;
            }
            dp[i] = 0;
            for(int j = i-1;j>=0;j--){
                if(dp[j]){
                    if(find(wordDict.begin(),wordDict.end(),s.substr(j+1,i-j))!=wordDict.end()){
                        dp[i] = 1;
                        break;
                    }
                }
            }
        }
        return dp[s.size()-1];
        
    }

    //question 140
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        
        vector<string> res;
        int dp[s.size()];
        for(int i=0;i<s.size();i++){
            if(find(wordDict.begin(),wordDict.end(),s.substr(0,i+1))!=wordDict.end()){
                dp[i] = 1;
                continue;
            }
            dp[i] = 0;
            for(int j = i-1;j>=0;j--){
                if(dp[j]){
                    if(find(wordDict.begin(),wordDict.end(),s.substr(j+1,i-j))!=wordDict.end()){
                        dp[i] = 1;
                        break;
                    }
                }
            }
        }
        if(!dp[s.size()-1]) return res;
        string tmp = "";
        dfs(res,tmp,s,wordDict);
        return res;
    }
    
    void dfs(vector<string>& res,string tmp,string s,vector<string>& wordDict){
        for(int i=1;i<=s.size();i++){
            string temp = s.substr(0,i);
            if(find(wordDict.begin(),wordDict.end(),temp)!=wordDict.end()){
                if(i==s.size()){
                    tmp += s;
                    res.push_back(tmp);
                    return;
                }
                else{
                    dfs(res,tmp+temp+" ",s.substr(i,s.size()-i),wordDict);
                }
            }
        }
    }



};





