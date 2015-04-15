#ifndef GAMECONFIGREADER_H
#define GAMECONFIGREADER_H

#include <iostream>
#include <vector>
#include <fstream>

class GameConfig
{
private:
    std::vector< std::vector<int> > gridConfig;
    int grid;
    int iterations;
    std::string configFile;
    std::string outFile;

public:
    GameConfig(int argc, char** argv);
    ~GameConfig();

    int gridSize();
    int numberOfIterarions();
    std::vector< std::vector<int> >& gridConfiguration();
    std::ostream& operator<<(std::ostream& os);
};

#endif // GAMECONFIGREADER_H
