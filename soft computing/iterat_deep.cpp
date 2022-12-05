/* Implementation of Binary Trees... A Binary Tree Node can have maximum Two Child Nodes...
The Maximum Nodes with level x is 2^x... The Maximum Nodes in Tree of Height h is 2^h - 1... For x
Nodes the minimum possible level is log(x + 1)... A Binary tree with n leaves has atleast 
log(n + 1) + 1 number of levels */
#include <iostream>
#include <queue>
using namespace std;
class Node                    // Node class created for each Tree Node creation
{
    public:
    int data;         // Data member
    Node* left;      // Left Node pointer
    Node* right;     // Right Node pointer
    Node* root;      // Root Node pointer
    public:
    Node (int val)    // Parametrized Constructor
    {
        data = val;
        left = NULL;
        right = NULL;
        root = NULL;
    }
};
class BinaryTree     //  Class created for Binary Tree Implementation ( Non-Linear Data Structure )
{
    public:
    Node* InsertNodeInTree(Node* root, int val)   // Inserting Node recursively.. O(log n) time
    {
        if(root == NULL)               // If No root node is there, create one
            return new Node(val);
        if(val <= root -> data)   // If data is lesser than or equal to parent store in left subtree
            root -> left = InsertNodeInTree(root -> left, val);
        else         // If data is greater than the parent stor it in right subtree
            root -> right = InsertNodeInTree(root -> right, val);
        return root;
    }
    void ShowTree(Node* root)   // Displaying tree with Node.. O(log n) time
    {
        Node* temp = root;
        if(temp == NULL)    // If Tree is empty nothing to show
            return;                            // Control moves out of the function
        ShowTree(temp -> left);     // Recursive Call
        cout << "Node: " << endl;
        if(temp -> left != NULL)    // If left subtree is not empty
            cout << "\t" << temp -> data << " ---> " << temp -> left -> data << "\t Left ( Occupied )" << endl;
        else      // If left subtree is empty
            cout << "\t" << temp -> data << "\t\t Left ( Empty )" << endl;
        if(temp -> right != NULL)   // If right subtree is not empty
            cout << "\t" << temp -> data << " ---> " << temp -> right -> data << "\t Right ( Occupied ) " << endl;
        else     // If right subtree is empty
            cout << "\t" << temp -> data << "\t\t Right ( Empty )" << endl;
        ShowTree(temp -> right);     // Recursive Call
    }
    void LevelOrderTraversal(Node* root)  // Level Order Traversal using Queues
    {
        if(root == NULL)      // If root is empty
            return;
        queue<Node*> Queue;          // Creating Queue of Node pointer
        Queue.push(root);       // Adding root Node
        Queue.push(NULL);       // Adding NULL value
        while(!Queue.empty())         // Checking if Queue is not Empty
        {
            Node* node = Queue.front();    // Getting the front pointer reference
            if(node != NULL)
            {
                cout << node -> data << ", ";    // Displaying Node data
                if(node -> left)
                    Queue.push(node -> left);    // Pushing Left data if present
                if(node -> right)
                    Queue.push(node -> right);   // Pushing Right data if present
            }
            Queue.pop();                 // Removing the element
            if(!Queue.empty())   // If Queue is not Empty
                Queue.push(NULL);
        }
    }
};
int main()
{
    Node* root = NULL;      // Root node initialization
    BinaryTree binarytree;      // Object creation of Binary Tree
    int s, x;
    cout << "Enter root Node value : ";
    cin >> x;
    root = binarytree.InsertNodeInTree(root, x);    // Root Node created
    cout << "Enter the number of Nodes to Insert in the Binary Search Tree : ";
    cin >> s;
    for(int i = 1; i <= s; i++)   // Loop begins
    {
        cout << "Enter the New Node value : ";
        cin >> x;
        binarytree.InsertNodeInTree(root, x);   // Calling Insert Tree function
    }
    binarytree.ShowTree(root);    // Displaying binary tree with Nodes
    cout << "The Level Order Traversal or Iterative Deepening Search is : " << endl;
    binarytree.LevelOrderTraversal(root);
    return 0;          // End of Program
}
