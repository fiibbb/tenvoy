#pragma once

#include <mutex>
#include <map>

#include <event2/event.h>
#include <pthread.h>

namespace Tenvoy {
    namespace Server {

        class Worker {
        public:
            Worker(int, int);
            void run();
            void wait();
            void thread_routine();
            event_base* event_base;
            int listen_fd;
            int id;
        private:
            pthread_t thread_handle;
            std::mutex mu;
        };

        void* worker_pthread_routine_wrapper(void* arg);
    }
}
