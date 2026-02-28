#include <iostream>
#include <random>

#include "AVLTree.h"

/**
 * @brief Takes an AVL Tree structure and prints out all the nodes (i.e., their values) within the tree and their
 * respective heights
 * @param T the tree structure
 */
void displayNode_Children_Heights(AVLTree<int>& T) {
    auto elements_in_tree = T.getTreeElements();
    std::cout << "\n\nHeights of Nodes in the tree with " << elements_in_tree.size() << " elements:";
    for (auto& i : elements_in_tree) {
        int height = T.computeTreeHeight(i);
        std::string children = i->left != nullptr ? std::to_string(i->left->data) : "";
        children += i->right != nullptr ? ", " + std::to_string(i->right->data) : "";
        printf("\nThe height of node %d(%s) is %d", i->data, children.c_str(), height);
    }
}

/**
 * The main function tests the use of the AVL tree by randomly carrying out an action between two options
 * (insertion and deletion). The probability of insertion at every iteration is 70%
 * @return
 */
int main() {
    AVLTree<int> tree;
    int n_iterations = 20;
    std::vector<int> bucket_values(99);
    std::vector<int> inserted_values;
    std::iota(bucket_values.begin(), bucket_values.end(), 1);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> uniform_real(0.0, 1.0); // Uniform distribution in [0.0, 1.0)
    for (int i = 1; i < n_iterations; i++) {
        constexpr double insert_delete_ratio = 0.7;
        double rand_value = uniform_real(gen);
        // insert/delete a new value with a given probability (see insert_delete_ratio)
        if (rand_value < insert_delete_ratio) {
            int rand_index = std::uniform_int_distribution<> {0, (int) bucket_values.size() - 1}(gen);
            int data = bucket_values.at(rand_index);
            tree.insert(data);
            bucket_values.erase(bucket_values.begin() + rand_index);
            inserted_values.push_back(data);
        }
        else {
            double rand_choice = uniform_real(gen);
            int rand_index, data_to_delete;
            if (rand_choice < 0.9 && !inserted_values.empty()) {
                rand_index = std::uniform_int_distribution<> {0, (int) inserted_values.size() - 1} (gen);
                data_to_delete = inserted_values.at(rand_index);
                std::printf("\n\nTree Information before the deletion of %d", data_to_delete);
                displayNode_Children_Heights(tree);
                tree.deleteAVLNode(data_to_delete);
                std::printf("\n\nTree Information after the deletion of %d", data_to_delete);
                displayNode_Children_Heights(tree);

                // update the vectors
                inserted_values.erase(inserted_values.begin() + rand_index);
                bucket_values.emplace_back(data_to_delete);
            }
            else {  // pick from the bigger bucket, chance of a miss (value may not be selected from the tree)!
                rand_index = std::uniform_int_distribution<> {0, static_cast<int>(bucket_values.size()) - 1} (gen);
                data_to_delete = bucket_values.at(rand_index);
                std::printf("\n\nTree Information before the deletion of %d", data_to_delete);
                displayNode_Children_Heights(tree);
                if (tree.deleteAVLNode(data_to_delete)) {
                    // update the vectors
                    std::printf("\n\nTree Information after the deletion of %d", data_to_delete);
                    displayNode_Children_Heights(tree);
                    inserted_values.erase(inserted_values.begin() + rand_index);
                    bucket_values.emplace_back(data_to_delete);
                }
                else
                    std::printf("\n\nTree Information remains the same after the non-deletion of %d",
                        data_to_delete);
            }
        }
    }

    std::printf("\nPreorder Traversal:\n"); tree.preorder(tree.getRoot()); std::printf("\n");
    std::printf("Inorder Traversal:\n"); tree.inorder(tree.getRoot()); std::printf("\n");
    std::printf("Postorder Traversal:\n"); tree.postorder(tree.getRoot()); std::printf("\n");
    std::printf("Levelorder Traversal:\n"); tree.levelorder(tree.getRoot()); // std::printf("\n");
    displayNode_Children_Heights(tree);
}