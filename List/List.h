#ifndef __LIST_MARK__
#define __LIST_MARK__

#include <utility>
#include <initializer_list>

template <typename Object>
class List
{
private:
    struct Node
    {
        Object data; /**<! 节点内存放的数据. */
        Node *prev;  /**<! 指向前一个节点的指针. */
        Node *next;  /**<! 指向后一个节点的指针. */
        Node(const Object &d = Object{}, Node *p = nullptr,
             Node *n = nullptr)
            : data{d}, prev{p}, next{n} {}

        Node(Object &&d, Node *p = nullptr, Node *n = nullptr)
            : data{std::move(d)}, prev{p}, next{n} {}
    };

public:
    class const_iterator
    {
    public:
        const_iterator() : current{nullptr}
        {
        }

        const Object &operator*() const
        {
            return retrieve();
        }

        const_iterator &operator++()
        {
            current = current->next;
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        const_iterator &operator--()
        {
            current = current->prev;
            return *this;
        }

        const_iterator operator--(int)
        {
            const_iterator old = *this;
            --(*this);
            return old;
        }

        bool operator==(const const_iterator &rhs) const
        {
            return current == rhs.current;
        }

        bool operator!=(const const_iterator &rhs) const
        {
            /// 这里直接调用 == 运算，多了一次调用，但能确保一致性.
            return !(*this == rhs);
        }

    protected:

        Node *current; /**<! 当前节点的指针. */

        Object &retrieve() const
        {
            return current->data;
        }

        const_iterator(Node *p) : current{p}
        {
        }

        friend class List<Object>; /**<! 使 List 类可以访问到迭代器的私有成员和 protected 成员. */

        /// 注意到 const_iterator 并没有提供析构函数，因为它不需要也不应该释放内存.
    };

    class iterator : public const_iterator
    {
    public:
        iterator()
        {
        }

        Object &operator*()
        {
            return const_iterator::retrieve();
        }

        const Object &operator*() const
        {
            return const_iterator::operator*();
        }

        iterator &operator++()
        {
            this->current = this->current->next;
            return *this;
        }

        iterator operator++(int)
        {
            iterator old = *this;
            ++(*this);
            return old;
        }

        iterator &operator--()
        {
            this->current = this->current->prev;
            return *this;
        }
        
        iterator operator--(int)
        {
            iterator old = *this;
            --(*this);
            return old;
        }

    protected:
        iterator(Node *p) : const_iterator{p}
        {
        }

        friend class List<Object>;  /**<! 同样使 List 类可以访问到迭代器的私有成员和 protected 成员. */
    };

public:
    List() { init( ); }

    List(std::initializer_list<Object> il) : List()
    {
        for (const auto & x : il)
            push_back(x);
    }

    List(const List &rhs)
    {
        /// 先初始化一个空的 List.
        init( );
        /// 然后遍历右操作对象，将右操作对象的数据一个一个插入到 List 中.
        /// 这里的 auto 指针会自行推断类型. 这里的 x 是一个引用，所以不会发生拷贝.
        /// 而这里的 for 循环的方式实际上让我们可以遍历一个容器，而不需要知道容器的具体类型.
        /// 也就是说，实际上这里是通过 iterator 来遍历的. 这里的 rhs 是一个 List，所以它有 begin 和 end 函数.
        /// 这段代码的实际效果等价于
        ///     for (auto it = rhs.begin(); it != rhs.end(); ++it) {  
        ///         auto &x = *it;  
        ///         push_back(x);  
        ///     }
        for (auto & x : rhs)
            /// 调用成员函数从后方（为何）插入到 List 中.
            push_back(x);
    }

    /**
     * @brief 析构函数，用于释放 List 中的内存.
     * 实际工作是调用 clear 函数，然后释放头尾节点的内存. 别忘了这两个哨兵.
     * 
     */
    ~List()
    {
        clear( );
        delete head;
        delete tail;
    }

    /// ？？？
    // List &operator=(const List &rhs)
    // {
    //     List copy = rhs;
    //     std::swap( *this, copy );
    //     return *this;
    // }

    /**
     * @brief 赋值运算符. 用于将一个 List 的数据赋值给另一个 List.
     * 这里采用了 copy-and-swap 的技术. 通过传值的方式来调用拷贝构造函数，
     * 然后通过 swap 来交换数据. 而 copy 这个临时对象会在函数结束时被销毁.
     * 这个技术使得整个过程逻辑简单，并且效率更高. 但是一些实现的关键技术细节都是在 
     * C++ 14 起引入的，因此只实现了 C++ 11 的版本的课本并没有做到.
     */
    List &operator=(List copy)
    {
    //    std::swap( *this, copy );
    /// 这里直接 swap 两个对象是错误的，因为 List 并未定义 swap 操作.
    /// 当发生右值引用时, 会导致一个对象被析构，而另一个对象被赋值.
        std::swap( theSize, copy.theSize );
        std::swap( head, copy.head );
        std::swap( tail, copy.tail );
        return *this;
    }

    /**
     * @brief 移动构造函数. 用于将一个右值引用的 List 的数据移动到另一个 List 中.
     * 
     * @param rhs 必须是一个右值引用. 因此不存在右操作数不存在的情况，不需要考虑缺省.
     */
    List(List &&rhs) : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
    {
        /// 因为 rhs 是一个右值引用，所以我们最好直接将其数据置空. 
        /// 从而实现移动. 不然如果 rhs.head 还管理原来的数据，那么当它被析构时，
        /// 就可能释放掉已经移交给新对象的数据.
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }
    
    // // 这个功能已经被上面的实现所覆盖. 所以不再需要.
    // List &operator=(List &&rhs)
    // {
    //     std::swap( theSize, rhs.theSize );
    //     std::swap( head, rhs.head );
    //     std::swap( tail, rhs.tail );
    //     return *this;
    // }

