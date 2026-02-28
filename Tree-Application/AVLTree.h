//
// Created by Stephen A. Adubi on 03/02/2026.
// Modified on 27/02/2026
//

#ifndef CSC301_PROJECT_AVLTREE_H
#define CSC301_PROJECT_AVLTREE_H
#include <array>
#include <cmath>
#include <cstdio>
#include <queue>
#include <utility>
#include <vector>

template <typename T>
class AVLTree{
    struct AVLNode
    {
        T data;
        int height;
        AVLNode* left;
        AVLNode* right;
        AVLNode(T d) {
            data = d;
            left = right = nullptr;
            height = 0;
        }
    };

    AVLNode* root;
    std::vector<AVLNode*> insertTrace;
    std::vector<AVLNode*> deleteTrace;
    AVLNode* criticalNode;
    AVLNode* criticalNode_successor;
    AVLNode* node_to_delete;
    AVLNode* node_with_swapped_data;
    T swapped_data;
    T deleted_node_data;

    void getTreeElements(AVLNode* node, std::vector<AVLNode*>& elements) {
        if (node == nullptr) {
            return;
        }
        if (node->left != nullptr) {
            getTreeElements(node->left, elements);
        }
        elements.emplace_back(node);
        if (node->right != nullptr) {
            getTreeElements(node->right, elements);
        }
    }

    // Method to insert a new AVLNode -- Version 2
    void insert(T data, AVLNode*& AVLNode){
        if (AVLNode == nullptr) {
            auto* temp = new AVLTree::AVLNode(data);
            AVLNode = temp;
        }
        else if (data < AVLNode->data) {
            insertTrace.emplace_back(AVLNode); // record the current parent node
            insert(data, AVLNode->left);
        }
        else {
            insertTrace.emplace_back(AVLNode); // record the current parent node
            insert(data, AVLNode->right);
        }
    }

    /**
     * @brief Method to search for an AVLNode and its parent
     * @param data the value of the item that was deleted
     * @param code the flag that signifies which operation triggered the function call
     * \n[<b>0:</b> rotation operation, <b>1:</b> deletion operation]
     * @return a pair <node, parent_node> where parent_node represents the parent of the node that was searched for
     */
    std::pair<AVLNode*, AVLNode*> search_with_Parent(T data, const int code) {
        AVLNode* current = root;
        AVLNode* parent = nullptr;
        if (code == 1) deleteTrace.clear(); // reset the deleteTrace data structure
        while (current != nullptr)
        {
            if (current->data == data) {
                break;
            }
            if (data < current->data) {
                parent = current;
                if (code == 1) deleteTrace.emplace_back(current);
                current = current->left;
            }
            else {
                parent = current;
                if (code == 1) deleteTrace.emplace_back(current);
                current = current->right;
            }
        }

        if (current != nullptr) {
            if (code == 1) deleteTrace.emplace_back(current);
            return std::make_pair(current, parent);
        }

        if (code == 1) deleteTrace.clear();
        return std::make_pair(nullptr, nullptr);
    }

    void updateHeight_insert() {
        criticalNode = nullptr;
        criticalNode_successor = nullptr;
        AVLNode* temp = nullptr;
        int bf_temp = 0;
        int bf_critical = 0;
        for (auto r_it = insertTrace.rbegin(); r_it != insertTrace.rend(); ++r_it)
        {
            AVLNode* item = *r_it;
            int height_of_left_child = item->left != nullptr ? item->left->height : -1;
            int height_of_right_child = item->right != nullptr ? item->right->height : -1;
            item->height = std::max(height_of_left_child, height_of_right_child) + 1;
            int balance_factor = height_of_left_child - height_of_right_child;
            if (std::abs(balance_factor) > 1) {
                criticalNode = item;
                criticalNode_successor = temp;
                bf_critical = balance_factor;
                break; // found a critical node
            }

            temp = item;
            bf_temp = balance_factor;
        }

        if (criticalNode)
            perform_rotation(bf_critical, bf_temp); // call the function for self-rotation
    }

