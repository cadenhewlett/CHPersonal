#include "main.h"
#include "vision.hpp"
#include <array>
#include <vector>

void VisionFunctions::visionAlign(int sig) {

}
int VisionFunctions::visionFilterX(int size, int sig){ //Simple Median Filter of the Camera X Values
  //variables
std::array<int, 20> XValues;
std::vector<int> XValues_D;

int Q1;
double MED;
int Q3;
int IQR;
int Max;
int Min;
int j;
int temp;
vision_object_s_t object = vSensor.get_by_sig(size, sig);
for(int i = 0; i < 20; i++){ //fills each value of the array
  XValues[i] = object.x_middle_coord; //record X Value from the Camera and store it in the Array
  delay(50); //delay for camera processing
}
for(int i = 1; i < (XValues.size()); i++){
  j = i - 1;
  while((j >= 0) && (XValues[j] < XValues[i])){// while j is greater than 0, and the 'j'th term of the array is greater than the 'i'th term of the array
  //INSERTION SORT: NOTE https://en.wikipedia.org/wiki/Insertion_sort
  //Animation of the Sort: NOTE  https://en.wikipedia.org/wiki/Insertion_sort#/media/File:Insertion-sort-example-300px.gif
    temp = XValues[i]; //determines temp as stored array index
    XValues[i] = XValues[j]; //stores the second value as the array index of j
    XValues[j] = temp; //jth term becomes temp
    i = j; // i value becomes j value
    j--; //decrements j value
  }
}

MED = XValues[(int)(XValues.size() * 0.5)]; //determines the median of the data to be the average of the middle two values
Q1 = XValues[(int)(XValues.size() * 0.25)+1]; //first quartile of the data is the fifth number
Q3 = XValues[(int)(XValues.size() * 0.75)+1]; //third quartile is the fifteenth number
IQR = Q3 - Q1; //determines interquartile range
Max = Q3 + (1.5 * IQR); //uses interquartile range to calculate max
Min = Q1 - (1.5 * IQR);  //uses interquartile range to calculate min
for(int i = 0; i < (XValues.size()); i++){
  XValues_D.push_back(i); //pushes the 'i'th index of the array into the Vector
  if(XValues[i] > Max){
    XValues_D.erase(XValues_D.end()); //if its outside the maximum remove the end-most value - a.k.a the highest
  }
  else if(XValues[i] < Min){
    XValues_D.erase(XValues_D.begin()); //if its outside the minimum remove the front-most value - a.k.a the highest
  }
}
if(XValues_D.size() % 2 == 0){ //if there is an even number of items in the vector
  MED = (XValues_D.at((XValues.size()/2)) + XValues_D.at((XValues.size()/2) + 1))/2;//gets the middle two values' average. see below
  /*
  EXAMPLE VECTOR
  {0, 2, 4, 5, 6, 7} --> Size is 6, so XValues.size() = 6: NOTE https://www.geeksforgeeks.org/vectorempty-vectorsize-c-stl/
  --> returns: (XValues_D.at(6/2) + XValues_D.at((6/2)+1)) / 2
  --> returns: (XValues_D.at(3) + XValues_D.at(4)) / 2
  --> returns: (4 + 5)/2
  --> returns: 4.5
  */

}else{
  MED = XValues_D.at(((int)(XValues.size()/2))+1); //gets the middle value. see below
  /*
  EXAMPLE VECTOR
  {0, 1, 2, 3, 4} --> Size is 5
  --> returns: (XValues_D.at(((int)(5/2))+1)
  --> returns: (XValues_D.at((int)(2.5))+1))
  --> returns: (XValues_D.at(2)+1)) : NOTE : casting an int will ignore decimals, so we add 1:  http://www.cplusplus.com/doc/tutorial/typecasting/
  --> returns: (XValues_D.at(3))
  --> returns: 2
  */
}
//= XValues[(sizeof(XValues) / sizeof(XValues[0])/2)]
return MED;

}
