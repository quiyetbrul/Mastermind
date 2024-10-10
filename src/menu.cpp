#include "menu.h"

#include "util.h"

#include <iostream>

void title(){
    // clearScreen();
    // TODO: get terminal width dynamically
    std::cout << "                                      _ _ _ ____ _    ____ ____ _  _ ____     ___ ____\n";
    std::cout << "                                      | | | |___ |    |    |  | |\\/| |___      |  |  |\n";
    std::cout << "                                      |_|_| |___ |___ |___ |__| |  | |___      |  |__|\n\n";
    std::cout << ANSI_COLOR_BLUE;
    std::cout << "███╗   ███╗ █████╗ ███████╗████████╗███████╗██████╗ ███╗   ███╗██╗███╗   ██╗██████╗       ██████╗  █████╗ ███╗   ███╗███████╗\n";
    std::cout << "████╗ ████║██╔══██╗██╔════╝╚══██╔══╝██╔════╝██╔══██╗████╗ ████║██║████╗  ██║██╔══██╗     ██╔════╝ ██╔══██╗████╗ ████║██╔════╝\n";
    std::cout << "██╔████╔██║███████║███████╗   ██║   █████╗  ██████╔╝██╔████╔██║██║██╔██╗ ██║██║  ██║     ██║  ███╗███████║██╔████╔██║█████╗\n";
    std::cout << "██║╚██╔╝██║██╔══██║╚════██║   ██║   ██╔══╝  ██╔══██╗██║╚██╔╝██║██║██║╚██╗██║██║  ██║     ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝\n";
    std::cout << "██║ ╚═╝ ██║██║  ██║███████║   ██║   ███████╗██║  ██║██║ ╚═╝ ██║██║██║ ╚████║██████╔╝     ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗\n";
    std::cout << "╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═════╝       ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝\n";
    std::cout << ANSI_COLOR_RESET;
    std::cout << "                                ___  _   _    ____ _  _ _ _   _ ____ ___    ___  ____ _  _ _\n";
    std::cout << "                                |__]  \\_/     |  | |  | |  \\_/  |___  |     |__] |__/ |  | |\n";
    std::cout << "                                |__]   |      |_\\| |__| |   |   |___  |     |__] |  \\ |__| |___\n\n";
}

void congratulations(){
    // clearScreen();
    std::cout << ANSI_COLOR_GREEN;
    std::cout << " ██████╗ ██████╗ ███╗   ██╗ ██████╗ ██████╗  █████╗ ████████╗██╗   ██╗ █████╗ ████████╗██╗ ██████╗ ███╗   ██╗███████╗\n";
    std::cout << "██╔════╝██╔═══██╗████╗  ██║██╔════╝ ██╔══██╗██╔══██╗╚══██╔══╝██║   ██║██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝\n";
    std::cout << "██║     ██║   ██║██╔██╗ ██║██║  ███╗██████╔╝███████║   ██║   ██║   ██║███████║   ██║   ██║██║   ██║██╔██╗ ██║███████╗\n";
    std::cout << "██║     ██║   ██║██║╚██╗██║██║   ██║██╔══██╗██╔══██║   ██║   ██║   ██║██╔══██║   ██║   ██║██║   ██║██║╚██╗██║╚════██║\n";
    std::cout << "╚██████╗╚██████╔╝██║ ╚████║╚██████╔╝██║  ██║██║  ██║   ██║   ╚██████╔╝██║  ██║   ██║   ██║╚██████╔╝██║ ╚████║███████║\n";
    std::cout << " ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝\n\n";
    std::cout << ANSI_COLOR_RESET;
}

void tryAgain(){
    // clearScreen();
    std::cout << ANSI_COLOR_RED;
    std::cout << "████████╗██████╗ ██╗   ██╗      █████╗  ██████╗  █████╗ ██╗███╗   ██╗\n";
    std::cout << "╚══██╔══╝██╔══██╗╚██╗ ██╔╝     ██╔══██╗██╔════╝ ██╔══██╗██║████╗  ██║\n";
    std::cout << "   ██║   ██████╔╝ ╚████╔╝      ███████║██║  ███╗███████║██║██╔██╗ ██║\n";
    std::cout << "   ██║   ██╔══██╗  ╚██╔╝       ██╔══██║██║   ██║██╔══██║██║██║╚██╗██║\n";
    std::cout << "   ██║   ██║  ██║   ██║        ██║  ██║╚██████╔╝██║  ██║██║██║ ╚████║\n";
    std::cout << "   ╚═╝   ╚═╝  ╚═╝   ╚═╝        ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝\n\n";
    std::cout << ANSI_COLOR_RESET;
}

void goodbye(){
    // clearScreen();
    std::cout << ANSI_COLOR_MAGENTA;
    std::cout << " ██████╗  ██████╗  ██████╗ ██████╗ ██████╗ ██╗   ██╗███████╗\n";
    std::cout << "██╔════╝ ██╔═══██╗██╔═══██╗██╔══██╗██╔══██╗╚██╗ ██╔╝██╔════╝\n";
    std::cout << "██║  ███╗██║   ██║██║   ██║██║  ██║██████╔╝ ╚████╔╝ █████╗\n";
    std::cout << "██║   ██║██║   ██║██║   ██║██║  ██║██╔══██╗  ╚██╔╝  ██╔══╝\n";
    std::cout << "╚██████╔╝╚██████╔╝╚██████╔╝██████╔╝██████╔╝   ██║   ███████╗\n";
    std::cout << " ╚═════╝  ╚═════╝  ╚═════╝ ╚═════╝ ╚═════╝    ╚═╝   ╚══════╝\n\n";
    std::cout << ANSI_COLOR_RESET;
}
