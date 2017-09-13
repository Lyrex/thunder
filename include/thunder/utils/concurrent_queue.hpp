#ifndef THUNDER_UTILS_CONCURRENT_QUEUE_HPP_
#define THUNDER_UTILS_CONCURRENT_QUEUE_HPP_

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
        std::queue<T> queue_;
        std::mutex mutex_;
    
    public:
        T pop()
        {
            std::lock_guard<std::mutex> lock{ mutex_ };
            if ( !queue_.empty() )
            {
				return std::forward<T>(queue_.pop());
            }

            return nullptr;
        }

        void push( const T& element )
        {
            std::lock_guard<std::mutex> lock{ mutex_ };
            queue_.push( element );
        }

        bool empty()
        {
            std::lock_guard<std::mutex> lock{ mutex_ };
            return queue_.empty();
        }
    };
};
};
};

#endif // THUNDER_UTILS_CONCURRENT_QUEUE_HPP_
