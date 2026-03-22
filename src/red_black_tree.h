#pragma once

#include <string>
#include <vector>
#include <cstddef>

enum class Color {
    RED,
    BLACK
};

struct RBNode {
    std::string key;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;

    RBNode();
    explicit RBNode(const std::string& value);
};

class RedBlackTree {
public:
    RedBlackTree();
    ~RedBlackTree();

    void insert(const std::string& key);
    std::vector<std::string> inorder() const;
    double estimate_memory_mb() const;

private:
    RBNode* root;
    RBNode* nil;
    std::size_t node_count;

    void left_rotate(RBNode* x);
    void right_rotate(RBNode* y);
    void insert_fixup(RBNode* z);
    void inorder_collect(RBNode* node, std::vector<std::string>& result) const;
    void destroy(RBNode* node);
    std::size_t estimate_memory_bytes(RBNode* node) const;
};