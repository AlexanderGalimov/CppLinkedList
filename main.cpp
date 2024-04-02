#include <iostream>
#include <cassert>

using namespace std;

template<class T>
class ListNode {
private:
    ListNode *prev;
    ListNode *next;
    T value;

public:
    ListNode(ListNode *prev, ListNode *next, T value) : prev(prev), next(next), value(value) {}

    ListNode *getPrev() const {
        return prev;
    }

    ListNode *getNext() const {
        return next;
    }

    T getValue() const {
        return value;
    }

    void setPrev(ListNode *newNode) {
        ListNode::prev = newNode;
    }

    void setNext(ListNode *newNode) {
        ListNode::next = newNode;
    }

    void setValue(T newValue) {
        ListNode::value = newValue;
    }

    void toString() {
        cout << value;
    }
};

template<class T>
class DoublyLinkedList {
private:
    ListNode<T> *head = nullptr;
    ListNode<T> *tail = nullptr;
    int size = 0;

public:
    virtual ~DoublyLinkedList() {
        while (head != nullptr) {
            ListNode<T> *temp = head;
            head = head->getNext();
            delete temp;
        }
        tail = nullptr;
    }

    void prepend(ListNode<T> *nodeToAppend) {
        if (head == nullptr) {
            head = nodeToAppend;
            tail = head;
        } else {
            head->setPrev(nodeToAppend);
            nodeToAppend->setNext(head);
            head = nodeToAppend;
        }
        size++;
    }

    void appendToTail(ListNode<T> *nodeToAppend) {
        if (head == nullptr) {
            head = nodeToAppend;
            tail = head;
        } else {
            tail->setNext(nodeToAppend);
            nodeToAppend->setPrev(tail);
            tail = nodeToAppend;
        }
        size++;
    }

    void append(int index, ListNode<T> *nodeToAdd) {
        if (index == size) {
            appendToTail(nodeToAdd);
            return;
        }

        ListNode<T> *findNode = findByIndex(index);
        if (findNode == head || findNode == nullptr) {
            prepend(nodeToAdd); // Если узел не найден или он равен head, добавляем узел в начало
        } else {
            ListNode<T> *findPrev = findNode->getPrev();
            findPrev->setNext(nodeToAdd);
            nodeToAdd->setPrev(findPrev);
            nodeToAdd->setNext(findNode);
            findNode->setPrev(nodeToAdd);
        }
        size++;
    }

    bool setValue(int index, T value){
        ListNode<T>* node = findByIndex(index);
        if(node){
            node->setValue(value);
            return true;
        }
        else{
            return false;
        }
    }

    int getSize() const {
        return size;
    }

    ListNode<T> *findByIndex(int index) {
        if (head == nullptr) {
            return nullptr;
        }
        int currIndex = 0;
        ListNode<T> *currNode = head;
        while (true) {
            if (currNode == nullptr) {
                return nullptr;
            }
            if (currIndex == index) {
                return currNode;
            }
            if (currIndex > index) {
                return nullptr;
            }
            currNode = currNode->getNext();
            currIndex++;
        }
    }

    bool removeFirst() {
        if (head == nullptr) {
            return false;
        } else if (size == 1) {
            delete head;
            head = tail = nullptr;
        } else {
            ListNode<T> *next = head->getNext();
            next->setPrev(nullptr);
            delete head;
            head = next;
        }
        size--;
        return true;
    }

    bool removeLast() {
        if (head == nullptr) {
            return false;
        } else if (size == 1) {
            delete tail;
            tail = head = nullptr;
        } else {
            ListNode<T> *prev = tail->getPrev();
            prev->setNext(nullptr);
            delete tail;
            tail = prev;
        }
        size--;
        return true;
    }

    bool removeByIndex(int index) {
        if (head == nullptr) {
            return false;
        }
        if (head->getNext() == nullptr && index == 0) {
            delete head;
            head = tail = nullptr;
            size--;
            return true;
        } else {
            ListNode<T> *node = findByIndex(index);
            if (node) {
                ListNode<T> *prev = node->getPrev();
                ListNode<T> *next = node->getNext();
                prev->setNext(next);
                next->setPrev(prev);
                delete node;
                size--;
                return true;
            } else {
                return false;
            }
        }
    }

    ListNode<T> *getHead() const {
        return head;
    }

    ListNode<T> *getTail() const {
        return tail;
    }

    void toString() {
        ListNode<T> *node = head;
        cout << "[ ";
        while (node != nullptr) {
            node->toString();
            node = node->getNext();
            cout << " ";
        }
        cout << "]";
    }
};

class DoublyLinkedListTester {
public:
    static void runTests() {
        testAppendToTail();
        testPrepend();
        testAppend();
        testFindByIndex();
        testRemoveFirst();
        testRemoveLast();
        testRemoveByIndex();
        testSetValue();
    }

private:
    static void testAppendToTail() {
        cout << "---Test append to tail---" << endl;
        DoublyLinkedList<int> linkedList;
        auto *listNode = new ListNode<int>(nullptr, nullptr, 30);
        linkedList.appendToTail(listNode);
        cout << "result: ";
        linkedList.toString();
        cout << "\n" << endl;
        assert(linkedList.getSize() == 1);
        assert(linkedList.getTail()->getValue() == 30);
    }

