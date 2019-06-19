#include <iostream>
#include <stdio.h>

#include <event2/thread.h>

#include "init.h"

namespace Tenvoy {
    namespace Server {

        ProcessWideInit::ProcessWideInit() {
            std::cout << "Initializing process wide config..." << std::endl;
            setvbuf(stdout, nullptr, _IONBF, 0);
            setvbuf(stderr, nullptr, _IONBF, 0);
            evthread_use_pthreads();
            std::cout << "Initialization finished" << std::endl;
        };

    }
}
