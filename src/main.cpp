#include <sstream>
#include <iostream>
#include "media_manager/media_manager.h"


int main( int argc, char** argv )
{
    MediaManager mm( argc, argv, "config/config.xml" );
    return 0;
}
