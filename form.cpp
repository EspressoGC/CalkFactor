/*
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

*/

#include <windows.h>
#include "linker.hpp"

using namespace AlgParser;
using namespace std;

typedef HWND Button;
Button BtnOne, BtnTwo, BtnThree, BtnFour, BtnFive, BtnSix, BtnSeven, BtnEight, BtnNine, BtnZero, BtnPls, BtnMin, BtnMul, 
BtnDiv, BtnMod, BtnExp, BtnEq;
HWND Field;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

const char *BLANK = "";

struct WindowProperties {       
       unsigned int Height;
       unsigned int Width;
};
typedef WindowProperties ButtonProperties;
typedef WindowProperties OptProps;
const WindowProperties WSizes = { 290, 215 }; // Window Size properties: modify here
const ButtonProperties ButtonSizes = { 30, 50 };
const OptProps opt = { 45, 30 };
Button CreateButton(const char*, HWND&);

/*  Make the class name into a global variable  */
char szClassName[] = "calc_factor";

// declare variable to be retained (ANS)
static long long int ANS = 0;
static std::string HOLDER = "";

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "CalkFactor ",       /* Title Text */
           WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_VISIBLE,         /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           WSizes.Width,                /* The programs width */
           WSizes.Height,        /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nFunsterStil);
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE: 
             // <create_output_field>
             Field = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("STATIC"), TEXT("0"), WS_VISIBLE | WS_CHILD | SS_CENTER, 5, 5, 200 , 34, hwnd, NULL, NULL, NULL);
             SendMessage(Field, WM_SETFONT, (WPARAM) CreateFont(/*the*/32/*answer*/, 0, 0, 0, FW_EXTRALIGHT, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Tahoma")), TRUE);
             // </create_output_field>
             /**
             *  Create input buttons
             **/
             BtnOne = CreateWindow(TEXT("button"), TEXT("1"),    
		             WS_VISIBLE | WS_CHILD,
					 /* First 2 Integers are location; last 2 are size */
		            2, 56, ButtonSizes.Width, ButtonSizes.Height,       
		             hwnd, (HMENU) OPTONE, NULL, NULL); 
             BtnTwo = CreateWindow(TEXT("button"), TEXT("2"),    
		             WS_VISIBLE | WS_CHILD,
					 /* First 2 Integers are location; last 2 are size */
		            58, 56, ButtonSizes.Width, ButtonSizes.Height,       
		             hwnd, (HMENU) OPTTWO, NULL, NULL); 
		             
             BtnThree = CreateWindow(TEXT("button"), TEXT("3"),    
		             WS_VISIBLE | WS_CHILD,
					 /* First 2 Integers are location; last 2 are size */
		            117, 56, ButtonSizes.Width, ButtonSizes.Height,       
		             hwnd, (HMENU) OPTTHREE, NULL, NULL); 
		             
             BtnFour = CreateWindow(TEXT("button"), TEXT("4"),    
		             WS_VISIBLE | WS_CHILD,
					 /* First 2 Integers are location; last 2 are size */
		            2, 100, ButtonSizes.Width, ButtonSizes.Height,       
		             hwnd, (HMENU) OPTFOUR, NULL, NULL); 
		             
            BtnFive = CreateWindow(TEXT("button"), TEXT("5"),    
		             WS_VISIBLE | WS_CHILD,
					 /* First 2 Integers are location; last 2 are size */
		            58, 100, ButtonSizes.Width, ButtonSizes.Height,       
		             hwnd, (HMENU) OPTFIVE, NULL, NULL);
            BtnSix = CreateWindow(TEXT("button"), TEXT("6"),    
		             WS_VISIBLE | WS_CHILD,
					 /* First 2 Integers are location; last 2 are size */
		            117, 100, ButtonSizes.Width, ButtonSizes.Height,       
		             hwnd, (HMENU) OPTSIX, NULL, NULL);  
            
            BtnSeven = CreateWindow(TEXT("button"), TEXT("7"),    
		             WS_VISIBLE | WS_CHILD,
					 /* First 2 Integers are location; last 2 are size */
		            2, 144, ButtonSizes.Width, ButtonSizes.Height,       
		             hwnd, (HMENU) OPTSEVEN, NULL, NULL);  
            BtnEight = CreateWindow(TEXT("button"), TEXT("8"),    
		             WS_VISIBLE | WS_CHILD,
					 /* First 2 Integers are location; last 2 are size */
		            58, 144, ButtonSizes.Width, ButtonSizes.Height,       
		             hwnd, (HMENU) OPTEIGHT, NULL, NULL);
            BtnNine = CreateWindow(TEXT("button"), TEXT("9"),
                     WS_VISIBLE | WS_CHILD,
                     117, 144, ButtonSizes.Width, ButtonSizes.Height,
                     hwnd, (HMENU) OPTNINE, NULL, NULL);           
            BtnZero = CreateWindow(TEXT("button"), TEXT("0"),
                     WS_VISIBLE | WS_CHILD,
                     2, 188, (ButtonSizes.Width * 2), ButtonSizes.Height,
                     hwnd, (HMENU) OPTNINE, NULL, NULL);  
            BtnPls = CreateWindow(TEXT("button"), TEXT("+"),    
		             WS_VISIBLE | WS_CHILD,
					 /* First 2 Integers are location; last 2 are size */
		            176, 56, opt.Width, opt.Height,       
		             hwnd, (HMENU) OPTPLS, NULL, NULL);    
            BtnMin= CreateWindow(TEXT("button"), TEXT("-"),    
		             WS_VISIBLE | WS_CHILD,
					 /* First 2 Integers are location; last 2 are size */
		            176, 110, opt.Width, opt.Height,       
		             hwnd, (HMENU) OPTMIN, NULL, NULL); 
            BtnMul= CreateWindow(TEXT("button"), TEXT("*"),    
		             WS_VISIBLE | WS_CHILD,
					 /* First 2 Integers are location; last 2 are size */
		            176, 164, opt.Width, opt.Height,       
		             hwnd, (HMENU) OPTMUL, NULL, NULL); 
            BtnDiv= CreateWindow(TEXT("button"), TEXT("/"),    
		             WS_VISIBLE | WS_CHILD,
					 /* First 2 Integers are location; last 2 are size */
		            110, 188, (opt.Width + 25), opt.Height - 15,       
		             hwnd, (HMENU) OPTDIV, NULL, NULL); 
      BtnEq= CreateWindow(TEXT("button"), TEXT("="),    
		             WS_VISIBLE | WS_CHILD,
					 /* First 2 Integers are location; last 2 are size */
		            85, 225, (opt.Width * 4), opt.Height - 10,       
		             hwnd, (HMENU) OPTEQU, NULL, NULL); 
        break;
        case WM_COMMAND:   // event handler
             switch (LOWORD(wParam)) {
                    // <number_handler>
                    case OPTONE:
                         HOLDER += '1';
                    break;  
                    case OPTTWO:
                         HOLDER += '2';
                    break;
                    case OPTTHREE:
                         HOLDER += '3';
                    break;
                    case OPTFOUR:
                         HOLDER += '4';
                    break;
                    case OPTFIVE:
                         HOLDER += '5';
                    break;
                    case OPTSIX: 
                         HOLDER += '6';
                    break;
                    case OPTSEVEN:
                         HOLDER += '7';
                    break;
                    case OPTEIGHT:
                         HOLDER += '8';
                    break;
                    case OPTNINE:
                         HOLDER += '9';
                    break;
                    case OPTZERO:
                         HOLDER += '0';
                    break;
                    // </number_handler>                    
                    case OPTPLS:
                         HOLDER += '+';
                    break;
                    case OPTMIN:
                         HOLDER += '-';
                    break;
                    case OPTMUL:
                         HOLDER += '*';
                    break;
                    case OPTDIV:
                         HOLDER += '/';
                    break;
                    case OPTEQU:
                         try 
                         {
                             AlgorithmParser calc;  
                             std::string out;
                             std::stringstream sObj;
                             sObj << calc.calculate(HOLDER);  
                             out = sObj.str();                   
                            SendMessage(Field, WM_SETTEXT, 0, (LPARAM) out.c_str());
                             HOLDER = BLANK;
                         }                           
                         catch (...) { MessageBox(0, "Err:Syntax\n\nA primary expression was expected.\nString will be nullified.", "Err:Syntax", 60); };
                    break;
                    
             };
        break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
