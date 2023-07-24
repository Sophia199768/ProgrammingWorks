#include <iostream>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>

#define EMPTY_STRING ""
#include "arc.h"
#pragma once

struct Node {
    char ch;
    int freq;
    Node *left, *right;
};
Node* getNode(char ch, int freq, Node* left, Node* right);
struct comp {
    bool operator()(const Node* l, const Node* r) const {
      return l->freq > r->freq;
    }
};
Node* getNode(char ch, int freq, Node* left, Node* right);
void decode(Node* root, int &index, std::string str);
bool isLeaf(Node* root);
void encode(Node* root, std::string str, std::unordered_map<char, std::string> &huffmanCode);
void buildHuffmanTree(std::string text);
