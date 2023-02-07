#include "../manager/game_manager.hpp"


Node::Node(int _id, Node* _right, Node* _left) : id(_id), parent(nullptr), right(_right), left(_left) {
    // by default we dont have parent
    if (right != nullptr) right->parent = this;
    if (left != nullptr) left->parent = this;
}
 
void Node::shutdown() {
    if (right) right->shutdown();
    if (left) left->shutdown();
    delete this;
}

bool Node::is_root() { return parent == nullptr; }