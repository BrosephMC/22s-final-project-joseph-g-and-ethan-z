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

    int getNodeHeight(AVLNode* node);

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
     * @param k2 - Node to rotate with its left child.
     */
    void rotateWithLeftChild(AVLNode*& k2);

    /**
     * Double rotates the given node with its left child. Rotation 2.
     * @param k2 - Node to double rotate with its left child.
     */
    void doubleWithLeftChild(AVLNode*& k2);

    /**
     * Rotates the given node with its right child. Rotation 4.
     * @param k2 - Node to rotate with its right child.
     */
    void rotateWithRightChild(AVLNode*& k2);

    /**
     * Double rotates the given node with its right child. Rotation 3.
     * @param k2 - Node to double rotate with its right child.
     */
    void doubleWithRightChild(AVLNode*& k2);

    //Recursive Output Functions
    void PreOrder(AVLNode* node, std::ostream& output);
    void InOrder(AVLNode* node, std::ostream& output);
    void PostOrder(AVLNode* node, std::ostream& output);

    /**
     * Called by the destructor to delete every node.
     * @param node - Node to delete.
     */
    void PostOrderDelete(AVLNode* node);

public:
    //Constructors and Destructors
    DSAVLTree() : root(nullptr) { };
    DSAVLTree(const DSAVLTree<T>& rhs) : root(nullptr);
    ~DSAVLTree();

    //Getters and Setters

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

template<typename T>
int DSAVLTree<T>::getNodeHeight(DSAVLTree::AVLNode *node) {
    return node == nullptr?-1:node->height;
}

template<typename T>
void DSAVLTree<T>::insert(const int& element, DSAVLTree::AVLNode*& node) {
    if(node == nullptr)
        node = new AVLNode(element, nullptr, nullptr);
    else if(element < node->data)
        insert(element, node->left);
    else if(node->data <= element)
        insert(element, node->right);
    //else
    //Handle Duplicates
    balance(node);
}

template<typename T>
void DSAVLTree<T>::balance(DSAVLTree::AVLNode*& node) {
    if(node == nullptr)
        return;
    //Case 1 or 2
    if(getNodeHeight(node->left) - getNodeHeight(node->right) > 1){
        //Case 1
        if(getNodeHeight(node->left->left) >= getNodeHeight(node->left->right))
            rotateWithLeftChild(node);
            //Case 2
        else
            doubleWithLeftChild(node);
    }
        //Case 3 or 4
    else if(getNodeHeight(node->right) - getNodeHeight(node->left) > 1){
        //Case 4
        if(getNodeHeight(node->right->right) >= getNodeHeight(node->right->left))
            rotateWithRightChild(node);
            //Case 3
        else
            doubleWithRightChild(node);
    }
    node->height = max(getNodeHeight(node->left), getNodeHeight(node->right)) + 1;
}

//Case 1
template<typename T>
void DSAVLTree<T>::rotateWithLeftChild(DSAVLTree::AVLNode*& k2) {
    AVLNode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(getNodeHeight(k2->left), getNodeHeight(k2->right)) + 1;
    k1->height = max(getNodeHeight(k1->left), k2->height) + 1;
    k2 = k1;
}

//Case 2
template<typename T>
void DSAVLTree<T>::doubleWithLeftChild(DSAVLTree::AVLNode*& k2) {
    AVLNode* k1 = k2->left;
    AVLNode* k3 = k1->right;
    //First Rotation
    k1->right = k3->left;
    k3->left = k1;
    k2->left = k3;
    k1->height = max(getNodeHeight(k1->left), getNodeHeight(k1->right)) + 1;
    k3->height = max(k1->height, getNodeHeight(k3->right)) + 1;
    //Second Rotation
    rotateWithLeftChild(k2);
}

//Case 4
template<typename T>
void DSAVLTree<T>::rotateWithRightChild(DSAVLTree::AVLNode*& k2) {
    AVLNode* k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = max(getNodeHeight(k2->left), getNodeHeight(k2->right)) + 1;
    k1->height = max(k2->height, getNodeHeight(k1->right)) + 1;
    k2 = k1;
}

//Case 3
template<typename T>
void DSAVLTree<T>::doubleWithRightChild(DSAVLTree::AVLNode *&k2) {
    AVLNode* k1 = k2->right;
    AVLNode* k3 = k1->left;
    //First Rotation
    k1->left = k3->right;
    k3->right = k1;
    k2->right = k3;
    k1->height = max(getNodeHeight(k1->left), getNodeHeight(k1->right)) + 1;
    k3->height = max(getNodeHeight(k3->left), k1->height) + 1;
    //Second Rotation
    rotateWithRightChild(k2);
}

template<typename T>
void DSAVLTree<T>::PreOrder(DSAVLTree::AVLNode* node, std::ostream& output) {
    if(node != nullptr){
        output << node->data;
        PreOrder(node->left);
        PreOrder(node->right);
    }
}

template<typename T>
void DSAVLTree<T>::InOrder(DSAVLTree::AVLNode* node, std::ostream& output) {
    if(node != nullptr){
        InOrder(node->left, output);
        output << node->data;
        InOrder(node->right, output);
    }
}

template<typename T>
void DSAVLTree<T>::PostOrder(DSAVLTree::AVLNode* node, std::ostream& output) {
    if(node != nullptr){
        PostOrder(node->left);
        PostOrder(node->right);
        output << node->data;
    }
}

template<typename T>
void DSAVLTree<T>::PostOrderDelete(DSAVLTree::AVLNode* node) {
    if(node != nullptr){
        PostOrderDelete(node->left);
        PostOrderDelete(node->right);
        delete node;
    }
}

template<typename T>
DSAVLTree<T>::DSAVLTree(const DSAVLTree<T> &rhs) {
    *this = rhs;
}

template<typename T>
void DSAVLTree<T>::insert(const T& element) {
    insert(element, root);
}

template<typename T>
std::ostream DSAVLTree<T>::outputPreOrder() {
    std::ostream output;
    PreOrder(root, output);
    return output;
}

template<typename T>
std::ostream DSAVLTree<T>::outputInOrder() {
    std::ostream output;
    InOrder(root, output);
    return output;
}

template<typename T>
std::ostream DSAVLTree<T>::outputPostOrder() {
    std::ostream output;
    PostOrder(root, output);
    return output;
}

template<typename T>
DSAVLTree<T>::~DSAVLTree() {
    PostOrderDelete(root);
}

#endif //INC_22S_FINAL_PROJECT_JOSEPH_G_AND_ETHAN_Z_DSAVLTREE_H
