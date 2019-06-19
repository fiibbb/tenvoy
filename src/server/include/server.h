#pragma once

#include "init.h"
#include "manager.h"

namespace Tenvoy {
    namespace Server {

        class Server {
        public:
            Server(std::unique_ptr<ProcessWideInit>);
            void run();
        private:
            std::unique_ptr<ProcessWideInit> pw_init;
            std::unique_ptr<Manager> manager;
        };

    }
}