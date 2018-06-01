/*-----------------------------------------
   MAIN.C -- Othello Game for Win95
  -----------------------------------------*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"


#define ID_TIMER    1

#define MAX_DIVISIONS 	MAX_GRID
#define DEF_DIVISIONS  	MAX_GRID

#define MoveTo(hdc, x, y) MoveToEx (hdc, x, y, NULL)

#define GREEN		RGB(0, 255, 0)
#define RED		RGB(255, 0, 0)
#define BLUE		RGB(0, 0, 255)
#define WHITE		RGB(255, 255, 255)
#define BLACK		RGB(0, 0, 0)

#define LONG_BUFFER_LEN  120



void DrawGrid(HDC hdc, MyProgram *data);
void DrawPieces(HDC hdc, MyProgram *data);
void DrawHint( HDC hdc, MyProgram *data, int r, int c );

void PopupWinner(HWND hwnd, MyProgram *data);
void PopupStatus(HWND hwnd, MyProgram *data);
void PopupNoMoveFound(HWND hwnd, MyProgram *data);
void PopupHelp(HWND hwnd, MyProgram *data);
void PopupAbout(HWND hwnd, MyProgram *data);



LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

char szAppName[] = "Othello" ;



int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     HWND       hwnd ;
     MSG        msg ;
     WNDCLASSEX wndclass ;

     wndclass.cbSize        = sizeof (wndclass) ;
     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) CreateSolidBrush( GREEN ) ;
     wndclass.lpszMenuName  = szAppName ;
     wndclass.lpszClassName = szAppName ;
     wndclass.hIconSm       = LoadIcon (NULL, IDI_APPLICATION) ;

     RegisterClassEx (&wndclass) ;

     hwnd = CreateWindow (szAppName, "Othello Game",
                          WS_OVERLAPPEDWINDOW,
                          100, 0,
                          442, 480,
                          NULL, NULL, hInstance, NULL) ;

     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;

     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
}




LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
     static MyProgram mydata; 

     static int  mSelection = IDM_SINGLE ;
     static int  bSelection = IDM_BOARD12 ;
     static int  sSelection = IDM_NOSKILL ;

     static int  divisions = DEF_DIVISIONS ;
     static int  divarray[3] = { 8, 10, 12 };

     static char status_string[LONG_BUFFER_LEN];

     static COLORREF rgbPureColor;

     HDC         hdc ;
     PAINTSTRUCT ps ;
     RECT        rect ;
     int         r, c ;
     HMENU       hMenu ;
     int	 row[MAX_MOVES];      /* array of row moves */
     int 	 col[MAX_MOVES];      /* array of col moves */

     switch (iMsg)
     {
          case WM_CREATE :
               InitScreen(&mydata);
               InitDatabase(&mydata);
               return 0 ;

          case WM_SIZE :
               mydata.screen.screen_x_size = LOWORD (lParam) ;
               mydata.screen.screen_y_size = HIWORD (lParam) ;
               mydata.grid.size.x = mydata.screen.screen_x_size / mydata.screen.max_grid_col ;
               mydata.grid.size.y = mydata.screen.screen_y_size / mydata.screen.max_grid_row ;
               return 0 ;

          case WM_TIMER :
               if (mydata.data.player_mode == PLAYER_DEMO)
               {
                  HandleComputerMove(&mydata);
                  mydata.data.current_player = TOGGLE_PLAYER(mydata.data.current_player);
                  if ( GameIsOver(&mydata) )
                  {
                     KillTimer(hwnd, ID_TIMER);
                     PopupWinner(hwnd, &mydata);
                  }
                  else
                  {
                     InvalidateRect (hwnd, NULL, TRUE) ;
                  }
               }
               else if ( GameIsOver(&mydata) )
               {
                  KillTimer(hwnd, ID_TIMER);
                  PopupWinner(hwnd, &mydata);
               }
               return 0 ;

          case WM_LBUTTONDOWN :
               c = LOWORD (lParam) / mydata.grid.size.x ;
               r = HIWORD (lParam) / mydata.grid.size.y ;

               if ( r < divisions && c < divisions )
               {
                    if ( HandlePlayerMove(&mydata, r, c) )
                    {
                       if (mydata.data.player_mode == PLAYER_SINGLE)
                       {
                          mydata.data.current_player = TOGGLE_PLAYER(mydata.data.current_player);

                          if ( GameIsOver(&mydata) )
                          {
                             PopupWinner(hwnd, &mydata);
                          }
                          else
                          {
                             HandleComputerMove(&mydata);

                             mydata.data.current_player = TOGGLE_PLAYER(mydata.data.current_player);

                             if ( GameIsOver(&mydata) )
                             {
                                PopupWinner(hwnd, &mydata);
                             }
                          }

                          InvalidateRect (hwnd, NULL, TRUE) ;
                       }
                       else  /* else, two players */
                       {
                          mydata.data.current_player = TOGGLE_PLAYER(mydata.data.current_player);

                          if ( GameIsOver(&mydata) )
                          {
                             PopupWinner(hwnd, &mydata);
                          }

                          InvalidateRect (hwnd, NULL, TRUE) ;
                       }  /* end if player_mode is single */
                    }
                    else  /* else, not valid move */
                    {
                       MessageBeep (0) ;
                    }  /* end if handle player move */

//                    rect.left   = c * mydata.grid.size.x ;
//                    rect.top    = r * mydata.grid.size.y ;
//                    rect.right  = (c + 1) * mydata.grid.size.x ;
//                    rect.bottom = (r + 1) * mydata.grid.size.y ;

//                    InvalidateRect (hwnd, &rect, FALSE) ;
               }
               else
                    MessageBeep (0) ;
               return 0 ;

          case WM_RBUTTONDOWN :
               MessageBeep (0) ;
               return 0 ;

          case WM_PAINT :
               hdc = BeginPaint (hwnd, &ps) ;

               DrawGrid( hdc, &mydata );
               DrawPieces( hdc, &mydata );

               EndPaint (hwnd, &ps) ;
               return 0 ;

          case WM_COMMAND :
               hMenu = GetMenu (hwnd) ;

               switch (LOWORD (wParam))
               {
                    case IDM_NEW :
                         HandleNewGame(&mydata);
                         SetTimer (hwnd, ID_TIMER, 200, NULL);
                         InvalidateRect (hwnd, NULL, TRUE) ;
                         return 0 ;

                    case IDM_LOAD :
                         MessageBeep (0) ;
                         return 0 ;

                    case IDM_SAVE :
                         MessageBeep (0) ;
                         return 0 ;

                    case IDM_EXIT :
                         SendMessage (hwnd, WM_CLOSE, 0, 0L) ;
                         return 0 ;

                    case IDM_UNDO :
                    case IDM_CUT :
                    case IDM_COPY :
                    case IDM_PASTE :
                    case IDM_DEL :
                         MessageBeep (0) ;
                         return 0 ;

                    case IDM_SINGLE :
                         CheckMenuItem (hMenu, mSelection, MF_UNCHECKED) ;
                         mSelection = LOWORD (wParam) ;
                         CheckMenuItem (hMenu, mSelection, MF_CHECKED) ;
                         mydata.data.network_game = FALSE;
                         mydata.data.player_mode = PLAYER_SINGLE;
                         return 0 ;

                    case IDM_MULTI :
                         CheckMenuItem (hMenu, mSelection, MF_UNCHECKED) ;
                         mSelection = LOWORD (wParam) ;
                         CheckMenuItem (hMenu, mSelection, MF_CHECKED) ;
                         mydata.data.network_game = FALSE;
                         mydata.data.player_mode = PLAYER_MULTI;
                         return 0 ;

                    case IDM_NETWORK :
                         CheckMenuItem (hMenu, mSelection, MF_UNCHECKED) ;
                         mSelection = LOWORD (wParam) ;
                         CheckMenuItem (hMenu, mSelection, MF_CHECKED) ;
                         mydata.data.network_game = TRUE;
                         mydata.data.player_mode = PLAYER_MULTI;
                         return 0 ;

                    case IDM_DEMO :
                         CheckMenuItem (hMenu, mSelection, MF_UNCHECKED) ;
                         mSelection = LOWORD (wParam) ;
                         CheckMenuItem (hMenu, mSelection, MF_CHECKED) ;
                         mydata.data.network_game = FALSE;
                         mydata.data.player_mode = PLAYER_DEMO;
                         SetTimer (hwnd, ID_TIMER, 200, NULL);
                         return 0 ;

                    case IDM_BOARD8 :
                    case IDM_BOARD10 :
                    case IDM_BOARD12 :
                         CheckMenuItem (hMenu, bSelection, MF_UNCHECKED) ;
                         bSelection = LOWORD (wParam) ;
                         CheckMenuItem (hMenu, bSelection, MF_CHECKED) ;
                         divisions = divarray[ LOWORD (wParam) - IDM_BOARD8 ] ;
                         mydata.grid.size.x = mydata.screen.screen_x_size / divisions ;
                         mydata.grid.size.y = mydata.screen.screen_y_size / divisions ;
                         HandleBoard( &mydata, divisions );
                         SetTimer (hwnd, ID_TIMER, 200, NULL);
                         InvalidateRect (hwnd, NULL, TRUE) ;
                         return 0 ;

                    case IDM_NOSKILL :
                         CheckMenuItem (hMenu, sSelection, MF_UNCHECKED) ;
                         sSelection = LOWORD (wParam) ;
                         CheckMenuItem (hMenu, sSelection, MF_CHECKED) ;
                         mydata.data.skill_level = SKILL_NONE;
                         return 0 ;

                    case IDM_RANDOM :
                         CheckMenuItem (hMenu, sSelection, MF_UNCHECKED) ;
                         sSelection = LOWORD (wParam) ;
                         CheckMenuItem (hMenu, sSelection, MF_CHECKED) ;
                         mydata.data.skill_level = SKILL_RANDOM;
                         return 0 ;

                    case IDM_CORNERS :
                         CheckMenuItem (hMenu, sSelection, MF_UNCHECKED) ;
                         sSelection = LOWORD (wParam) ;
                         CheckMenuItem (hMenu, sSelection, MF_CHECKED) ;
                         mydata.data.skill_level = SKILL_CORNERS;
                         return 0 ;

                    case IDM_MAXFLIPS :
                         CheckMenuItem (hMenu, sSelection, MF_UNCHECKED) ;
                         sSelection = LOWORD (wParam) ;
                         CheckMenuItem (hMenu, sSelection, MF_CHECKED) ;
                         mydata.data.skill_level = SKILL_MAXFLIP;
                         return 0 ;

                    case IDM_AI :
                         CheckMenuItem (hMenu, sSelection, MF_UNCHECKED) ;
                         sSelection = LOWORD (wParam) ;
                         CheckMenuItem (hMenu, sSelection, MF_CHECKED) ;
                         mydata.data.skill_level = SKILL_AI;
                         return 0 ;

                    case IDM_HINT :
                         if (HandleGetMoveList( &mydata, row, col, 1) == 0)
                         {
                            PopupNoMoveFound( hwnd, &mydata );
                         }
                         else
                         {
                            r = row[0];
                            c = col[0];
                            hdc = GetDC (hwnd) ;
                            DrawHint( hdc, &mydata, r, c ); 
                            ReleaseDC (hwnd, hdc) ;
                         }
                         return 0 ;

                    case IDM_PASS :
                         if (mydata.data.player_mode == PLAYER_SINGLE)
                         {
                            mydata.data.current_player = TOGGLE_PLAYER(mydata.data.current_player);
                            InvalidateRect (hwnd, NULL, TRUE) ;

                            HandleComputerMove(&mydata);

                            mydata.data.current_player = TOGGLE_PLAYER(mydata.data.current_player);
                            InvalidateRect (hwnd, NULL, TRUE) ;

                            if ( GameIsOver(&mydata) )
                            {
                               PopupWinner( hwnd, &mydata );
                            }
                         }
                         else
                         {
                            mydata.data.current_player = TOGGLE_PLAYER(mydata.data.current_player);
                            InvalidateRect (hwnd, NULL, TRUE) ;
                         }
                         return 0 ;

                    case IDM_HELP :
                    case IDM_HELPKEY :
                    case IDM_HELPRULE :
                         MessageBeep (0) ;
                         PopupHelp( hwnd, &mydata );
                         return 0 ;

                    case IDM_STATUS :
                         PopupStatus( hwnd, &mydata );
                         return 0 ;

                    case IDM_ABOUT :
                         PopupAbout( hwnd, &mydata );
                         return 0 ;
               }
               break ;

          case WM_DESTROY :
               KillTimer (hwnd, ID_TIMER) ;
               PostQuitMessage (0) ;
               return 0 ;
     }

     return DefWindowProc (hwnd, iMsg, wParam, lParam) ;
}


