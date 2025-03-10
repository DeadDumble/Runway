#include "reserve.h"
#include <iostream>
using namespace std;

reservation::reservation(int t) {
    time = t;
    left = nullptr;
    right = nullptr; 
    subtreeSize = 1; // Initialize subtree size
}

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    clearTree(root);
}

void BST::clearTree(reservation* node)
{
    if (node == nullptr)
        return;

    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

// Reserve new landing time
bool BST::reserve(int time) 
{
    cout << "Checking for conflicts for time: " << time << endl;
    if (checkConflict(root, time)) {
        cout << "Conflict detected for " << time << endl;
        return false; // Conflict - reservation fails
    }
 
    insert(root, time); 
    cout << "Successfully reserved: " << time << endl;
    return true; // No conflict - reservation successful
}

// Improved checkConflict using in-order traversal
bool BST::checkConflict(reservation* node, int time) 
{
    if (node == nullptr)
        return false;
    
    reservation* pred = nullptr;
    reservation* succ = nullptr;
    reservation* curr = node;
    
    while (curr) {
        if (curr->time == time)
            return true;
        
        if (curr->time < time) {
            pred = curr;
            curr = curr->right;
        } else {
            succ = curr;
            curr = curr->left;
        }
    }
    
    if ((pred && abs(pred->time - time) < 3) || (succ && abs(succ->time - time) < 3))
        return true;
    
    return false;
}

// Insert new reservation and update subtree size correctly
void BST::insert(reservation*& node, int time) 
{
    if (node == nullptr) {
        node = new reservation(time);
        cout << "Inserted: " << time << endl;
        return;
    }
    
    if (time < node->time)
        insert(node->left, time);
    else if (time > node->time)
        insert(node->right, time);
    else
        return; // No duplicates allowed
    
    node->subtreeSize = 1 + (node->left ? node->left->subtreeSize : 0) + (node->right ? node->right->subtreeSize : 0);
    cout << "Updated subtree size for " << node->time << " to " << node->subtreeSize << endl;
}

// Fixed countPlanes function to prevent integer overflow
int BST::countPlanes(reservation* node, int t) 
{
    if (node == nullptr)
        return 0;
    
    int leftCount = node->left ? countPlanes(node->left, t) : 0;
    int rightCount = node->right ? countPlanes(node->right, t) : 0;
    
    if (node->time <= t) {
        int total = 1 + leftCount + rightCount;
        cout << "Counting planes at time " << node->time << ": " << total << endl;
        return total;
    }
    else {
        return leftCount;
    }
}

void BST::inorder(reservation* root)
{
    if (root == nullptr)
        return;
    
    inorder(root->left);
    cout << root->time << " ";
    inorder(root->right);
}
