#include<iostream>

using namespace std;

// Purpose: Implementation of BST class
template<typename T>
class BST {
private:
    // Purpose: Node class for BST
    class Node {
    public:
        T data;
        Node* left;
        Node* right;
        // Constructor
        Node(T newdata) : data(newdata), left(nullptr), right(nullptr) {}
    };

    Node* root;
    //����ڵ�
    Node* insert(Node* node, T data) {
        //����ڵ�Ϊ�գ������½ڵ�
        if (node == nullptr) {
            return new Node(data);
        }//����ڵ㲻Ϊ�գ��ж�Ҫ�����ֵ��ڵ��ֵ�Ĵ�С
        if (data < node->data) {
            node->left = insert(node->left, data);
        }//���Ҫ�����ֵС�ڽڵ��ֵ���ݹ�������
        else if (data > node->data) {
            node->right = insert(node->right, data);
        }//���Ҫ�����ֵ���ڽڵ��ֵ���ݹ�������
        return node;
    }
    //���ҽڵ�
    bool search(Node* node, T data) {
        //����ڵ�Ϊ�գ�����false
        if (node == nullptr) {
            return false;
        }//����ڵ㲻Ϊ�գ��ж�Ҫ���ҵ�ֵ��ڵ��ֵ�Ĵ�С
		else if (data < node->data) {
            return search(node->left, data);
        }//���Ҫ���ҵ�ֵ���ڽڵ��ֵ���ݹ�������
        else if (data > node->data) {
            return search(node->right, data);
        }
        //���Ҫ���ҵ�ֵ���ڽڵ��ֵ������true
        return true;
    }
    //�ҵ�����������С�Ľڵ�
    Node* findMinNode(Node* node) {
        //����ڵ�Ϊ�գ����ؿ�
        Node* current = node;
        if (current == nullptr) return current;

        //����ڵ㲻Ϊ�գ�һֱ�����ң�ֱ���ҵ���С�Ľڵ�
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
    //ɾ���ڵ�
    Node* remove(Node* root, T data) {
        //�ҵ�Ҫɾ���Ľڵ�
        if (root == nullptr) return root;
        //���Ҫɾ���Ľڵ�С�ڸ��ڵ㣬�ݹ�������
        if (data < root->data) {
            root->left = remove(root->left, data);
        }//���Ҫɾ���Ľڵ���ڸ��ڵ㣬�ݹ�������
        else if (data > root->data) {
            root->right = remove(root->right, data);
        }//���Ҫɾ���Ľڵ���ڸ��ڵ�
        else {
            //���Ҫɾ���Ľڵ�û��������
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            }//���Ҫɾ���Ľڵ�û��������
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            //���Ҫɾ���Ľڵ�����������
            //�ҵ�����������С�Ľڵ�
            //���ýڵ��ֵ��ֵ��Ҫɾ���Ľڵ�
            //ɾ���ýڵ�
            
            Node* temp = findMinNode(root->right);
            root->data = temp->data;
            root->right = remove(root->right, temp->data);
        }
        //���ظ��ڵ�
        return root;
    }
    //ɾ����
    void deleteTree(Node* node) {
        if (node) {
            //�ݹ�ɾ����������
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
    //��ӡ��
    void printTree(Node*root) {
        if (!root)return;
        cout << root->data << "\t";
        printTree(root->left);
        printTree(root->right);
    }
public:
    // Constructor
    BST() : root(nullptr) {}
    // Destructor
    ~BST() {
        deleteTree(root);
    }
    //���ⲿ����ʱ������˽�г�Ա����
    void insert(T data) {
        //������ڵ�Ϊ�գ�ֱ�Ӳ���
        root = insert(root, data);
    }
    //���ⲿ����ʱ������˽�г�Ա����
    bool search(T data) {
        //������ڵ�Ϊ�գ�����false
        return search(root, data);
    }
    //���ⲿ����ʱ������˽�г�Ա����
    void remove(T data) {
        //������ڵ�Ϊ�գ�ֱ�ӷ���
        root = remove(root, data);
    }
    //���ⲿ����ʱ������˽�г�Ա����
    void print() {
        printTree(root);
        std::cout << endl;
    }
};
