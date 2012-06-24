/**

/+ The AlgorithmParser class is: +/

   Copyright (C) 2012 Edward Chernysh

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
   documentation files (the "Software"), to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and
   to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   - The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

**/

#pragma once

#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cmath>

#include "linker.hpp"
typedef unsigned int uint;
namespace AlgParser {

#define DEADCHAR (-1)

#ifndef CBOOLS
#define CFALSE 0
#define CTRUE 1
#endif
          
class AlgorithmParser {
      public:              
             // Define AlgorithmParser's const Order of Operations handler
             // Does not /yet/ support nesting!
             void Bedmass(std::string *s)
             {
                  std::string subtext = (*s).substr(FirstIndexOf((*s), '('), FirstIndexOf((*s), ')'));
                  if (this->isformatted(subtext) == true && (*s).size() >= 3) {
                     double _result = ((*this).calculate(subtext));
                     std::string sresult = "";
                     sresult += (int)_result;
                     delete &_result;
                     (*s).replace(FirstIndexOf((*s), '(') - 1, (FirstIndexOf((*s), ')') + 1) - (FirstIndexOf((*s), '(') - 1), sresult);
                     delete &sresult;
                  }
                  delete &subtext;
             }             
             // <end_const_definition>
             static bool isformatted(std::string str)
             {
                 bool ret = true;   
                 if (str.find("(", 0) != (DEADCHAR))
                    if (cOccur(str, '(') != cOccur(str, ')'))
                       ret = false;                  
                 if (str.find(")", 0) != (DEADCHAR))
                    if (cOccur(str, '(') != cOccur(str, ')'))
                       ret = false;
                 return ret;                    
             }             
             static int tokenCount(std::string str)
             {
                 int occur = 0;
                 for (int i = 0; i < str.size(); ++i)
                     if (str[i] == '+' || str[i] == '-' 
                        || str[i] == '*' || str[i] == '/' || str[i] == '^' )
                           occur++;
                 return occur;          
             }
             virtual volatile double calculate(std::string math)
             {
                 volatile double result = atof(&(math[0]));
                 for (int i = 0; i < math.size(); i++)
                 {
                     if (isToken(math[i]) == true)
                     {
                         if (i >= 1 && i < (math.size() - 1))
                            switch (math[i])
                            {
                                case '+':
                                     result += atof(&math[i + 1]);
                                     i++; 
                                break;  
                                case '-':
                                     result -= atof(&math[i + 1]);
                                     i++;
                                break;
                                case '*':
                                     result *= atof(&math[i + 1]);
                                     i++;
                                break;  
                                case '/':
                                     result /= atof(&math[i + 1]);
                                     i++;
                                break; 
                                case '^':
                                     result = (pow(result, atof(&math[i + 1])));
                                     i++;
                                break;
                                case '!':
                                     std::cout << (factorial(result)) << std::endl;
                                break;
                            }                      
                     }               
                 }
                 return result;
             }             
             static signed int bracketCount(std::string s)
             {
                 int left = 0, right = 0;
                 for (int i = 0; i < s.size(); ++i)
                     if (s[i] == '(')
                        left++;
                     else if (s[i] == ')')
                        right++;
                 if (left == right)
                    return left;
                 else
                    return (EOF); 
             }
             
             static int digitCount(std::string str)
             {
                 int count = 0;
                 for (int i = 0; i < str.size(); i++)
                     if (isdigit(str[i]) == CTRUE)
                        count++;
                 return count;                                         
             }
      private:
             static int cOccur(std::string s, char _token)
             {
                 int count = 0;
                 for (int i = 0; i < s.size(); ++i)
                     if (s[i] == _token)
                        ++count;
                 return count;                       
             }
             virtual bool isToken(char c)
             {
                  if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
                      return true;
                  else
                      return false;
             }
             long factorial(double dval)
             {
                    long fact = (long)dval;
                    for (short int i = ((int)dval - 1); i > 0; i--)
                        dval *= (long)i;
                    return fact;      
             }
             inline int FirstIndexOf(std::string str, char c) const {
                 int index = 0;
                 for (uint i = 0; i < str.size(); ++i)
                     if (str[i] == c)
                        break;
                 return index;                
             }
};        
};
