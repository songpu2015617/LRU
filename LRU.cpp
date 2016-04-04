//
//  test.cpp
//  
//
//  Created by Pu Song on 10/28/15.
//
//
/*************************************************************************************************************
What is LRU?

Least Recently Used (LRU) is a family of caching algorithms, which discards the least recently used items first. This algorithm requires keeping track of when the item was used, which is expensive if one wants to make sure the algorithm always discards the least recently used item. General implementations of this technique require keeping "age bits" for cache-lines and track the "Least Recently Used" cache-line based on age-bits.

Data Structure

The key data structure of the algorithm is the combination of Hash Map and Doubly-Linked List. We initialize a Hash Map in a pre-defined size to store pairs, and use Doubly-Linked List to index the pairs in the order of data age.
***********************************************************************************************************/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class LRUCache{
public:
    struct LRUCacheEntry
    {
        int key;
        int data;
        LRUCacheEntry* prev;
        LRUCacheEntry* next;
    };
    
    unordered_map<int, LRUCacheEntry*>	_mapping;
    vector<LRUCacheEntry*>		_freeEntries;
    LRUCacheEntry*			head;
    LRUCacheEntry*			tail;
    LRUCacheEntry*			entries;
    
    LRUCache(int capacity) {
        entries = new LRUCacheEntry[capacity];
        for (int i=0; i<capacity; i++)
            _freeEntries.push_back(entries+i);
        head = new LRUCacheEntry();
        tail = new LRUCacheEntry();
        head->prev = NULL;
        head->next = tail;
        tail->next = NULL;
        tail->prev = head;
    }
    
    ~LRUCache()
    {
        delete head;
        delete tail;
        delete [] entries;
    }
    
    int get(int key) {
        LRUCacheEntry* node = _mapping[key];
        // If the key exists
        if(node)
        {
            detach(node);
            attach(node);
            return node->data;
        }
        else return -1;
    }
    
    void set(int key, int value) {
        LRUCacheEntry* node = _mapping[key];
        if(node)
        {
            // refresh the link list
            detach(node);
            node->data = value;
            attach(node);
        }
        else{
            if ( _freeEntries.empty() )
            {
                // Get the last node
                node = tail->prev;
                // Remove the key from the hash map
                _mapping.erase(node->key);
                // Update the node
                node->data = value;
                node->key = key;
                // Move the node to the head
                detach(node);
                attach(node);
                // Update the hash map
                _mapping[key] = node;
            }
            else{
                // Get the free entry
                node = _freeEntries.back();
                _freeEntries.pop_back();
                // Fill the node with key and value
                node->key = key;
                node->data = value;
                // Move the node to the head
                attach(node);
                // Update the hash map
                _mapping[key] = node;
            }
        }
    }
    
private:
    void detach(LRUCacheEntry* node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    void attach(LRUCacheEntry* node)
    {
        node->next = head->next;
        node->prev = head;
        head->next = node;
        node->next->prev = node;
    }
};