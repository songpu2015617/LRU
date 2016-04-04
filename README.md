# LRU
What is LRU?

Least Recently Used (LRU) is a family of caching algorithms, which discards the least recently used items first. This algorithm requires keeping track of when the item was used, which is expensive if one wants to make sure the algorithm always discards the least recently used item. General implementations of this technique require keeping "age bits" for cache-lines and track the "Least Recently Used" cache-line based on age-bits.

Data Structure

The key data structure of the algorithm is the combination of Hash Map and Doubly-Linked List. We initialize a Hash Map in a pre-defined size to store pairs, and use Doubly-Linked List to index the pairs in the order of data age.

Maintain the Cache

Once the data with key K is queried, the function get(K) is first called. If the data of key K is in the cache, the cache just returns the data and refresh the data in the linked list. To refresh data T in the list, we move the item of data T to the head of the list. Otherwise, if the data T of key K is not in the cache, we need to insert the pair into the list. If the cache is not full, we insert into the hash map, and add the item at the head of the list. If the cache is already full, we get the tail of the list and update it with , then move this item to the head of the list.
