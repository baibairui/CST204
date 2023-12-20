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
};

