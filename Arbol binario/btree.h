#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

#include "node.h"

class BTreeException : public std::exception {
private:
    std::string msg;

public:
    explicit BTreeException( const char* message ) : msg(message) { };

    explicit BTreeException( const std::string message ) : msg( message) { }

    virtual ~BTreeException() throw() {}

    virtual const char* what() const throw() {
        return msg.c_str();
    }
};

template <class T>
class BTree {
private:
    Node<T>* root;

    void insertData(Node<T>*&, const T&);

    Node<T>*& findData(Node<T>*&, const T&);

    Node<T>*& getLowest(Node<T>*&);
    Node<T>*& getHighest(Node<T>*&);

    unsigned getHeight(Node<T>*&);

    void preorder(Node<T>*&);
    void inorder(Node<T>*&);
    void postorder(Node<T>*&);

    void deleteAll(Node<T>*&);

public:
    BTree();
    ~BTree();

    bool isEmpty();

    void insertData(const T&);
    void deleteData(Node<T>*&);

    bool isLeaf(Node<T>*&);

    Node<T>*& findData(const T&);
    T& retrieve(Node<T>*&);

    Node<T>*& getLowest();
    Node<T>*& getHighest();

    unsigned getHeight();

    void preorder();
    void inorder();
    void postorder();

    void deleteAll();

};

template <class T>
BTree<T>::BTree() {
    root = nullptr;
}

template <class T>
BTree<T>::~BTree() {
    deleteAll();
}

template <class T>
bool BTree<T>::isEmpty() {
    return root == nullptr;
}

template <class T>
void BTree<T>::insertData(const T& e) {
    insertData(root, e);
}

template <class T>
void BTree<T>::insertData(Node<T>*& r, const T& e) {
    if(r == nullptr){
        try{
            r = new Node<T>(e);
        }catch(NodeException ex){
            throw BTreeException("Algo salio mal...");
        }

        if(r == nullptr){
            throw BTreeException("Memoria no disponible al insertar");
        }

    }else{
        if(e < r->getData()){
            insertData(r->getLeft(), e);
        }else{
            insertData(r->getRight(), e);
        }
    }
}

template <class T>
void BTree<T>::deleteData(Node<T>*& r) {
    if(r == nullptr){
        throw BTreeException("Posicion invalida para eliminar");
    }

    if(isLeaf(r)){
        delete r;

        r = nullptr;
    }else{
        Node<T>* aux;

        if(r->getLeft() != nullptr){
            aux = getHighest(r->getLeft());
        }else{
            aux = getLowest(r->getRight());
        }

        r->setData(aux->getData());

        deleteData(aux);
    }
}

template <class T>
bool BTree<T>::isLeaf(Node<T>*& r) {
    if(r == nullptr){
        return false;
    }

    if(r->getLeft() == nullptr and r->getRight() == nullptr){
        return true;
    }else{
        return false;
    }
}

template <class T>
Node<T>*& BTree<T>::findData(const T& e) {
    findData(root, e);
}

template <class T>
Node<T>*& BTree<T>::findData(Node<T>*& r, const T& e) {
    if(r == nullptr or r->getData() == e){
        return r;
    }else{
        if(e < r->getData()){
            return findData(r->getLeft(), e);
        }else{
            return findData(r->getRight(), e);
        }
    }
}

template <class T>
T& BTree<T>::retrieve(Node<T>*& r) {
    if(r == nullptr){
        throw BTreeException("Posicion invalida al recuperar");
    }

    return r->getData();
}

template <class T>
Node<T>*& BTree<T>::getLowest() {
    return getLowest(root);
}

template <class T>
Node<T>*& BTree<T>::getLowest(Node<T>*& r) {
    if(r == nullptr or r->getLeft() == nullptr){
        return r;
    }else{
        return getLowest(r->getLeft());
    }
}

template <class T>
Node<T>*& BTree<T>::getHighest() {
    return getHighest(root);
}

template <class T>
Node<T>*& BTree<T>::getHighest(Node<T>*& r) {
    if(r == nullptr or r->getRight() == nullptr){
        return r;
    }else{
        return getHighest(r->getRight());
    }
}

template <class T>
unsigned BTree<T>::getHeight() {
    return getHeight(root);
}

template <class T>
unsigned BTree<T>::getHeight(Node<T>*& r) {
    if(r == nullptr){
        return 0;
    }else{
        unsigned leftH = getHeight(r->getLeft());
        unsigned rightH = getHeight(r->getRight());

        if(leftH > rightH){
            return leftH + 1;
        }else{
            return rightH + 1;
        }
    }
}

template <class T>
void BTree<T>::preorder() {
    preorder(root);
}

template <class T>
void BTree<T>::preorder(Node<T>*& r) {
    if(r == nullptr){
        return;
    }
    std::cout << r->getData() << ", ";
    preorder(r->getLeft());
    preorder(r->getRight());
}

template <class T>
void BTree<T>::inorder() {
    inorder(root);
}

template <class T>
void BTree<T>::inorder(Node<T>*& r) {
    if(r == nullptr){
        return;
    }

    inorder(r->getLeft());
    std::cout << r->getData() << ", ";
    inorder(r->getRight());
}

template <class T>
void BTree<T>::postorder() {
    postorder(root);
}

template <class T>
void BTree<T>::postorder(Node<T>*& r) {
    if(r == nullptr){
        return;
    }

    postorder(r->getLeft());
    postorder(r->getRight());
    std::cout << r->getData() << ", ";
}

template <class T>
void BTree<T>::deleteAll() {
    deleteAll(root);

    root = nullptr;
}

template <class T>
void BTree<T>::deleteAll(Node<T>*& r) {
    if(r == nullptr){
        return;
    }

    deleteAll(r->getLeft());
    deleteAll(r->getRight());

    delete r;
}


#endif // BTREE_H_INCLUDED
