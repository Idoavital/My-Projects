#ifndef __DICT_H__
#define __DICT_H__

#include <cstdio>


namespace ilrd
{

//uncopyable class

class Dict
{

public:
            
    enum STATUS
    {
        SUCCESS,
        MEMORY_FAILUE
    };

    explicit Dict();
    ~Dict();

    STATUS Insert(const char* word);

    STATUS Remove(const char* word);

    size_t Count() const;

    bool Contains(const char* word) const;

private:

    Dict(const Dict& other);

    Dict& operator=(const Dict& other);

    class Trie;

    Trie *root;

    size_t m_size;
    };

}
#endif /* __DICT_H__ */
