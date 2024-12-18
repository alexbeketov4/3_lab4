#pragma once
#include "BinaryTree.h"
#include "ISet.h"

template<class T>
class SetOnBinaryTree : public ISet<T>
{
private:
	BinaryTree<T> tree;
public:

	SetOnBinaryTree() : tree() {}

	SetOnBinaryTree(const BinaryTree<T>& other) : tree(other) {}

	SetOnBinaryTree(const SetOnBinaryTree<T>& other) : tree(other.tree) {}

	SetOnBinaryTree(T* items, int count) : tree(items, count) {}


	T Get(int index) const override
	{
		return tree.Get(index);
	}

	void Insert(const T& item) override
	{
		tree += item;
	}

	size_t GetLength() const override
	{
		return tree.GetLength();
	}

	void Delete(const T& item) override
	{
		tree -= item;
	}

	bool Contains(const T& item) const override
	{
		return tree.SearchBool(item);
	}

	bool SubSet(const ISet<T>* other) const override
	{
		for (int i = 0; i != other->GetLength(); i++)
		{
			if (!(this->Contains(other->Get(i))))
			{
				return false;
			}
		}
		return true;
	}
};
