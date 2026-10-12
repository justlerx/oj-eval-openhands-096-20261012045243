#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct NodeInfo {
    int depth;
    int parent;
    NodeInfo(int d, int p) : depth(d), parent(p) {}
};

class Solution {
private:
    unordered_map<int, NodeInfo*> nodeMap;
    vector<TreeNode*> allNodes;
    int index;
    
    TreeNode* buildTree(const vector<int>& preorder, int depth, int parent) {
        if (index >= preorder.size()) {
            return nullptr;
        }
        
        int val = preorder[index++];
        if (val == -1) {
            return nullptr;
        }
        
        TreeNode* node = new TreeNode(val);
        allNodes.push_back(node);
        nodeMap[val] = new NodeInfo(depth, parent);
        
        node->left = buildTree(preorder, depth + 1, val);
        node->right = buildTree(preorder, depth + 1, val);
        
        return node;
    }
    
public:
    Solution() : index(0) {}
    
    void buildTreeFromPreorder(const vector<int>& preorder) {
        index = 0;
        nodeMap.clear();
        // Clear previous tree nodes
        for (TreeNode* node : allNodes) {
            delete node;
        }
        allNodes.clear();
        buildTree(preorder, 0, -1); // root has depth 0 and parent -1
    }
    
    bool areCousins(int x, int y) {
        if (nodeMap.find(x) == nodeMap.end() || nodeMap.find(y) == nodeMap.end()) {
            return false;
        }
        
        NodeInfo* infoX = nodeMap[x];
        NodeInfo* infoY = nodeMap[y];
        
        return (infoX->depth == infoY->depth) && (infoX->parent != infoY->parent);
    }
    
    ~Solution() {
        for (auto& pair : nodeMap) {
            delete pair.second;
        }
        for (TreeNode* node : allNodes) {
            delete node;
        }
    }
};

vector<int> parseLineToIntegers(const string& line) {
    vector<int> result;
    istringstream iss(line);
    int num;
    while (iss >> num) {
        result.push_back(num);
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    
    // Read number of queries
    getline(cin, line);
    int q = stoi(line);
    
    // Read queries
    vector<pair<int, int>> queries;
    for (int i = 0; i < q; i++) {
        getline(cin, line);
        vector<int> nums = parseLineToIntegers(line);
        if (nums.size() >= 2) {
            queries.emplace_back(nums[0], nums[1]);
        }
    }
    
    // Read preorder traversal
    getline(cin, line);
    vector<int> preorder = parseLineToIntegers(line);
    
    // Build tree and answer queries
    Solution sol;
    sol.buildTreeFromPreorder(preorder);
    
    for (const auto& query : queries) {
        cout << (sol.areCousins(query.first, query.second) ? 1 : 0) << '\n';
    }
    
    return 0;
}