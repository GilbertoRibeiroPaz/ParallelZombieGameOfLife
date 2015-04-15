#include "gameconfig.h"

using namespace std;

GameConfig::GameConfig(int argc, char** argv)
{
    if(argc != 5){
        cout << "Invalid init config" << endl;
        exit(1);
    }
    else {
        // Get parameters
        this->grid = std::stoi(argv[1]);
        this->iterations = std::stoi(argv[2]);
        this->configFile = std::string(argv[3]);
        this->outFile = std::string(argv[4]);

        // Get config
        ifstream file(configFile, ifstream::in);
        file.seekg(ios::end);
        size_t fileLength = file.tellg();
        file.seekg(ios::beg);


        // Read file
        char* buffer = new char[fileLength];
        file.read(buffer, fileLength);


        string fileContent = buffer;

        // Test
        cout << "File Length: " << fileLength << endl;
        cout << "File Content:\n" << buffer << endl;
    }

}

GameConfig::GameConfig(){
    this->outFile = "DefaultOutFile.txt";
}

GameConfig::~GameConfig()
{

}

int GameConfig::gridSize(){
    return grid;
}

int GameConfig::numberOfIterarions(){
    return iterations;
}

std::vector< std::vector<int> >& GameConfig::gridConfiguration(){
    return gridConfig;
}

void GameConfig::printToFile(std::vector< std::vector<int> >& matrix){
    ofstream outFile(this->outFile, ofstream::app);
    for(auto line: matrix){
        for(auto cell: line){
            outFile << cell << " ";
        }
        outFile << "\n";
    }
}


std::ostream& GameConfig::operator<<(std::ostream& os){

    os << "GameConfig: " << endl;
    os << "Grid: " << grid <<endl;
    os << "Iterations: " << iterations << endl;
    os << "Config File: " << configFile << endl;
    os << "Output File: " << outFile << endl;

    return os;
}
