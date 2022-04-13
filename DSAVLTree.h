//
// Owner - Ethan Zech
//

#ifndef INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_DSAVLTREE_H
#define INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_DSAVLTREE_H

#include <iostream>

template<typename T>
class DSAVLTree{
private:
    /**
     * Stores data and pointers to left and/or right children trees.
     */
    struct AVLNode{
    public:
        T data;
        AVLNode* left;
        AVLNode* right;
        int height;

        AVLNode(const T& element, AVLNode *lt, AVLNode *rt, int h = 0) : data(element), left(lt), right(rt), height(h) { }
    };

    //Root of the tree
    AVLNode* root = nullptr;

    int height;

    /**
     * Recursive function to insert the element as the child of the correct node. Called by public insert.
     * @param element - Element to be inserted.
     * @param node - Node to check for insertion.
     */
    void insert(const int& element, AVLNode*& node);

    /**
     * Determines and calls the correct rotation function for this node to balance the tree.
     * @param node - Node to center the rotation on.
     */
    void balance(AVLNode*& node);

    /**
     * Rotates the given node with its left child. Rotation 1.
     * @param node - Node to rotate with its left child.
     */
    void rotateWithLeftChild(AVLNode*& node);

    /**
     * Double rotates the given node with its left child. Rotation 2.
     * @param node - Node to double rotate with its left child.
     */
    void doubleWithLeftChild(AVLNode*& node);

    /**
     * Rotates the given node with its right child. Rotation 4.
     * @param node - Node to rotate with its right child.
     */
    void rotateWithRightChild(AVLNode*& node);

    /**
     * Double rotates the given node with its right child. Rotation 3.
     * @param node - Node to double rotate with its right child.
     */
    void doubleWithRightChild(AVLNode*& node);

public:
    //Constructors and Destructors
    DSAVLTree() : height(0) { };
    DSAVLTree(const DSAVLTree<T>& rhs);
    ~DSAVLTree();

    //Getters and Setters
    int getHeight() const;

    /**
     * Inserts the given element into the DSAVLTree.
     * @param element - Element to be inserted.
     */
    void insert(const T& element);

    /**
     * Returns true if the tree contains the element. The tree contains the element if the element returns true
     * when a tree element is entered as an argument into the elements operator==().
     * @param element - The element to search for in the DSAVLTree.
     * @return Whether the element is in the DSAVLTree or not.
     */
    bool contains(const T& element);

    /**
     * Returns a reference to the element in the DSAVLTree. Throws an error if the element is not
     * in the tree.
     * @param element - The element to search for in the DSAVLTree.
     * @return The element in the tree that was searched for.
     */
    T& Find(const T& element);

    /**
     * Outputs the elements of the DSAVLTree pre order.
     * @return A ostream with the elements of of the DSAVLTree pre order.
     */
    std::ostream outputPreOrder();

    /**
     * Outputs the elements of the DSAVLTree in order.
     * @return A ostream with the elements of of the DSAVLTree in order.
     */
    std::ostream outputInOrder();

    /**
     * Outputs the elements of the DSAVLTree post order.
     * @return A ostream with the elements of of the DSAVLTree post order.
     */
    std::ostream outputPostOrder();
};

#endif //INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_DSAVLTREE_H
