#include <iostream>

#include "worker.h"

namespace Tenvoy {
    namespace Server {

        Worker::Worker() {

        }

        void Worker::run() {
            std::cout << "worker starting" << std::endl;
        }

    }
}
