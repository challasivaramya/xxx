#include "digipin.h"
// Implement your code here

using namespace std;

// SOME HELPER FUNCTIONS DECLATIONS, WHICH MAY HELP YOU IMPLEMENT THE TASK

// Digipin symbols grid
array<array<char, 4>, 4> GRID = {{{'F', 'C', '9', '8'},
                                  {'J', '3', '2', '7'},
                                  {'K', '4', '5', '6'},
                                  {'L', 'M', 'P', 'T'}}};

// function to get the grid index corresponding to a Digipin symbols
pair<int, int> symbolToRC(char s)
{
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 4; ++c)
            if (GRID[r][c] == s)
                return {r, c};
    return {0, 0};
}

void applyGridlineRules(double &lat, double &lon,
                        double latMin, double latMax,
                        double lonMin, double lonMax)
{
    // To handle coordinates coinciding with DIGIPIN Grid Lines
    // shift by 1e-12 in the correct direction according to the specification;
}

// TASK IS TO IMPLEMENT THE FOLLOWING TWO FUNCTIONS

string Digipin::encode(double lat, double lon)
{
    
if(lat<LAT_MIN || lat>LAT_MAX || 
             lon<LON_MIN  || lon>LON_MAX)return "";
    string digipin="";
    double latmin=LAT_MIN;
    double latmax=LAT_MAX;
    double lonmin=LON_MIN;
    double lonmax=LON_MAX;
        double latdiff=(latmax-latmin)/4.0;
        
    double londiff=(lonmax-lonmin)/4.0;
    int x;
    for( x=0;x<10;x++){
        
    for(int i=0;i<4;i++){
        int j;
        for( j=0;j<4;j++){
            if(lat>latmin+i*latdiff && lat<=latmin+(i+1)*latdiff && 
             lon>lonmin+j*londiff && lon<=latmin+(j+1)*londiff){
                digipin+=(GRID[i][j]);
            
             
             latmin=latmin+(i*latdiff);
             latmax=latmin+((i+1)*latdiff);
             lonmin=lonmin+(j*londiff);
             lonmax=latmin+((j+1)*londiff);
             latdiff=(latmax-latmin)/4.0;
            londiff=(lonmax-lonmin)/4.0;
            break;
             }
        }
        if(j!=4)break;
    }
}

    // Implement to get Digipin from latitude and longitude values
  return digipin;
}

pair<double, double> Digipin::decode(string &code)
{
    // Implement to get the center of the bounding box
    if(code=="")return {-1,-1};

double latdiffs[10];
double londiffs[10];
double latdiff=(LAT_MAX-LAT_MIN)/4.0;
        
    double londiff=(LON_MAX-LON_MIN)/4.0;
    for(int j=0;j<10;j++){
        latdiffs[j]=latdiff;
        latdiff=latdiff/4.0;
        londiffs[j]=londiff;
        londiff=londiff/4.0;
    }
  double latCenter = LAT_MIN;
  double lonCenter = LON_MIN;
  for(int x=0;x<10;x++){
int r,c;
r=symbolToRC(code[x]).first;
c=symbolToRC(code[x]).second;
latCenter+=(r*latdiffs[x]);
lonCenter+=(c*londiffs[x]);


  }
  latCenter+=(latdiffs[9]/2.0);
  lonCenter+=(londiffs[9]/2.0);

  return {latCenter, lonCenter}; // Return center of the cell
}
