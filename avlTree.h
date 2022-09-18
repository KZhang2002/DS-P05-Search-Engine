///avlTree header file
///Contains function prototypes and definitions.
///Created by Kenny Zhang

#ifndef INC_22S_FINAL_PROJ_AVLTREE_H
#define INC_22S_FINAL_PROJ_AVLTREE_H

#include <functional>
#include <iostream>
#include <experimental/optional>

using std::cout;
using std::endl;
using std::max;

#define COUNT 10

template <typename t>
class avlTree {
private:
    class avlNode {
    public:
        t data;
        avlNode* left = nullptr;
        avlNode* right = nullptr;
        int height = 0; //distance from the furthest leaf

        avlNode() = default;
        avlNode(const t & dataVal): data(dataVal), height(0){}
        avlNode(const t & dataVal, avlNode *lt, avlNode *rt, int h = 0): data(dataVal), left(lt), right(rt), height(h) {}
    };
    avlNode *root;

public:
    //Stats
    int numNodes = 0;

    //Constructors/Destructors
    avlTree() : root(nullptr){}
    avlTree(const avlTree<t> & rhs ) : root (nullptr){ *this = rhs; }
    ~avlTree() { makeEmpty(); }

    //Getters
    int height(avlNode* n);
    std::experimental::optional<t> lookUp(t query, int (*func)(const t&, const t&));
    std::experimental::optional<t> lookUp(t query, avlNode *&n, int (*func)(const t&, const t&));
    std::experimental::optional<t> lookUpKW(t query, int (*func)(const t&, const t&));
    std::experimental::optional<t> lookUpKW(t query, avlNode *&n, int (*func)(const t&, const t&));

    //Node Addition & Subtraction
    void insert(const t & x);
    void insert(const t & x, avlNode*& n);
    void insert(const t & x, int (*func)(const t&, const t&));
    void insert(const t & x, avlNode*& n, int (*func)(const t&, const t&));
    void deleteNode(const t & x, avlNode*& n);
    void deleteNode(const t & x);
    void makeEmpty();

    //Destructor
    void destroyTree();
    void destroyNode(avlNode*& n);

    //Tree Balancing
    void balance(avlNode*& n);
    void rotateWLChild(avlNode*& k2);
    void rotateWRChild(avlNode*& k1);
    void doubleWLChild(avlNode*& n);
    void doubleWRChild(avlNode*& n);

    //Print Functions
    ///NOTE, THESE FUNCTIONS ARE NOT MINE AND ARE ONLY MEANT FOR DEBUGGING
    ///These functions were written by Aditya Goel of GeeksForGeeks
    ///https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
    void print2DUtil(avlNode *root, int space);
    void print2D(avlNode *root);
    void print2D();
};

///Node addition & subtraction

/**
 * Inserts node into avlTree node n. Pushes back ID into
 * keyword ID vector if keyword already exists. Uses
 * functor func to compare nodes.
 * @tparam t
 * @param x
 * @param n
 * @param func
 */
template<typename t>
void avlTree<t>::insert(const t &x, avlNode*& n, int (*func)(const t&, const t&)) {
    if (n == nullptr) {
        n = new avlNode(x);
        numNodes++;
        //n->height++; //this isnt right i think
        return;
    } else if (0 < func(n->data, x)) { //greater than 0 if x is greater than n->data
        insert(x, n->right, func);
    } else if (func(n->data, x) < 0) {
        insert(x, n->left, func);
    } else {
        for (int i = 0; i < n->data.idVect.size(); i++) {
            if (x.idVect[0].first == n->data.idVect[i].first) {
                n->data.idVect[i].second++;
                return;
            }
        }
        n->data.idVect.push_back(x.idVect[0]);
        n->data.numUses++;
        return;
    }
    //cout << n->height << " -> " << height(n->left) << " == " << height(n->right) << endl;
    n->height = 1 + max(height(n->left), height(n->right));
    balance(n);
}

/**
 * Inserts node into avlTree root. Pushes back ID into
 * keyword ID vector if keyword already exists. Uses
 * functor func to compare nodes.
 * @tparam t
 * @param x
 * @param func
 */
template<typename t>
void avlTree<t>::insert(const t &x, int (*func)(const t&, const t&)) {
    insert(x, root, func);
}

/**
 * Inserts node into avlTree node n if duplicate node
 * is not found.
 * @tparam t
 * @param x
 * @param n
 */
