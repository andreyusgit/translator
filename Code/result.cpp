#include <iostream>
#include <string>

int code()
{
try{
int A = 3 ;
int B = 0 ;
B = 5  ;
 if(( B == 0 )) {
  std::cout <<  "B equals 0"  << std::endl;
 std::cout <<  "B equals 0"  << std::endl;
}
else  if(( A>2) && (B>0 )) {
  std::cout <<  "A greater than 2 and B greater than 0"  << std::endl;
 }
 for(int indexB = 20; indexB >= 1;indexB = indexB + (-3)) {
 std::cout <<  "FOR WORKS"  << std::endl;
 }
 }
catch(...)
{
std::cout << "Error";
}
return 0; 
}