    static void testPrepend() {
        cout << "---Test prepend---" << endl;
        DoublyLinkedList<int> linkedList;
        auto *listNode1 = new ListNode<int>(nullptr, nullptr, 10);
        auto *listNode2 = new ListNode<int>(nullptr, nullptr, 20);
        linkedList.prepend(listNode1);
        linkedList.prepend(listNode2);
        cout << "result: ";
        linkedList.toString();
        cout << "\n" << endl;
        assert(linkedList.getSize() == 2);
        assert(linkedList.getHead()->getValue() == 20);
        assert(linkedList.getTail()->getValue() == 10);
    }

    static void testAppend() {
        cout << "---Test append---" << endl;
        DoublyLinkedList<int> linkedList;
        auto *listNode1 = new ListNode<int>(nullptr, nullptr, 10);
        auto *listNode2 = new ListNode<int>(nullptr, nullptr, 20);
        auto *listNode3 = new ListNode<int>(nullptr, nullptr, 30);
        linkedList.prepend(listNode1);
        linkedList.append(1, listNode2);
        linkedList.append(2, listNode3);
        cout << "result: ";
        linkedList.toString();
        cout << "\n" << endl;
        assert(linkedList.getSize() == 3);
        assert(linkedList.getTail()->getValue() == 30);
        assert(linkedList.getHead()->getNext()->getValue() == 20);
        assert(linkedList.getHead()->getNext()->getNext()->getValue() == 30);
    }

    static void testFindByIndex() {
        cout << "---Test find by index---" << endl;
        DoublyLinkedList<int> linkedList;
        auto *listNode1 = new ListNode<int>(nullptr, nullptr, 10);
        auto *listNode2 = new ListNode<int>(nullptr, nullptr, 20);
        linkedList.prepend(listNode1);
        linkedList.prepend(listNode2);
        ListNode<int> *foundNode = linkedList.findByIndex(1);
        cout << "found node: ";
        foundNode->toString();
        cout << "\n" << endl;
        assert(foundNode->getValue() == 10);
    }

    static void testRemoveFirst() {
        cout << "---Test remove first---" << endl;
        DoublyLinkedList<int> linkedList;
        auto *listNode1 = new ListNode<int>(nullptr, nullptr, 10);
        auto *listNode2 = new ListNode<int>(nullptr, nullptr, 20);
        linkedList.prepend(listNode1);
        linkedList.prepend(listNode2);
        linkedList.removeFirst();
        cout << "result: ";
        linkedList.toString();
        cout << "\n" << endl;
        assert(linkedList.getSize() == 1);
        assert(linkedList.getHead()->getValue() == 10);
    }

    static void testRemoveLast() {
        cout << "---Test remove last---" << endl;
        DoublyLinkedList<int> linkedList;
        auto *listNode1 = new ListNode<int>(nullptr, nullptr, 10);
        auto *listNode2 = new ListNode<int>(nullptr, nullptr, 20);
        linkedList.prepend(listNode1);
        linkedList.prepend(listNode2);
        linkedList.removeLast();
        cout << "result: ";
        linkedList.toString();
        cout << "\n" << endl;
        assert(linkedList.getSize() == 1);
        assert(linkedList.getTail()->getValue() == 20);
    }

    static void testRemoveByIndex() {
        cout << "---Test remove by index---" << endl;
        DoublyLinkedList<int> linkedList;
        auto *listNode1 = new ListNode<int>(nullptr, nullptr, 10);
        auto *listNode2 = new ListNode<int>(nullptr, nullptr, 20);
        auto *listNode3 = new ListNode<int>(nullptr, nullptr, 30);
        linkedList.prepend(listNode1);
        linkedList.prepend(listNode2);
        linkedList.prepend(listNode3);
        linkedList.removeByIndex(1);
        cout << "result: ";
        linkedList.toString();
        cout << "\n" << endl;
        assert(linkedList.getSize() == 2);
        assert(linkedList.getHead()->getValue() == 30);
    }

    static void testSetValue() {
        cout << "---Test set value---" << endl;
        DoublyLinkedList<int> linkedList;
        auto* listNode1 = new ListNode<int>(nullptr, nullptr, 10);
        auto* listNode2 = new ListNode<int>(nullptr, nullptr, 20);
        linkedList.prepend(listNode1);
        linkedList.prepend(listNode2);

        bool result = linkedList.setValue(1, 30);
        cout << "result: ";
        linkedList.toString();
        cout << "\n" << endl;

        assert(result == true);
        assert(linkedList.findByIndex(1)->getValue() == 30);

        result = linkedList.setValue(3, 40);

        assert(result == false);
    }
};

int main() {
    DoublyLinkedListTester::runTests();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