template<typename t>
void avlTree<t>::insert(const t &x, avlTree::avlNode *&n) {
    //cout << "Curr: " << x << endl;
    if (n == nullptr) {
        n = new avlNode(x);
        //n->height++; //this isnt right i think
    } else if (x > n->data) { //greater than 0 if x is greater than n->data
        insert(x, n->right);
    } else if (n->data > x) {
        insert(x, n->left);
    } else {
        return;
    }

    //cout << n->height << " -> " << height(n->left) << " == " << height(n->right) << endl;
    n->height = 1 + max(height(n->left), height(n->right));
    //cout << "new height:"  << n->height << endl;
    balance(n);
}

/**
 * Inserts node into avlTree root if duplicate node
 * is not found.
 * @tparam t
 * @param x
 */
template<typename t>
void avlTree<t>::insert(const t &x) {
    insert(x, root);
}

/**
 * Deletes node with value x from avlTree node n
 * @tparam t
 * @param x
 * @param n
 */
template<typename t>
void avlTree<t>::deleteNode(const t &x, avlTree::avlNode *&n) {
    //cout << "Curr: " << x << endl;
    if (n == nullptr) { return; }

    if (x > n->data) { //greater than 0 if x is greater than n->data
        deleteNode(x, n->right);
    } else if (n->data > x) {
        deleteNode(x, n->left);
    } else { //execute deletion
        //checks for only one or no child
        if ((n->left == nullptr) || (n->right == nullptr)) {
            avlNode *temp = n->left ? n->left : n->right;

            //if no child
            if (temp == nullptr) {
                temp = n;
                delete n;
                n = nullptr;
            } else { //if one child
                *n = *temp; //copies child contents to root node
            }

            //delete(temp);
        } else {
            avlNode *temp = std::min(n->right->right, n->right->left);
            n->data = temp->data;
            deleteNode(x, n->right);
        }
    }

    if (n == nullptr) { return; }

    n->height = max(height(n->right), height(n->left));
    balance(n);
}

/**
 * Deletes node with value x from root
 * @tparam t
 * @param x
 */
template<typename t>
void avlTree<t>::deleteNode(const t &x) {
    deleteNode(x, root);
}

/**
 * Clears avlTree of all nodes.
 * @tparam t
 */
template<typename t>
void avlTree<t>::makeEmpty() {
    destroyTree();
}

/**
 * Driver function for tree destructor
 * @tparam t
 */
template<typename t>
void avlTree<t>::destroyTree() {
    destroyNode(root);
}

/**
 * Recursive function to destroy all nodes
 * @tparam t
 * @param n
 */
template<typename t>
void avlTree<t>::destroyNode(avlTree::avlNode *&n) {
    if (n) {
        destroyNode(n->left);
        destroyNode(n->right);
        delete n;
    }
}

///Balancing Functions

/**
 * Checks balance of node n's child heights
 * and performs rotations if found to be unbalanaced.
 * @tparam t
 * @param n
 */
template<typename t>
void avlTree<t>::balance(avlTree::avlNode *&n) {
    if (n == nullptr)
        return;

    //cout << height(n->left) << " =? " << height(n->right) << endl;
    if (height(n->left) - height(n->right) > 1) {
        if (height(n->left->left) > height(n->left->right)) {
            rotateWLChild(n);//C1
        } else {
            doubleWLChild(n);//C2
        }
    } else if (height(n->right) - height(n->left) > 1) {
        if (height(n->right->right) > height(n->right->left)) {
            rotateWRChild(n);//C4
        } else {
            doubleWRChild(n);//C3
        }
    }
    n->height = std::max(height(n->left), height(n->right)) + 1;
}

/**
 * Performs balance for a
 * double left child situation.
 * @tparam t
 * @param n
 */
