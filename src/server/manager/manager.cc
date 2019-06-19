#include <iostream>

#include <event2/event.h>

#include "manager.h"

namespace Tenvoy {
    namespace Server {

        Manager::Manager() {
            event_base = event_base_new();
            if (event_base == nullptr) {
                throw std::exception();
            }
            for (int i = 0; i < 10; i++) {
                auto worker = std::make_unique<Worker>();
                workers.push_back(std::move(worker));
            }
        }

        void Manager::run() {
            std::cout << "Manager starting" << std::endl;
            for (const auto& worker : workers) {
                worker->run();
            }
            for (const auto& worker : workers) {
                worker->wait();
            }
            std::cout << "Manager exiting" << std::endl;
        }

    }
}
