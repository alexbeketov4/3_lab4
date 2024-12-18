#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <string>
#include <functional> 

template <typename T> class BinaryTree
{
private:
    template <typename T> class Node
    {
    private:
        size_t height;
        T data;
        Node<T>* left;
        Node<T>* right;
    public:
        Node() : height(1), data(0), left(nullptr), right(nullptr) {}

        Node(const T& item) : height(1), data(item), left(nullptr), right(nullptr) {}

        /*Node(const Node<T>& other) :
            height(other.height),
            data(other.data),
            left(other.left ? new Node<T>(*other.left) : nullptr),
            right(other.right ? new Node<T>(*other.right) : nullptr)
        {}*/

        Node(const Node<T>& other)
            : height(0), data(T()), left(nullptr), right(nullptr)
        {
            if (&other != nullptr)
            {
                height = other.height;
                data = other.data;
                left = other.left ? new Node<T>(*other.left) : nullptr;
                right = other.right ? new Node<T>(*other.right) : nullptr;
            }
        }

        T GetData() const
        {
            return data;
        }

        Node<T>* GetLeft() const
        {
            if (left)
            {
                return left;
            }
            return nullptr;
        }

        Node<T>* GetRight() const
        {
            if (right)
            {
                return right;
            }
            return nullptr;
        }

        size_t GetHeight() const
        {
            return height;
        }

        void SetHeight(size_t h)
        {
            height = h;
        }

        void SetLeft(Node<T>* node)
        {
            left = node;
        }

        void SetRight(Node<T>* node)
        {
            right = node;
        }

        void SetData(const T& value)
        {
            this->data = value;
        }
    };

    Node<T>* root;

    void DeleteTree(Node<T>* elem)
    {
        if (elem == nullptr)
        {
            return;
        }

        DeleteTree(elem->GetLeft());
        DeleteTree(elem->GetRight());
        delete elem;
    }

    Node<T>* FindBSTMin(Node<T>* startRoot) const
    {
        if (startRoot->GetLeft() == nullptr)
        {
            return startRoot;
        }
        return FindBSTMin(startRoot->GetLeft());
    }

    Node<T>* DeleteElem(Node<T>* startRoot, const T& value)
    {
        if (startRoot == nullptr)
        {
            return startRoot;
        }

        else if (value < startRoot->GetData())
        {
            startRoot->SetLeft(DeleteElem(startRoot->GetLeft(), value));
        }

        else if (value > startRoot->GetData())
        {
            startRoot->SetRight(DeleteElem(startRoot->GetRight(), value));
        }

        else
        {
            if (startRoot->GetLeft() == nullptr && startRoot->GetRight() == nullptr)
            {
                delete startRoot;
                return nullptr;
            }

            else if (startRoot->GetLeft() == nullptr)
            {
                Node<T>* temp = startRoot;
                startRoot = startRoot->GetRight();
                delete temp;
            }

            else if (startRoot->GetRight() == nullptr)
            {
                Node<T>* temp = startRoot;
                startRoot = startRoot->GetLeft();
                delete temp;
            }

            else
            {
                startRoot->SetData(FindBSTMin(startRoot->GetRight())->GetData());
                startRoot->SetRight(DeleteElem(startRoot->GetRight(), startRoot->GetData()));
            }
        }
        return Balance(startRoot);
    }

    Node<T>* Insert(Node<T>* startRoot, const T& value)
    {
        if (startRoot == nullptr)
        {
            startRoot = new Node<T>(value);
        }

        if (value < startRoot->GetData())
        {
            startRoot->SetLeft(Insert(startRoot->GetLeft(), value));
        }

        else if (value > startRoot->GetData())
        {
            startRoot->SetRight(Insert(startRoot->GetRight(), value));
        }
        return Balance(startRoot);
    }

    Node<T>* FindNode(Node<T>* startRoot, const T& val) const
    {
        if (startRoot == nullptr)
        {
            return nullptr;
        }

        if (val == startRoot->GetData())
        {
            return startRoot;
        }

        else if (val < startRoot->GetData())
        {
            return FindNode(startRoot->GetLeft(), val);
        }

        else
        {
            return FindNode(startRoot->GetRight(), val);
        }
    }

    bool Compare(Node<T>* node1, Node<T>* node2) const
    {
        if (node1 == nullptr && node2 == nullptr)
        {
            return true;
        }

        else if (node1 == nullptr || node2 == nullptr)
        {
            return false;
        }
        return (node1->GetData() == node2->GetData()) && Compare(node1->GetLeft(), node2->GetLeft()) && Compare(node1->GetRight(), node2->GetRight());
    }

    bool SearchSubtree(Node<T>* node1, Node<T>* node2) const
    {
        if (node2 == nullptr)
        {
            return true;
        }

        else if (node1 == nullptr)
        {
            return false;
        }

        if (Compare(node1, node2))
        {
            return true;
        }
        return SearchSubtree(node1->GetLeft(), node2) || SearchSubtree(node1->GetRight(), node2);
    }

    Node<T>* Search(Node<T>* startRoot, const T& value) const
    {
        if (startRoot == nullptr)
        {
            throw  "ValueOutOfRange";
        }

        if (startRoot->GetData() == value)
        {
            return startRoot;
        }

        if (value <= startRoot->GetData())
        {
            return Search(startRoot->GetLeft(), value);
        }
        return Search(startRoot->GetRight(), value);
    }

    size_t Height(Node<T>* node) const
    {
        if (node)
        {
            return node->GetHeight();
        }
        return 0;
    }

    int BalanceFactor(Node<T>* node) const
    {
        if (node != nullptr)
        {
            return Height(node->GetLeft()) - Height(node->GetRight());
        }
        return 0;
    }

    void UpdateHeight(Node<T>* node) const
    {
        if (node)
        {
            size_t leftHeight = Height(node->GetLeft());
            size_t rightHeight = Height(node->GetRight());

            size_t maxHeight = (leftHeight > rightHeight) ? leftHeight : rightHeight;

            node->SetHeight(1 + maxHeight);
        }
    }

    Node<T>* RotateRight(Node<T>* node1)
    {
        Node<T>* node2 = node1->GetLeft();
        Node<T>* temp = node2->GetRight();

        node2->SetRight(node1);
        node1->SetLeft(temp);

        UpdateHeight(node1);
        UpdateHeight(node2);

        return node2;
    }

    Node<T>* RotateLeft(Node<T>* node1)
    {
        Node<T>* node2 = node1->GetRight();
        Node<T>* temp = node2->GetLeft();

        node2->SetLeft(node1);
        node1->SetRight(temp);

        UpdateHeight(node1);
        UpdateHeight(node2);

        return node2;
    }

    Node<T>* Balance(Node<T>* node)
    {
        UpdateHeight(node);

        int balance = BalanceFactor(node);
        if (balance > 1)
        {
            if (BalanceFactor(node->GetLeft()) < 0)
            {
                node->SetLeft(RotateLeft(node->GetLeft()));
            }
            return RotateRight(node);
        }

        if (balance < -1)
        {
            if (BalanceFactor(node->GetRight()) > 0)
            {
                node->SetRight(RotateRight(node->GetRight()));
            }
            return RotateLeft(node);
        }

        return node;
    }

    size_t CountNodes(Node<T>* node) const
    {
        if (!node)
        {
            return 0;
        }
        return 1 + CountNodes(node->GetLeft()) + CountNodes(node->GetRight());
    }

    T Get(Node<T>* node, size_t index) const
    {
        if (index >= CountNodes(node) || index < 0 || !node)
        {
            throw "Index out of range";
        }

        size_t leftSize = CountNodes(node->GetLeft());

        if (index < leftSize)
        {
            return Get(node->GetLeft(), index);
        }
        else if (index == leftSize)
        {
            return node->GetData();
        }
        else
        {
            return Get(node->GetRight(), index - leftSize - 1);
        }
    }

    bool SearchBool(Node<T>* startRoot, const T& value) const
    {
        if (startRoot == nullptr)
        {
            return false;
        }
        if (startRoot->GetData() == value)
        {
            return true;
        }
        if (value <= startRoot->GetData())
        {
            return SearchBool(startRoot->GetLeft(), value);
        }
        else
        {
            return SearchBool(startRoot->GetRight(), value);
        }
    }

    Node<T>* GetRoot() const
    {
        return this->root;
    }

public:
    BinaryTree() : root(nullptr) {}

    BinaryTree(Node<T>* root) : root(root) {}

    BinaryTree(const T& val) : root{ new Node<T>(val) } {}

    BinaryTree(T* items, int count)
    {
        for (int i = 0; i < count; i++)
        {
            *this += (items[i]);
        }
    }

    BinaryTree(const Node<T>& other) : root(new Node<T>(other)) {}

    BinaryTree(const BinaryTree<T>& other) : root{ new Node<T>(*other.root) } {}

    ~BinaryTree()
    {
        DeleteTree(this->GetRoot());
    }

    /*Node<T>* GetRoot() const
    {
        return this->root;
    }*/

    bool SearchBool(const T& value) const
    {
        return SearchBool(root, value);
    }

    BinaryTree<T>* SubTree(const T& val) const
    {
        Node<T>* subTreeRoot = FindNode(root, val);
        if (!subTreeRoot)
        {
            throw "Value not found in the tree";
        }
        return new BinaryTree<T>(new Node<T>(*subTreeRoot));
    }

    bool SearchSubtree(BinaryTree<T>* tree2) const
    {
        return SearchSubtree(this->GetRoot(), tree2->GetRoot());
    }

    T Get(size_t index) const
    {
        if (!root)
        {
            throw "Tree is empty";
        }
        return Get(root, index);
    }

    size_t GetLength() const
    {
        return CountNodes(this->GetRoot());
    }

    BinaryTree<T>& operator-=(const T& data)
    {
        root = DeleteElem(root, data);
        return *this;
    }

    BinaryTree<T>& operator+=(const T& data)
    {
        root = Insert(root, data);
        return *this;
    }
};

#endif 
