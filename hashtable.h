#include "lista.h"
#include <algorithm>
#include <functional>
#include <vector>
template <typename K, typename T> 
class HashPair {
public:
    K key;
    T value;
    HashPair(K key, T value) {
        this->key = key;
        this->value = value;
    }
    HashPair() {}
};

template <typename K, typename T> class Hashtable {
private:
    int size;
    LinkedList<HashPair<K, T>> *tabla;
    int fh(K key) const {
        hash<K> khash;
        return khash(key) % size;
    }

public:
    Hashtable(int size = 23000) {
        this->size = size;
        tabla = new LinkedList<HashPair<K, T>>[size];
        for (int i = 0; i < size; i++) {
			tabla[i] = LinkedList<HashPair<K, T> *>();
		}
    }
    int elementsSize() const {
        int n = 0;
        for (int i = 0; i < size; i++) {
            n += tabla[i].size();
        }
        return n;
    }
    bool put(K key, T value) {
        int posicion = fh(key);
        LinkedList<HashPair<K, T>> lista = tabla[posicion];
        int indice = -1;
        for (int i = 0; i < lista.size(); i++) {
            if (lista.get(i).key == key) {
                indice = i;
            }
        }
        if(indice >=0){
            lista.get(indice)->value = value;
        } else {
            tabla[posicion].addLast(HashPair<K, T>(key, value));
        }
        return (indice >= 0) ? 0 : 1;
    }
    //Complejidad: O(n^2)
    T getOrDefault(K key, const T DEFAULT_VALUE) const {
        int posicion = fh(key);
        LinkedList<HashPair<K, T>*> lista = tabla[posicion];
        int indice = -1;
        for (int i = 0; i < lista.size(); i++) {
            if (lista.get(i).key == key)
                return lista.get(i).value;
        }
        return DEFAULT_VALUE;
    }
    bool remove(K key) {
        int posicion = fh(key);
        LinkedList<HashPair<K, T>> &lista = tabla[posicion];
        if (lista.is_empty())
            return false;
        int i = 0;
        /*while (lista.get(i).key != key) {
        if (i++ >= lista.size())
            return false;
        }*/ 
        for (int i = 0; i < lista.size(); i++) {
            if (lista.get(i).key == key) {
                lista.remove(i);
                return true;
            }
        }
        return false;
    }
    bool is_empty() {
		return tabla->is_empty();
	}
    //Complejidad: O(n^2)
    bool contains(K key) const {
        int posicion = fh(key);
        LinkedList<HashPair<K, T> *> lista = tabla[posicion];
        int indice = -1;
        for (int i = 0; i < lista.size(); i++) {
            if (lista.get(i).key == key) {
            indice = i;
            }
        }
        return (indice == -1) ? 0 : 1;
    }
    LinkedList<K> keys() const {
        vector<K> ks;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < tabla[i].size(); j++) { //O(n^2)
                K key = tabla[i].get(j).key;
                if (!count(ks.begin(), ks.end(), key))
                    ks.push_back(key);
            }
        }
        sort(ks.begin(), ks.end());
        LinkedList<K> kays;
        while (!ks.empty()) {
            kays.addFirst(ks.back());
            ks.pop_back();
        }
        return kays;
    }
    friend ostream &operator<<(ostream &out, const Hashtable &h) {
        LinkedList<K> ks = h.keys();
        while (!ks.is_empty()) {
            K key = ks.remove_front();
            int pos = h.fh(key);
            out << "____\t" << key << "\t____\n";
            for (int i = 0; i < h.tabla[pos].size(); i++) {
                if (h.tabla[pos].get(i).key == key) {
                    T p = h.tabla[pos].get(i).value;
                    out << p << "\n";
                }
            }
        }
        return out;
    }
    void printSizeKeys() {
        LinkedList<K> ks = keys();
        while (!ks.is_empty()) {
            K key = ks.remove_front();
            int pos = fh(key), count = 0;
            cout << "-\t" << key << ": ";
            for (int i = 0; i < tabla[pos].size(); i++) {
                if (tabla[pos].get(i).key == key)
                    count++;
            }
            cout << count << "\n";
        }
    }
    int hashSize() {
		int nElements = 0;
		for (int i = 0; i < size; i++) {
			nElements += tabla[i].size();
		}
		return nElements;
	}
};