#pragma once

#include <functional>
#include <iostream>
#include <utility>
#include <vector>

namespace Da
{
    template <typename T, typename Container = std::vector<T>, typename Compare = std::less<T>>
    class Heap
    {

    public:
        Heap();
        ~Heap();

        void push(const T & value);
        void pop();
        const T & top() const;
        bool empty() const;
        int size() const;
        void swap(Heap<T, Container, Compare> & other);
        void show() const;

    private:
        void heapify(int i);

    private:
        Container m_container;
        Compare m_compare;
    };

    template <typename T, typename Container, typename Compare>
    Heap<T, Container, Compare>::Heap() {}

    template <typename T, typename Container, typename Compare>
    Heap<T, Container, Compare>::~Heap() {}

    template <typename T, typename Container, typename Compare>
    void Heap<T, Container, Compare>::heapify(int i) //堆化
    {
        int size = m_container.size();
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < size && m_compare(m_container[largest], m_container[l]))
        {
            largest = l;
        }
        if (r < size && m_compare(m_container[largest], m_container[r]))
        {
            largest = r;
        }
        if (largest != i)
        {
            // swap the value of index i and largest
            T temp = m_container[i];
            m_container[i] = m_container[largest];
            m_container[largest] = temp;
        }
    }

    template <typename T, typename Container, typename Compare>
    void Heap<T, Container, Compare>::push(const T & value)
    {
        m_container.push_back(value);
        int size = m_container.size();
        if (size > 1)
        {
            int index = size - 1;
            int parent = (index - 1) / 2;
            while (index > 0 && m_compare(m_container[parent], m_container[index]))
            {
                std::swap(m_container[index], m_container[parent]);
                index = parent;
            }
        }
    }

    template <typename T, typename Container, typename Compare>
    void Heap<T, Container, Compare>::pop()
    {
        int size = m_container.size();
        
        std::swap(m_container[size - 1], m_container[0]);

        m_container.pop_back();

        size = m_container.size();
        if (size > 1)
        {
            int index = 0;
            while (index <= (size - 1 - 1) / 2)
            {
                int left = 2 * index + 1;
                int right = 2 * index + 2;
                int max_ = index;

                if (m_compare(m_container[max_], m_container[left]))
                {
                    max_ = left;
                }
                if (m_compare(m_container[max_], m_container[right]))
                {
                    max_ = right;
                }

                if (max_ == index) break;

                std::swap(m_container[index], m_container[max_]);

                index = max_;
            }
        }
    }

    template <typename T, typename Container, typename Compare>
    const T & Heap<T, Container, Compare>::top() const
    {
        return m_container.front();
    }

    template <typename T, typename Container, typename Compare>
    bool Heap<T, Container, Compare>::empty() const
    {
        return m_container.empty();
    }

    template <typename T, typename Container, typename Compare>
    int Heap<T, Container, Compare>::size() const
    {
        return m_container.size();
    }

    template <typename T, typename Container, typename Compare>
    void Heap<T, Container, Compare>::swap(Heap<T, Container, Compare> & other)
    {
        m_container.swap(other.m_container);
    }

    template <typename T, typename Container, typename Compare>
    void Heap<T, Container, Compare>::show() const
    {
        m_container.show();
    }

}
