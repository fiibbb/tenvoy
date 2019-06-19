#pragma once

#include <mutex>

#include <event2/event.h>
#include <pthread.h>

namespace Tenvoy {
    namespace Server {

        class Worker {
        public:
            Worker();
            void run();
            void wait();
        private:
            event_base* event_base;
            pthread_t thread_handle;
            std::mutex mu;
        };

        void* worker_thread_routine(void* arg);
    }
}
