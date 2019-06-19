#pragma once

#include <vector>
#include <memory>

#include "worker.h"

namespace Tenvoy {
    namespace Server {

        class Manager {
        public:
            Manager();
            void run();
        private:
            std::vector<std::unique_ptr<Worker>> workers;
        };

    }
}
