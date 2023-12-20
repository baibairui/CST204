#include<iostream>
#include<algorithm> // ���������ͷ�ļ���ʹ�� std::move

// ����һ��ģ���� List�����ڴ���һ��˫������
template<typename Object>
class List {
private:
    // �ڲ��ṹ Node ���ڱ�ʾ����Ľڵ�
    struct Node {
        Object data; // �洢�ڵ������
        Node* prev;  // ָ��ǰһ���ڵ��ָ��
        Node* next;  // ָ����һ���ڵ��ָ��

        // ���캯��ʹ�ó�ʼ���б��﷨����ʼ���ڵ�����ݺ�ָ��
        Node(const Object& d = Object{}, Node* p = nullptr, Node* n = nullptr)
            : data{ d }, prev{ p }, next{ n } {}

        // �ƶ����캯����������ʱ�������Դ�ƶ����½ڵ���
        Node(Object&& d, Node* p = nullptr, Node* n = nullptr)
            : data{ std::move(d) }, prev{ p }, next{ n } {}
    };

public:
    // const_iterator �� List ��һ��Ƕ���࣬�����ṩ�������ֻ������
    class const_iterator {
    protected:
        Node* current; // ָ��ǰ��������ָ�ڵ��ָ��

        // ���ص�ǰ�ڵ��д洢�����ݵ�����
        Object& retrieve() const {
            return current->data;
        }

        // �ܱ����Ĺ��캯�������� List ���������ʹ��
        const_iterator(Node* p) : current(p) {}

        // ��Ԫ���������� List ����� const_iterator �ı�����˽�г�Ա
        friend class List<Object>;

    public:
        // Ĭ�Ϲ��캯��������һ����ָ���κνڵ�ĵ�����
        const_iterator() : current(nullptr) {}

        // ���ؽ����ò����������ص�ǰ�ڵ��д洢�����ݵ�����
        const Object& operator* () const {
            return retrieve();
        }

        // ����ǰ��++�������������������������е���һ���ڵ㲢����
        const_iterator& operator++() {
            current = current->next;
            return *this;
        }

        // ���غ���++���������ȱ��浱ǰ�������ĸ���������ǰ�ƶ��������ظ���
        const_iterator operator++(int) {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        // ������Ȳ��������ж������������Ƿ�ָ�������е���ͬ�ڵ�
        bool operator==(const const_iterator& rhs) const {
            return current == rhs.current;
        }

        // ���ز��Ȳ�������ͨ��������Ȳ������Ľ��ȡ�����жϵ������Ƿ����
        bool operator!=(const const_iterator& rhs) const {
            return !(*this == rhs);
        }
    };
    class iterator : public const_iterator {
    public:
        // Ĭ�Ϲ��캯��������һ����ָ���κνڵ�ĵ�����
		iterator() {}

		// ���ؽ����ò����������ص�ǰ�ڵ��д洢�����ݵ�����
        Object& operator* () {
			return const_iterator::retrieve();
		}

		// ����ǰ��++�������������������������е���һ���ڵ㲢����
        iterator& operator++() {
			this->current = this->current->next;
			return *this;
		}

		// ���غ���++���������ȱ��浱ǰ�������ĸ���������ǰ�ƶ��������ظ���
        iterator operator++(int) {
			iterator old = *this;
			++(*this);
			return old;
		}

		// �ܱ����Ĺ��캯�������� List ���������ʹ��
		iterator(Node* p) : const_iterator(p) {}

		// ��Ԫ���������� List ����� iterator �ı�����˽�г�Ա
		friend class List<Object>;
	};

public:
    // Ĭ�Ϲ��캯��������һ��������
    List() {
		init();
    };
    // ���ƹ��캯��������һ�������������ͬ������
    List(const List& rhs) {
        // ���ø��Ƹ�ֵ�����
        *this = rhs;

    }
    // �ƶ����캯��������ʱ�������Դ�ƶ�����������
    List(List&& rhs) {
		// �����ƶ���ֵ�����
		*this = std::move(rhs);
	}
    // �����������ͷ������е����нڵ�
    ~List() {
        	clear();
            delete head;
            delete tail;
    }
    // ���Ƹ�ֵ�������ʹ�õ�ǰ���������������ͬ
    const List& operator= (const List& rhs) {
		// �������Ҹ�ֵ
        if (this != &rhs) {
			clear(); // ��յ�ǰ����
			// �Ӹ��������и��ƽڵ�
            for (auto& x : rhs) {
				push_back(x);
			}
		}
		return *this;
	}
    // �ƶ���ֵ�����������ʱ�������Դ�ƶ�����ǰ������
    List& operator= (List&& rhs) {
        if (this != &rhs) {
			clear(); // ��յ�ǰ����
			// ����ʱ�������Դ�ƶ�����ǰ������
			head = rhs.head;
			tail = rhs.tail;
			theSize = rhs.theSize;
			// ������ʱ����
			rhs.head = nullptr;
			rhs.tail = nullptr;
			rhs.theSize = 0;
		}
    }
    // ��������ͷ�ڵ�ĵ�����
    iterator begin() {
        const_iterator itr{*this,head};
        return itr;
        }
    // ��������ͷ�ڵ��ֻ��������
    const_iterator begin() const {
		const_iterator itr{*this,head};
		return itr;
	}
    // ���������Ƿ�Ϊ��
    bool empty() const {
		return size() == 0;
	}
    // ���������д洢�����ݵĸ���
    int size() const {
        return theSize;
    }
    
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }
private:
    int theSize; // �����д洢�����ݵĸ���
	Node* head;  // ָ������ͷ�ڵ��ָ��
	Node* tail;  // ָ������β�ڵ��ָ��

	// ��ʼ������
    void init() {
		theSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
	}
};

