#include <iostream>

#include "Application.h"

int main()
{
    try
    {
        Application application{};
        application.run();
    }
    catch (vk::SystemError &err)
    {
        std::cerr << "vk::SystemError: " << err.what() << std::endl;
        exit(-1);
    }
    catch (std::exception &err)
    {
        std::cerr << "std::exception: " << err.what() << std::endl;
        exit(-1);
    }
    catch (...)
    {
        std::cerr << "unknown error\n";
        exit(-1);
    }

    return 0;
}
