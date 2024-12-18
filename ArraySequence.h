#pragma once
#include "Sequence.h"
#include "DynamicArray.h"

template <class T>
class ArraySequence : public Sequence <T>
{
private:
	DynamicArray<T> items;
public:
	ArraySequence() : items{ DynamicArray<T>() } {}
	ArraySequence(const T* item, int count) : items{ DynamicArray<T>(item , count) } {}
	ArraySequence(const DynamicArray <T>& other) : items{ DynamicArray<T>(other) } {}

	T GetFirst() const override
	{
		if (this->items.GetSize() == 0)
		{
			throw "EmptyDynamicArray";
		}
		return this->items.Get(0);
	}

	T GetLast() const override
	{
		if (this->items.GetSize() == 0)
		{
			throw "EmptyDynamicArray";
		}
		return this->items.Get(this->items.GetSize() - 1);
	}

	T Get(int index) const override
	{
		return this->items.Get(index);
	}

	ArraySequence<T>* GetSubsequence(int startIndex, int endIndex) const override
	{
		DynamicArray<T> result(endIndex - startIndex + 1);

		if (startIndex >= this->items.GetSize() || startIndex < 0 || endIndex >= this->items.GetSize() || endIndex < 0)
		{
			throw  "IndexOutOfRange";
		}
		for (int i = startIndex; i <= endIndex; i++)
		{
			result.Set(i - startIndex, this->items.Get(i));
		}
		return new ArraySequence<T>(result);
	}

	int GetLength() const override
	{
		return this->items.GetSize();
	}

	void Append(const T& item) override
	{
		this->items.Resize(this->items.GetSize() + 1);
		this->items.Set(this->items.GetSize() - 1, item);
	}

	void Prepend(const T& item) override
	{
		DynamicArray<T> arr(this->items.GetSize() + 1);

		for (int i = this->items.GetSize(); i > 0; i--)
		{
			arr.Set(i, this->items.Get(i - 1));
		}
		arr.Set(0, item);

		this->items = *(new DynamicArray<T>(arr));
	}

	void InsertAt(const T& item, int index) override
	{
		if (index > this->GetLength() or index < 0)
		{
			throw  "IndexOutOfRange";
		}

		DynamicArray<T> arr(this->items.GetSize() + 1);

		for (int i = this->items.GetSize(); i > index; i--)
		{
			arr.Set(i, this->items.Get(i - 1));
		}
		arr.Set(index, item);
		for (int i = index - 1; i >= 0; i--)
		{
			arr.Set(i, this->items.Get(i));
		}
		this->items = *(new DynamicArray<T>(arr));
	}

	void Set(const T& item, int index) override
	{
		this->items.Set(index, item);
	}

	void RemoveAt(int index)
	{
		this->items.Pop(index);
	}

	ArraySequence <T>* Concat(const Sequence<T>* other) const override
	{
		DynamicArray<T> result(this->items);
		for (int i = 0; i < other->GetLength(); i++)
		{
			result.Append(other->Get(i));
		}
		return new ArraySequence<T>(result);
	}
};