void DrawGrid(HDC hdc, MyProgram *data)
{
   int r, c;

   SelectObject( hdc, CreateSolidBrush( GREEN ) );
   SelectObject( hdc, GetStockObject( BLACK_PEN) );

   for (r = 0 ; r < data->screen.max_grid_row ; r++)
   {
      for (c = 0 ; c < data->screen.max_grid_col ; c++)
      {
         Rectangle (hdc, 
 		c * data->grid.size.x, 
		r * data->grid.size.y,
		(c + 1) * data->grid.size.x, 
		(r + 1) * data->grid.size.y) ;
      }
   }
}


void DrawPieces(HDC hdc, MyProgram *data)
{
   int	r, c ;
   int  count_1, count_2;


   count_1 = count_2 = 0;

   for (r = 0 ; r < data->screen.max_grid_row ; r++)
   {
      for (c = 0 ; c < data->screen.max_grid_col ; c++)
      {
         if (data->data.board[r][c] == PIECE_PLAYER_1)
         {
            count_1++;

            SelectObject( hdc, CreateSolidBrush(WHITE) );
            SelectObject( hdc, GetStockObject( WHITE_PEN) );

            Ellipse (hdc, 
			(c * data->grid.size.x) + 2, 
			(r * data->grid.size.y) + 2,
			((c+1) * data->grid.size.x) - 2, 
			((r+1) * data->grid.size.y) - 2) ;
         }
         else if (data->data.board[r][c] == PIECE_PLAYER_2)
         {
            count_2++;

            SelectObject( hdc, CreateSolidBrush(BLACK) );
            SelectObject( hdc, GetStockObject( BLACK_PEN) );

            Ellipse (hdc, 
 			(c * data->grid.size.x) + 2, 
			(r * data->grid.size.y) + 2,
			((c+1) * data->grid.size.x) - 2, 
			((r+1) * data->grid.size.y) - 2) ;
         }
      }
   }

   data->score.player1_score = count_1;
   data->score.player2_score = count_2;
}


