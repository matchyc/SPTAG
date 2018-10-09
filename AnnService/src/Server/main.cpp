#include "inc/Server/SearchService.h"

SpaceV::Service::SearchService g_service;

int main(int argc, char* argv[])
{
    if (!g_service.Initialize(argc, argv))
    {
        return 1;
    }

    g_service.Run();

    return 0;
}

