#pragma once
#include "ArraySequence.h"

template<class TKey, class TElement>
class IDictionary
{
public:
	virtual int GetCount() const = 0;

	virtual TElement Get(TKey key) const = 0;

	virtual bool ContainsKey(TKey key) const = 0;

	virtual void Add(TKey key, TElement element) = 0;

	virtual ArraySequence<TKey> GetKeys() const = 0;

	virtual void Remove(TKey key) = 0;
};