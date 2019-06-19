#include <iostream>

#include <event2/event.h>

#include "init.h"
#include "server.h"
#include "manager.h"

namespace Tenvoy {
    namespace Server {

        Server::Server(std::unique_ptr<ProcessWideInit> pw_init): pw_init(std::move(pw_init)), manager(std::move(std::make_unique<Manager>())) {}

        void Server::run() {
            manager->run();
        }

    }
}
