
#include <iostream>     // std::cout
#include <string.h>     //strlen , memset
#include <ctype.h>      // tolower

#include "dictionary.hpp"

#define AB_SIZE 26

using namespace ilrd;


/*******************class Trie**********************************************/
    class Dict::Trie
    {
    public:
        explicit Trie (): m_is_end_of_word (0) 
        {
            memset(m_node , 0 , sizeof(m_node));
        }
        ~Trie();

        Dict::STATUS Insert (const char* word );

        bool Contains(const char* word) const;

        Dict::STATUS Remove(const char* word);

    private:
        int m_is_end_of_word ;
        Trie *m_node[AB_SIZE];
    };

/********************class Dict functoins***************************************/
/*******************************************************************************/
    Dict::Dict():root ( new Trie()) ,m_size (0)
    {
    }

    Dict::~Dict()
    {
        delete root;
    }

    /* insert word , call to insert Trie
        and increase the size in 1 if success */
    Dict::STATUS Dict::Insert(const char* word)
    {
       if(0== root->Insert(word))
       {
           m_size++;
           return SUCCESS;
       }
        return MEMORY_FAILUE;
    }

    Dict::STATUS Dict::Remove(const char* word)
    {
        if (SUCCESS == root->Remove(word))
        {
            m_size--;
            return SUCCESS;
        }

        return MEMORY_FAILUE;

    }

    size_t Dict::Count() const
    {
        return m_size;
    }

    bool Dict::Contains(const char* word) const
    {
        return (root->Contains(word));
    }


/******************* class Trie functoins **************************************/
/*******************************************************************************/
 Dict::Trie::~Trie()
 {
     for (int i = 0; i<AB_SIZE ; i++ )
     {
         delete m_node[i];
     }
 }

Dict::STATUS Dict::Trie::Insert(const char* word)
{
   if ('\0' == word[0])
   {
       m_is_end_of_word = true;
       return SUCCESS;
   }

   if (tolower(word[0]) < 'a' || tolower(word[0]) > 'z')
   {
        return   MEMORY_FAILUE;
   }
   if (NULL == m_node[tolower(word[0]) - 'a'])
   {
       m_node[tolower(word[0]) - 'a'] = new Trie();
   }
   
    return  m_node[tolower(word[0]) - 'a']->Insert(&word[1]);     
}


Dict::STATUS Dict::Trie::Remove(const char* word)
{
   if ('\0' == word[0])
   {
       if (m_is_end_of_word)
       {
            m_is_end_of_word = false;
            
            return SUCCESS;
       }
        return MEMORY_FAILUE;

   }

   if (NULL == m_node[tolower(word[0]) - 'a'])
   {
      return MEMORY_FAILUE;
   }
     return  m_node[tolower(word[0]) - 'a']->Remove(&word[1]);
       
    
}

bool Dict::Trie::Contains(const char* word) const
{
   if ('\0' == word[0])
   {
        return m_is_end_of_word;
   }

   if (NULL == m_node[tolower(word[0]) - 'a'])
   {
      return false;
   }
     return  m_node[tolower(word[0]) - 'a']->Contains(&word[1]);

}





