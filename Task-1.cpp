#include <iostream>
#include <vector>
#include <string>

using namespace std;

//1. Structure for a Huffman Tree Node
struct Node {
    char data;         
    int freq;           
    Node *left, *right; 

    Node(char d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}
};
//2 Vector-based Min-Heap Class
class MinHeap {
private:
    vector<Node*> heap;

    void swapNodes(Node*& a, Node*& b) {
        Node* temp = a;
        a = b;
        b = temp;
    }
    //Heapify Down: Restores Min-Heap property from top to bottom
    void minHeapify(int idx) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int n = heap.size();

        if (left < n && heap[left]->freq < heap[smallest]->freq) {
            smallest = left;
        }
        if (right < n && heap[right]->freq < heap[smallest]->freq) {
            smallest = right;
        }
        if (smallest != idx) {
            swapNodes(heap[smallest], heap[idx]);
            minHeapify(smallest);
        }
    }
public:
    //Returns current number of elements in the heap
    int size() const {
        return heap.size();
    }
    //Insert Node: Adds a new node and bubbles it up to its right position
    void insert(Node* newNode) {
        heap.push_back(newNode); 
        int i = heap.size() - 1;
      
        while (i > 0 && heap[i]->freq < heap[(i - 1) / 2]->freq) {
            swapNodes(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
    //Extract Min: Removes and returns the node with the lowest frequency
    Node* extractMin() {
        if (heap.empty()) return nullptr;

        Node* minNode = heap[0];     
        heap[0] = heap.back();       
        heap.pop_back();            
        
        if (!heap.empty()) {
            minHeapify(0);            
        }
        return minNode;
    }
};
//3 Build the Huffman Tree
Node* buildHuffmanTree(const string& S, const vector<int>& f) {
    MinHeap minHeap;

    //Insert all characters as leaf nodes into the Min-Heap
    for (size_t i = 0; i < S.length(); i++) {
        minHeap.insert(new Node(S[i], f[i]));
    }
    //Merge the two smallest nodes until only the root remains
    while (minHeap.size() > 1) {
        Node* left = minHeap.extractMin();
        Node* right = minHeap.extractMin();

        Node* top = new Node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        minHeap.insert(top);
    }
    return minHeap.extractMin();
}
//4 Print Huffman Codes in Preorder Traversal (Root -> Left -> Right)
void printPreorderCodes(Node* root, string code) {
    if (root == nullptr) return;

    //Print code if it's a leaf node
    if (root->data != '$') {
        cout << root->data << " : " << code << endl;
    }
    printPreorderCodes(root->left, code + "0");
    printPreorderCodes(root->right, code + "1");
}
//5 function to free allocated memory 
void deleteTree(Node* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}
int main() {
    int N;
    cout << "Enter the number of distinct characters: ";
    cin >> N;

    if (N <= 0) {
        cout << "Invalid size" << endl;
        return 0;
    }
    string S;
    cout << "Enter the string of " << N << " distinct character: ";
    cin >> S;

    //Basic validation to ensure string length matches N
    if (S.length() != (size_t)N) {
        cout << "Error: String length does not match " << N << "." << endl;
        return 0;
    }
    vector<int> f(N);
    cout << "Enter the " << N << " resprective frequencies (separated by spaces): ";
    for (int i = 0; i < N; i++) {
        cin >> f[i];
    }
    //Build tree and display codes
    Node* root = buildHuffmanTree(S, f);

    cout << "\nHuffman Codes:\n";
    cout << "-----------------------------------\n";
    printPreorderCodes(root, "");
    deleteTree(root);

    return 0;
}