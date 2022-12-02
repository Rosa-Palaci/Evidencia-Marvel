#include <iostream>
using namespace std;

template <typename T> class AVL {
private:
    Nodo<T> *root;
    int _length;

    void insert(Nodo<T> *&nodo, T dato) {
        if (!nodo) // O(1)
        {
            nodo = new Nodo<T>(dato);   // O(1)
            balance();
        } else if (dato < nodo->data) // O(1)
        {
            insert(nodo->left, dato);   // O(n)
        } else if (dato > nodo->data) // O(1)
        {
        insert(nodo->right, dato); // O(n)
        }
    }

    void inOrden(Nodo<T> *&nodo) {
        if (nodo) // O(1)
        {
            inOrden(nodo->left);                  // O(n)
            cout << " | " << nodo->data << " | "; // O(1)
            inOrden(nodo->right);                 // O(n)
        }
    }

    ostream &print(Nodo<T> *&nodo, ostream &out) {
        if (nodo) // O(1)
        {
            print(nodo->left, out);              // O(n)
            out << " | " << nodo->data << " | "; // O(1)
            print(nodo->right, out);             // O(n)
        }
        return out;
    }

    void preOrden(Nodo<T> *&nodo) {
        if (nodo) {
            cout << " | " << nodo->data << " | "; // O(1)
            preOrden(nodo->left);                 // O(n)
            preOrden(nodo->right);                // O(n)
        }
    }

    void postOrden(Nodo<T> *&nodo) {
        if (nodo) // O(1)
        {
            postOrden(nodo->left);                 // O(n)
            postOrden(nodo->right);                // O(n)
            cout << " | " << nodo->data << " | "; // O(1)
        }
    }

    void inNotOrden(Nodo<T> *&nodo) {
        if (nodo) // O(1)
        {
            inNotOrden(nodo->right);              // O(n)
            cout << " | " << nodo->data << " | "; // O(1)
            inNotOrden(nodo->left);               // O(n)
        }
    }

    bool contains(Nodo<T> *&nodo, T dato) {
        if (!nodo)             // O(1)
            return false;        // O(1)
        if (dato < nodo->data) // O(1)
        {
            return contains(nodo->left, dato); // O(n)
        } else if (dato > nodo->data)        // O(1)
        {
            return contains(nodo->right, dato); // O(n)
        }
        return true; // O(1)
    }

    T max(Nodo<T> *&nodo) {
        if (!nodo->right)        // O(1)
            return nodo->data;     // O(1)
        return max(nodo->right); // O(n)
    }

    T min(Nodo<T> *&nodo) {
        if (!nodo->left)        // O(1)
            return nodo->data;    // O(1)
        return min(nodo->left); // O(n)
    }

    int lengthRec(Nodo<T> *&nodo) {
        if (!nodo)
            return 0;
        int n = 1;
        return 1 + lengthRec(nodo->left) + lengthRec(nodo->right);
    }

    bool remove(Nodo<T> *&nodo, T dato) {
        if (!contains(nodo, dato))
            return 0;
        if (dato < nodo->data) // O(1)
        {
        return remove(nodo->left, dato); // O(n)
        } else if (dato > nodo->data)      // O(1)
        {
        return remove(nodo->right, dato); // O(n)
        } else {
            if (!nodo->right && !nodo->left) {
            nodo = nullptr;
            return true;
            /*Borra nodo y regresa true*/
        }
        /* Obtén el left de nodo.
        Asigna a temp el nodo.
        Asigna a nodo el left
        Borra temp y regresa true*/
        else if (!nodo->right && nodo->left) {
            Nodo<T> *&temp = nodo->left;
            nodo = nodo->left;
            temp = nullptr;
            return true;
        }
        /* Obtén el right de nodo.
        Asigna a temp el nodo.
        Asigna a nodo el right
        Borra temp y regresa true*/
        else if (nodo->right && !nodo->left) {
            Nodo<T> *&temp = nodo->right;
            nodo = nodo->right;
            temp = nullptr;
            return true;
        } else {
            auto temp = nodo->right;
            while (temp->left)
            temp = temp->left;
            nodo->data = temp->data;
            remove(nodo->right, temp->data);
        }
        }
    }
    
    int height(Nodo<T> *&nodo) const {
        if (!nodo)
            return -1;
        int leftHeight = height(nodo->left);
        int rightHeight = height(nodo->right);
        return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }


    void balance(Nodo<T> *&nodo){
        if (getBalanceFactor(nodo) > 1)       // O(1)
        {
            
            if (getBalanceFactor(nodo->right) == 1) // O(1)
            {
                rotateRight(nodo); 
            }
            
            else if (getBalanceFactor(nodo->right) == -1) // O(1)
            {
                rotateDoubleRight(nodo);// O(1)
            }

            else{
                balance(nodo->right); // O log(n)
            }
            
        }else if (getBalanceFactor(nodo) < -1) // O(1)
        {
            
            if (getBalanceFactor(nodo->left) == 1) // O(1)
            {
                rotateDoubleLeft(nodo); // O(1)
            }
            
            else if (getBalanceFactor(nodo->left) == -1) // O(1)
            {
                rotateLeft(nodo); // O(1)
            }
            
            else{
                balance(nodo->left); // O log(n)
            }
            

        } 
    }

    int getBalanceFactor(Nodo<T> *&nodo){
        if (nodo == NULL) // O(1)
        {
            return 0;
        }
        return height(nodo->right) - height(nodo->left); // O log(n)
    }

    void rotateLeft(Nodo<T> *&nodo){

        Nodo<T> *aux = nodo->left; // O(1)
        nodo->left = aux->right; // O(1)
        aux->right = nodo;       // O(1)

        nodo = aux; // O(1)

    }

    void rotateRight(Nodo<T> *&nodo){
        
        Nodo<T> *aux = nodo->right; // O(1)
        nodo->right = aux->left; // O(1)
        aux->left = nodo;      // O(1) 

        nodo = aux; // O(1)
    }

    void rotateDoubleLeft(Nodo<T> *&nodo){
        Nodo<T> *aux = nodo->left; // O(1)
        Nodo<T> *aux2 = aux->right; // O(1)

        nodo->left = aux2; // O(1)
        aux->right = aux2->right; // O(1)
        aux2->left = aux; // O(1)
            
        return rotateLeft(nodo); // O(1)
    }

    Nodo<T> rotateDoubleRight(Nodo<T> *&nodo){
        Nodo<T> *aux = nodo->right; // O(1)
        Nodo<T> *aux2 = aux->left; // O(1)

        nodo->right = aux2; // O(1)
        aux->left = aux2->left; // O(1)
        aux2->right = aux; // O(1)        
        rotateRight(nodo); // O(1)
    }

public:

    AVL() {
        root = nullptr; // O(1)
        _length = 0;    // O(1)
    }
    
    void insert(T dato) {
        _length++;      // O(1)
        if (is_empty()) // O(1)
        {
            root = new Nodo<T>(dato); // O(1)
        } else {
            insert(root, dato); // O(n)
        }
    }
    
    bool is_empty() {
        return !root; // O(1)
    }

    void inOrden() {
        inOrden(root); // O(n)
    }
    
    void preOrden() {
        preOrden(root); // O(n)
    }

    void postOrden() {
        postOrden(root); // O(n)
    }

    void inNotOrden() {
        inNotOrden(root); // O(n)
    }
    
    bool contains(T dato) { return contains(root, dato); }

    int length() { return _length; }

    T max() { return max(root); }

    T min() { return min(root); }

    int lengthRec() {
        return lengthRec(root); 
    }
    
    bool remove(T dato) { return remove(root, dato); }

    T getroot() { return root->data; }

    int height() const { return height(root); }

    void balance(){
        balance(root);
    }

    friend ostream &operator<<(ostream &out, AVL<T> &avl) {
        return avl.print(avl.root, out);
    }
    };