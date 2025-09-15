#ifndef BTREE
#define BTREE

template <typename T, int ORDER>
class BTree {
    private:
        struct BTreeNode {
            T keys[ORDER-1];
            int t;
            BTreeNode<T>* children[ORDER];
            int n;
            bool leaf;
            BTreeNode(bool isLeaf = true) : n(0), leaf(isLeaf) {
                for (int i = 0; i < ORDER; i++)
                    children[i] = nullptr;
            }
        };

        void remove(T k) {
            remove(root, k);
            
        }

        BTreeNode<T, ORDER>* root;

    public:
        BTree() : root(nullptr) {};
        ~BTree();
        void insertNonFull(T key);
        void deleteNode(BTreeNode* node, int idx);
        T search(T key);
        T traverse();
        void splitChild(int i);
        void merge(BTreeNode* node, int idx);
        void borrow();
        void

};

#endif