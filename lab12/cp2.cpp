#include <iostream>
#include <vector>
#include <algorithm>

/* The heapify function is designed to ensure that a subtree rooted at a given index i
 * in an array representation of a min heap maintains the heap property.
 */
void heapify(std::vector<int>& nums, int n, int i){
    int largest = i; // assuming i is the largest
    int left = 2*i+1;    // i's left child is at this location
    int right = 2*i+2;   // i's right child is at this location

    if(left<n && nums[left]>nums[largest]){
        largest = left;
    }

    if(right<n && nums[right]>nums[largest]){
        largest = right;
    }

    // after the above, smallest basically will either stay the same, 
    // or will be either left or right, depending on nums[left] is smaller or nums[right] is smaller. 
    // smallest stays the same if it is already smallest than its two children.
    // if smallest is changed, then we do need to swap.
    if(largest != i){
        std::swap(nums[i], nums[largest]);
        heapify(nums, n, largest);
    }
}

// heap sort: O(nlogn)
std::vector<int> sortArray(std::vector<int>& nums) {
    int n = nums.size();
    // build the heap, starting from the last non-leaf node.
    // why we start from the last non-leaf node? 
    // because leaf nodes inherently satisfy the heap property, as they have no children.
    // By beginning the heapify process from the last non-leaf node and moving upwards:
    // We ensure that when we heapify a node, its children are already heapified.
    // This bottom-up approach guarantees that each subtree satisfies the heap property before moving to the next node.
    for(int i=n/2-1; i>=0; i--){
        // heapify the subtree whose root is at i
        // i.e., build a min heap, with i being the root; and this heap contains nodes from i to n-1;
        heapify(nums, n, i);
    }

    // now the first one is the smallest, swap it to the back
    // do this n-1 times.
    for(int i=n-1; i>0; i--){
        // build the min heap again, with 0 being the root.
        // but only consider i elements, as the others are already in the right place.
        std::swap(nums[0], nums[i]);     // move smallest to the end
        heapify(nums, i, 0);
    }

    return nums;
}

int main() {
    // Sample data to be sorted
    // std::vector<int> nums = {42, 12, 13, 65, 98, 45, 97, 85, 76, 90};
    std::vector<int> nums = {3, 8, 5, 2, 1, 4, 6, 7};

    // Output the original array
    std::cout << "Original array:\n";
    for (int num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::vector<int> sortedNums = sortArray(nums);

    // Output the sorted array
    std::cout << "\nSorted array:\n";
    for (int num : sortedNums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}