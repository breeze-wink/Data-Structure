#pragma once

#include <iostream>
#include <stdexcept>
#include "forward_list_node.h"
#include "forward_list_iterator.h"
#include "forward_list_const_iterator.h"

namespace DataStructure::forward_list
{
    template <typename T>
    class ForwardList
    {
        typedef ForwardListNode<T> Node;
    public:
        typedef ForwardListIterator<T> iterator;
        typedef ForwardListConstIterator<T> const_iterator;
    public:
        ForwardList();
        ~ForwardList();

        void assign(int n, const T & value);
        bool empty() const;
        int size() const;
        void show() const;

        void push_front(const T & value);
        void pop_front();

        void push_back(const T & value);
        void pop_back();

        T & front();
        const T & front() const;

        T & back();
        const T & back() const;

        void remove(const T & value);
        void clear();
        void resize(int size);
        void merge(ForwardList<T> & other);
        void swap(ForwardList<T> & other);
        void reverse();

        ForwardList<T> & operator = (const ForwardList<T> & other);

        iterator begin();
        iterator end();

        iterator insert_after(iterator pos, const T & value);
        iterator insert_after(iterator pos, int n, const T & value);

        iterator erase_after(iterator pos);
        iterator erase_after(iterator first, iterator last);

        const_iterator cbegin() const;
        const_iterator cend() const;

    private:
        Node * m_head;
        Node * m_tail;
        int m_size;
    };
    
    template <typename T>
    ForwardList<T>::ForwardList() : m_head(nullptr), m_tail(nullptr), m_size(0)
    {
    }

    template <typename T>
    ForwardList<T>::~ForwardList()
    {
        clear();
    }

    template <typename T>
    void ForwardList<T>::assign(int n, const T & value)
    {
        clear();
        for (int i = 0; i < n; i++)
        {
            push_back(value);
        }
    }

    template <typename T>
    bool ForwardList<T>::empty() const
    {
        return m_size == 0;
    }

    template <typename T>
    int ForwardList<T>::size() const
    {
        return m_size;
    }

    template <typename T>
    void ForwardList<T>::show() const
    {
        std::cout << "size=" << size() << std::endl;
        Node * node = m_head;
        while (node != nullptr)
        {
            std::cout << node -> m_value << ", ";
            node = node -> m_next;
        }
        std::cout << std::endl;
    }

    template <typename T>
    void ForwardList<T>::push_front(const T &value)
    {
        Node * node = new Node(value);
        if (m_size == 0)
        {
            m_head = m_tail = node;
            m_size++;
            return;
        }
        node -> m_next = m_head;
        m_head = node;
        m_size++;
    }

    template <typename T>
    void ForwardList<T>::pop_front()
    {
        if (m_size == 0)
        {
            return;
        }
        if (m_size == 1)
        {
            delete m_head;
            m_head = m_tail = nullptr;
            m_size--;
            return;
        }
        Node * head = m_head -> m_next;
        delete m_head;
        m_head = head;
        m_size--;
    }

    template <typename T>
    void ForwardList<T>::push_back(const T &value)
    {
        Node * node = new Node(value);
        if (m_size == 0)
        {
            m_head = m_tail = node;
            m_size++;
            return;
        }
        m_tail -> m_next = node;
        m_tail = node;
        m_size++;
    }

    template <typename T>
    void ForwardList<T>::pop_back()
    {
        if (m_size == 0)
        {
            return;
        }
        if (m_size == 1)
        {
            delete m_tail;
            m_head = m_tail = nullptr;
            m_size--;
            return;
        }
        Node * node = m_head;
        while (node != nullptr)
        {
            if (node -> m_next == m_tail)
            {
                break;
            }
            node = node -> m_next;
        }
        delete m_tail;
        node -> m_next = nullptr;
        m_tail = node;
        m_size--;
    }

    template <typename T>
    T & ForwardList<T>::front()
    {
        if (m_size == 0)
        {
            throw std::logic_error("forward list is empty");
        }
        return m_head -> m_value;
    }

    template <typename T>
    const T & ForwardList<T>::front() const
    {
        if (m_size == 0)
        {
            throw std::logic_error("forward list is empty");
        }
        return m_head -> m_value;
    }

    template <typename T>
    T & ForwardList<T>::back()
    {
        if (m_size == 0)
        {
            throw std::logic_error("forward list is empty");
        }
        return m_tail -> m_value;
    }

