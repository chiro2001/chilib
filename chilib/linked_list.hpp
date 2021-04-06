// Last modified at 2021-04-06 by Chiro

#ifndef CHILIB_LINKED_LIST_HPP
#define CHILIB_LINKED_LIST_HPP

#include <memory>

namespace chilib {

// 单向链表，C++智能指针实现
template<typename T>
class linked_list {
public:
  linked_list() = default;

  linked_list(linked_list<T> &li) = default;

  explicit linked_list(T &d) : data(d) {}

  ~linked_list() = default;

  std::shared_ptr<linked_list<T>> next = nullptr;  // 指向下一个节点的指针
  T data{};                                        // 当前数据

  // return: 得到链表尾部
  // @notice  : 只有自己一个节点的时候也返回nullptr
  std::shared_ptr<linked_list<T>> get_tail() {
    auto p = this->next;
    if (p == nullptr) return nullptr;
    while (p->next != nullptr) p = p->next;
    return p;
  }

  // @prog    : 连接一个节点到this节点后面
  // @notice  : 这个传入的节点之后的数据被释放
  auto link(T &d) {
    auto p = linked_list::make(d);
    this->link(p);
    return p;
  }

  // @prog    : 接一个已经存在的链表串到本节点之后
  // @notice  : 本节点之后的数据释放
  //            参数节点之后的数据保留
  std::shared_ptr<linked_list<T>> link(std::shared_ptr<linked_list<T>> &p) {
    if (p == nullptr) return nullptr;
    this->next = p;
    return p;
  }

  // @prog     : 接一个已经存在的链表串到本节点之后
  // @notice   : 本节点之后的数据接到参数节点之后
  //             参数节点之后的数据保留到串中
  std::shared_ptr<linked_list<T>> append(std::shared_ptr<linked_list<T>> &p) {
    if (p == nullptr) return nullptr;
    auto tail = p->get_tail();
    tail->next = this->next;
    this->next = p;
    return p;
  }

  // @prog    : 获取往下几个节点的指针
  // @notice  : 不能返回自己的指针
  std::shared_ptr<linked_list<T>> step(size_t s) {
    if (!s) return nullptr;
    auto p = this->next;
    while (s) {
      if (p == nullptr) return p;
      p = p->next;
      s--;
    }
    return p;
  }

  static auto make(T &d) {
    return std::make_shared<linked_list<T>>(d);
  }

  static auto make_head() {
    return std::make_shared<linked_list<T>>();
  }

  static bool check_circulation(std::shared_ptr<linked_list<T>> &p) {
    // 快慢指针法
    auto p1 = p, p2 = p;
    do {
      p1 = p1->step(1);
      p2 = p2->step(2);
      if (p1 == nullptr || p2 == nullptr) return false;
    } while (p1 != p2);
    return true;
  }

  // 支持迭代器
  template<class T2, class ref, class ptr>
  class linked_list_iterator {
  public:
    using self = linked_list_iterator<T2, ref, ptr>;
    using self_const = const linked_list_iterator<T2, ref, ptr>;
    std::shared_ptr<linked_list<T2>> node;

    explicit linked_list_iterator(std::shared_ptr<linked_list<T2>> &list) : node(list) {}

    ref operator*() { return node->data; }

    ptr operator->() { return &(operator*()); }

    // ++it
    self &operator++() {
      node = node->next;
      return *this;
    }

    // it++
    self operator++(int) {
      // 保存之前的迭代器
      self tmp(*this);
      node = node->next;
      return tmp;
    }

    bool operator==(const self &s) {
      return node == s.node;
    }

    bool operator!=(const self &s) {
      return node != s.node;
    }
  };

  using iterator = linked_list_iterator<T, T &, T *>;
  using const_iterator = linked_list_iterator<T, const T &, const T *>;

  // 由于没法指向自己，所以只能指向下一个。使用的时候空出头结点
  iterator begin() { return iterator(this->next); }

  iterator end() { return iterator(this->get_tail()->next); }
};

// 外部可以使用 linked_list_p 做指针简单名字
template<typename T>
using linked_list_p = std::shared_ptr<linked_list<T>>;


}  // namespace chilib

#endif //CHILIB_LINKED_LIST_HPP