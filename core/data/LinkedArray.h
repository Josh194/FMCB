#pragma once

/*
An array where nodes and empty spaces are singly linked together.

The array is split into multiple doubly linked blocks of nodes that are created/destroyed as needed.
add()/insert()/deleteNext() are O(1) operations, except when all empty spaces are filled (or two blocks worth of nodes have been deleted),
in which case time complexity is dependent on the implementation of malloc()/free().

? Would indices be fast enough for our purposes? If so, nodes could use an index instead of a pointer to reduce memory overhead,
? though we would then be limited in the max number of nodes, and add()/insert()/deleteNext() would become O(n) operations (though this could potentially be mitigated).
Memory usage is relatively efficient (two pointers per node), and cache locality is good (when treated as an array). The list can also be looped over like an array.

'TType' specifies the type held in the list, 'TBlock' specifies the block size.
*/
// TODO: maybe overload [] operator
// TODO: maybe provide function to run code on all elements
// TODO: implement array looping functionality
// TODO: maybe move function definitions to a .inl or .cpp (does .inl hint to the compiler to no treat it as a translation unit?) file
template<class TType, unsigned int TBlock>
class LinkedArray {
// ? Could the access specifier layout be cleaned up at all?
public:
    struct Node;

private:
    // ! Bad link cache locality
    struct Block {
        Block *prev, *next;

        Node link[TBlock];
        //TType data[TBlock];
    };

    Block root;
    Node *dataHead, *emptyHead;

    unsigned int length;

public:
    struct Node {
        Node *next;
        TType data;
        // Block *block; // TODO: This could/should be improved
    };

    LinkedArray() {
        initBlock(&root);

        dataHead = &root.link[0];
        emptyHead = &root.link[0];

        length = 0;
    }

    TType* add() {
        Node *nextEmpty = emptyHead -> next;

        emptyHead -> next = dataHead -> next;
        dataHead -> next = emptyHead;

        dataHead = emptyHead;

        emptyHead = nextEmpty;

        length++;

        return &(dataHead -> data);
    }

    void deleteNext(Node *node) {
        Node *nextEmpty = node -> next;

        node -> next = nextEmpty -> next;

        nextEmpty -> next = emptyHead;
        emptyHead = nextEmpty;

        length--;
    }

    void clear() {
        // TODO: Implement

        length = 0;
    }

    inline Node* getHead() {
        return dataHead;
    }

    inline unsigned int getLength() {
        return length;
    }

private:
    void initBlock(Block* block) {
        for (unsigned int i = 0; i < TBlock; i++) {
            block -> link[i].next = &(block -> link[i + 1]); // TODO: optimize this
        }
    }

    void allocate() {
        return;
    }
};