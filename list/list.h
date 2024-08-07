#pragma once

#include <iostream>
#include <stdexcept>
#include "list_node.h"
#include "list_iterator.h"
#include "list_const_iterator.h"
#include "list_reverse_iterator.h"

namespace DataStructure
{
    template <typename T>
    class List
    {
        typedef ListNode<T> Node;
    public:
        typedef ListIterator<T> iterator;
        typedef ListConstIterator<T> const_iterator;
        typedef ListReverseIterator<T> reverse_iterator;
    public:
        List();
        List(const List<T> & other);
        ~List();

        void assign(int n, const T & value);
        bool empty() const;
        int size() const;
        void show() const;

        void push_back(const T & value);
        void push_front(const T & value);
        void pop_back();
        void pop_front();
        T & front();
        const T & front() const;

        T & back();
        const T & back() const;

        void remove(const T & value);
        void clear();
        void resize(int size);
        void merge(List<T> & other);
        void reverse();
        void swap(List<T> & other);

        List<T> & operator = (const List<T> & other);

        iterator begin();
        iterator end();
        iterator insert(iterator pos, const T & value);
        iterator insert(iterator pos, int n, const T & value);
        iterator erase(iterator pos);
        iterator erase(iterator first, iterator last);
        iterator find(const T & value);

        const_iterator cbegin() const;
        const_iterator cend() const;
        const_iterator find(const T & value) const;

        reverse_iterator rbegin();
        reverse_iterator rend();
        reverse_iterator rfind(const T & value);

    private:
        Node * m_head;
        Node * m_tail;
        int m_size;
    };

    template <typename T>
    List<T>::List() : m_head(nullptr), m_tail(nullptr), m_size(0)
    {
    }

    template <typename T>
    List<T>::List(const List<T> & other)
    {
        *this = other;
    }

    template <typename T>
    List<T>::~List()
    {
        clear();
    }

    template <typename T>
    void List<T>::assign(int n, const T & value)
    {
        clear();
        for (int i = 0; i < n; i ++)
        {
            push_back(value);
        }
    }

    template <typename T>
    bool List<T>::empty() const
    {
        return m_size == 0;
    }

    template <typename T>
    int List<T>::size() const
    {
        return m_size;
    }

    template <typename T>
    void List<T>::show() const
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
    void List<T>::push_back(const T & value)
    {
        Node * node = new Node(value);
        if (m_size == 0)
        {
            m_head = m_tail = node;
            m_size++;
            return;
        }

        m_tail -> m_next = node;
        node -> m_prev = m_tail;
        m_tail = node;
        m_size++;
    }

    template <typename T>
    void List<T>::push_front(const T & value)
    {
        Node * node = new Node(value);
        if (m_size == 0)
        {
            m_head = m_tail = node;
            m_size++;
            return;
        }
        m_head -> m_prev = node;
        node -> m_next = m_head;
        m_head = node;
        m_size++;
    }

