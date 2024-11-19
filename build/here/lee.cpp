Function findSingleElement(nums):
 Initialize left to 0
 Initialize right to length of nums - 1
 While left < right:
 Calculate mid as left + (right - left) / 2
 If mid is odd:
 Decrease mid by 1 to make it even
 If nums[mid] is equal to nums[mid + 1]:
 // Single element is in the right half
 Set left to mid + 2
 Else:
 // Single element is in the left half
 Set right to mid
 Return nums[left]

 ==

 bool isPowerOfFour(int n) {
if (n <= 0){
return false;
}
while (n > 1){
if (n % 4 != 0){
return false;
}
n = n / 4;
}
return n == 1;
}
==
//convert sorted
list to a binary search tree
class Solution {
public:
TreeNode* sortedListToBST(ListNode* head) {
if (!head) return nullptr;
int size = 0;
ListNode* temp = head;
while (temp) {
size++;
temp = temp->next;
}
return sortedListToBSTHelper(head, 0, size - 1);
}
private:
TreeNode* sortedListToBSTHelper(ListNode*& head, int left, int right) {
if (left > right) return nullptr;
int mid = left + (right - left) / 2;
TreeNode* leftChild = sortedListToBSTHelper(head, left, mid - 1);
TreeNode* root = new TreeNode(head->val);
root->left = leftChild;
head = head->next;
root->right = sortedListToBSTHelper(head, mid + 1, right);
return root;
}
};

==
//. If
there are two middle nodes, return the second middle node
class Solution {
public:
ListNode* middleNode(ListNode* head) {
ListNode* slow = head;
ListNode* fast = head;
while (fast != nullptr && fast->next != nullptr) {
slow = slow->next; // Move slow by one
fast = fast->next->next; // Move fast by two
}
return slow;
}
};
===

public:
bool validPalindrome(string s) {
int left = 0;
int right = s.size() - 1;
while (left < right) {
if (s[left] != s[right]) {
return isPalindrome(s, left + 1, right) || isPalindrome(s, left, right - 1);
}
left++;
right--;
}
return true;
}
bool isPalindrome(const string& s, int left, int right) {
while (left < right) {
if (s[left] != s[right]) {
return false; // Not a palindrome
}
left++;
right--;
}
return true; // Is a palindrome
}
};
==
//Given a list of words, list of single letters (might be repeating) and score of every character.
Return the maximum score of any valid set of words formed by using the given letters (words[i]
cannot be used two or more times)

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;
class Solution {
public:
 // Helper function to calculate the score of a word
 int calculateWordScore(const string& word, vector<int>& score) {
 int word_score = 0;
 for (char c : word) {
 word_score += score[c - 'a'];
 }
 return word_score;
 }
 bool canFormWords(const vector<string>& subset, unordered_map<char, int>& letter_count) {
 unordered_map<char, int> used_letters;
 for (const string& word : subset) {
 for (char c : word) {
 used_letters[c]++;
 // If using this letter exceeds availability, return false
 if (used_letters[c] > letter_count[c]) {
 return false;
 }
 }
 }
 return true;
 }
 // Recursive function to generate all subsets and calculate the maximum score
 void backtrack(int index, vector<string>& words, vector<int>& score,
 unordered_map<char, int>& letter_count, vector<string>& current_set,
 int& max_score) {

 // Base case: when all words have been considered
 if (index == words.size()) {
 // Calculate the score of the current subset if it's valid
 if (canFormWords(current_set, letter_count)) {
 int current_score = 0;
 for (const string& word : current_set) {
 current_score += calculateWordScore(word, score);
 }
 // Update the maximum score if the current subset score is higher
 max_score = max(max_score, current_score);
 }
 return;
 }
 // Option 1: Exclude the current word
 backtrack(index + 1, words, score, letter_count, current_set, max_score);
 // Option 2: Include the current word in the subset
 current_set.push_back(words[index]);
 backtrack(index + 1, words, score, letter_count, current_set, max_score);
 current_set.pop_back(); // Backtrack
 }
 int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
 // Create a frequency map of the available letters
 unordered_map<char, int> letter_count;
 for (char letter : letters) {
 letter_count[letter]++;
 }
 int max_score = 0;
 vector<string> current_set;
 backtrack(0, words, score, letter_count, current_set, max_score);
 return max_score;
 }
};
