    #include "includes.h"
    #include "defines.h"
     
    using namespace cv;
     
    #define FULL_HD_WIDTH	1920
    #define FULL_HD_HEIGHT	1080
     
    unsigned char paddedImg[FULL_HD_HEIGHT\+2][FULL_HD_WIDTH\+2] = {0};
     
    void connectedComponents(unsigned char* Image,int width, int height, int* noOfComponents, char* list)
    {
    	unsigned char  west, north,northWest, northEast,south,east,southEast,southWest = 0;
    	
    	int label = 0;
    	int min = 0;
     
    	for(int i=0; i<height; i\+\+)
    	{
    		for(int j=0; j<width; j\+\+)
    		{
    			paddedImg[i\+1][j\+1] = Image[(i*width) \+ j];
    		}
    	}
     
    	for(int i=1; i<(height\+1); i\+\+)
    	{
    		for(int j=1; j<(width\+1); j\+\+)
    		{
    			west      =	paddedImg[i][j-1];
    			northWest =	paddedImg[i-1][j-1];
    			north     =	paddedImg[i-1][j];
    			northEast =	paddedImg[i-1][j\+1];
     
    			if(paddedImg[i][j] != 0)
    			{
    				min = 25500;
     
    				
    				{
    					if( west != 0 || north != 0 || northWest != 0 || northEast != 0)
    					{
    						if(west < min && west != 0)			min  = west;
    						if(northWest < min && northWest != 0)		min  = northWest;
    						if(north < min && north != 0)			min  = north;
    						if(northEast < min && northEast != 0)		min  = northEast;
     
    						paddedImg[i][j] = min;
    					}
    					else
    					{
    						paddedImg[i][j] = \+\+label;
    					}
    				}
    				
    			}
    		}
    	}
     
    	for(int i=1; i<height\+1; i\+\+)
    	{
    		for(int j=1; j<width\+1; j\+\+)
    		{
    			if(paddedImg[i][j] != 0)
    			{	
    				
    				{
    					west =		paddedImg[i][j-1];
    					northWest = paddedImg[i-1][j-1];
    					north =		paddedImg[i-1][j];
    					northEast = paddedImg[i-1][j\+1];
     
    					east =		paddedImg[i][j\+1];
    					southEast = paddedImg[i\+1][j\+1];
    					south =		paddedImg[i\+1][j];
    					southWest = paddedImg[i\+1][j-1];
    					
    					min = paddedImg[i][j];
    					
    					if(west < min && west != 0)				min  = west;
    					if(northWest < min && northWest != 0)		min  = northWest;
    					if(north < min && north != 0)				min  = north;
    					if(northEast < min && northEast != 0)		min  = northEast;
    					if(east < min && east != 0)				min  = east;
    					if(southEast < min && southEast != 0)		min  = southEast;
    					if(south < min && south != 0)				min  = south;
    					if(southWest < min && southWest != 0)		min  = southWest;
    					
    					if(west != 0)		paddedImg[i][j-1] = min;
    					if(northWest != 0)	paddedImg[i-1][j-1] = min;
    					if(north != 0)		paddedImg[i-1][j] = min;
    					if(northEast != 0)	paddedImg[i-1][j\+1] = min;
    					if(east != 0)		paddedImg[i][j\+1] = min;
    					if(southEast != 0)	paddedImg[i\+1][j\+1] = min;
    					if(south != 0)		paddedImg[i\+1][j] = min;
    					if(southWest != 0)	paddedImg[i\+1][j-1] = min;
    					
    				}
    				
    			}
    		}
    	}
     
    	for(int i=0; i<height; i\+\+)
    	{
    		for(int j=0; j<width; j\+\+)
    		{
    			Image[i*width \+ j] = paddedImg[i\+1][j\+1];
    		}
    	}
     
    	*noOfComponents = min;
    }