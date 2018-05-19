#ifndef VISIONPARAMETERS_H
#define VISIONPARAMETERS_H

// Only used to pull #defines - Needed for all algos
#include "Algorithms/sobel.h"


/*      ALGO SWITCH

    To switch between contour algorithms, comment out
    one of the following defines, and uncomment the other.
    The build will fail if neither are defined as
    the class defined in this header (AlgoParams) is required
    by the GUI to build the parameters windows as-well-as
    the video player and display widget for passing
    algorithm parameters from the user to the algs.
*/

// --------------------------------------

/* Traditiaonal-ish snake algorithm */

    #define ACTIVE_CONTOUR_ALG 0

/* END traditional-ish snake algorithm */

// --------------------------------------

/* Custom snake algorithm */

 //   #define CUSTOM_CONTOUR_ALG 0

/*  END custom snake algorithm*/

// --------------------------------------

/*  END ALGO SWITCH */



#ifdef ACTIVE_CONTOUR_ALG

// Optionals
#define DRAW_LINE 1
#define DRAW_POINTS 1
#define DRAW_NEIGHBORS

// Required
#define CONTOUR_ALPHA 0.2
#define CONTOUR_BETA 1
#define CONTOUR_GAMMA 100
#define MINIMUM_POINTS 4
#define CONTOUR_START_POINT 100

/* Active Contour */

class AlgoParams
{
public:
    AlgoParams(){
#ifdef SOBEL_FILL_IN_NEG_SPACE
        this->_sobelDeadSpace = true;
#else
        this->_sobelDeadSpace = false;
#endif

#ifdef SOBEL_CALCULATE_ANGLE
        this->_sobelAngle = true;
#else
        this->_sobelAngle = false;
#endif

#ifdef DRAW_LINE
        this->_drawSnakeLines = true;
#else
        this->_drawSnakeLines = false;
#endif

#ifdef DRAW_POINTS
        this->_drawSnakePoints = true;
#else
        this->_drawSnakePoints = false;
#endif

        this->_sobelThresh = SOBEL_THRESH;
        this->_viewSobel = false;
        this->_nPoints = CONTOUR_START_POINT;
        this->_alpha = CONTOUR_ALPHA;
        this->_beta = CONTOUR_BETA;
        this->_gamma = CONTOUR_GAMMA;
    }

    ~AlgoParams(){}
    void setNumberPoints(int n){ this->_nPoints = n; }
    void setSobelThresh(int t){ this->_sobelThresh = t; }
    void setCalcSobelAngle(bool state){ this->_sobelAngle = state; }
    void setDrawSobelDeadpace(bool state){ this->_sobelDeadSpace = state; }
    void setDrawSnakePoints(bool state){ this->_drawSnakePoints = state; }
    void setDrawSnakeLines(bool state){ this->_drawSnakeLines = state; }
    void setViewSobel(bool state){ this->_viewSobel = state; }
    void setAlpha(float val){ this->_alpha = val; }
    void setBeta(float val){ this->_beta = val; }
    void setGama(float val){ this->_gamma = val; }
    int getNumberPoints(){ return this->_nPoints; }
    int getSobelThreash(){ return this->_sobelThresh; }
    bool getSobelAngle(){ return this->_sobelAngle; }
    bool getSobelDeadSpace(){ return this->_sobelDeadSpace; }
    bool getDrawSnakeLines(){ return this->_drawSnakeLines; }
    bool getDrawSnakePoints(){ return this->_drawSnakePoints; }
    bool getViewSobel(){ return this->_viewSobel; }
    float getAlpha(){ return _alpha; }
    float getBeta(){ return _beta; }
    float getGama(){ return _gamma; }

private:
    int _nPoints;
    int _sobelThresh;
    bool _sobelAngle;
    bool _sobelDeadSpace;
    bool _drawSnakeLines;
    bool _drawSnakePoints;
    bool _viewSobel;
    float _alpha;
    float _beta;
    float _gamma;
};

/*    End Active Contours   */
#else

#ifdef CUSTOM_CONTOUR_ALG

#define SHOW_SNAKE 1
#define MINIMUM_POINTS 5
#define INITIAL_DISPERSAL_FACTOR 20

