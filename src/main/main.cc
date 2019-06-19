#include <iostream>
#include <memory>

#include "server.h"
#include "init.h"

int main(int argc, char** argv)
{
    std::cout << "Hello from tenvoy" << std::endl;
    auto pwi = std::make_unique<Tenvoy::Server::ProcessWideInit>();
    auto server = std::make_unique<Tenvoy::Server::Server>(std::move(pwi));
    server->run();
    return 0;
}