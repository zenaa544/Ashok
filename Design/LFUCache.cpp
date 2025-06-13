Design and implement a data structure for a Least Frequently Used (LFU) cache.

Implement the LFUCache class:

LFUCache(int capacity) Initializes the object with the capacity of the data structure.
int get(int key) Gets the value of the key if the key exists in the cache. Otherwise, returns -1.
void put(int key, int value) Update the value of the key if present, or inserts the key if not already present.
When the cache reaches its capacity, it should invalidate and remove the least frequently used key before inserting a new item.
  For this problem, when there is a tie (i.e., two or more keys with the same frequency), the least recently used key would be invalidated.
To determine the least frequently used key, a use counter is maintained for each key in the cache. 
The key with the smallest use counter is the least frequently used key.

When a key is first inserted into the cache, its use counter is set to 1 (due to the put operation). 
The use counter for a key in the cache is incremented either a get or put operation is called on it.

The functions get and put must each run in O(1) average time complexity.


class LFUCache {
private:
struct Node {
        int key, val, freq;
        Node* prev;
        Node* next;
        Node(int k, int v) : key(k), val(v), freq(1), prev(nullptr), next(nullptr) {}
    };

    struct List {
        Node* head;
        Node* tail;

        List() {
            head = new Node(-1, -1);
            tail = new Node(-1, -1);
            head->next = tail;
            tail->prev = head;
        }

        void addToFront(Node* node) {
            node->next = head->next;
            head->next->prev = node;
            head->next = node;
            node->prev = head;
        }

        void removeNode(Node* node) {
            Node* prevNode = node->prev;
            Node* nextNode = node->next;
            prevNode->next = nextNode;
            nextNode->prev = prevNode;
        }

        bool isListEmpty() const {
            return head->next == tail;
        }

        ~List() {
            Node* current = head;
            while (current) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }
    };

    int capacity;
    int size;
    int minFreq;
    unordered_map<int, Node*> keyToNode;
    unordered_map<int, List*> freqList;

    void updateFreq(Node* node) {
        int freq = node->freq;
        freqList[freq]->removeNode(node);

        // Clean up old freq list if empty
        if (freqList[freq]->isListEmpty()) {
            delete freqList[freq];
            freqList.erase(freq);
            if (minFreq == freq) {
                minFreq++;
            }
        }

        node->freq++;
        if (freqList.find(node->freq) == freqList.end()) {
            freqList[node->freq] = new List();
        }
        freqList[node->freq]->addToFront(node);
    }

    void removeLRUNode() {
        Node* lru = freqList[minFreq]->tail->prev;
        freqList[minFreq]->removeNode(lru);

        if (freqList[minFreq]->isListEmpty()) {
            delete freqList[minFreq];
            freqList.erase(minFreq);
        }

        keyToNode.erase(lru->key);
        delete lru;
        size--;
    }

public:
    LFUCache(int capacity) : capacity(capacity), size(0), minFreq(0) {}

    int get(int key) {
        if (keyToNode.find(key) == keyToNode.end())
            return -1;

        Node* node = keyToNode[key];
        updateFreq(node);
        return node->val;
    }

    void put(int key, int value) {
        if (capacity == 0) return;

        if (keyToNode.find(key) != keyToNode.end()) {
            Node* node = keyToNode[key];
            node->val = value;
            updateFreq(node);
        } else {
            if (size == capacity) {
                removeLRUNode();
            }
            Node* node = new Node(key, value);
            keyToNode[key] = node;
            if (freqList.find(1) == freqList.end()) {
                freqList[1] = new List();
            }
            freqList[1]->addToFront(node);
            minFreq = 1;
            size++;
        }
    }

    ~LFUCache() {
   keyToNode.clear();  // Just clear map

    for (auto& [_, list] : freqList) {
        delete list;  // Each list will delete its nodes
    }
    freqList.clear();
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

=========================

  GPT Solution
Perfect! You're asking for an LFU cache in C++ with:

✅ Full implementation

✅ O(1) get() and put() time

✅ Custom implementation of a doubly-linked list node instead of std::list<Node*>::iterator

We'll build the LFU cache using:

A Node structure that contains:

key, value, frequency

Pointers to support a custom doubly linked list

A FreqList per frequency, holding a doubly linked list of Node*.

Two hash maps:

keyToNode: key → Node*

freqToList: freq → custom doubly linked list

minFreq to track the minimum frequency present in the cache.

class LFUCache {
private:
    struct Node {
        int key, value, freq;
        Node* prev;
        Node* next;
        Node(int k, int v) : key(k), value(v), freq(1), prev(nullptr), next(nullptr) {}
    };

    struct DoublyLinkedList {
        Node* head;
        Node* tail;
        DoublyLinkedList() {
            head = new Node(-1, -1);  // dummy head
            tail = new Node(-1, -1);  // dummy tail
            head->next = tail;
            tail->prev = head;
        }

        void addToFront(Node* node) {
            node->next = head->next;
            node->prev = head;
            head->next->prev = node;
            head->next = node;
        }

        void removeNode(Node* node) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }

        Node* removeLeastRecentlyUsed() {
            if (head->next == tail) return nullptr;
            Node* node = tail->prev;
            removeNode(node);
            return node;
        }

        bool isEmpty() const {
            return head->next == tail;
        }

        ~DoublyLinkedList() {
            Node* current = head;
            while (current) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }
    };

    int capacity, size, minFreq;
    unordered_map<int, Node*> keyToNode;
    unordered_map<int, DoublyLinkedList*> freqToList;

    void updateFreq(Node* node) {
        int oldFreq = node->freq;
        freqToList[oldFreq]->removeNode(node);

        if (oldFreq == minFreq && freqToList[oldFreq]->isEmpty()) {
            minFreq++;
        }

        node->freq++;
        if (freqToList.find(node->freq) == freqToList.end()) {
            freqToList[node->freq] = new DoublyLinkedList();
        }
        freqToList[node->freq]->addToFront(node);
    }

public:
    LFUCache(int capacity) : capacity(capacity), size(0), minFreq(0) {}

    int get(int key) {
        if (keyToNode.find(key) == keyToNode.end()) return -1;

        Node* node = keyToNode[key];
        updateFreq(node);
        return node->value;
    }

    void put(int key, int value) {
        if (capacity == 0) return;

        if (keyToNode.find(key) != keyToNode.end()) {
            Node* node = keyToNode[key];
            node->value = value;
            updateFreq(node);
            return;
        }

        if (size == capacity) {
            DoublyLinkedList* minList = freqToList[minFreq];
            Node* toRemove = minList->removeLeastRecentlyUsed();
            keyToNode.erase(toRemove->key);
            delete toRemove;
            size--;
        }

        Node* newNode = new Node(key, value);
        minFreq = 1;

        if (freqToList.find(1) == freqToList.end()) {
            freqToList[1] = new DoublyLinkedList();
        }

        freqToList[1]->addToFront(newNode);
        keyToNode[key] = newNode;
        size++;
    }

    ~LFUCache() {
        for (auto& pair : freqToList) {
            delete pair.second;
        }
    }
};