    template <typename T>
    void List<T>::pop_back()
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
        Node * tail = m_tail -> m_prev;
        tail -> m_next = nullptr;
        delete m_tail;
        m_tail = tail;
        m_size--;
    }

    template <typename T>
    void List<T>::pop_front()
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
        head -> m_prev = nullptr;
        delete m_head;
        m_head = head;
        m_size--;
    }

    template <typename T>
    T & List<T>::front()
    {
        if (m_size == 0)
        {
            throw std::logic_error("list is empty");
        }
        return m_head -> m_value;
    }

    template <typename T>
    const T & List<T>::front() const
    {
        if (m_size == 0)
        {
            throw std::logic_error("list is empty");
        }
        return m_head -> m_value;
    }

    template <typename T>
    T & List<T>::back()
    {
        if (m_size == 0)
        {
            throw std::logic_error("list is empty");
        }
        return m_tail -> m_value;
    }

    template <typename T>
    const T & List<T>::back() const
    {
        if (m_size == 0)
        {
            throw std::logic_error("list is empty");
        }
        return m_tail -> m_value;
    }

    template <typename T>
    void List<T>::remove(const T & value)
    {
        if (m_size == 0)
        {
            return;
        }
        while (m_head && m_head -> m_value == value)
        {
            Node * node = m_head -> m_next;
            node -> m_prev = nullptr;
            delete m_head;
            m_head = node;
            m_size--;
        }
        Node * node = m_head;
        while (node && node -> m_next)
        {
            if (node -> m_next -> m_value == value)
            {
                Node * temp = node -> m_next;
                node -> m_next = temp -> m_next;
                temp -> m_next -> m_prev = node;
                delete temp;
                m_size--;
            }
            node = node -> m_next;
        }
    }

    template <typename T>
    void List<T>::clear()
    {
        while (m_size > 0)
        {
            pop_back();
        }
    }

    template <typename T>
    void List<T>::resize(int size)
    {
        if (size < m_size)
        {
            for (int i = 0; m_size - size; i++)
            {
                pop_back();
            }
        }
        else if (size > m_size)
        {
            for (int i = 0; size - m_size; i++)
            {
                push_back(T());
            }
        }
    }

    template <typename T>
    void List<T>::merge(List<T> & other)
    {
        m_tail -> m_next = other.m_head;
        other.m_head -> m_prev = m_tail;
        m_tail = other.m_tail;
        m_size += other.m_size;

        other.m_head = other.m_tail = nullptr;
        other.m_size = 0;
    }

    template <typename T>
    void List<T>::reverse()
    {
        if (m_size == 0 || m_size == 1)
        {
            return;
        }
        Node * head = m_head;
        Node * tail = m_tail;
        Node * node = m_tail;
        while (node != nullptr)
        {
            Node * prev = node -> m_prev;
            Node * next = node -> m_next;
            node -> m_next = prev;
            node -> m_prev = next;
            node = prev;
        }
        m_head = tail;
        m_tail = head;
    }

    template <typename T>
    void List<T>::swap(List<T> & other)
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
    List<T> & List<T>::operator = (const List<T> & other)
    {
        if (this == &other)
        {
            return *this;
        }
        clear();
        for (auto it = other.cbegin(); it != other.cend(); ++it)
        {
            push_back(*it);
        }
        return *this;
    }

    template <typename T>
    typename List<T>::iterator List<T>::begin()
    {
        return iterator(m_head);
    }

    template <typename T>
    typename List<T>::iterator List<T>::end()
    {
        if (m_size == 0)
            return iterator();
        else
            return iterator(m_tail -> m_next);
    }

    template <typename T>
    typename List<T>::iterator List<T>::insert(iterator pos, const T & value)
    {
        return insert(pos, 1, value);
    }

    template <typename T>
    typename List<T>::iterator List<T>::insert(iterator pos, int n, const T & value) //return the iterator to the first inserted element
    {
        if (pos == begin())
        {
            for (int i = 0; i < n; i++)
            {
                push_front(value);
            }
            return begin();
        }
        else if (pos == end())
        {
            Node * tail = m_tail;
            for (int i = 0; i < n; i++)
            {
                push_back(value);
            }
            return iterator(tail -> m_next);
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                Node * node = new Node(value);
                Node * prev = pos.m_pointer -> m_prev;
                node -> m_prev = prev;
                prev -> m_next = node;
                node -> m_next = pos.m_pointer;
                pos.m_pointer -> m_prev = node;
                pos.m_pointer = node;
            }
            m_size += n;
            return pos;
        }
    }

    template <typename T>
    typename List<T>::iterator List<T>::erase(iterator pos)
    {
        if (pos == begin())
        {
            Node * node = m_head;
            if (m_size > 1)
            {
                m_head = m_head -> m_next;
                m_head -> m_prev = nullptr;
                delete node;
            }
            else
            {
                delete m_head;
                m_head = m_tail = nullptr;
            }
            m_size--;
            return begin();
        }
        else if (pos == end())
        {
            return pos;
        }
        else
        {
            Node * node = pos.m_pointer;
            if (node -> m_prev != nullptr)
            {
                node -> m_prev -> m_next = node -> m_next;
            }
            if (node -> m_next != nullptr)
            {
                node -> m_next -> m_prev = node -> m_prev;
            }
            auto next = node -> m_next;
            delete node;
            m_size--;
            return iterator(next);
        }
    }

    template <typename T>
    typename List<T>::iterator List<T>::erase(iterator first, iterator last)
    {
        for (auto it = first; it != last; it++)
        {
            erase(it);
        }
        return last;
    }

    template <typename T>
    typename List<T>::iterator List<T>::find(const T & value)
    {
        auto node = m_head;
        while (node != nullptr)
        {
            if (node -> m_value == value)
                break;
        }
        return iterator(node);
    }

    template <typename T>
    typename List<T>::const_iterator List<T>::cbegin() const
    {
        return const_iterator(m_head);
    }

    template <typename T>
    typename List<T>::const_iterator List<T>::cend() const
    {
        if (m_size == 0)
            return const_iterator();
        else
            return const_iterator(m_tail -> m_next);
    }

    template <typename T>
    typename List<T>::const_iterator List<T>::find(const T & value) const
    {
        auto node = m_head;
        while (node != nullptr)
        {
            if (node -> m_value == value)
                break;
        }
        return const_iterator(node);
    }

    template <typename T>
    typename List<T>::reverse_iterator List<T>::rbegin()
    {
        return reverse_iterator(m_tail);
    }

    template <typename T>
    typename List<T>::reverse_iterator List<T>::rend()
    {
        if (m_size == 0)
            return reverse_iterator();
        else
            return reverse_iterator(m_head -> m_prev);
    }

    template <typename T>
    typename List<T>::reverse_iterator List<T>::rfind(const T & value)
    {
        for (auto it = rbegin(); it != rend(); it++)
        {
            if (*it == value)
            {
                return it;
            }
        }
        return rend();
    }


}
