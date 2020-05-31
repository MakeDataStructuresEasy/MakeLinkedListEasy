// { Driver Code Starts

#include <bits/stdc++.h>
using namespace std;


 // } Driver Code Ends



// design the class:
class Node{
    public: 
        int key, val;
        Node * prev, *next;
        Node(int key, int val){
            this->key = key;
            this->val = val;
            this->prev = NULL;
            this->next = NULL;
        }
};

class LRUCache{
    public:
        Node *front, *rear;
        unordered_map < int, Node* > cache;
        int maxCap;
        
        void addNodeAtFront(Node* node){
            if(node == NULL) return;
            
            if(front == NULL){
                front = node;
                rear = front;
            }else{
                node -> next = front;
                front -> prev = node;
                front = node;
            }
        }
        
        void detachNode(Node* node){
            if(node == NULL) return;
            if(front == rear){
                front = rear = NULL;
                return;
            }
            
            if(node -> prev != NULL){
                node -> prev ->next = node -> next;
            }else{
                front = node->next;
            }
            if(node -> next != NULL){
                node -> next ->prev = node -> prev;
            }else{
                rear = node->prev;
            }
            node -> prev = NULL;
            node -> next = NULL;
        }
        
        void deleteRearNode(){
            if(rear == NULL) return;
            if(rear == front){
                delete rear;
                rear = front = NULL;
            }else{
                Node* temp = rear;
                rear = rear->prev;
                rear->next =  NULL;
                delete temp;
            }
        }
        

        LRUCache(int cap){   
            front = NULL;
            rear = NULL;
            maxCap = cap;
        }
    
        int get(int key){
            if(cache.find(key) == cache.end())
                return -1;
            Node * node = cache[key];
            detachNode(node);
            addNodeAtFront(node);
            return node -> val;
        }
    
        void set(int key, int val){
            Node * node;
            if(cache.find(key) == cache.end()){
                node = new Node(key,val);
            
                if( maxCap == cache.size()){
                    cache.erase(rear->key);
                    deleteRearNode();
                }
                cache[key] = node;
                addNodeAtFront(node);
            }else{
        
                node = cache[key];
                node->val = val;
                detachNode(node);
                addNodeAtFront(node);
            }
    
        }
};

// { Driver Code Starts.

int main()
{
    int t;
    cin >> t;
    while (t--)
    {

        int capacity;
        cin >> capacity;
        LRUCache *cache = new LRUCache(capacity);
        
        int queries;
        cin >> queries;
        while (queries--)
        {
            string q;
            cin >> q;
            if (q == "SET")
            {
                int key;
                cin >> key;
                int value;
                cin >> value;
                cache->set(key, value);
            }
            else
            {
                int key;
                cin >> key;
                cout << cache->get(key) << " ";
            }
        }
        cout << endl;
    }
    return 0;
}
  // } Driver Code Ends
