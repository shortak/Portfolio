#ifndef LL_H
#define LL_H

class SList {
    protected:
        struct SNode {
            int value;
            SNode* next;
            SNode(int value) : value(value), next(nullptr) {}
        };
        SNode* head;
    public:
        SList() : head(nullptr) {};
        virtual ~SList();
        virtual bool placeFront(int value);
        virtual bool insertNode(size_t idx, int value, std::string mode = "after_idx");
        virtual bool search(int value);
        //virtual void traverse(); // ONLY USE IF YOU HAVE A CURSOR BUILT INTO THE LIST OBJECT 
        virtual bool deleteNode(int value);
        virtual void printList();
        virtual bool placeBack(int value);
        virtual void findKthFromEnd(int K);
        virtual bool reverseList();
};

class DList : public SList {
    protected:
        struct DNode : public SNode {
            DNode* prev;
            DNode(int value) : SNode(value), prev(nullptr) {};
        };
        DNode* tail;

    public:
        DList() : SList(), tail(nullptr) {}
        ~DList();

        //void insertNode(int value) override;
        bool search(int value) override;
        //void traverse() override;
        bool deleteNode(int value) override;
        void printList();
};


#endif