    void updateHeight_delete() {
        criticalNode = nullptr;
        criticalNode_successor = nullptr;
        int bf_critical_child = 0;
        int bf_critical = 0;
        if (deleteTrace.size() < 2)
            return;
        for (auto r_it = deleteTrace.rbegin(); r_it != deleteTrace.rend(); ++r_it)
        {
            AVLNode* item = *r_it;
            if (item == node_to_delete)
                continue;
            int height_of_left_child = item->left != nullptr ? item->left->height : -1;
            int height_of_right_child = item->right != nullptr ? item->right->height : -1;
            item->height = std::max(height_of_left_child, height_of_right_child) + 1;
            int balance_factor = height_of_left_child - height_of_right_child;
            if (std::abs(balance_factor) > 1) {
                criticalNode = item;
                T comparator1, comparator2;
                if (criticalNode == node_with_swapped_data)
                {
                    comparator1 = deleted_node_data;
                    comparator2 = swapped_data;
                }
                else
                {
                    comparator1 = item->data;
                    comparator2 = node_with_swapped_data != nullptr ? swapped_data : deleted_node_data;
                }

                criticalNode_successor = comparator1 < comparator2 ? item->left : item->right;
                bf_critical = balance_factor;

                height_of_left_child = criticalNode_successor->left != nullptr ? criticalNode_successor->left->height : -1;
                height_of_right_child = criticalNode_successor->right != nullptr ? criticalNode_successor->right->height : -1;
                bf_critical_child = height_of_left_child - height_of_right_child;

                break; // found a critical node
            }
        }

        if (criticalNode)
            perform_rotation(bf_critical, bf_critical_child); // call the function for self-rotation
    }

    void perform_rotation(int bf_critical, int bf_critical_child) {
        std::array<AVLNode*, 3> updateList = {criticalNode, criticalNode_successor, nullptr};
        if (bf_critical > 0 && bf_critical_child >= 0) // condition to perform single right rotation
            right_rotate(criticalNode, criticalNode_successor);
        else if (bf_critical < 0 && bf_critical_child <= 0) // condition to perform single left rotation
            left_rotate(criticalNode, criticalNode_successor);
        else if (bf_critical < 0 && bf_critical_child > 0) { // condition to perform double right-left rotation
            AVLNode* child_of_target = criticalNode_successor->left;
            updateList[2] = child_of_target;
            right_rotate(criticalNode_successor, child_of_target);
            child_of_target = criticalNode->right;
            left_rotate(criticalNode, child_of_target);
        }
        else { // condition to perform double left-right rotation
            AVLNode* child_of_target = criticalNode_successor->right;
            updateList[2] = child_of_target;
            left_rotate(criticalNode_successor, child_of_target);
            child_of_target = criticalNode->left;
            right_rotate(criticalNode, child_of_target);
        }

        updateHeightsAfterRotation(updateList);
    }

    void updateHeightsAfterRotation(std::array<AVLNode*, 3>& list) {
        for (AVLNode* node : list)
            if (node != nullptr)
                node->height = computeTreeHeight(node);
    }

    void left_rotate(AVLNode* targetNode, AVLNode* childNode) {
        // STEP 1: If Y has a left subtree (beta), make the beta the right subtree of X
        if (childNode->left != nullptr)
            targetNode->right = childNode->left;
        else
            targetNode->right = nullptr;

        auto search_terms = search_with_Parent(targetNode->data, 0);
        AVLNode* parent_of_target = search_terms.second;

        //STEP 2: Make P (the parent of X) the parent of Y or make Y the root of the tree (if X has no parent)
        if (parent_of_target == nullptr)
            root = childNode;
        else if (parent_of_target->data < targetNode->data)
            parent_of_target->right = childNode;
        else
            parent_of_target->left = childNode;

        // STEP 3: Make Y the parent of X
        childNode->left = targetNode;
    }

