#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
    Node(int data) : m_data(data){}
    Node* m_leftChild  = nullptr;
    Node* m_rightChild = nullptr;
    int   m_data;
};

class BinaryTree
{
public:
    BinaryTree(Node* root)
    {
        m_root = root;
    }
    void add(int newData)
    {
        vector<Node*> tempQueue;
        tempQueue.push_back(m_root);

        while(!tempQueue.empty())
        {
            Node* tempNode = tempQueue.front();
            tempQueue.erase(tempQueue.begin());
            if(!tempNode)
            {
                tempNode = new Node(newData);
                break;
            }
            else
            {
                if(!tempNode->m_leftChild)
                {
                    tempNode->m_leftChild = new Node(newData);
                    break;
                }
                else
                {
                    tempQueue.push_back(tempNode->m_leftChild);
                }
                if(!tempNode->m_rightChild)
                {
                    tempNode->m_rightChild = new Node(newData);
                    break;
                }
                else
                {
                    tempQueue.push_back(tempNode->m_rightChild);
                }
            }
        }
    }
    void printTree()
    {
        vector<Node*> tempQueue;
        tempQueue.push_back(m_root);

        while(!tempQueue.empty())
        {
            Node* tempNode = tempQueue.front();
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

private:
    Node* m_root;
};

int main()
{
    Node root(0);
    BinaryTree tree(&root);

    for(int i = 1; i <= 10; ++i)
    {
        tree.add(i);
    }
    tree.printTree();
	return 0;
}
