#include <iostream>
#include <vector>

using namespace std;
//1. Structure for a Linked List Node
struct ListNode {
    int val;
    ListNode* next;

    ListNode(int x) : val(x), next(nullptr) {}
};
//2.Vector-based Min-Heap Class
class MinHeap {
private:
    vector<ListNode*> heap; 

    void swapNodes(ListNode*& a, ListNode*& b) {
        ListNode* temp = a;
        a = b;
        b = temp;
    }
    //Heapify Down: Restores Min-Heap property from top to bottom
    void minHeapify(int idx) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int n = heap.size();

        if (left < n && heap[left]->val < heap[smallest]->val) {
            smallest = left;
        }
        if (right < n && heap[right]->val < heap[smallest]->val) {
            smallest = right;
        }
        if (smallest != idx) {
            swapNodes(heap[smallest], heap[idx]);
            minHeapify(smallest);
        }
    }
public:
    //Checks if the heap has any elements left
    bool isEmpty() const {
        return heap.empty();
    }
    //Insert Node: Adds a node and bubbles it up based on its value
    void insert(ListNode* newNode) {
        if (newNode == nullptr) return;

        heap.push_back(newNode);
        int i = heap.size() - 1;

        while (i > 0 && heap[i]->val < heap[(i - 1) / 2]->val) {
            swapNodes(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
    //Extract Min: Removes and returns the node with the smallest value
    ListNode* extractMin() {
        if (heap.empty()) return nullptr;

        ListNode* minNode = heap[0];  
        heap[0] = heap.back();       
        heap.pop_back();              

        if (!heap.empty()) {
            minHeapify(0);            
        }
        return minNode;
    }
};
//3. Merge K Sorted Linked Lists using the Min-Heap
ListNode* mergeKLists(const vector<ListNode*>& lists) {
    MinHeap minHeap;
    //Push the head of every non-empty list into the heap
    for (size_t i = 0; i < lists.size(); i++) {
        if (lists[i] != nullptr) {
            minHeap.insert(lists[i]);
        }
    }
    ListNode* dummy = new ListNode(0);
    ListNode* tail = dummy;

    //Continuously extract the smallest node and push its next node
    while (!minHeap.isEmpty()) {
        ListNode* smallest = minHeap.extractMin(); 
        tail->next = smallest;                     
        tail = tail->next;                         

        if (smallest->next != nullptr) {
            minHeap.insert(smallest->next);
        }
    }
    ListNode* mergedHead = dummy->next;
    delete dummy; // Clean up the temporary dummy node
    return mergedHead;
}
//4 Helper function to print a linked list
void printList(ListNode* head) {
    if (head == nullptr) {
        cout << "Empty list" << endl;
        return;
    }
    while (head != nullptr) {
        cout << head->val;
        if (head->next != nullptr) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}
//free allocated memory
void deleteList(ListNode* head) {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}
int main() {
    int k;
    cout << "Enter the number of sorted linked lists (k): ";
    cin >> k;

    if (k <= 0) {
        cout << "No lists to merge." << endl;
        return 0;
    }
    vector<ListNode*> lists(k, nullptr);

    //Read each sorted linked list from the user
    for (int i = 0; i < k; i++) {
        int size;
        cout << "\nEnter number of elements in list " << i + 1 << ": ";
        cin >> size;

        if (size <= 0) continue;

        cout << "Enter " << size << " sorted elements (separated by spaces): ";
        ListNode* head = nullptr;
        ListNode* tail = nullptr;

        for (int j = 0; j < size; j++) {
            int val;
            cin >> val;
            ListNode* newNode = new ListNode(val);

            if (head == nullptr) {
                head = tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }
        lists[i] = head;
    }
    //Merge all lists and display result
    ListNode* result = mergeKLists(lists);

    cout << "\nMerged Sorted Linked List:\n";
    cout << "--------------------------\n";
    printList(result);

    deleteList(result);
    return 0;
}