template<typename t>
void avlTree<t>::rotateWLChild(avlTree::avlNode *&k2) { //C1
    avlNode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = std::max(height(k2->left), height(k2->right)) + 1;
    k1->height = std::max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

/**
* Performs balance for a
* double right child situation.
* @tparam t
* @param n
*/
template<typename t>
void avlTree<t>::rotateWRChild(avlTree::avlNode *&k1) { //C4
    avlNode* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k2->height = std::max(height(k2->right), k1->height) + 1;
    k1->height = std::max(height(k1->left), height(k1->right)) + 1;
    k1 = k2;
}

/**
* Performs balance for a
* left child right child situation.
* @tparam t
* @param n
*/
template<typename t>
void avlTree<t>::doubleWLChild(avlTree::avlNode *&n) { //C2
    rotateWRChild(n->left);
    rotateWLChild(n);
}

/**
* Performs balance for a
* right child left child situation.
* @tparam t
* @param n
*/
template<typename t>
void avlTree<t>::doubleWRChild(avlTree::avlNode *&n) { //C3
    rotateWLChild(n->right);
    rotateWRChild(n);
}

/**
 * returns height of a given node.
 * @tparam t
 * @param n
 * @return
 */
template<typename t>
int avlTree<t>::height(avlTree::avlNode *n) {
    return n == nullptr ? - 1 : n->height;
}

///Search Functions

/**
 * Searches root for query and returns query if it exists.
 * Not a very useful function, mostly just a template for
 * future lookUp programs. Uses functor func to compare
 * nodes.
 * @tparam t
 * @param query
 * @param func
 * @return
 */
template<typename t>
std::experimental::optional<t> avlTree<t>::lookUp(t query, int (*func)(const t &, const t &)) {
    return lookUp(query, root, func);
}

/**
 * Searches node n for query and returns query if it exists.
 * Not a very useful function, mostly just a template for
 * future lookUp programs. Uses functor func to compare
 * nodes.
 * @tparam t
 * @param query
 * @param n
 * @param func
 * @return
 */
template<typename t>
std::experimental::optional<t> avlTree<t>::lookUp(t query, avlTree::avlNode *&n, int (*func)(const t &, const t &)) { //check this, not sure if implemented right
    int compNum = func(n->data, query);

    if (compNum < 0) {
        if (n->left == nullptr) {
            return nullptr;
        } else {
            return lookUp(query, n->left, func); //address of func?
        }
    } else if (compNum > 0) {
        if (n->right == nullptr) {
            return nullptr;
        } else {
            return lookUp(query, n->left, func);
        }
    } else {
        return n->data;
    }
}

/**
 * Searches node root for keyword and returns keyword object
 * if it exists. Uses functor func to compare nodes for search.
 * Optional is false if null value is returned.
 * @tparam t
 * @param query
 * @param func
 * @return
 */
template<typename t>
std::experimental::optional<t> avlTree<t>::lookUpKW(t query, int (*func)(const t &, const t &)) {
    return lookUpKW(query, root, func);
}

/**
 * Searches node n for keyword and returns keyword object
 * if it exists. Uses functor func to compare nodes for search.
 * Optional is false if null value is returned.
 * @tparam t
 * @param query
 * @param n
 * @param func
 * @return
 */
template<typename t>
std::experimental::optional<t> avlTree<t>::lookUpKW(t query, avlTree::avlNode *&n, int (*func)(const t &, const t &)) {
    int compNum = func(n->data, query);

    if (compNum < 0) { //Returns num that is < 0 if b comes last alphabetically. (b is left of a.)
        if (n->left == nullptr) {
            return {};
        } else {
            return lookUpKW(query, n->left, func); //address of func?
        }
    } else if (compNum > 0) { //Returns num that is > 0 if b comes first alphabetically. (b is right of a.)
        if (n->right == nullptr) {
            return {};
        } else {
            return lookUpKW(query, n->right, func);
        }
    } else {
        return n->data;
    }
}

///Print Functions

/**
 * Function to print binary tree in 2D
 * through reverse inorder traversal.
 * @note THIS FUNCTION IS NOT MINE.
 * @note These functions were written by Aditya Goel of GeeksForGeeks
 * @note https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
 */
template<typename t>
void avlTree<t>::print2DUtil(avlTree::avlNode *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<root->data<<"\n";

    // Process left child
    print2DUtil(root->left, space);
}

/**
 * Wrapper over print2DUtil().
 * Function to print binary tree in 2D
 * through reverse inorder traversal.
 * @note THIS FUNCTION IS NOT MINE.
 * @note These functions were written by Aditya Goel of GeeksForGeeks
 * @note https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
 */
template<typename t>
void avlTree<t>::print2D(avlTree::avlNode *rootVal)
{
    // Pass initial space count as 0
    print2DUtil(rootVal, 0);
}

/**
 * Wrapper over print2DUtil().
 * Function to print root tree in 2D
 * through reverse inorder traversal.
 * @note THIS FUNCTION IS NOT MINE.
 * @note These functions were written by Aditya Goel of GeeksForGeeks
 * @note https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
 */
template<typename t>
void avlTree<t>::print2D() {
    print2DUtil(root, 0);
}






#endif //INC_22S_FINAL_PROJ_AVLTREE_H
