#include <iostream>
#include <queue>
#include <vector>

struct Node {
  int val;
  Node* left;
  Node* right;
  Node() : val(0), left(nullptr), right(nullptr) {}
  Node(int x) : val(x), left(nullptr), right(nullptr) {}
  Node(int x, Node* left, Node* right) : val(x), left(left), right(right) {}

  // ~Node() {
  //   delete left;
  //   delete right;
  // }
 };

/**
 * ------------------------------------------------------------------
  7 - {3,8}
  0 => i
  l = 0 + 1 => i + j
  r = 0 + 2 => i + j+1

  3 - {9,10}
  1 => i
  l = 1 + 2 => i + j
  r = 1 + 3 => i + j+1

  2 => i
  l = 2 + 3 => i + j
  r = 2 + 4 => i + j+1

  3 => i
  l = 3 + 4 => i + j
  r = 3 + 5 => i + j+1

  Trend does not hold once a node fails to have children but other nodes continue to have children and grow longer
 * ------------------------------------------------------------------

 * ------------------------------------------------------------------
  If the tree was uniform/complete and all positions were encoded even if those positions were empty/null
  ie. if a parent was not going to have any more children (like 8) but another part of the tree continued to grow (like LHS of tree)
  and even then all non-existent nodes on rhs were represented with NULL, then a standard formula could be used:

  Parent = i
  Child Left = 2*i + 1
  Child Right = 2*i + 2

  But, since this is not done in level order traversal array, the general trend/equations will not always hold.
 * ------------------------------------------------------------------

 * ------------------------------------------------------------------
  1. Pre-create pointers to all the nodes of the tree based on the level order traversal array
  2. Load those pointers into a duplicate list/queue to use as children
  3. Attach the pointers to each other as required
    a. Traverse the main array one element at a time, taking the selected element as the parent node
    b. Traverse and pop elements from the queue one at a time (starting AFTER the root) and attach them as children
 * ------------------------------------------------------------------
*/
Node* createTree(std::vector<int> tree_array) {

  std::cout << "===" << std::endl;

  // Pre-create all the pointers to the nodes of the tree. NOT create them on the fly in the loop.
  std::vector<Node*> tree_array_ndptr;
  for(int elem : tree_array) tree_array_ndptr.push_back(new Node(elem));

  // Load these pre-created pointers 
  std::queue<Node*> children_ndptr;
  for(Node* elem : tree_array_ndptr) children_ndptr.push(elem);
  

  Node* root;

  for(int i=0; i<tree_array_ndptr.size(); ++i) {

    if(children_ndptr.empty()) break; // No more children to attach to parents

    Node* nd = tree_array_ndptr[i];
    std::cout << "Parent: " << nd->val << std::endl;
    
    if(nd->val != -1) { // If it is a valid node, create that node and add children to it

      if(i == 0) { // Special operations for root node - Save it separetely and pop it off of children 
        root = nd;
        children_ndptr.pop(); // Pop off root node from children list
      }

      if(children_ndptr.empty()) break; // No more children to attach to parents
      Node* child = children_ndptr.front();
      if(child->val != -1) { // Valid child node
        std::cout << "Child left: " << child->val << std::endl;
        nd->left = child;
      }
      children_ndptr.pop(); // Pop child element even if not attached, since null children need to be removed

      if(children_ndptr.empty()) break; // No more children to attach to parents
      child = children_ndptr.front();
      if(child->val != -1) { // Valid child node
        std::cout << "Child right: " << child->val << std::endl;
        nd->right = child;
      }
      children_ndptr.pop(); // Pop child element even if not attached, since null children need to be removed

    }
  }

  std::cout << "===" << std::endl;

  return root;
}

/**
 * Involves two que.empty() checks. 
 * One to buffer each layer of nodes. 
 * Another for the overall loop to run the while loop and go through all the layers of the tree
*/
std::vector<std::vector<Node*>> levelOrderTraversal(Node* nd) {

  std::vector<std::vector<Node*>> ret_vec;
  std::vector<Node*> vec;

  std::queue<Node*> qu;
  qu.push(nd);

  while(!qu.empty()) { // QUE_CHECK_1: Till qu is completely empty after an iteration

    Node* nd = qu.front();
    vec.push_back(nd);
    qu.pop();

    if(qu.empty()) { // QUE_CHECK_2: If qu for a given level is empty, populate it with the next level
      
      for(Node* elem : vec) {
        if(elem->left != nullptr) qu.push(elem->left);
        if(elem->right != nullptr) qu.push(elem->right);
      }

      ret_vec.push_back(vec);
      vec.clear();
    }
  }

  for(std::vector<Node*> vec : ret_vec) {
    for (Node* nd : vec) {
      std::cout << nd->val << ", ";
    }
    std::cout << std::endl;
  }

  return ret_vec;
}

int main() {

  /*
              7
            /  \
          3     8
        / \
        9  10
    11 12  13 14

  */
  // std::vector<int> tree = {7, 3, 8, 9, 10, nullptr, nullptr};
  std::vector<int> tree_array = {7, 3, 8, 9, 10, -1, -1, 11, 12, 13, 14};
  // std::vector<int> tree_array = {2,1,3,0,7,9,1,2,-1,1,0,-1,-1,8,8,-1,-1,-1,-1,7};


  Node* root = createTree(tree_array);
  

  // std::vector<std::vector<Node*>> level_order_traversal_array = levelOrderTraversal(root);
  levelOrderTraversal(root);


  return 0;
}
