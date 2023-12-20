#include<iostream>
#include<algorithm> // 必须包含此头文件以使用 std::move

// 声明一个模板类 List，用于创建一个双向链表
template<typename Object>
class List {
private:
    // 内部结构 Node 用于表示链表的节点
    struct Node {
        Object data; // 存储节点的数据
        Node* prev;  // 指向前一个节点的指针
        Node* next;  // 指向下一个节点的指针

        // 构造函数使用初始化列表语法来初始化节点的数据和指针
        Node(const Object& d = Object{}, Node* p = nullptr, Node* n = nullptr)
            : data{ d }, prev{ p }, next{ n } {}

        // 移动构造函数，它将临时对象的资源移动到新节点中
        Node(Object&& d, Node* p = nullptr, Node* n = nullptr)
            : data{ std::move(d) }, prev{ p }, next{ n } {}
    };

public:
    // const_iterator 是 List 的一个嵌套类，用于提供对链表的只读访问
    class const_iterator {
    protected:
        Node* current; // 指向当前迭代器所指节点的指针

        // 返回当前节点中存储的数据的引用
        Object& retrieve() const {
            return current->data;
        }

        // 受保护的构造函数，仅供 List 类和其子类使用
        const_iterator(Node* p) : current(p) {}

        // 友元声明，允许 List 类访问 const_iterator 的保护和私有成员
        friend class List<Object>;

    public:
        // 默认构造函数，创建一个不指向任何节点的迭代器
        const_iterator() : current(nullptr) {}

        // 重载解引用操作符，返回当前节点中存储的数据的引用
        const Object& operator* () const {
            return retrieve();
        }

        // 重载前置++操作符，将迭代器移向链表中的下一个节点并返回
        const_iterator& operator++() {
            current = current->next;
            return *this;
        }

        // 重载后置++操作符，先保存当前迭代器的副本，再向前移动，并返回副本
        const_iterator operator++(int) {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        // 重载相等操作符，判断两个迭代器是否指向链表中的相同节点
        bool operator==(const const_iterator& rhs) const {
            return current == rhs.current;
        }

        // 重载不等操作符，通过调用相等操作符的结果取反来判断迭代器是否不相等
        bool operator!=(const const_iterator& rhs) const {
            return !(*this == rhs);
        }
    };
    class iterator : public const_iterator {
    public:
        // 默认构造函数，创建一个不指向任何节点的迭代器
		iterator() {}

		// 重载解引用操作符，返回当前节点中存储的数据的引用
        Object& operator* () {
			return const_iterator::retrieve();
		}

		// 重载前置++操作符，将迭代器移向链表中的下一个节点并返回
        iterator& operator++() {
			this->current = this->current->next;
			return *this;
		}

		// 重载后置++操作符，先保存当前迭代器的副本，再向前移动，并返回副本
        iterator operator++(int) {
			iterator old = *this;
			++(*this);
			return old;
		}

		// 受保护的构造函数，仅供 List 类和其子类使用
		iterator(Node* p) : const_iterator(p) {}

		// 友元声明，允许 List 类访问 iterator 的保护和私有成员
		friend class List<Object>;
	};

public:
    // 默认构造函数，创建一个空链表
    List() {
		init();
    };
    // 复制构造函数，创建一个与给定链表相同的链表
    List(const List& rhs) {
        // 调用复制赋值运算符
        *this = rhs;

    }
    // 移动构造函数，将临时对象的资源移动到新链表中
    List(List&& rhs) {
		// 调用移动赋值运算符
		*this = std::move(rhs);
	}
    // 析构函数，释放链表中的所有节点
    ~List() {
        	clear();
            delete head;
            delete tail;
    }
    // 复制赋值运算符，使得当前链表与给定链表相同
    const List& operator= (const List& rhs) {
		// 避免自我赋值
        if (this != &rhs) {
			clear(); // 清空当前链表
			// 从给定链表中复制节点
            for (auto& x : rhs) {
				push_back(x);
			}
		}
		return *this;
	}
    // 移动赋值运算符，将临时对象的资源移动到当前链表中
    List& operator= (List&& rhs) {
        if (this != &rhs) {
			clear(); // 清空当前链表
			// 将临时对象的资源移动到当前链表中
			head = rhs.head;
			tail = rhs.tail;
			theSize = rhs.theSize;
			// 重置临时对象
			rhs.head = nullptr;
			rhs.tail = nullptr;
			rhs.theSize = 0;
		}
    }
    // 返回链表头节点的迭代器
    iterator begin() {
        const_iterator itr{*this,head};
        return itr;
        }
    // 返回链表头节点的只读迭代器
    const_iterator begin() const {
		const_iterator itr{*this,head};
		return itr;
	}
    // 返回链表是否为空
    bool empty() const {
		return size() == 0;
	}
    // 返回链表中存储的数据的个数
    int size() const {
        return theSize;
    }
    
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }
private:
    int theSize; // 链表中存储的数据的个数
	Node* head;  // 指向链表头节点的指针
	Node* tail;  // 指向链表尾节点的指针

	// 初始化链表
    void init() {
		theSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
	}
};