    void right_rotate(AVLNode* targetNode, AVLNode* childNode) {
        // STEP 1: If X has a right subtree (beta), make the beta the left subtree of Y
        if (childNode->right != nullptr)
            targetNode->left = childNode->right;
        else
            targetNode->left = nullptr;

        auto search_terms = search_with_Parent(targetNode->data, 0);
        AVLNode* parent_of_target = search_terms.second;

        //STEP 2: Make P (the parent of X) the parent of Y or make Y the root of the tree (if X has no parent)
        if (parent_of_target == nullptr)
            root = childNode;
        else if (parent_of_target->data < targetNode->data)
            parent_of_target->right = childNode;
        else
            parent_of_target->left = childNode;

        // STEP 3: Make Y the parent of X
        childNode->right = targetNode;
    }

    /**
     * Finds the inorder successor of a AVLNode and the parent of the successor:<br/>
     * Returns a pair: <Successor, Parent_Successor>
     */
    std::pair<AVLNode *, AVLNode *> search_successor(AVLNode *aNode) {
        AVLNode* parent_successor = aNode;
        AVLNode* successor = aNode->right;
        deleteTrace.emplace_back(successor);
        while (successor->left != nullptr) {
            parent_successor = successor;
            successor = successor->left;
            deleteTrace.emplace_back(successor);
        }

        return std::make_pair(successor, parent_successor);
    }

public:
    AVLTree() : root(nullptr), criticalNode(nullptr), criticalNode_successor(nullptr), node_to_delete(nullptr),
                node_with_swapped_data(nullptr) {
    } // constructor

    AVLNode* getRoot() const { return root; }

    bool isEmpty() const { return root == nullptr; }    // determines emptiness of the tree

    // Method to insert a new AVLNode
    bool insert(T data) {
        if (isEmpty()) {
            auto* temp = new AVLNode(data);
            root = temp;
        }
        else {
            insertTrace.clear(); // clear the insert trace to prepare for another insert operation.
            insert(data, root);
            updateHeight_insert();
        }

        return true;
    }

