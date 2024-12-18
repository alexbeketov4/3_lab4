#pragma once
template <class T>
class DynamicArray
{
private:
	size_t size;
	T* data;
public:
	DynamicArray()
	{
		this->size = 0;
		this->data = new T[0];
	}

	DynamicArray(const T* items, int count)
	{
		this->size = count;
		this->data = new T[size];
		for (int i = 0; i < size; i++)
		{
			this->data[i] = items[i];
		}
	}

	DynamicArray(size_t size)
	{
		this->size = size;
		data = new T[size];
		for (int i = 0; i < size; i++)
		{
			this->data[i] = T();
		}
	}

	DynamicArray(const DynamicArray<T>& dynamicArray)
	{
		this->size = dynamicArray.size;
		this->data = new T[size];
		for (int i = 0; i < size; i++)
		{
			data[i] = dynamicArray.data[i];
		}
	}

	~DynamicArray()
	{
		delete[] data;
	}

	size_t GetSize() const
	{
		return this->size;
	}

	T Get(int index) const
	{
		if (index < 0 || index >= this->size || index >= this->GetSize())
		{
			throw "IndexOutOfRange";
		}
		return this->data[index];
	}

	void Set(int index, const T& value)
	{
		if (index < 0 || index >= this->size || index >= this->GetSize())
		{
			throw "IndexOutOfRange";
		}
		this->data[index] = value;
	}

	void Resize(size_t newSize)
	{
		T* newData = new T[newSize];
		size_t minSize = (size < newSize) ? size : newSize;

		for (int i = 0; i < minSize; i++)
		{
			newData[i] = this->data[i];
		}

		delete[] this->data;
		this->data = newData;
		this->size = newSize;
	}

	void Append(const T& item)
	{
		this->Resize(this->GetSize() + 1);
		this->Set(this->GetSize() - 1, item);
	}

	void Pop(int index)
	{
		if (index < 0 || index >= this->size)
		{
			throw "IndexOutOfRange";
		}

		T* newData = new T[this->size - 1];
		for (int i = 0, j = 0; i < this->size; i++)
		{
			if (i != index)
			{
				newData[j] = this->data[i];
				j++;
			}
		}

		delete[] this->data;
		this->data = newData;
		this->size--;
	}
};
