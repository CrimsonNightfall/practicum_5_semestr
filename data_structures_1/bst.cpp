#include <iostream>
#include <algorithm>

struct TNode {
    int value;
    TNode* left;
    TNode* right;

    explicit TNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BST() : root_(nullptr) {}

    void Insert(int val) {
        root_ = InsertRec(root_, val);
    }

    int Height() const {
        return HeightRec(root_);
    }

private:
    TNode* root_;

    TNode* InsertRec(TNode* node, int val) {
        if (node == nullptr) {
            return new TNode(val);
        }
        if (val < node->value) {
            node->left = InsertRec(node->left, val);
        } else if (val > node->value) {
            node->right = InsertRec(node->right, val);
        }
        return node;
    }

    int HeightRec(const TNode* node) const {
        if (node == nullptr) {
            return 0;
        }
        int left_height = HeightRec(node->left);
        int right_height = HeightRec(node->right);
        return std::max(left_height, right_height) + 1;
    }
};

int main() {
    BST tree;
    int number;

    while (std::cin >> number && number != 0) {
        tree.Insert(number);
    }

    std::cout << tree.Height() << std::endl;
    return 0;
}