    /**
     * @brief 返回一个迭代器，指向 List 的第一个元素.
     * 
     * @return iterator 
     */
    iterator begin()
    {
        /// head 指向的是一个哨兵节点，它的 next 指向的是第一个数据节点.
        return { head->next };
    }

    /**
     * @brief 返回一个只读的迭代器，指向 List 的第一个元素.
     * 
     * @return const_iterator 
     */
    const_iterator begin() const
    {
        return { head->next };
    }

    /**
     * @brief 返回一个迭代器，指向 List 的最后一个元素之后（哨兵元素）.
     * 
     * @return iterator 动态迭代器，可修改元素.
     */
    iterator end()
    {
        return { tail };
    }

    /**
     * @brief 返回一个迭代器，指向 List 的最后一个元素之后（哨兵元素）.
     * 
     * @return const_iterator 静态迭代器，只读.
     */
    const_iterator end() const
    {
        return { tail };
    }

    /// 这里调用静态还是动态，实际上取决于调用的环境. 如果调用的是 const 对象，那么就会调用 const 的版本. 

    /**
     * @brief 返回 List 中数据节点的总数.
     * 
     * @return int 
     */
    int size() const
    {
        return theSize;
    }

    /**
     * @brief 判断 List 是否为空.
     * 
     * @return true 空.
     * @return false 非空.
     */
    bool empty() const
    {
        return size() == 0;
    }

    /**
     * @brief 清空 List 中的数据.
     * 
     */
    void clear()
    {
        /// 这里其实用计数器来判断 List 是否为空.
        while (!empty())
            pop_front();
    }

    /**
     * @brief 返回 List 中第一个数据节点的数据.
     * 
     * @return Object& 可以修改的第一个数据节点的数据.
     */
    Object &front()
    {
        return *begin();
    }

    /**
     * @brief 返回 List 中第一个数据节点的数据.
     * 
     * @return const Object& 只读的第一个数据节点的数据.
     */
    const Object &front() const
    {
        return *begin();
    }

    /**
     * @brief 返回 List 中最后一个数据节点的数据.
     * 
     * @return Object& 可以修改.
     */
    Object &back()
    {
        return *--end();
    }

    /**
     * @brief 返回 List 中最后一个数据节点的数据.
     * 
     * @return const Object& 只读.
     */
    const Object &back() const
    {
        return *--end();
    }

    /**
     * @brief 将一个左值数据节点插入到 List 的头部.
     * 
     * @param x 数据节点.
     */
    void push_front(const Object &x)
    {
        insert(begin(), x);
    }

    /**
     * @brief 将一个右值数据节点插入到 List 的头部.
     * 
     * @param x 数据节点.
     */
    void push_front(Object &&x)
    {
        insert(begin(), std::move(x));
    }

    /**
     * @brief 将一个左值数据节点插入到 List 的尾部.
     * 
     * @param x 数据节点.
     */
    void push_back(const Object &x)
    {
        insert(end(), x);
    }

    /**
     * @brief 将一个右值数据节点插入到 List 的尾部.
     * 
     * @param x 数据节点.
     */
    void push_back(Object &&x)
    {
        insert(end(), std::move(x));
    }

    /**
     * @brief 删除 List 的第一个数据节点.
     * 
     */
    void pop_front()
    {
        erase(begin());
    }

    /** 
     * @brief 删除 List 的最后一个数据节点.
     * 
     */
    void pop_back()
    {
        erase(--end());
    }

    /**
     * @brief 插入一个左值数据节点到指定位置.
     * 
     * @param itr 插入位置的迭代器.
     * @param x 数据节点.
     * @return iterator 返回插入位置的迭代器.
     */
    iterator insert(iterator itr, const Object &x)
    {
        Node *p = itr.current;
        theSize++;
        /// 仔细想一下这个过程.
        return { p->prev = p->prev->next = new Node{ x, p->prev, p } };
    }

    /**
     * @brief 插入一个右值数据节点到指定位置.
     * 
     * @param itr 插入位置的迭代器.
     * @param x 数据节点.
     * @return iterator 返回插入位置的迭代器.
     */
    iterator insert(iterator itr, Object &&x)
    {
        Node *p = itr.current;
        theSize++;
        return { p->prev = p->prev->next = new Node{ std::move( x ), p->prev, p } };
    }

    /**
     * @brief 删除指定位置的数据节点. 由于哨兵节点的存在，不用担心删完了以后最后变成一个 nullptr.
     * 
     * @param itr 指定位置的迭代器.
     * @return iterator 返回删除位置的下一个迭代器.
     */
    iterator erase(iterator itr)
    {
        Node *p = itr.current;
        iterator retVal{ p->next };
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        theSize--;
        return retVal;
    }

    /**
     * @brief 删除指定范围的数据节点. 比一个个删除效率高么？
     * 
     * @param from 起始位置的迭代器.
     * @param to 结束位置的迭代器.
     * @return iterator 返回删除位置的下一个迭代器.
     */
    iterator erase(iterator from, iterator to)
    {
        /// 这里其实就是重复调用了单个节点删除的 erase 函数.
        /// 因此这个内循环和外部循环完全一致. 
        /// 这里可以做适当的优化么?
        for( iterator itr = from; itr != to; )
            itr = erase( itr );
        return to;
    }

private:
    int theSize;    /**<! 数据节点总数. */
    Node *head;     /**<! 头指针. */
    Node *tail;     /**<! 尾指针. */
    
    /**
     * @brief 初始化 List. 用于构造函数中初始化 List. 构建一张空表.
     * 
     */
    void init()
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
};

#else
// DO NOTHING.
#endif