void DrawHint(HDC hdc, MyProgram *data, int r, int c)
{
   SelectObject( hdc, CreateSolidBrush( GREEN ) );

   if (data->data.current_player == PIECE_PLAYER_1)
   {
      SelectObject( hdc, GetStockObject( WHITE_PEN) );
   }
   else
   {
      SelectObject( hdc, GetStockObject( BLACK_PEN) );
   }

   Ellipse (hdc, 
		(c * data->grid.size.x) + 2, 
		(r * data->grid.size.y) + 2,
		((c+1) * data->grid.size.x) - 2, 
		((r+1) * data->grid.size.y) - 2) ;
}


void PopupWinner(HWND hwnd, MyProgram *data)
{
   char status_string[LONG_BUFFER_LEN];

   sprintf(&status_string[0], 
	"Player %d Wins!\n",
	data->data.winning_player);

   MessageBox (hwnd, status_string, szAppName, MB_ICONINFORMATION | MB_OK) ;
}


void PopupNoMoveFound(HWND hwnd, MyProgram *data)
{
   char status_string[LONG_BUFFER_LEN];

   sprintf(&status_string[0], 
	"No move found\nfor player %d", 
	data->data.current_player);

   MessageBox (hwnd, status_string, szAppName, MB_ICONINFORMATION | MB_OK) ;
}


void PopupHelp(HWND hwnd, MyProgram *data)
{
   MessageBox (hwnd, 
	"Help not yet implemented!",
	szAppName, MB_ICONEXCLAMATION | MB_OK) ;
}


void PopupStatus(HWND hwnd, MyProgram *data)
{
   char status_string[LONG_BUFFER_LEN];

   sprintf(&status_string[0], 
	"grid x = %d\ngrid y = %d\nscreen x = %d\nscreen y = %d\np1score = %d\np2score = %d\nwinning player = %d\n",
	data->grid.size.x, data->grid.size.y, 
	data->screen.screen_x_size, data->screen.screen_y_size,
	data->score.player1_score, data->score.player2_score,
	data->data.winning_player);

   MessageBox (hwnd, status_string, szAppName, MB_ICONINFORMATION | MB_OK) ;
}


void PopupAbout(HWND hwnd, MyProgram *data)
{
   MessageBox (hwnd, 
	"   Othello\n\n Version 0.1\n\nBrian Lingard",
	szAppName, MB_ICONINFORMATION | MB_OK) ;
}


/* end of main.c */

