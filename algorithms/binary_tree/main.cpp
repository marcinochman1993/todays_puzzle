#include <iostream>
#include <vector>
#include <memory>

using namespace std;

template <typename T>
class Node
{
public:
    Node(T data) : m_data(data){}
    shared_ptr<Node<T>> m_leftChild  = nullptr;
    shared_ptr<Node<T>> m_rightChild = nullptr;
    T                   m_data;
};

template <typename T>
class BinaryTree
{
public:
    BinaryTree(shared_ptr<Node<T>> root)
    {
        m_root = root;
    }

    shared_ptr<Node<T>> getRoot()
    {
        return m_root;
    }

    void add(T newData) //BFS
    {
        vector<shared_ptr<Node<T>>> tempQueue;
        tempQueue.push_back(m_root);

        while(!tempQueue.empty())
        {
            shared_ptr<Node<T>> tempNode = tempQueue.front();
            tempQueue.erase(tempQueue.begin());
            if(!tempNode)
            {
                tempNode = make_shared<Node<T>>(newData);
                break;
            }
            else
            {
                if(!tempNode->m_leftChild)
                {
                    tempNode->m_leftChild = make_shared<Node<T>>(newData);
                    break;
                }
                else
                {
                    tempQueue.push_back(tempNode->m_leftChild);
                }
                if(!tempNode->m_rightChild)
                {
                    tempNode->m_rightChild = make_shared<Node<T>>(newData);
                    break;
                }
                else
                {
                    tempQueue.push_back(tempNode->m_rightChild);
                }
            }
        }
    }
    void printTree() //BFS
    {
        vector<shared_ptr<Node<T>>> tempQueue;
        tempQueue.push_back(m_root);

        while(!tempQueue.empty())
        {
            shared_ptr<Node<T>> tempNode = tempQueue.front();
            tempQueue.erase(tempQueue.begin());

            if(tempNode)
            {
                cout << tempNode->m_data << ", ";
                if(tempNode->m_leftChild)
                {
                    tempQueue.push_back(tempNode->m_leftChild);
                }
                if(tempNode->m_rightChild)
                {
                    tempQueue.push_back(tempNode->m_rightChild);
                }
            }
        }
    }
    void printTreePreOrder(shared_ptr<Node<T>> node) //DFS
    {
        if(node)
        {
            cout << node->m_data << ", ";
            printTreePreOrder(node->m_leftChild);
            printTreePreOrder(node->m_rightChild);
        }
    }
    void printTreeInOrder(shared_ptr<Node<T>> node) //DFS
    {
        if(node)
        {
            printTreeInOrder(node->m_leftChild);
            cout << node->m_data << ", ";
            printTreeInOrder(node->m_rightChild);
        }
    }
    void printTreePostOrder(shared_ptr<Node<T>> node) //DFS
    {
        if(node)
        {
            printTreePostOrder(node->m_leftChild);
            printTreePostOrder(node->m_rightChild);
            cout << node->m_data << ", ";
        }
    }
private:
    shared_ptr<Node<T>> m_root;
};

int main()
{
    shared_ptr<Node<char>> root = make_shared<Node<char>>('A');
    BinaryTree<char> tree(root);

    for(int i = 1; i <= 10; ++i)
    {
        tree.add('A' + i);
    }
    tree.printTree();
    cout<<endl;
    tree.printTreePreOrder(tree.getRoot());
    cout << endl;
    tree.printTreeInOrder(tree.getRoot());
    cout << endl;
    tree.printTreePostOrder(tree.getRoot());
    cout << endl;
    return 0;
}
