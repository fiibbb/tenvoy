#include <iostream>

#include <event2/thread.h>

#include "init.h"

namespace Tenvoy {
    namespace Server {

        ProcessWideInit::ProcessWideInit() {
            std::cout << "Initializing process wide config..." << std::endl;
            evthread_use_pthreads();
            std::cout << "Initialization finished" << std::endl;
        };

    }
}
