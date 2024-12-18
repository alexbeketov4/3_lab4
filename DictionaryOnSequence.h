#pragma once
#include "IDictionary.h"
#include "ArraySequence.h"

template<typename TKey, typename TElement>
class DictionaryOnSequence : public IDictionary<TKey, TElement>
{
private:
    struct KeyValuePair
    {
        TKey key;
        TElement value;

        KeyValuePair() : key(TKey()), value(TElement()) {}

        KeyValuePair(TKey key, TElement value) : key(key), value(value) {}

        TKey GetKey()
        {
            return key;
        }
    };

    ArraySequence<KeyValuePair> list;

public:
    DictionaryOnSequence() {}

    int GetCount() const override
    {
        return list.GetLength();
    }

    TElement Get(TKey key) const override
    {
        for (int i = 0; i < list.GetLength(); ++i)
        {
            if (list.Get(i).key == key)
            {
                return list.Get(i).value;
            }
        }
        throw "Key not found";
    }

    KeyValuePair GetByIndex(int index) const
    {
        if (index < 0 || index >= list.GetLength())
        {
            throw "Index out of range";
        }
        return list.Get(index);
    }

    bool ContainsKey(TKey key) const override
    {
        for (int i = 0; i < list.GetLength(); ++i)
        {
            if (list.Get(i).key == key)
            {
                return true;
            }
        }
        return false;
    }

    void Add(TKey key, TElement element) override
    {
        if (ContainsKey(key))
        {
            throw "Key already exists";
        }
        list.Append(KeyValuePair(key, element));
    }

    ArraySequence<TKey> GetKeys() const override
    {
        ArraySequence<TKey> keys;
        for (int i = 0; i < list.GetLength(); ++i)
        {
            keys.Append(list.Get(i).key);
        }
        return keys;
    }

    void Remove(TKey key) override
    {
        for (int i = 0; i < list.GetLength(); ++i)
        {
            if (list.Get(i).key == key)
            {
                list.RemoveAt(i);
                return;
            }
        }
        throw "Key not found";
    }
};