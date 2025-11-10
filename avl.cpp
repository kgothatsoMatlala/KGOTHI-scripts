#include <iostream>
#include "avl.h"

using namespace std;


///////////////////////////////////////////////////////////////////////////////////////
///										   ///	
///     		Implement the functions below			          ///
///									         ///
////////////////////////////////////////////////////////////////////////////////////


int BST::height(TreeNode* subtree){

    //TODO: Implement this function
    if(subtree == nullptr){
        return -1;
    }

    int lefth = height(subtree->left);
    int righth = height(subtree->right);

    return 1 + std::max(lefth,righth);
}


bool BST::isAVL(TreeNode* subtree){
    
   //TODO: Implement this function
    if(subtree == nullptr){
       return true;
   }
    if(abs(height(subtree->left) - height(subtree->right)) > 1 || abs(height(subtree->right) - height(subtree->left)) >1){
       return false;
   }

    return isAVL(subtree->right) && isAVL(subtree->left);
}

void BST::left_rotate(TreeNode*& subtree){
  
   // TODO: Implement this function
    if(subtree == nullptr){
       return;
   }
    TreeNode* new_p = subtree-> right;
    TreeNode* p2 = new_p->left;

    new_p->left = subtree;
    subtree->right = p2;
    subtree = new_p;
}

void BST::right_rotate(TreeNode*& subtree){

   // TODO: Implement this function
    if(subtree == nullptr){
       return;
   }

    TreeNode* new_p = subtree->left;
    TreeNode* p2 = new_p->right;

    new_p->right = subtree;
    subtree->left = p2;
    subtree = new_p;
}


///////////////////////////////////////////////////////////////////////////////////////
///										   ///	
///     All functions below have been implemented correctly, DO NOT MODIFY        ///
///									         ///
////////////////////////////////////////////////////////////////////////////////////

// These functions just call the recursive implementions

// Regular BST insert
void BST::insert(int value){
    insert(root, value);
}

int BST::height(){
    return height(root);
}

bool BST::isAVL(){
    return isAVL(root);
}

// BST Insert wih AVL Balancing (assumes tree is already AVL before insert)
void BST::insertAVL(int value){
    insertAVL(root, value);
}


void BST::insert(TreeNode*& subtree, int value){
    if (subtree == nullptr){
        subtree = new TreeNode(value);
    } else if (value < subtree->value){
        insert(subtree->left, value);
    } else {
        insert(subtree->right, value);
    }
}

// Checks if tree has more weight on left hand side (helper for checking which rotation)
bool BST::left_heavy(TreeNode* subtree){
    if (subtree == nullptr){
	return false;
    }
    return height(subtree->left) - height(subtree->right) > 0;
}

// Checks if tree has more weight on right hand side (helper for checking which rotation
bool BST::right_heavy(TreeNode* subtree){
    if (subtree == nullptr){
           return false;
    }
    return height(subtree->left) - height(subtree->right) < 0;
}

// Main AVL Insert - Putting all the above functions together
void BST::insertAVL(TreeNode*& subtree, int value){
    // BST insert as usual
    if (subtree == nullptr){
        subtree = new TreeNode(value);
    } else if (value < subtree->value){
        insertAVL(subtree->left, value);
    } else {
        insertAVL(subtree->right, value);
    }

    // After insert, we need to check at every ancestor on the insertion path if
    // AVL condition is violated

    // Need to balance if we violated properties after insertion
    if (!isAVL(subtree)){
        // Left heavy
        if (left_heavy(subtree)){
	    // LL
            if (left_heavy(subtree->left)){
                right_rotate(subtree);
	    // LR
            } else {
                left_rotate(subtree->left);
                right_rotate(subtree);
            }

        } 
        // Right heavy
        else {
	    // RR
            if (right_heavy(subtree->right)){
                left_rotate(subtree);
	    // RL	
            } else {
                right_rotate(subtree->right);
                left_rotate(subtree);
            }
        } 
    }
}

