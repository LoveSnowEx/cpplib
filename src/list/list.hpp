#ifndef LIST_HPP
#define LIST_HPP

#include <memory>

template <typename T> class List;

template <typename T>
class Node: public std::enable_shared_from_this<Node<T>> {
private:
    T data_;
public:
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;

    // ctor, dtor
    Node() {}
    Node(const T &val): data_(val) {}
    Node(T &&val): data_(std::move(val)) {}
    ~Node() {
        next.reset();
    };

    // getters
    T &data() {
        return data_;
    }
    const T &data() const {
        return data_;
    }
    std::shared_ptr<Node<T>> shared() {
        return this->shared_from_this();
    }

    // modifiers
    std::shared_ptr<Node<T>> insert(std::shared_ptr<Node> node) {
        node->prev = prev;
        node->next = shared();
        prev.lock()->next = node;
        prev = node;
        return node;
    }
    std::shared_ptr<Node<T>> erase() {
        prev.lock()->next = next;
        next->prev = prev;
        return next;
    }
};

// ========================================

template <typename T>
std::shared_ptr<Node<T>> newNode() {
    auto node = std::make_shared<Node<T>>();
    node->next = node;
    node->prev = node;
    return node;
}

template <typename T>
std::shared_ptr<Node<T>> newNode(const T &val) {
    auto node = std::make_shared<Node<T>>(val);
    node->next = node;
    node->prev = node;
    return node;
}

template <typename T>
std::shared_ptr<Node<T>> newNode(T &&val) {
    auto node = std::make_shared<Node<T>>(val);
    node->next = node;
    node->prev = node;
    return node;
}

// ========================================

template <typename T>
class List {
public:
    class Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    public:
        Iterator(std::shared_ptr<Node<T>> node): node_(node) {}
        Iterator &operator++() {
            node_ = node_->next;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp(node_);
            operator++();
            return tmp;
        }
        Iterator &operator--() {
            node_ = node_->prev.lock();
            return *this;
        }
        Iterator operator--(int) {
            Iterator tmp(node_);
            operator--();
            return tmp;
        }
        constexpr bool operator==(const Iterator &rhs) {
            return node_ == rhs.node_;
        }
        constexpr bool operator!=(const Iterator &rhs) {
            return node_ != rhs.node_;
        }
        T &operator*() const {
            return node_->data();
        }
        Iterator insert(const T &val) {
            auto tmp = newNode(val);
            return Iterator(node_->insert(tmp));
        }
        Iterator insert(T &&val) {
            auto tmp = newNode(val);
            return Iterator(node_->insert(tmp));
        }
        Iterator erase() {
            return Iterator(node_->erase());
        }
    private:
        std::shared_ptr<Node<T>> node_;
    };

    // ========================================

    List(): end_(newNode<T>()), size_(0) {}
    ~List() {
        end_->next.reset();
        end_.reset();
    }
    constexpr size_t size() {
        return size_;
    }
    constexpr bool empty() {
        return size_ == 0;
    }
    Iterator begin() {
        return Iterator(end_->next);
    }
    Iterator end() {
        return Iterator(end_);
    }
    Iterator erase(Iterator pos) {
        if(pos != end()) {
            pos.erase();
            ++pos;
            --size_;
        }
        return pos;
    }
    Iterator insert(Iterator pos, const T &val) {
        ++size_;
        return pos.insert(val);
    }
    Iterator insert(Iterator pos, T &&val) {
        ++size_;
        return pos.insert(val);
    }
    void pushFront(const T &val) {
        insert(begin(), val);
    }
    void pushFront(T &&val) {
        insert(begin(), val);
    }
    void popFront() {
        erase(begin());
    }
    void pushBack(const T &val) {
        insert(end(), val);
    }
    void pushBack(T &&val) {
        insert(end(), val);
    }
    void popBack() {
        auto tmp = end();
        erase(--tmp);
    }
private:
    std::shared_ptr<Node<T>> end_;
    size_t size_;
};

#endif