#define EPOCH_PER_CYCLE 50
#define GENERATION_TOP_SNAKES 5
#define SNAKES_PER_GENERATION 50
#define NEIGHBORHOOD_BLOCK_SIZE 21

#define CONTOUR_ALPHA 0.2
#define CONTOUR_BETA 1
#define CONTOUR_GAMMA 100

#define CROSSOVER_MATING_RATIO .5
#define CROSSOVER_SWAP_RATIO 2

/* Active Contour */

class AlgoParams
{
public:
    AlgoParams(){
#ifdef SOBEL_FILL_IN_NEG_SPACE
        this->_sobelDeadSpace = true;
#else
        this->_sobelDeadSpace = false;
#endif

#ifdef SOBEL_CALCULATE_ANGLE
        this->_sobelAngle = true;
#else
        this->_sobelAngle = false;
#endif

#ifdef SHOW_SNAKE
        this->_showSnake = true;
#else
        this->_showSnake = false;
#endif
        this->_sobelThresh = SOBEL_THRESH;
        this->_viewSobel = false;
        this->_dispersalFactor = INITIAL_DISPERSAL_FACTOR;
        this->_epochPerCycle = EPOCH_PER_CYCLE;
        this->_numTopSnakes = GENERATION_TOP_SNAKES;
        this->_populationCount = SNAKES_PER_GENERATION;
        this->_neighborhoodBlock = NEIGHBORHOOD_BLOCK_SIZE;
        this->_alpha = CONTOUR_ALPHA;
        this->_beta = CONTOUR_BETA;
        this->_gamma = CONTOUR_GAMMA;
        this->_xoverMatingRatio = CROSSOVER_MATING_RATIO;
        this->_xoverSwapRatio = CROSSOVER_MATING_RATIO;
    }
    //Sobel
    void setSobelThresh(int t){ this->_sobelThresh = t; }
    void setCalcSobelAngle(bool state){ this->_sobelAngle = state; }
    void setDrawSobelDeadpace(bool state){ this->_sobelDeadSpace = state; }
    void setViewSobel(bool state){ this->_viewSobel = state; }

    int getSobelThreash(){ return this->_sobelThresh; }
    bool getSobelAngle(){ return this->_sobelAngle; }
    bool getSobelDeadSpace(){ return this->_sobelDeadSpace; }
    bool getViewSobel(){ return this->_viewSobel; }

    //Snake
    void setDrawSnake(bool state){ this->_showSnake = state; }
    void setDispFactor(float f){ this->_dispersalFactor = f; }
    void setEpochPerCycle(int e){ this->_epochPerCycle = e; }
    void setGenSurvive(int g){ this->_numTopSnakes = g; }
    void setPopCount(int p){ this->_populationCount = p; }
    void setNeighborHoodBlockSize(int b){ this->_neighborhoodBlock = b; }
    void setAlpha(float val){ this->_alpha = val; }
    void setBeta(float val){ this->_beta = val; }
    void setGamma(float val){ this->_gamma = val; }
    void setMatingRatio(float r){ this->_xoverMatingRatio = r; }
    void setSwapRatio(float r){ this->_xoverSwapRatio = r; }

    bool getDrawSnake(){ return this->_showSnake; }
    float getDispFact(){ return this->_dispersalFactor; }
    int getEpochPerCycle(){ return this->_epochPerCycle; }
    int getGenSurvive(){ return this->_numTopSnakes; }
    int getPopCount(){ return this->_populationCount; }
    int getNeighborhoodBlock() { return this->_neighborhoodBlock; }
    float getAlpha(){ return _alpha; }
    float getBeta(){ return _beta; }
    float getGama(){ return _gamma; }
    float getMatingRatio(){ return this->_xoverMatingRatio; }
    float getSwapRatio(){ return this->_xoverSwapRatio; }

private:
    bool _showSnake;
    int _sobelThresh;
    bool _sobelAngle;
    bool _sobelDeadSpace;
    bool _viewSobel;
    float _dispersalFactor;
    int _epochPerCycle;
    int _numTopSnakes;
    int _populationCount;
    int _neighborhoodBlock;
    float _alpha;
    float _beta;
    float _gamma;
    float _xoverMatingRatio;
    float _xoverSwapRatio;
};



/*    End Custom Contours   */
#endif

/*    End If -Else   */
#endif


#endif // VISIONPARAMETERS_H

