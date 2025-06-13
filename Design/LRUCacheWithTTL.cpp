🧭 What is TTL (Time To Live)?
TTL (Time To Live) is a mechanism that limits how long data (like a cache entry or network packet) is valid or allowed to exist.

💡 In Caching (like LRUCache):
TTL defines how long a key-value pair should stay in the cache, even if it's not evicted by capacity constraints.

✅ How It Works:
Each cache entry has a timestamp or expiration time.

When you get(key):

You check if the current time exceeds the key's TTL.

If yes, the entry is considered expired and treated as not present.

When you put(key, value):

You also set a TTL duration (e.g., 60 seconds).

📦 Example:
cpp
Copy
Edit
put("A", 100, ttl=60)  // store key A with value 100 for 60 seconds
Now, 59 seconds later: get("A") → returns 100 ✅

After 61 seconds: get("A") → returns -1 ❌ (expired)

🔁 Why TTL is Useful in Caches:
Benefit	Explanation
⏰ Prevents stale data	Ensures outdated values are not returned
💾 Controls memory usage	Expired data can be cleaned up over time
🌐 Common in DNS, CDNs	TTL avoids constant re-fetching from the source

🧠 TTL vs LRU
Aspect	TTL	LRU
Based on	Time (expiration)	Access pattern (recentness)
Entry removed	When time expires	When cache exceeds capacity
Use case	Time-sensitive data (e.g., DNS, API)	Memory-constrained caching
Can combine?	✅ Yes — LRU+TTL hybrid caches exist	✅ Better control over data lifecycle


=========================================================================
  #include <unordered_map>
#include <chrono>
using namespace std;
using namespace std::chrono;

class LRUCache {
private:
    struct Node {
        int key;
        int val;
        time_point<steady_clock> expiry;  // Expiration time
        Node* prev;
        Node* next;

        Node(int k, int v, int ttl_secs)
            : key(k), val(v), prev(nullptr), next(nullptr)
        {
            expiry = steady_clock::now() + seconds(ttl_secs);
        }

        bool isExpired() const {
            return steady_clock::now() > expiry;
        }
    };

    int capacity;
    unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;

    void addToFront(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(Node* node) {
        Node* prev = node->prev;
        Node* next = node->next;
        prev->next = next;
        next->prev = prev;
    }

    void moveToFront(Node* node) {
        removeNode(node);
        addToFront(node);
    }

    void deleteNode(Node* node) {
        removeNode(node);
        cache.erase(node->key);
        delete node;
    }

public:
    LRUCache(int cap) {
        capacity = cap;
        head = new Node(0, 0, 0);  // dummy node
        tail = new Node(0, 0, 0);  // dummy node
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            if (node->isExpired()) {
                deleteNode(node);
                return -1;
            }
            moveToFront(node);
            return node->val;
        }
        return -1;
    }

    void put(int key, int value, int ttl_seconds) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            if (node->isExpired()) {
                deleteNode(node);
            } else {
                node->val = value;
                node->expiry = steady_clock::now() + seconds(ttl_seconds);
                moveToFront(node);
                return;
            }
        }

        if ((int)cache.size() >= capacity) {
            Node* lru = tail->prev;
            while (lru != head && lru->isExpired()) {
                Node* expired = lru;
                lru = lru->prev;
                deleteNode(expired);
            }

            if ((int)cache.size() >= capacity) {
                Node* toEvict = tail->prev;
                deleteNode(toEvict);
            }
        }

        Node* newNode = new Node(key, value, ttl_seconds);
        addToFront(newNode);
        cache[key] = newNode;
    }

    ~LRUCache() {
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }
};


int main() {
    LRUCache cache(2);  // capacity 2

    cache.put(1, 100, 5);  // key=1, val=100, TTL=5s
    cache.put(2, 200, 3);  // key=2, val=200, TTL=3s

    cout << cache.get(1) << endl;  // returns 100

    this_thread::sleep_for(chrono::seconds(4));

    cout << cache.get(2) << endl;  // returns -1 (expired)
    cout << cache.get(1) << endl;  // returns 100 (still valid)

    cache.put(3, 300, 5);  // evicts key=2, inserts key=3
}