    template <typename T>
    const T & ForwardList<T>::back() const
    {
        if (m_size == 0)
        {
            throw std::logic_error("forward list is empty");
        }
        return m_tail -> m_value;
    }

    template <typename T>
    void ForwardList<T>::remove(const T & value) //删除值为value的元素
    {
        if (m_size == 0)
        {
            return;
        }
        //先删除头结点之后的
        while (m_head && m_head -> m_value == value)
        {
            Node * node = m_head -> m_next;
            delete m_head;
            m_head = node;
            m_size--;
        }
        //确保头结点不变后，接着删除后面的
        Node * node = m_head;
        while (node && node -> m_next)
        {
            if (node -> m_next -> m_value == value)
            {
                Node * temp = node -> m_next;
                node -> m_next = temp -> m_next;
                delete temp;
                m_size--;
            }
            node = node -> m_next;
        }
    }

    template <typename T>
    void ForwardList<T>::clear()
    {
        while (m_size > 0)
        {
            pop_front();
        }
    }

    template <typename T>
    void ForwardList<T>::resize(int size)
    {
        if (size < m_size)
        {
            for (int i = 0; i < m_size - size; i++)
            {
                pop_back();
            }
        }
        else if (size > m_size)
        {
            for (int i = 0; i < size - m_size; i++)
            {
                push_back(T());
            }
        }
    }

    template <typename T>
    void ForwardList<T>::merge(ForwardList<T> & other)
    {
        m_tail -> m_next = other.m_head;
        m_tail = other.m_tail;
        m_size += other.m_size;

        other.m_head = other.m_tail = nullptr;
        other.m_size = 0;
    }

    template <typename T>
    void ForwardList<T>::swap(ForwardList<T> & other)
    {
        if (this == &other)
        {
            return;
        }
        Node * head = other.m_head;
        Node * tail = other.m_tail;
        int size = other.m_size;

        other.m_head = m_head;
        other.m_tail = m_tail;
        other.m_size = m_size;

        m_head = head;
        m_tail = tail;
        m_size = size;
    }

    template <typename T>
    ForwardList<T> & ForwardList<T>::operator = (const ForwardList<T> & other)
    {
        if (this == &other)
        {
            return *this;
        }
        resize(other.size());
        Node * l = m_head;
        Node * r = other.m_head;
        while (l != nullptr)
        {
            l -> m_value = r -> m_value;
            l = l -> m_next;
            r = r -> m_next;
        }
        return *this;
    }

    template <typename T>
    typename ForwardList<T>::iterator ForwardList<T>::begin()
    {
        return iterator(m_head);
    }

    template <typename T>
    typename ForwardList<T>::iterator ForwardList<T>::end()
    {
        if (m_size == 0)
            return iterator();
        else
            return iterator(m_tail -> m_next);
    }

    template <typename T>
    typename ForwardList<T>::iterator ForwardList<T>::insert_after(iterator pos, const T & value)
    {
        return insert_after(pos, 1, value);
    }

    template <typename T>
    typename ForwardList<T>::iterator ForwardList<T>::insert_after(iterator pos, int n, const T & value) //从pos开始插入n个value
    {
        if (pos == begin())
        {
            for (int i = 0; i < n; i++)
            {
                push_front(value);
            }
            return begin();
        }
        for (int i = 0; i < n; i++)
        {
            Node * node = new Node(value);
            node -> m_next = pos.m_pointer -> m_next;
            pos.m_pointer -> m_next = node;
        }
        m_size += n;
        return pos;
    }

    template <typename T>
    typename ForwardList<T>::iterator ForwardList<T>::erase_after(iterator pos)
    {
        if (pos == end())
        {
            return pos;
        }
        Node * node = pos.m_pointer;
        Node * temp = node -> m_next;
        node -> m_next = temp -> m_next;
        delete temp;
        m_size--;
        return iterator(node -> m_next);
    }

    template <typename T>
    typename ForwardList<T>::iterator ForwardList<T>::erase_after(iterator first, iterator last)
    {
        for (ForwardList<T>::iterator it = first; it != last; it++)
        {
            erase_after(it);
        }
        return last;
    }

    template <typename T>
    typename ForwardList<T>::const_iterator ForwardList<T>::cbegin() const
    {
        return const_iterator(m_head);
    }

    template <typename T>
    typename ForwardList<T>::const_iterator ForwardList<T>::cend() const
    {
        if (m_size == 0)
            return const_iterator();
        else
            return const_iterator(m_tail -> m_next);
    }
}
