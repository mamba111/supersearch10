// File: avl_tree_map.h

#ifndef AVL_TREE_MAP_H
#define AVL_TREE_MAP_H

#include <algorithm>
#include <utility> // For std::pair

template <typename Key, typename Value>
class AVLTreeMap {
public:
    AVLTreeMap() : root(nullptr) {}
    ~AVLTreeMap() { freeNode(root); }

    void insert(const Key& key, const Value& value) {
        root = insert(root, key, value);
    }

    void remove(const Key& key) {
        root = remove(root, key);
    }

    Value* search(const Key& key) const {
        Node* result = search(root, key);
        return result ? &(result->data.second) : nullptr;
    }

private:
    struct Node {
        std::pair<Key, Value> data;
        Node* left;
        Node* right;
        int height;

        Node(const Key& key, const Value& value) : data(key, value), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    Node* insert(Node* node, const Key& key, const Value& value);
    Node* remove(Node* node, const Key& key);
    Node* search(Node* node, const Key& key) const;

    int getHeight(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int getBalanceFactor(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    Node* minValueNode(Node* node);
    void freeNode(Node* node);
};

// Insert method implementation
template <typename Key, typename Value>
typename AVLTreeMap<Key, Value>::Node* AVLTreeMap<Key, Value>::insert(Node* node, const Key& key, const Value& value) {
    if (node == nullptr) {
        return new Node(key, value);
    }

    if (key < node->data.first) {
        node->left = insert(node->left, key, value);
    } else if (key > node->data.first) {
        node->right = insert(node->right, key, value);
    } else {
        // Update the value for duplicate key
        node->data.second = value;
        return node;
    }

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalanceFactor(node);

    // Left Left Case
    if (balance > 1 && key < node->left->data.first) {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && key > node->right->data.first) {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && key > node->left->data.first) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->data.first) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Remove method implementation
template <typename Key, typename Value>
typename AVLTreeMap<Key, Value>::Node* AVLTreeMap<Key, Value>::remove(Node* node, const Key& key) {
        if (node == nullptr) {
        return node;
    }

    if (key < node->data.first) {
        node->left = remove(node->left, key);
    } else if (key > node->data.first) {
        node->right = remove(node->right, key);
    } else {
        if ((node->left == nullptr) || (node->right == nullptr)) {
            Node* temp = node->left ? node->left : node->right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp; // Copy the contents
            }
            delete temp;
        } else {
            Node* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data.first);
        }
    }

    if (node == nullptr) {
        return node;
    }

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalanceFactor(node);

    // Balancing the node if it became unbalanced
    // Implement rotations similar to the insert method

    return node;
}

// Search method implementation
template <typename Key, typename Value>
typename AVLTreeMap<Key, Value>::Node* AVLTreeMap<Key, Value>::search(Node* node, const Key& key) const {
    if (node == nullptr || node->data.first == key) {
        return node;
    }

    if (key < node->data.first) {
        return search(node->left, key);
    } else {
        return search(node->right, key);
    }
}

// RightRotate method implementation
template <typename Key, typename Value>
typename AVLTreeMap<Key, Value>::Node* AVLTreeMap<Key, Value>::rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    // Return new root
    return x;
}

// LeftRotate method implementation
template <typename Key, typename Value>
typename AVLTreeMap<Key, Value>::Node* AVLTreeMap<Key, Value>::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    // Return new root
    return y;
}

// MinValueNode method implementation
template <typename Key, typename Value>
typename AVLTreeMap<Key, Value>::Node* AVLTreeMap<Key, Value>::minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// FreeNode method implementation
template <typename Key, typename Value>
void AVLTreeMap<Key, Value>::freeNode(Node* node) {
    if (node != nullptr) {
        freeNode(node->left);
        freeNode(node->right);
        delete node;
    }
}

#endif // AVL_TREE_MAP_H
