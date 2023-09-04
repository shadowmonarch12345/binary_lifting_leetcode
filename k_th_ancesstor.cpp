class TreeAncestor {
public:
    // Binary Lifting
    // Preprocess time of NlogN and can answer each query in logN
    // Build a lifing structure which can jump powers of two
    
    vector<int> g[50005];
    int depth[50005];
    int par[50005][20];
    
    void dfs(int node,int prev,int dep){
        depth[node] = dep;
        par[node][0] = prev;
        for(int i=1;i<20;i++){
            par[node][i] = par[par[node][i-1]][i-1];
        }
        for(int child:g[node]){
            if(child == prev) continue;
            dfs(child,node,dep+1);
        }
    }
    
    TreeAncestor(int n, vector<int>& parent) {
        for(int i=1;i<n;i++){
            // building adj list
            // making it into 1 based indexing
            g[i+1].push_back(parent[i]+1);
            g[parent[i]+1].push_back(i+1);
        } 
        dfs(1,0,0);
    }
    
    int getKthAncestor(int node, int k) {
        int cur = node+1;
        for(int i=0;i<20;i++){
            if((k&(1<<i))) cur = par[cur][i];
           
        }
        return cur-1;
    }
};


 /* if parent array given we can directly compute like this*/
 
  vector<vector<int>> dp;
    int height;
	
    TreeAncestor(int n, vector<int>& parent) {

        height = (int)ceil(log2(n)); 

        dp = vector<vector<int>>(n, vector<int>(height, -1));
 
        for(int i = 0; i < n; i++)
            dp[i][0] = parent[i];

        for(int h = 1; h < height; h++)
            for(int i = 0; i < n; i++)
                if( dp[i][h-1] != -1)
                    dp[i][h] = dp[dp[i][h-1]][h-1];
    }
	
	// O(h) - h = height of tree
    int getKthAncestor(int node, int k) {
        for (int i = 0; i <= height; i++) 
        { 
            if (k & (1 << i)) 
            { 
                node = dp[node][i]; 
                if (node == -1) 
                    break; 
            } 
        }
        return node;
    }