#pragma once

template<class T>
class ISet
{
public:
	virtual T Get(int index) const = 0;

	virtual void Insert(const T& item) = 0;

	virtual size_t GetLength() const = 0;

	virtual void Delete(const T& item) = 0;

	virtual bool Contains(const T& item) const = 0;

	virtual bool SubSet(const ISet<T>* other) const = 0;
};