    /**
     * @brief Method to search for a value in the BST
     * @param data the item to be inserted
     * @return the pointer to the node that holds @code data@endcode
     */
    AVLNode* search(T data) {
        AVLNode* current = root;
        while (current != nullptr) {
            if (current->data == data) {
                return current;
            }
            if (data < current->data) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        return nullptr;
    }

    /**
     * @brief Method to perform <b>inorder</b> traversal
     * @param AVLNode the root node
     * @attention pass in the root node as the function call argument (can be accessed via the
     * @code getRoot()@endcode method)
     */
    void inorder(AVLNode* AVLNode) {
        if (AVLNode->left != nullptr)
            inorder(AVLNode->left);
        std::printf("%d ", AVLNode->data);
        if (AVLNode->right != nullptr)
            inorder(AVLNode->right);
    }

    /**
     * The method returns a vector of elements within the tree via inorder traversal.
    */
    std::vector<AVLNode*> getTreeElements() {
        std::vector<AVLNode*> elements;
        getTreeElements(root, elements);
        return elements;
    }

    /**
     * @brief Method to perform <b>preorder</b> traversal
     * @param AVLNode the root node
     * @attention pass in the root node as the function call argument (can be accessed via the
     * @code getRoot()@endcode method)
     */
    void preorder(AVLNode *AVLNode) {
        // Node Left Right
        printf("%d ", AVLNode->data);
        if (AVLNode->left != nullptr) {
            preorder(AVLNode->left);
        }
        if (AVLNode->right != nullptr) {
            preorder(AVLNode->right);
        }
    }

    /**
     * @brief Method to perform <b>postorder</b> traversal
     * @param AVLNode the root node
     * @attention pass in the root node as the function call argument (can be accessed via the
     * @code getRoot()@endcode method)
     */
    void postorder(AVLNode *AVLNode) {
        // Left Right Node
        if (AVLNode->left != nullptr) {
            postorder(AVLNode->left);
        }
        if (AVLNode->right != nullptr) {
            postorder(AVLNode->right);
        }
        printf("%d ", AVLNode->data);
    }

    /**
     * @brief Method to perform <b>level-order</b> traversal
     * @param Node the root node
     * @attention pass in the root node as the function call argument (can be accessed via the
     * @code getRoot()@endcode method)
     */
    void levelorder(AVLNode *Node) {
        if (Node == nullptr) // return when the current node is NULL
            return;
        std::queue<AVLNode*> q;
        q.push(Node);
        while (!q.empty()) {
            auto next = q.front();
            q.pop();
            printf("%d ", next->data);
            if (next->left != nullptr)
                q.push(next->left);
            if (next->right != nullptr)
                q.push(next->right);
        }
    }

    int computeTreeHeight(AVLNode* p) {
        if (p->left == nullptr && p->right == nullptr)
            return 0;
        int h = 0;
        if (p->left != nullptr)
            h = std::max(h, computeTreeHeight(p->left));
        if (p->right != nullptr)
            h = std::max(h, computeTreeHeight(p->right));
        return 1 + h;
    }

    // A call to delete a AVLNode from the BST
    bool deleteAVLNode(T data){
        node_with_swapped_data = nullptr;
        auto node_to_delete_parent = search_with_Parent(data, 1);
        node_to_delete = node_to_delete_parent.first;
        AVLNode* target_node_parent = node_to_delete_parent.second;
        if (node_to_delete == nullptr)
            return false;

        bool cond1 = node_to_delete->left != nullptr && node_to_delete->right == nullptr;
        bool cond2 = node_to_delete->left == nullptr && node_to_delete->right != nullptr;

        // Handle Case 1:
        if (node_to_delete->left == nullptr && node_to_delete->right == nullptr) {
            if (target_node_parent != nullptr) {
                if (node_to_delete->data < target_node_parent->data)
                    target_node_parent->left = nullptr;
                else
                    target_node_parent->right = nullptr;
            }
            else
                root = nullptr;
            deleted_node_data = node_to_delete->data;
            delete node_to_delete;
        }

        // Handle Case 2:
        else if (cond1 || cond2) { // target node has one child
            if (target_node_parent != nullptr) { // if target node has a parent
                if (node_to_delete->data < target_node_parent->data) { // if target node is the left child of its parent
                    if(node_to_delete->left != nullptr) {
                        target_node_parent->left = node_to_delete->left;
                        deleteTrace.emplace_back(node_to_delete->left);
                    }
                    else {
                        target_node_parent->left = node_to_delete->right;
                        deleteTrace.emplace_back(node_to_delete->right);
                    }
                }
                else { // if target node is the right child of its parent
                    if(node_to_delete->left != nullptr) {
                        target_node_parent->right = node_to_delete->left;
                        deleteTrace.emplace_back(node_to_delete->left);
                    }
                    else {
                        target_node_parent->right = node_to_delete->right;
                        deleteTrace.emplace_back(node_to_delete->right);
                    }
                }
            }
            else { // if target node does not have a parent
                if(node_to_delete->left != nullptr)
                    root = node_to_delete->left;
                else
                    root = node_to_delete->right;
            }

            deleted_node_data = node_to_delete->data;
            delete node_to_delete;  // delete the target node
        }

        // Handle Case 3:
        else { // if target node has two children
            auto successor_parent = search_successor(node_to_delete);
            // swap the values of the successor and the target node:
            T successor_data = successor_parent.first->data;
            T successor_parent_data = successor_parent.second->data;
            node_with_swapped_data = node_to_delete;
            deleted_node_data = node_to_delete->data;
            swapped_data = successor_data;
            std::swap(node_to_delete->data, successor_parent.first->data);
            // point the successor parent's (left or right) pointer to the right child of the successor
            if (successor_data < successor_parent_data)
                successor_parent.second->left = successor_parent.first->right;
            else
                successor_parent.second->right = successor_parent.first->right;
            // delete the successor node
            node_to_delete = successor_parent.first;
            delete node_to_delete;
        }

        updateHeight_delete();
        return true;
    }
};

#endif //CSC301_PROJECT_AVLTREE_H