#include "haffman.h"

Node* getNode(char ch, int freq, Node* left, Node* right) {
  Node* node = new Node();
  node->ch = ch;
  node->freq = freq;
  node->left = left;
  node->right = right;
  return node;
}

bool isLeaf(Node* root) {
  return root->left == nullptr && root->right == nullptr;
}

void encode(Node* root, std::string str, std::unordered_map<char, std::string> &huffmanCode) {
  if (root == nullptr) {
    return;
  }

  if (isLeaf(root)) {
    huffmanCode[root->ch] = (str != EMPTY_STRING) ? str : "1";
  }

  encode(root->left, str + "0", huffmanCode);
  encode(root->right, str + "1", huffmanCode);
}

void decode(Node* root, int &index, std::string str) {
  if (root == nullptr) {
    return;
  }

  if (isLeaf(root)) {
    std::cout << root->ch;
    return;
  }

  index++;

  if (str[index] == '0') {
    decode(root->left, index, str);
  } else {
    decode(root->right, index, str);
  }
}

void buildHuffmanTree(std::string text) {
  if (text == EMPTY_STRING) {
    return;
  }

  std::unordered_map<char, int> freq;
  for (char ch: text) {
    freq[ch]++;
  }

  std::priority_queue<Node*, std::vector<Node*>, comp> pq;

  for (auto pair: freq) {
    pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
  }

  while (pq.size() != 1) {
    Node* left = pq.top(); pq.pop();
    Node* right = pq.top();    pq.pop();

    int sum = left->freq + right->freq;
    pq.push(getNode('\0', sum, left, right));
  }

  Node* root = pq.top();

  std::unordered_map<char, std::string> huffmanCode;
  encode(root, EMPTY_STRING, huffmanCode);


  std::ofstream small;
  small.open("C:\\tmp\\", std::ios_base::binary | std::ios_base::app);

  for (auto pair: huffmanCode) {
    std::cout << pair.first << " " << pair.second << std::endl;
    small << pair.first;
    small << pair.second;

  }



  small << text << std::endl;

  std::string str;
  for (char ch: text) {
    str += huffmanCode[ch];
  }

  small << str;

  if (isLeaf(root)) {
    while (root->freq--) {
      std::cout << root->ch;
    }
  } else {
    int index = -1;

    while (index < (int)str.size() - 1) {
      decode(root, index, str);
    }

  }
}
