#ifndef thunder_utils_concurrent_queue_hpp__
#define thunder_utils_concurrent_queue_hpp__

#include <queue>
#include <mutex>

namespace thunder
{
namespace utils
{
namespace concurrent
{
    template<class T>
    class Queue
    {
        std::queue<T> m_queue;
        std::mutex m_mutex;
    
    public:
        T& pop()
        {
            std::scoped_lock lock{ m_mutex };
            if ( !m_queue.empty() )
            {
                auto element = m_queue.front();
                m_queue.pop();
                return std::move(element);
            }

            return nullptr;
        }

        void push( const T& element )
        {
            std::scoped_lock lock{ m_mutex };
            m_queue.push( element );
        }

        bool empty()
        {
            std::scoped_lock lock{ m_mutex };
            return m_queue.empty();
        }
    };
};
};
};

#endif // thunder_utils_concurrent_queue_hpp__
