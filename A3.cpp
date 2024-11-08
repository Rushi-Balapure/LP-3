#include<bits/stdc++.h>
using namespace std;

struct Item {
    int weight;
    int value;
    int idx;
    double ratio;  // value per unit weight
    
    Item(int w, int v, int i) : weight(w), value(v), idx(i) {
        ratio = static_cast<double>(v) / w;
    }
};

// Structure for nodes in Branch and Bound tree
struct Node {
    int level;          // Level of node in decision tree
    int value;          // curr value of knapsack
    int weight;         // curr weight of knapsack
    double bound;       // Upper bound of maximum possible value
    vector<int> items;  // Items included in curr node(indices)
    
    Node(int l, int v, int w) : level(l), value(v), weight(w), bound(0.0) {}
};

class KnapSack {
    int solve(int i, int capacity, vector<int> &weights, vector<int> &values, vector<vector<int>> &dp) {
        if(i == 0) {
            if(weights[0] <= capacity) return values[0];
            return 0;
        }
        if(dp[i][capacity] != -1) return dp[i][capacity];

        int notTaken = solve(i-1, capacity, weights, values, dp);
        int taken = INT_MIN;
        if(weights[i] <= capacity) taken = values[i] + solve(i-1, capacity - weights[i], weights, values, dp);

        return dp[i][capacity] = max(taken, notTaken);
    }

    double calculateBound(Node *node, int capacity, vector<Item> &items) {
        // If we've exceeded the capacity, this node is not valid
        if (node -> weight >= capacity) return 0;

        // Initialize bound with curr value
        double valueBound = node -> value;
        int currWeight = node -> weight;
        int j = node -> level + 1;

        // Add items until we exceed capacity
        while (j < items.size() && currWeight + items[j].weight <= capacity) {
            currWeight += items[j].weight;
            valueBound += items[j].value;
            j++;
        }

        // Add the fraction of the next item if possible
        if (j < items.size()) {
            valueBound += (capacity - currWeight) * items[j].ratio;
        }

        return valueBound;
    }

public:
    void memoization(int maxCapacity, vector<int> &weights, vector<int> &values) {
        int n = weights.size();
        vector<vector<int>> dp(n, vector<int> (maxCapacity + 1, -1));
        int maxProfit = solve(n-1, maxCapacity, weights, values, dp);

        cout<<"The max profit by recursion-memoization is "<<maxProfit<<endl;  
    }

    void tabulation(int maxCapacity, vector<int> &weights, vector<int> &values) {
        int n = weights.size();
        vector<vector<int>> dp(n, vector<int> (maxCapacity + 1, 0));
        for(int w=weights[0];w<=maxCapacity;w++) {
            dp[0][w] = values[0];
        }

        for(int i=1;i<n;i++) {
            for(int w=0;w<=maxCapacity;w++) {
                int notTaken = dp[i-1][w];
                int taken = INT_MIN;
                if(weights[i] <= w) taken = values[i] + dp[i-1][w - weights[i]];
                dp[i][w] = max(taken, notTaken); 
            }
        }

        cout<<"The max profit by tabulation is "<<dp[n-1][maxCapacity]<<endl;
    }

    void spaceOptimized(int maxCapacity, vector<int> &weights, vector<int> &values) {
        int n = weights.size();
        vector<int> prev(maxCapacity + 1, 0);
        for(int w=weights[0];w<=maxCapacity;w++) {
            prev[w] = values[0];
        }

        for(int i=1;i<n;i++) {
            vector<int> curr(maxCapacity + 1, 0);
            for(int w=0;w<=maxCapacity;w++) {
                int notTaken = prev[w];
                int taken = INT_MIN;
                if(weights[i] <= w) taken = values[i] + prev[w - weights[i]];
                curr[w] = max(taken, notTaken); 
            }
            prev = curr;
        }

        cout<<"The max profit by space optimization is "<<prev[maxCapacity]<<endl;
    }

    void branchAndBound(int maxCapacity, vector<int> &weights, vector<int> &values) {
        int n = weights.size();    
        // Create and sort items by value/weight ratio
        vector<Item> items;
        for (int i = 0; i < n; i++) {
            items.push_back(Item(weights[i], values[i], i));
        }
        sort(items.begin(), items.end(), [](const Item &a, const Item &b) { return a.ratio > b.ratio; });

        // Create a priority queue that will sort nodes by their bounds
        auto compare = [](Node *a, Node *b) { return a -> bound < b -> bound; };
        priority_queue<Node *, vector<Node *>, decltype(compare)> pq(compare);

        // Create root node
        Node *root = new Node(-1, 0, 0);
        root -> bound = calculateBound(root, maxCapacity, items);
        pq.push(root);

        // Initialize best solution
        int maxValue = 0;
        vector<int> bestItems;
        int nodesCount = 0;

        // Branch and Bound
        while(!pq.empty()) {
            // Get node with highest bound
            Node *curr = pq.top();
            pq.pop();
            nodesCount++;

            // Skip if bound is less than curr best solution
            if (curr -> bound <= maxValue) {
                delete curr;
                continue;
            }

            // Get next level
            int level = curr -> level + 1;

            // If we've processed all items
            if (level >= n) {
                delete curr;
                continue;
            }

            // Try including curr item
            int newWeight = curr -> weight + items[level].weight;
            if (newWeight <= maxCapacity) {
                Node *includeNode = new Node(level, 
                                            curr -> value + items[level].value,
                                            newWeight);
                includeNode -> items = curr->items;
                includeNode -> items.push_back(items[level].idx);
                includeNode -> bound = calculateBound(includeNode, maxCapacity, items);

                // Update best solution if needed
                if (includeNode -> value > maxValue) {
                    maxValue = includeNode -> value;
                    bestItems = includeNode -> items;
                }

                if (includeNode -> bound > maxValue) {
                    pq.push(includeNode);
                } else {
                    delete includeNode;
                }
            }

            // Try excluding curr item
            Node *excludeNode = new Node(level, curr -> value, curr -> weight);
            excludeNode -> items = curr -> items;
            excludeNode -> bound = calculateBound(excludeNode, maxCapacity, items);

            if (excludeNode -> bound > maxValue) {
                pq.push(excludeNode);
            } else {
                delete excludeNode;
            }

            delete curr;
        }

        // Sort the items before returning
        sort(bestItems.begin(), bestItems.end());
        cout<<"The max profit by branch and bound is "<<maxValue<<endl;
        cout<<"The items selected are: ";
        for(int i : bestItems) cout<<i<<" ";
        cout<<endl;
    }
};

int main() {
    vector<int> weights = {95, 4, 60, 32, 23, 72, 80, 62, 65, 46};
    vector<int> values = {55, 10, 47, 5, 4, 50, 8, 61, 85, 87};
    int capacity = 269;

    KnapSack k;
    k.memoization(capacity, weights, values);
    k.tabulation(capacity, weights, values);
    k.spaceOptimized(capacity, weights, values);
    k.branchAndBound(capacity, weights, values);

    return 0;
}