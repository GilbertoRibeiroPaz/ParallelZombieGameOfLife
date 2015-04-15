#include "parallelzombiegameoflife.h"

using namespace std;

/////////////////////////
// PRIVATE METHODS
////////////////////////
void ParallelZombieGameOfLife::printMatrix(){
    for(int i = 0; i < grid; i++){
        for(int j = 0; j < grid; j++){
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/////////////////////
/// \brief ParallelZombieGameOfLife::applyRule
/// Apply rules:
///     - for each cell apply right rule based on neibors.
/// \param cel
/// \param neibors
///
void ParallelZombieGameOfLife::applyRule(int& cel, vector<int>& neibors){
    // 1º - for living cells
    if (cel == 1){

        int aliveNeibors = 0;
        bool zombieNeibor = false;


        for(auto neibor: neibors){
            // Counting alive neibors
            if (neibor == 1) aliveNeibors++;

            // zome neibor is zombieee, turn zombie
            if (neibor == 2){
                zombieNeibor = true;
                break;
            }
        }

        // 70M813 RULEZ FIRST
        // zome neibor is zombieee, turn zombie
        // 5ª rule
        if (zombieNeibor) cel = 2;
        else {
            // 8 alive neibors, turn zombie
            // 6ª rule
            if (aliveNeibors == 8) cel = 2;
            // Less than 2 alive neibors, death by lonelliness
            // 1ª rule
            else if (aliveNeibors < 2) cel = 0;
            // More than 3 neibors, death by overpopulation
            // 2ª rule
            else if (aliveNeibors > 3) cel = 0;
            // 2 or 3 neibors, same state. Not needed
            // 4ª rule
            else if (aliveNeibors == 2 || aliveNeibors == 3) cel = cel;
        }
    }
    // 2º for zombie cells
    else if (cel == 2){
        int aliveNeibors = 0;
        for(auto neibor: neibors){
            // counting alive neibors
            if (neibor == 1) aliveNeibors++;
        }
        // no alive neibors, zombie dies
        // 7ª rule
        if (aliveNeibors == 0) cel = 0;
        // zome alive neibor makes cell keeps zombie
        // if some neibor is zombie, keeps zombie? TODO
        // 8ª rule
        if (aliveNeibors > 0) cel = cel;
    }
    else if (cel == 0){
        int aliveNeibors = 0;
        for(auto neibor: neibors)
            if(neibor == 1) aliveNeibors++;

        // some dead cell with 3 alive neibors, turns ALIVE!!!
        // 3ª rule
        if(aliveNeibors == 3) cel = 1;
    }
}



/////////////////////////
// PUBLIC METHODS
////////////////////////


//////////////////////////////
/// \brief ParallelZombieGameOfLife::ParallelZombieGameOfLife
/// The constructor:
///     - Pass grid width x height, number of iterations and grid configuration;
///     - Prints the initial state.
/// \param grid
/// \param iterations
/// \param gridConfig
///
ParallelZombieGameOfLife::ParallelZombieGameOfLife(int grid, int iterations, vector< vector<int> >& gridConfig){
    this->grid = grid;
    this->iterations = iterations;
    this->m = gridConfig;

    cout << "Initial configuration" << endl;
    printMatrix();
}

///
/// \brief ParallelZombieGameOfLife::ParallelZombieGameOfLife
/// Construct the game using the game config parser.
/// \param gf
///
ParallelZombieGameOfLife::ParallelZombieGameOfLife(GameConfig gf){
    grid = gf.gridSize();
    iterations = gf.numberOfIterarions();
    m = gf.gridConfiguration();

    cout << "Initial configuration" << endl;
    printMatrix();
}

////
/// \brief ParallelZombieGameOfLife::run
/// Starts the game:
///     - For each iterarion cycle throught entire matrix;
///     - For each cell, select correct neibors and apply
///         rules.
///
void ParallelZombieGameOfLife::run(){
    vector<int> neibors;

    for(int currentIterarion = 0; currentIterarion < iterations; currentIterarion++){
        for(int i = 0; i < grid; i++){
            for(int j = 0; j < grid;  j++){

                //cleanup neibors
                neibors.clear();
                // To speedup neibors selection, make reference to the grid, instead of coping
                // the content of a cel.
                // To parallel, select pieces of the grid, with size to each thread. Embarasing threading.
                // TODO: Remember read cels
                //general case
                if  (i > 0 && i < (grid - 1) && j > 0 && j < (grid - 1)){
                    neibors = {
                        m[i - 1][j - 1], m[i - 1][j], m[i - 1][j + 1],
                        m[i][j - 1],  /* You are here */ m[i][j + 1],
                        m[i + 1][j - 1], m[i + 1][j], m[i + 1][j + 1]
                    };
                    /*
                     * N N N
                     * N Y N
                     * N N N
                    */
                }

                // first line first collum
                else if (i == 0 && j == 0){
                    neibors = {
                       m[i][j+1], m[i+1][j], m[i+1][j+1]
                    };

                    /*
                     * Y N
                     * N N
                    */
                }
                //last line, first colunm
                else if( i == (grid - 1) && j == 0){
                    neibors = {
                       m[i - 1] [j], m[i - 1][j + 1], m[i][j + 1]
                    };
                    /*
                     * N N
                     * Y N
                    */
                }
                //first line, last colunm
                else if( i  == 0 && j == (grid -  1)){
                    neibors = {
                        m[i] [j - 1], m[i + 1][j - 1], m[i + 1][j]
                    };
                    /*
                     * N Y
                     * N N
                    */
                }
                //last line, last colunm
                else if(i == (grid - 1) && j == (grid - 1)){
                    neibors = {
                        m[i - 1][j - 1], m[i - 1][j], m[i][j - 1]
                    };
                    /*
                     * N N
                     * N Y
                     */
                }
                // first line, not first or last colunm
                else if(i == 0 && j > 0 && j < (grid -  1)){
                    neibors = {
                        m[i][j - 1], m[i][j + 1],
                        m[i + 1][j - 1], m[i + 1][j], m[i + 1][j + 1]
                    };
                    /*
                     * N Y N
                     * N N N
                     */
                }
                // last line, not first or last colunm
                else if (i == (grid - 1) && j > 0 && j < (grid - 1)){
                    neibors = {
                        m[i - 1][j - 1], m[i - 1][j], m[i - 1][j + 1],
                        m[i][j - 1], m[i][j + 1]
                    };
                    /*
                     * N N N
                     * N Y N
                     */
                }
                // first colunm, not first or last line
                else if (j == 0 && i > 0 && i < (grid - 1)){
                    neibors = {
                        m[i - 1][j], m[i - 1][j + 1],
                        m[i][j + 1],
                        m[i + 1][j], m[i + 1][j]
                    };
                    /*
                     * N N
                     * Y N
                     * N N
                     */
                }
                // last colunm, not first or last line
               else if (j == (grid - 1) && i > 0 && i < (grid - 1)){
                    neibors = {
                        m[i - 1][j - 1], m[i - 1][j],
                        m[i][j - 1],
                        m[i + 1][j - 1], m[i + 1][j]
                    };
                    /*
                     * N N
                     * N Y
                     * N N
                     */
                }

                // Apply rules based on neibors
                applyRule(m[i][j], neibors);

            } // j
        } //i
        cout << "Current iteration: " << currentIterarion+1 << endl;
        printMatrix();
    } // iterations

}


void ParallelZombieGameOfLife::runParallel(int initIndex, int finalIndex){

}

///
/// \brief ParallelZombieGameOfLife::~ParallelZombieGameOfLife
/// Destructor NOTHING TODO
ParallelZombieGameOfLife::~ParallelZombieGameOfLife()
{

}

