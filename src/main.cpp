#include "Core/Application.h"

int main(int argc, char* argv[])
{
    Application app(argc, argv);
    app.Loop();
    return 0;
}