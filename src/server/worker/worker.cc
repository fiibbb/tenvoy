#include <iostream>

#include <pthread.h>

#include "worker.h"

namespace Tenvoy {
    namespace Server {

        Worker::Worker() {
            event_base = event_base_new();
            if (event_base == nullptr) {
                throw std::exception();
            }
        }

        void Worker::run() {
            pthread_create(&thread_handle, nullptr, worker_thread_routine, this);
        }

        void Worker::wait() {
            pthread_join(thread_handle, nullptr);
        }

        void* worker_thread_routine(void* arg) {
            Worker* worker = static_cast<Worker*>(arg);
            std::cout << "hello from pthread " << worker << std::endl;
            return nullptr;
        }

    }
}
