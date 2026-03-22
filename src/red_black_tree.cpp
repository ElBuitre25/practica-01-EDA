#include "red_black_tree.h"

RBNode::RBNode()
    : key(), color(Color::BLACK), left(nullptr), right(nullptr), parent(nullptr) {}

RBNode::RBNode(const std::string& value)
    : key(value), color(Color::RED), left(nullptr), right(nullptr), parent(nullptr) {}

RedBlackTree::RedBlackTree() : root(nullptr), nil(new RBNode()), node_count(0) {
    nil->color = Color::BLACK;
    nil->left = nil;
    nil->right = nil;
    nil->parent = nil;
    root = nil;
}

RedBlackTree::~RedBlackTree() {
    destroy(root);
    delete nil;
}

void RedBlackTree::left_rotate(RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;

    if (y->left != nil) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == nil) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void RedBlackTree::right_rotate(RBNode* y) {
    RBNode* x = y->left;
    y->left = x->right;

    if (x->right != nil) {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == nil) {
        root = x;
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }

    x->right = y;
    y->parent = x;
}

void RedBlackTree::insert(const std::string& key) {
    RBNode* z = new RBNode(key);
    z->left = nil;
    z->right = nil;

    RBNode* y = nil;
    RBNode* x = root;

    while (x != nil) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;

    if (y == nil) {
        root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    insert_fixup(z);
    ++node_count;
}

void RedBlackTree::insert_fixup(RBNode* z) {
    while (z->parent->color == Color::RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode* y = z->parent->parent->right;

            if (y->color == Color::RED) {
                z->parent->color = Color::BLACK;
                y->color = Color::BLACK;
                z->parent->parent->color = Color::RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(z);
                }
                z->parent->color = Color::BLACK;
                z->parent->parent->color = Color::RED;
                right_rotate(z->parent->parent);
            }
        } else {
            RBNode* y = z->parent->parent->left;

            if (y->color == Color::RED) {
                z->parent->color = Color::BLACK;
                y->color = Color::BLACK;
                z->parent->parent->color = Color::RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(z);
                }
                z->parent->color = Color::BLACK;
                z->parent->parent->color = Color::RED;
                left_rotate(z->parent->parent);
            }
        }
    }

    root->color = Color::BLACK;
}

std::vector<std::string> RedBlackTree::inorder() const {
    std::vector<std::string> result;
    result.reserve(node_count);
    inorder_collect(root, result);
    return result;
}

void RedBlackTree::inorder_collect(RBNode* node, std::vector<std::string>& result) const {
    if (node == nil) {
        return;
    }

    inorder_collect(node->left, result);
    result.push_back(node->key);
    inorder_collect(node->right, result);
}

void RedBlackTree::destroy(RBNode* node) {
    if (node == nil) {
        return;
    }

    destroy(node->left);
    destroy(node->right);
    delete node;
}

std::size_t RedBlackTree::estimate_memory_bytes(RBNode* node) const {
    if (node == nil) {
        return 0;
    }

    return sizeof(RBNode) + node->key.capacity()
        + estimate_memory_bytes(node->left)
        + estimate_memory_bytes(node->right);
}

double RedBlackTree::estimate_memory_mb() const {
    const std::size_t total_bytes = estimate_memory_bytes(root) + sizeof(RedBlackTree) + sizeof(RBNode);
    return static_cast<double>(total_bytes) / (1024.0 * 1024.0);
}