#include "GameData.h"
#include <string>
#include <conio.h>
#include <fstream>
#include <iostream>

int FR, FC, TR,TC;
int Flag=0;
bool PromotePawn=false;





bool isValidMove(GameData& Game, chessMove Move){

    // this function will return true if the move specified by the Move parameter is a valid move
   // You might make more functions to breakdown the task of this function into subtasks

    FR = Move.FromRow ;
    FC = Move.FromColumn;
    TR = Move.ToRow;
    TC = Move.ToColumn;

    //WHITE PAWN MOVEMENT
   	if(Game.TurningPlayer==WHITE)
	{

   		if( Game.Board[FR][FC].Code==PAWN)
  		{

   			if(FC==TC && TR==FR-1   && Game.Board[TR][TC].Code==NONE)
   			{
   				Flag=1;
   				return true;
			}
			else
			{
				//LEFT CAPTURE
				if(FC!=TC && TR==FR-1 && TC==FC-1 && Game.Board[TR][TC].PieceColor==BLACK)
				{
					Flag=1;
					return true;
				}
				//RIGHT CAPTURE
				if(FC!=TC && TR==FR-1 && TC==FC+1 && Game.Board[TR][TC].PieceColor==BLACK)
				{
					Flag=1;
					return true;
				}
			}//FROM FIRST ROW OF WHITE PAWN

			if((FR==6) && (FC==TC) && (TR==FR-2) && Game.Board[TR][TC].Code==NONE)
			{
				Flag=1;
				return true;
			}
			Flag=0;
			return false;

		}
	}
	//BLACK PAWN MOVEMENT
	if(Game.TurningPlayer==BLACK)
	{
		if( Game.Board[FR][FC].Code==PAWN)
  		{
   			if(FC==TC && TR==FR+1 && Game.Board[TR][TC].Code==NONE )
   			{
   				Flag=1;
   				return true;
			}
			else
			{		//RIGHT CAPTURE
					if(FC!=TC && TR==FR+1  && TC==FC+1  && Game.Board[TR][TC].PieceColor==WHITE)
					{
						Flag=1;
						return true;
					}
					//LEFT CAPTURE
					if(FC!=TC && TR==FR+1  && TC==FC-1  && Game.Board[TR][TC].PieceColor==WHITE)
					{
						Flag=1;
						return true;
					}
			}
			//FROM 1ST ROW OF BLACK PAWNS
			if(FR==1 && FC==TC && TR==FR+2 && Game.Board[TR][TC].Code==NONE)
			{
				Flag=1;
				return true;
			}
			Flag=0;
			return false;

		}
	}
	//KNIGHT

	if(Game.TurningPlayer==WHITE)
	{
		if(Game.Board[FR][FC].Code==KNIGHT)
		{
			//RIGHT MOVEMENT
			if((TR==FR+1 || TR==FR-1) && TC==FC+2 && (Game.Board[TR][TC].PieceColor==BLACK || Game.Board[TR][TC].Code==NONE))
			{
				Flag=1;
				return true;
			}
			//LEFT MOVEMENT
			if((TR==FR+1 || TR==FR-1) && TC==FC-2 && (Game.Board[TR][TC].PieceColor==BLACK || Game.Board[TR][TC].Code==NONE))
			{
				Flag=1;
				return true;
			}
			//DOWNWARD MOVEMENT
			if(TR==FR+2 && (TC==FC+1 || TC==FC-1 ) && (Game.Board[TR][TC].PieceColor==BLACK || Game.Board[TR][TC].Code==NONE))
			{
				Flag=1;
				return true;
			}
			//UPWARD MOVEMENT
			if(TR==FR-2 && (TC==FC+1 || TC==FC-1) && (Game.Board[TR][TC].PieceColor==BLACK || Game.Board[TR][TC].Code==NONE))
			{
				Flag=1;
				return true;
			}
		}
	}
	if(Game.TurningPlayer==BLACK)
	{
		if(Game.Board[FR][FC].Code==KNIGHT)
		{
			//RIGHT MOVEMENT
			if((TR==FR+1 || TR==FR-1) && TC==FC+2 && (Game.Board[TR][TC].PieceColor==WHITE || Game.Board[TR][TC].Code==NONE))
			{
				Flag=1;
				return true;
			}
			//LEFT MOVEMENT
			if((TR==FR+1 || TR==FR-1) && TC==FC-2 && (Game.Board[TR][TC].PieceColor==WHITE || Game.Board[TR][TC].Code==NONE))
			{
				Flag=1;
				return true;
			}
			//DOWNWARD MOVEMENT
			if(TR==FR+2 && (TC==FC+1 || TC==FC-1 ) && (Game.Board[TR][TC].PieceColor==WHITE || Game.Board[TR][TC].Code==NONE))
			{
				Flag=1;
				return true;
			}
			//UPWARD MOVEMENT
			if(TR==FR-2 && (TC==FC+1 || TC==FC-1) && (Game.Board[TR][TC].PieceColor==WHITE || Game.Board[TR][TC].Code==NONE))
			{
				Flag=1;
				return true;
			}
		}
	}
	//ROOK
	if(Game.TurningPlayer==WHITE)
	{
		if(Game.Board[FR][FC].Code==ROOK)
		{
			//RIGHT MOVEMENT
			if(FR==TR)
			{
				if(FC<TC)
				{
					for(int i=FC+1 ;i<TC;i++)
					{
						if(Game.Board[FR][i].Code!=NONE)
						{
							Flag=0;
							return false;
						}
					}
					 if(Game.Board[TR][TC].Code==NONE || (Game.Board[TR][TC].PieceColor==BLACK ))
                    {
                        Flag=1;
                        return true;
                    }

				}

                if(FC>TC)
                {
                    for(int i=FC - 1;i>TC;i--)
                    {
                        if(Game.Board[FR][i].Code!=NONE)
                        {
                            Flag=0;
                            return false;
                        }
                    }
                        if(Game.Board[TR][TC].Code==NONE || (Game.Board[TR][TC].PieceColor==BLACK ))
                        {
                            Flag=1;
                            return true;
                        }
                }
            }
			if(FC==TC)
			{
				if(FR<FC)
				{
					//MOVE DOWNNWARDS
					for(int i=FR+1;i<TR;i++)
					{
						if(Game.Board[i][FC].Code!=NONE)
						{
							Flag=0;
							return false;
						}
					}
					if(Game.Board[TR][TC].Code==NONE || (Game.Board[TR][TC].PieceColor==BLACK ))
                    {
                        Flag=1;
                        return true;
                    }
				}
                //MOVE UPWARDS
                if(FR>TR){
                    for(int i=FR-1;i>TR;i--)
                    {
                        if(Game.Board[i][FC].Code!=NONE )
                        {
                            Flag=0;
                            return false;
                        }
                    }
                    if(Game.Board[TR][TC].Code==NONE || (Game.Board[TR][TC].PieceColor==BLACK ))
                    {
                        Flag=1;
                        return true;
                    }
                }
            }
		}
	}
	if(Game.TurningPlayer==BLACK)
	{
		if(Game.Board[FR][FC].Code==ROOK)
		{
			//RIGHT MOVEMENT
			if(FR==TR)
			{
				if(FC<TC)
				{
					for(int i=FC +1;i<TC;i++)
					{
						if(Game.Board[FR][i].Code!=NONE)
						{
							Flag=0;
							return false;
						}
					}
					 if(Game.Board[TR][TC].Code==NONE || (Game.Board[TR][TC].PieceColor==WHITE ))
                    {
                        Flag=1;
                        return true;
                    }

				}

                if(FC>TC)
                {
                    for(int i=FC - 1;i>TC;i--)
                    {
                        if(Game.Board[FR][i].Code!=NONE)
                        {
                            Flag=0;
                            return false;
                        }
                    }
                    if(Game.Board[TR][TC].Code==NONE || (Game.Board[TR][TC].PieceColor==WHITE ))
                    {
                        Flag=1;
                        return true;
                    }
				}
            }
			if(FC==TC)
			{
				if(FR<FC)
				{
					//MOVE DOWNNWARDS
					for(int i=FR+1;i<TR;i++)
					{
						if(Game.Board[i][FC].Code==NONE)
						{
							Flag=0;
							return false;
						}
					}
					if(Game.Board[TR][TC].Code==NONE || (Game.Board[TR][TC].PieceColor==WHITE ))
                    {
                        Flag=1;
                        return true;
                    }
				}
				Flag=1;

				return true;
                //MOVE UPWARDS
                if(FR>TR){
                    for(int i=FR-1;i>TR;i--)
                    {
                        if(Game.Board[i][FC].Code!=NONE )
                        {
                            Flag=0;
                            return false;
                        }
                    }
                    if(Game.Board[TR][TC].Code==NONE || (Game.Board[TR][TC].PieceColor==WHITE ))
                    {
                        Flag=1;
                        return true;
                    }
                }
            }
		}
	}

	//WHITE QUEEN MOVEMENT
	if(Game.TurningPlayer==WHITE)
	{
		if(Game.Board[FR][FC].Code==QUEEN)
		{
			//RIGHT MOVEMENT
			if(FR==TR)
			{
				if(FC<TC)
				{
					for(int i=FC+1 ;i<TC;i++)
					{
						if(Game.Board[FR][i].Code!=NONE)
						{
							Flag=0;
							return false;
						}
					}
					 if(Game.Board[TR][TC].Code==NONE || (Game.Board[TR][TC].PieceColor==BLACK ))
                    {
                        Flag=1;
                        return true;
                    }

				}

                if(FC>TC)
                {
                    for(int i=FC - 1;i>TC;i--)
                    {
                        if(Game.Board[FR][i].Code!=NONE)
                        {
                            Flag=0;
                            return false;
                        }
                    }
                    if(Game.Board[TR][TC].Code==NONE || (Game.Board[TR][TC].PieceColor==BLACK ))
                    {
                        Flag=1;
                        return true;
                    }
				}
            }
			if(FC==TC)
			{
				if(FR<FC)
				{
					//MOVE DOWNNWARDS
					for(int i=FR+1;i<TR;i++)
					{
						if(Game.Board[i][FC].Code!=NONE)
						{
							Flag=0;
							return false;
						}
					}
					if(Game.Board[TR][TC].Code==NONE || (Game.Board[TR][TC].PieceColor==BLACK ))
                    {
                        Flag=1;
                        return true;
                    }
				}
                //MOVE UPWARDS
                if(FR>TR){
                    for(int i=FR-1;i>TR;i--)
                    {
                        if(Game.Board[i][FC].Code!=NONE )
                        {
                            Flag=0;
                            return false;
                        }
                    }
                    if(Game.Board[TR][TC].Code==NONE || (Game.Board[TR][TC].PieceColor==BLACK ))
                    {
                        Flag=1;
                        return true;
                    }
                }
            }
         int i, j;
            if(Game.Board[FR][FC].PieceColor == WHITE){
                //For top right movement
                if(FR>TR && FC<TC){
                    if(FR-TR != TC-FC)
                    {
                        Flag=0;
                        return false;
                    }
                    if(Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE)
                    {
                        Flag=0;
                        return false;
                    }
                    for(i=FR-1, j=FC+1; i>TR && j<TC; i--, j++){
                        if(Game.Board[i][j].Code != NONE){
                            Flag=0;
                            return false;
                        }
                    }
                    Flag=1;
                    return true;
                }
                //For top left movement
                if(FR>TR && FC>TC){
                    if(FR-TR != FC-TC)
                    {
                        Flag=0;
                        return false;
                    }
                   if(Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE)
                    {

                        Flag=0;
                        return false;
                    }
                    for(i=FR-1, j=FC-1; i>TR && j>TC; i--, j--){
                        if(Game.Board[i][j].Code != NONE){
                            Flag=0;
                            return false;
                        }
                    }
                    Flag=1;
                    return true;
                }
                //For bottom right movement
                if(FR<TR && FC<TC){
                    if(TR-FR != TC-FC)
                    {
                        Flag=0;
                        return false;
                    }
                    if(Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE)
                    {

                        Flag=0;
                        return false;
                    }
                    for(i=FR+1, j=FC+1; i<TR && j<TC; i++, j++){
                        if(Game.Board[i][j].Code != NONE){
                            Flag=0;
                            return false;
                        }
                    }
                    Flag=1;
                    return true;
                }
                //For bottom left movement
                if(FR<TR && FC>TC){
                    if(TR-FR != FC-TC)
                    {
                        Flag=0;
                        return false;
                    }
                    if(Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE)
                    {

                        Flag=0;
                        return false;
                    }
                    for(i=FR+1, j=FC-1; i<TR && j>TC; i++, j--){
                        if(Game.Board[i][j].Code != NONE){
                            Flag=0;
                            return false;
                        }
                    }
                    Flag=1;
                    return true;
                }
            }
		}
	}
	//BLACK QUEEN MOVEMENT
	if(Game.TurningPlayer==BLACK)
	{
		if(Game.Board[FR][FC].Code==QUEEN)
		{
			//RIGHT MOVEMENT
			if(FR==TR)
			{
				if(FC<TC)
				{
					for(int i=FC+1 ;i<TC;i++)
					{
						if(Game.Board[FR][i].Code!=NONE)
						{
							Flag=0;
							return false;
						}
					}
					 if(Game.Board[TR][TC].Code==NONE || (Game.Board[TR][TC].PieceColor==WHITE ))
                    {
                        Flag=1;
                        return true;
                    }

				}

                if(FC>TC)
                {
                    for(int i=FC - 1;i>TC;i--)
                    {
                        if(Game.Board[FR][i].Code!=NONE)
                        {
                            Flag=0;
                            return false;
                        }
                    }
                    if(Game.Board[TR][TC].Code==NONE || (Game.Board[TR][TC].PieceColor==WHITE))
                    {
                        Flag=1;
                        return true;
                    }
				}
            }
			if(FC==TC)
			{
				if(FR<FC)
				{
					//MOVE DOWNNWARDS
					for(int i=FR+1;i<TR;i++)
					{
						if(Game.Board[i][FC].Code!=NONE)
						{
							Flag=0;
							return false;
						}
					}
					if(Game.Board[TR][TC].Code==NONE || (Game.Board[TR][TC].PieceColor==WHITE ))
                    {
                        Flag=1;
                        return true;
                    }
				}
                //MOVE UPWARDS
                if(FR>TR){
                    for(int i=FR-1;i>TR;i--)
                    {
                        if(Game.Board[i][FC].Code!=NONE )
                        {
                            Flag=0;
                            return false;
                        }
                    }
                    if(Game.Board[TR][TC].Code==NONE || (Game.Board[TR][TC].PieceColor==WHITE ))
                    {
                        Flag=1;
                        return true;
                    }
                }
            }
         int i, j;
            if(Game.Board[FR][FC].PieceColor == BLACK){
                //For top right movement
                if(FR>TR && FC<TC){
                    if(FR-TR != TC-FC)
                    {
                        Flag=0;
                        return false;
                    }
                    if(Game.Board[TR][TC].PieceColor == WHITE && Game.Board[TR][TC].Code != NONE)
                    {
                        Flag=0;
                        return false;
                    }
                    for(i=FR-1, j=FC+1; i>TR && j<TC; i--, j++){
                        if(Game.Board[i][j].Code != NONE){
                            Flag=0;
                            return false;
                        }
                    }
                    Flag=1;
                    return true;
                }
                //For top left movement
                if(FR>TR && FC>TC){
                    if(FR-TR != FC-TC)
                    {
                        Flag=0;
                        return false;
                    }
                   if(Game.Board[TR][TC].PieceColor == WHITE && Game.Board[TR][TC].Code != NONE)
                    {

                        Flag=0;
                        return false;
                    }
                    for(i=FR-1, j=FC-1; i>TR && j>TC; i--, j--){
                        if(Game.Board[i][j].Code != NONE){
                            Flag=0;
                            return false;
                        }
                    }
                    Flag=1;
                    return true;
                }
                //For bottom right movement
                if(FR<TR && FC<TC){
                    if(TR-FR != TC-FC)
                    {
                        Flag=0;
                        return false;
                    }
                    if(Game.Board[TR][TC].PieceColor == WHITE && Game.Board[TR][TC].Code != NONE)
                    {

                        Flag=0;
                        return false;
                    }
                    for(i=FR+1, j=FC+1; i<TR && j<TC; i++, j++){
                        if(Game.Board[i][j].Code != NONE){
                            Flag=0;
                            return false;
                        }
                    }
                    Flag=1;
                    return true;
                }
                //For bottom left movement
                if(FR<TR && FC>TC){
                    if(TR-FR != FC-TC)
                    {
                        Flag=0;
                        return false;
                    }
                    if(Game.Board[TR][TC].PieceColor ==WHITE && Game.Board[TR][TC].Code != NONE)
                    {

                        Flag=0;
                        return false;
                    }
                    for(i=FR+1, j=FC-1; i<TR && j>TC; i++, j--){
                        if(Game.Board[i][j].Code != NONE){
                            Flag=0;
                            return false;
                        }
                    }
                    Flag=1;
                    return true;
                }
            }
		}
	}

	//WHITE BISHOP MOVEMENT
	 if(Game.Board[FR][FC].Code == BISHOP){
    int i, j;
        //For White Bishop
        if(Game.TurningPlayer == WHITE){
            if(Game.Board[FR][FC].PieceColor == WHITE){
                //For top right movement
                if(FR>TR && FC<TC){
                    if(FR-TR != TC-FC)
                    {
                        Flag=0;
                        return false;
                    }
                    if(Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE)
                    {
                        Flag=0;
                        return false;
                    }
                    for(i=FR-1, j=FC+1; i>TR && j<TC; i--, j++){
                        if(Game.Board[i][j].Code != NONE){
                            Flag=0;
                            return false;
                        }
                    }
                    Flag=1;
                    return true;
                }
                //For top left movement
                if(FR>TR && FC>TC){
                    if(FR-TR != FC-TC)
                    {
                        Flag=0;
                        return false;
                    }
                   if(Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE)
                    {

                        Flag=0;
                        return false;
                    }
                    for(i=FR-1, j=FC-1; i>TR && j>TC; i--, j--){
                        if(Game.Board[i][j].Code != NONE){
                            Flag=0;
                            return false;
                        }
                    }
                    Flag=1;
                    return true;
                }
                //For bottom right movement
                if(FR<TR && FC<TC){
                    if(TR-FR != TC-FC)
                    {
                        Flag=0;
                        return false;
                    }
                    if(Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE)
                    {

                        Flag=0;
                        return false;
                    }
                    for(i=FR+1, j=FC+1; i<TR && j<TC; i++, j++){
                        if(Game.Board[i][j].Code != NONE){
                            Flag=0;
                            return false;
                        }
                    }
                    Flag=1;
                    return true;
                }
                //For bottom left movement
                if(FR<TR && FC>TC){
                    if(TR-FR != FC-TC)
                    {
                        Flag=0;
                        return false;
                    }
                    if(Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE)
                    {

                        Flag=0;
                        return false;
                    }
                    for(i=FR+1, j=FC-1; i<TR && j>TC; i++, j--){
                        if(Game.Board[i][j].Code != NONE){
                            Flag=0;
                            return false;
                        }
                    }
                    Flag=1;
                    return true;
                }
            }

        }
        //For Black Bishop
        if(Game.TurningPlayer == BLACK){
            if(Game.Board[FR][FC].PieceColor == BLACK){
                //For top right movement
                if(FR>TR && FC<TC){
                    if(FR-TR != TC-FC)
                    {
                        Flag=0;
                        return false;
                    }
                    if(Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE)
                    {

                        Flag=0;
                        return false;
                    }
                    for(i=FR-1, j=FC+1; i>TR && j<TC; i--, j++){
                        if(Game.Board[i][j].Code != NONE){
                            Flag=0;
                            return false;
                        }
                    }
                    Flag=1;
                    return true;
                }
                //For top left movement
                if(FR>TR && FC>TC){
                    if(FR-TR != FC-TC)
                    {
                        Flag=0;
                        return false;
                    }
                    if(Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE)
                    {

                        Flag=0;
                        return false;
                    }
                    for(i=FR-1, j=FC-1; i>TR && j>TC; i--, j--){
                        if(Game.Board[i][j].Code != NONE){
                            Flag=0;
                            return false;
                        }
                    }
                     Flag=1;
                    return true;
                }
                //For bottom right movement
                if(FR<TR && FC<TC){
                    if(TR-FR != TC-FC)
                    {

                        Flag=0;
                        return false;
                    }
                    if(Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE)
                    {
                        Flag=0;
                        return false;
                    }
                    for(i=FR+1, j=FC+1; i<TR && j<TC; i++, j++){
                        if(Game.Board[i][j].Code != NONE){
                            Flag=0;
                            return false;
                        }
                    }
                    Flag=1;
                    return true;
                }
                //For bottom left movement
                if(FR<TR && FC>TC){
                    if(TR-FR != FC-TC)
                    {
                        Flag=0;
                        return false;
                    }
                    if(Game.Board[TR][TC].PieceColor == BLACK && Game.Board[TR][TC].Code != NONE)
                    {
                        Flag=0;
                        return false;
                    }
                    for(i=FR+1, j=FC-1; i<TR && j>TC; i++, j--){
                        if(Game.Board[i][j].Code != NONE){
                            Flag=0;
                            return false;
                        }
                    }
                    Flag=1;
                    return true;
                }
            }
        }
    }
	// BLACK KING MOVEMENT
	if(Game.TurningPlayer ==BLACK)
	{
		if(Game.Board[FR][FC].Code==KING)
		{  //FOR DOWNWARD MOVEMENT
			if(FC==TC && TR==FR+1 && (Game.Board[TR][TC].Code==NONE || Game.Board[TR][TC].PieceColor==WHITE))
			{
				Flag=1;
				return true;
			}
		    //FOR UPWARD MOVE
			if(FC==TC && TR==FR-1 && (Game.Board[TR][TC].Code==NONE || Game.Board[TR][TC].PieceColor==WHITE))
			{
				Flag=1;
				return true;
			}
			//FOR RIGHT MOVE
			if(FR==TR && TC==FC+1 && (Game.Board[TR][TC].Code==NONE || Game.Board[TR][TC].PieceColor==WHITE))
			{
				Flag=1;
				return 1;
			}
			//FOR LEFT MOVE
			if(  FR==TR && TC==FC-1 && (Game.Board[TR][TC].Code==NONE || Game.Board[TR][TC].PieceColor==WHITE))
			{
				Flag=1;
				return 1;
			}
			//FOR DIAGONAL MOVE
			if(FC!=TC  && FR!=TR && TR==FR+1  && TC==FC+1  && (Game.Board[TC][TR].Code==NONE || Game.Board[TR][TC].PieceColor==WHITE))
		  	{
				Flag=1;
				return true;
			}
			if(FC!=TC && FR!=TR && TR==FR-1  && TC==FC-1  && (Game.Board[TC][TR].Code==NONE || Game.Board[TR][TC].PieceColor==WHITE))
			{
				Flag=1;
				return true;
			}
			if(FC!=TC && FR!=TR && TR==FR+1  && TC==FC-1  && (Game.Board[TC][TR].Code==NONE || Game.Board[TR][TC].PieceColor==WHITE))
			{
				Flag=1;
				return true;
			}
			if(FC!=TC && FR!=TR && TR==FR-1  && TC==FC+1  &&(Game.Board[TC][TR].Code==NONE|| Game.Board[TR][TC].PieceColor==WHITE))
			{
				Flag=1;
				return true;
			}
			Flag=0;
			return false;
		}
    }
    //WHITE KING MOVEMENT
    if(Game.TurningPlayer ==WHITE)
	{
		if(Game.Board[FR][FC].Code==KING)
		{  //FOR DOWNWARD MOVEMENT
			if(FC==TC && TR==FR+1 && (Game.Board[TR][TC].Code==NONE || Game.Board[TR][TC].PieceColor==BLACK))
			{
				Flag=1;
				return true;
			}
		    //FOR UPWARD MOVE
			if(FC==TC && TR==FR-1 && (Game.Board[TR][TC].Code==NONE || Game.Board[TR][TC].PieceColor==BLACK))
			{
				Flag=1;
				return true;
			}
			//FOR RIGHT MOVE
			if(FR==TR && TC==FC+1 && (Game.Board[TR][TC].Code==NONE || Game.Board[TR][TC].PieceColor==BLACK))
			{

				return 1;
			}
			//FOR LEFT MOVE
			if(  FR==TR && TC==FC-1 && (Game.Board[TR][TC].Code==NONE || Game.Board[TR][TC].PieceColor==BLACK))
			{

				return true;
			}
			//FOR DIAGONAL MOVE
			if(FC!=TC  && FR!=TR && TR==FR+1  && TC==FC+1  && (Game.Board[TC][TR].Code==NONE || Game.Board[TR][TC].PieceColor==BLACK))
		  	{
				Flag=1;
				return true;
			}
			if(FC!=TC && FR!=TR && TR==FR-1  && TC==FC-1  && (Game.Board[TC][TR].Code==NONE || Game.Board[TR][TC].PieceColor==BLACK))
			{
				Flag=1;
				return true;
			}
			if(FC!=TC && FR!=TR && TR==FR+1  && TC==FC-1  && (Game.Board[TC][TR].Code==NONE || Game.Board[TR][TC].PieceColor==BLACK))
			{
				Flag=1;
				return true;
			}
			if(FC!=TC && FR!=TR && TR==FR-1  && TC==FC+1  &&(Game.Board[TC][TR].Code==NONE|| Game.Board[TR][TC].PieceColor==BLACK))
			{
				Flag=1;
				return true;
			}
		}
    }
    return false;
}
int MakeMove(GameData& Game, chessMove Move){
    //Function to make a mo6 0 5 5ve on the board
    // It will return 0 if the move is valid and a code of error to specify why the move is not valid otherwise
   if(!isValidMove(Game,Move))
     return 1;
    FR = Move.FromRow ;
    FC = Move.FromColumn ;
    TR = Move.ToRow ;
    TC = Move.ToColumn ;


    if(Flag==1)
    {
         Game.Board[TR][TC].Code =
         Game.Board[FR][FC].Code;
        Game.Board[TR][TC].PieceColor =
             Game.Board[FR][FC].PieceColor;
        Game.Board[FR][FC].Code = NONE;
    }
    if (((Game.Board[TR][TC].Code == PAWN )&& ((Game.Board[TR][TC].PieceColor==WHITE && TR==0 )|| (Game.Board[TR][TC].PieceColor==BLACK&& TR==7 ))))
    {
        PromotePawn=true;
    }
    if (PromotePawn==true)
    {
        cout<<"Choose your required Option in which you want to promote your Pawn?"<<endl<<"1.QUEEN"<<endl<<"2.BISHOP"<<endl
        <<"3.KNIGHT"<<endl<<"4.ROOK"<<endl;
        int option;
        cin>>option;
        if(option==1)
            Game.Board[TR][TC].Code=QUEEN;

        if(option==2)
            Game.Board[TR][TC].Code=BISHOP;
        if(option==3)
            Game.Board[TR][TC].Code=KNIGHT;
        if(option==4)
            Game.Board[TR][TC].Code=ROOK;

        Game.Board[TR][TC].PieceColor = Game.Board[FR][FC].PieceColor;

        PromotePawn=false;
        return 0;
    }
    if(isfacingCheck(Game,BLACK)==true)
    {
            return 2;
    }
    if(isfacingCheckW(Game,WHITE)==true)
    {
            return 3;
    }
    if(isCheckmate(Game,BLACK)==true)
    {
            return 4;
    }
    if(isCheckmateW(Game,WHITE)==true)
    {
            return 5;
    }
    if(Game.TurningPlayer == BLACK)
        Game.TurningPlayer = WHITE;
    else
    Game.TurningPlayer = BLACK;


    return 0;
}

 void initGame(GameData& Game){

    for(int r = 0; r < 2; r++)
        for(int c= 0; c < 8; c++ )
            Game.Board[r][c].PieceColor = BLACK;

    for(int r = 2; r < 6; r++)
        for(int c= 0; c < 8; c++ )
            Game.Board[r][c].Code = NONE;

    for(int r = 6; r < 8; r++)
        for(int c= 0; c < 8; c++ )
            Game.Board[r][c].PieceColor = WHITE;


    Game.Board[0][0].Code = Game.Board[0][7].Code = ROOK;
    Game.Board[7][0].Code = Game.Board[7][7].Code = ROOK;

    Game.Board[0][1].Code = Game.Board[0][6].Code = KNIGHT;
    Game.Board[7][1].Code = Game.Board[7][6].Code = KNIGHT;

    Game.Board[0][2].Code = Game.Board[0][5].Code = BISHOP;
    Game.Board[7][2].Code = Game.Board[7][5].Code = BISHOP;

    Game.Board[0][3].Code = Game.Board[7][3].Code = QUEEN;
    Game.Board[0][4].Code = Game.Board[7][4].Code = KING;

    for(int c= 0; c < 8; c++ )
        Game.Board[1][c].Code = Game.Board[6][c].Code = PAWN;

    Game.TurningPlayer = WHITE;

    return;
}
bool isfacingCheck(GameData& Game, Color Player){
    // This function must return true if player having Color Player is facing a check
    //BLACK KING
    for(int i=0;i<=7;i++)
    {
        for(int j=0;j<8;j++)
        {
            //WHITE PAWN
            if(Game.Board[i][j].Code==KING && Game.Board[i][j].PieceColor==BLACK)
            {
                if((Game.Board[i+1][j-1].Code==PAWN && Game.Board[i+1][j-1].PieceColor==WHITE) ||
                   (Game.Board[i+1][j+1].Code==PAWN && Game.Board[i+1][j+1].PieceColor==WHITE))
                {   Flag=1;
                    return true;
                }

            //WHITE ROOK AND QUEEN(HORIZOTAL AND VERTICAL MOVEMENTS)
                 for(int row=i-1; row>=0; row--)
                {
                    if(Game.Board[row][j].Code != NONE) //there's some piece in this direction
                    {
                        if( (Game.Board[row][j].PieceColor == BLACK) || (  Game.Board[row][j].Code != QUEEN && Game.Board[row][j].Code != ROOK
                        && Game.Board[row][j].PieceColor == WHITE  ) ) {
                            Flag=0;
                            break;
                        } //player's own piece means protection
                             //no need to check further
                        else
                        {
                            if (Game.Board[row][j].Code == QUEEN || Game.Board[row][j].Code == ROOK) //it is an opponent's queen or rook

                                {  Flag=1;
                                     return true;
                                }
                        }
                    }
                }

                 //check downwards.. ROOK or QUEEN can hit
                for(int row=i+1; row<=7; row++)
                {
                    if(Game.Board[row][j].Code != NONE) //there's some piece in this direction
                    {
                        if( (Game.Board[row][j].PieceColor == BLACK) || (  Game.Board[row][j].Code != QUEEN &&
                            Game.Board[row][j].Code != ROOK && Game.Board[row][j].PieceColor == WHITE  )) //player's own piece means protection
                          {Flag=0;
                             break;
                          }  //no need to check further
                        else
                        {
                            if(Game.Board[row][j].Code == QUEEN || Game.Board[row][j].Code == ROOK) //it is an opponent's queen or rook
                              {Flag=1;
                                 return true;
                              }
                        }
                    }
                }

                for(int col=j-1; col>=0; col--)
                {
                    if(Game.Board[i][col].Code != NONE) //there's some piece in this direction
                    {
                        if( (Game.Board[i][col].PieceColor == BLACK) || (  Game.Board[i][col].Code != QUEEN && Game.Board[i][col].Code != ROOK && Game.Board[i][col].PieceColor == WHITE  )) //player's own piece means protection

                           {Flag=0;
                             break;
                           }  //no need to check further
                        else
                        {
                            if(Game.Board[i][col].Code == QUEEN || Game.Board[i][col].Code == ROOK) //it is an opponent's queen or rook
                                {   Flag=1;
                                    return true;
                                }
                        }
                    }
                }

                //check Right side.. ROOK or QUEEN can hit
                for(int col=j+1; col<=7; col++)
                {
                    if(Game.Board[i][col].Code != NONE) //there's some piece in this direction
                    {
                        if( (Game.Board[i][col].PieceColor == BLACK) || (  Game.Board[i][col].Code != QUEEN && Game.Board[i][col].Code != ROOK && Game.Board[i][col].PieceColor == WHITE  )) //player's own piece means protection
                             {   Flag=0;
                                 break;
                                 }//no need to check further
                        else
                        {
                            if(Game.Board[i][col].Code == QUEEN || Game.Board[i][col].Code == ROOK) //it is an opponent's queen or rook
                                {Flag=1;
                                return true;
                                }

                        }
                    }
                }

            //WHITE BISHOP AND QUEEN(DIAGONAL MOVEMENTS)
            //BOTTOM LEFT
                for(int row=i+1,col=j-1;row>i && col<j ;row++,col--)
                {
                    if(Game.Board[row][col].Code != NONE) //there's some piece in this direction
                    {
                        if( (Game.Board[row][col].PieceColor == BLACK) || (  Game.Board[row][col].Code != QUEEN
                            && Game.Board[row][col].Code != BISHOP && Game.Board[row][col].PieceColor == WHITE  )) //player's own piece means protection
                             {
                                 Flag=0;
                                 break;
                             }//no need to check further
                        else
                        {
                            if(Game.Board[row][col].Code == QUEEN || Game.Board[row][col].Code == BISHOP) //it is an opponent's queen or rook
                            {
                                Flag=1;
                                return true;
                            }
                        }
                    }
                }
                //BOTTOM RIGHT
                 for(int row=i+1,col=j+1;row>i && col>j ;row++,col++)
                {
                    if(Game.Board[row][col].Code != NONE) //there's some piece in this direction
                    {
                        if( (Game.Board[row][col].PieceColor == BLACK) || (  Game.Board[row][col].Code != QUEEN
                            && Game.Board[row][col].Code != BISHOP && Game.Board[row][col].PieceColor == WHITE  )) //player's own piece means protection
                             {
                                 Flag=0;
                                 break;
                             }//no need to check further
                        else
                        {
                            if(Game.Board[row][col].Code == QUEEN || Game.Board[row][col].Code == BISHOP) //it is an opponent's queen or rook
                            {
                                Flag=1;
                                return true;
                            }
                        }
                    }
                }
                //TOP LEFT
                for(int row=i-1,col=j-1;row<i && col<j ;row--,col--)
                {
                    if(Game.Board[row][col].Code != NONE) //there's some piece in this direction
                    {
                        if( (Game.Board[row][col].PieceColor == BLACK) || (  Game.Board[row][col].Code != QUEEN
                            && Game.Board[row][col].Code != BISHOP && Game.Board[row][col].PieceColor == WHITE  )) //player's own piece means protection
                             {
                                 Flag=0;
                                 break;
                             }//no need to check further
                        else
                        {
                            if(Game.Board[row][col].Code == QUEEN || Game.Board[row][col].Code == BISHOP) //it is an opponent's queen or rook
                            {
                                Flag=1;
                                return true;
                            }
                            else
                            {
                                Flag=0;
                                return false;
                            }
                        }
                    }
                }
                //TOP RIGHT
                for(int row=i-1,col=j+1;row<i && col>j ;row--,col++)
                {
                    if(Game.Board[row][col].Code != NONE) //there's some piece in this direction
                    {
                        if( (Game.Board[row][col].PieceColor == BLACK) || (  Game.Board[row][col].Code != QUEEN
                            && Game.Board[row][col].Code != BISHOP && Game.Board[row][col].PieceColor == WHITE  )) //player's own piece means protection
                             {
                                 Flag=0;
                                 break;
                             }//no need to check further
                        else
                        {
                            if(Game.Board[row][col].Code == QUEEN || Game.Board[row][col].Code == BISHOP) //it is an opponent's queen or rook
                            {
                                Flag=1;
                                return true;
                            }
                        }
                    }
                }
                //knight
                //ROW-1,COL+2
                if(Game.Board[i-1][j+2].Code==KNIGHT && Game.Board[i-1][j+2].PieceColor==WHITE)
                {
                    Flag=1;
                    return true;
                }
                //ROW+1 , COL+2
               if(Game.Board[i+1][j+2].Code==KNIGHT && Game.Board[i+1][j+2].PieceColor==WHITE)
                {
                    Flag=1;
                    return true;
                }

               //ROW-1,COL-2
                if(Game.Board[i-1][j-2].Code==KNIGHT && Game.Board[i-1][j-2].PieceColor==WHITE)
                {
                    Flag=1;
                    return true;
                }

                //ROW+1 , COL-2
                if(Game.Board[i+1][j-2].Code==KNIGHT && Game.Board[i+1][j-2].PieceColor==WHITE)
                {
                    Flag=1;
                    return true;
                }

                //ROW +2,COL-1
                if(Game.Board[i+2][j-1].Code==KNIGHT && Game.Board[i+2][j-1].PieceColor==WHITE)
                {
                    Flag=1;
                    return true;
                }

                //ROW+2,COL+1
                if(Game.Board[i+2][j+1].Code==KNIGHT && Game.Board[i+2][j+1].PieceColor==WHITE)
                {
                    Flag=1;
                    return true;
                }

                //ROW-2,COL-1
                if(Game.Board[i-2][j-1].Code==KNIGHT && Game.Board[i-2][j+1].PieceColor==WHITE)
                {
                    Flag=1;
                    return true;
                }

                //ROW-2,COL+1
                if(Game.Board[i-2][j+1].Code==KNIGHT && Game.Board[i-2][j+1].PieceColor==WHITE)
                {
                    Flag=1;
                    return true;
                }
                Flag=0;
                return false;
            }
        }
    }


    return false;
}
bool isfacingCheckW(GameData& Game, Color Player){
      for(int i=0;i<=7;i++)
    {
        for(int j=0;j<8;j++)
        {

            if(Game.Board[i][j].Code==KING && Game.Board[i][j].PieceColor==WHITE)
            {
                 //WHITE PAWN
                if((Game.Board[i-1][j-1].Code==PAWN && Game.Board[i-1][j-1].PieceColor==BLACK) ||
                   (Game.Board[i-1][j+1].Code==PAWN && Game.Board[i-1][j+1].PieceColor==BLACK))
                {   Flag=1;
                    return true;
                }
                 //knight
                //ROW-1,COL+2
                if(Game.Board[i-1][j+2].Code==KNIGHT && Game.Board[i-1][j+2].PieceColor==BLACK)
                {
                    Flag=1;
                    return true;
                }
                //ROW+1 , COL+2
               if(Game.Board[i+1][j+2].Code==KNIGHT && Game.Board[i+1][j+2].PieceColor==BLACK)
                {
                    Flag=1;
                    return true;
                }

               //ROW-1,COL-2
                if(Game.Board[i-1][j-2].Code==KNIGHT && Game.Board[i-1][j-2].PieceColor==BLACK)
                {
                    Flag=1;
                    return true;
                }

                //ROW+1 , COL-2
                if(Game.Board[i+1][j-2].Code==KNIGHT && Game.Board[i+1][j-2].PieceColor==BLACK)
                {
                    Flag=1;
                    return true;
                }

                //ROW +2,COL-1
                if(Game.Board[i+2][j-1].Code==KNIGHT && Game.Board[i+2][j-1].PieceColor==BLACK)
                {
                    Flag=1;
                    return true;
                }

                //ROW+2,COL+1
                if(Game.Board[i+2][j+1].Code==KNIGHT && Game.Board[i+2][j+1].PieceColor==BLACK)
                {
                    Flag=1;
                    return true;
                }

                //ROW-2,COL-1
                if(Game.Board[i-2][j-1].Code==KNIGHT && Game.Board[i-2][j+1].PieceColor==BLACK)
                {
                    Flag=1;
                    return true;
                }

                //ROW-2,COL+1
                if(Game.Board[i-2][j+1].Code==KNIGHT && Game.Board[i-2][j+1].PieceColor==BLACK)
                {
                    Flag=1;
                    return true;
                }

                //BLACK ROOK AND QUEEN(HORIZOTAL AND VERTICAL MOVEMENTS)
                 for(int row=i-1; row>=0; row--)
                {
                    if(Game.Board[row][j].Code != NONE) //there's some piece in this direction
                    {
                        if( (Game.Board[row][j].PieceColor == WHITE) || (  Game.Board[row][j].Code != QUEEN && Game.Board[row][j].Code != ROOK
                        && Game.Board[row][j].PieceColor == BLACK  ) ) {
                            Flag=0;
                            break;
                        } //player's own piece means protection
                             //no need to check further
                        else
                        {
                            if (Game.Board[row][j].Code == QUEEN || Game.Board[row][j].Code == ROOK) //it is an opponent's queen or rook

                                {  Flag=1;
                                     return true;
                                }
                        }
                    }
                }

                 //check downwards.. ROOK or QUEEN can hit
                for(int row=i+1; row<=7; row++)
                {
                    if(Game.Board[row][j].Code != NONE) //there's some piece in this direction
                    {
                        if( (Game.Board[row][j].PieceColor == WHITE) || (  Game.Board[row][j].Code != QUEEN &&
                            Game.Board[row][j].Code != ROOK && Game.Board[row][j].PieceColor == BLACK  )) //player's own piece means protection
                          {Flag=0;
                             break;
                          }  //no need to check further
                        else
                        {
                            if(Game.Board[row][j].Code == QUEEN || Game.Board[row][j].Code == ROOK) //it is an opponent's queen or rook
                              {Flag=1;
                                 return true;
                              }
                        }
                    }
                }

                for(int col=j-1; col>=0; col--)
                {
                    if(Game.Board[i][col].Code != NONE) //there's some piece in this direction
                    {
                        if( (Game.Board[i][col].PieceColor == WHITE) || (  Game.Board[i][col].Code != QUEEN && Game.Board[i][col].Code != ROOK && Game.Board[i][col].PieceColor == BLACK  )) //player's own piece means protection

                           {Flag=0;
                             break;
                           }  //no need to check further
                        else
                        {
                            if(Game.Board[i][col].Code == QUEEN || Game.Board[i][col].Code == ROOK) //it is an opponent's queen or rook
                                {   Flag=1;
                                    return true;
                                }
                        }
                    }
                }

                //check Right side.. ROOK or QUEEN can hit
                for(int col=j+1; col<=7; col++)
                {
                    if(Game.Board[i][col].Code != NONE) //there's some piece in this direction
                    {
                        if( (Game.Board[i][col].PieceColor == WHITE) || (  Game.Board[i][col].Code != QUEEN && Game.Board[i][col].Code != ROOK && Game.Board[i][col].PieceColor == BLACK  )) //player's own piece means protection
                             {   Flag=0;
                                 break;
                                 }//no need to check further
                        else
                        {
                            if(Game.Board[i][col].Code == QUEEN || Game.Board[i][col].Code == ROOK) //it is an opponent's queen or rook
                                {
                                    Flag=1;
                                    return true;
                                }

                        }
                    }
                }
//WHITE BISHOP AND QUEEN(DIAGONAL MOVEMENTS)
            //BOTTOM LEFT
                for(int row=i+1,col=j-1;row>i && col<j ;row++,col--)
                {
                    if(Game.Board[row][col].Code != NONE) //there's some piece in this direction
                    {
                        if( (Game.Board[row][col].PieceColor == WHITE) || (  Game.Board[row][col].Code != QUEEN
                            && Game.Board[row][col].Code != BISHOP && Game.Board[row][col].PieceColor == BLACK  )) //player's own piece means protection
                             {
                                 Flag=0;
                                 break;
                             }//no need to check further
                        else
                        {
                            if(Game.Board[row][col].Code == QUEEN || Game.Board[row][col].Code == BISHOP) //it is an opponent's queen or rook
                            {
                                Flag=1;
                                return true;
                            }
                        }
                    }
                }
                //BOTTOM RIGHT
                 for(int row=i+1,col=j+1;row>i && col>j ;row++,col++)
                {
                    if(Game.Board[row][col].Code != NONE) //there's some piece in this direction
                    {
                        if( (Game.Board[row][col].PieceColor == WHITE) || (  Game.Board[row][col].Code != QUEEN
                            && Game.Board[row][col].Code != BISHOP && Game.Board[row][col].PieceColor == BLACK  )) //player's own piece means protection
                             {
                                 Flag=0;
                                 break;
                             }//no need to check further
                        else
                        {
                            if(Game.Board[row][col].Code == QUEEN || Game.Board[row][col].Code == BISHOP) //it is an opponent's queen or rook
                            {
                                Flag=1;
                                return true;
                            }
                        }
                    }
                }
                //TOP LEFT
                for(int row=i-1,col=j-1;row<i && col<j ;row--,col--)
                {
                    if(Game.Board[row][col].Code != NONE) //there's some piece in this direction
                    {
                        if( (Game.Board[row][col].PieceColor == WHITE) || (  Game.Board[row][col].Code != QUEEN
                            && Game.Board[row][col].Code != BISHOP && Game.Board[row][col].PieceColor == BLACK  )) //player's own piece means protection
                             {
                                 Flag=0;
                                 break;
                             }//no need to check further
                        else
                        {
                            if(Game.Board[row][col].Code == QUEEN || Game.Board[row][col].Code == BISHOP) //it is an opponent's queen or rook
                            {
                                Flag=1;
                                return true;
                            }
                        }
                    }
                }
                //TOP RIGHT
                for(int row=i-1,col=j+1;row<i && col>j ;row--,col++)
                {
                    if(Game.Board[row][col].Code != NONE) //there's some piece in this direction
                    {
                        if( (Game.Board[row][col].PieceColor == WHITE) || (  Game.Board[row][col].Code != QUEEN
                            && Game.Board[row][col].Code != BISHOP && Game.Board[row][col].PieceColor == BLACK  )) //player's own piece means protection
                             {
                                 Flag=0;
                                 break;
                             }//no need to check further
                        else
                        {
                            if(Game.Board[row][col].Code == QUEEN || Game.Board[row][col].Code == BISHOP) //it is an opponent's queen or rook
                            {
                                Flag=1;
                                return true;
                            }
                        }
                    }
                }

                Flag=0;
                return false;
            }
        }
    }
    return false;

 }
bool isCheckmate(GameData& Game, Color Player){
    // This function must return true if player having Color Player is facing a checkmate
    chessMove Move;
    FR = Move.FromRow ;
    FC = Move.FromColumn ;
    TR = Move.ToRow ;
    TC = Move.ToColumn ;
    if(Game.Board[FR][FC].Code==KING && Game.Board[FR][FC].PieceColor==BLACK  && isValidMove(Game,Move)==true)
    {
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(Game.Board[FR-i][FC].Code==NONE || Game.Board[FR-i][FC].PieceColor==WHITE && isValidMove(Game,Move)==true)
                {
                    if(isfacingCheck(Game,BLACK)==true)
                    {
                        Flag=1;
                        return true;
                    }
                }

                if(Game.Board[FR-i][FC+j].Code==NONE || Game.Board[FR-i][FC+j].PieceColor==WHITE && isValidMove(Game,Move)==true)
                {
                    if(isfacingCheck(Game,BLACK)==true)
                    {
                        Flag=1;
                        return true;
                    }

                }

                 if(Game.Board[FR-i][FC-j].Code==NONE || Game.Board[FR-i][FC-j].PieceColor==WHITE && isValidMove(Game,Move)==true)
                {
                    if(isfacingCheck(Game,BLACK)==true)
                    {
                        Flag=1;
                        return true;
                    }

                }

                 if(Game.Board[FR+i][FC].Code==NONE || Game.Board[FR+i][FC].PieceColor==WHITE && isValidMove(Game,Move)==true)
                {
                    if(isfacingCheck(Game,BLACK)==true)
                    {
                        Flag=1;
                        return true;
                    }
                }

                 if(Game.Board[FR+i][FC+j].Code==NONE || Game.Board[FR+i][FC+j].PieceColor==WHITE && isValidMove(Game,Move)==true)
                {
                    if(isfacingCheck(Game,BLACK)==true)
                    {
                        Flag=1;
                        return true;
                    }

                }

                 if(Game.Board[FR+i][FC-j].Code==NONE || Game.Board[FR+i][FC-j].PieceColor==WHITE && isValidMove(Game,Move)==true)
                {
                    if(isfacingCheck(Game,BLACK)==true)
                    {
                        Flag=1;
                        return true;
                    }

                }

                 if(Game.Board[FR][FC+j].Code==NONE || Game.Board[FR][FC+j].PieceColor==WHITE && isValidMove(Game,Move)==true)
                {
                    if(isfacingCheck(Game,BLACK)==true)
                    {
                        Flag=1;
                        return true;
                    }

                }

                 if(Game.Board[FR][FC-j].Code==NONE || Game.Board[FR][FC-j].PieceColor==WHITE && isValidMove(Game,Move)==true)
                {
                    if(isfacingCheck(Game,BLACK)==true)
                    {
                        Flag=1;
                        return true;
                    }

                }

        }
        }
    }
    Flag=0;
    return false;
}
bool isCheckmateW(GameData& Game, Color Player){
    chessMove Move;
    FR = Move.FromRow ;
    FC = Move.FromColumn ;
    TR = Move.ToRow ;
    TC = Move.ToColumn ;
    if(Game.Board[FR][FC].Code==KING && Game.Board[FR][FC].PieceColor==BLACK  && isValidMove(Game,Move)==true)
    {
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(Game.Board[FR-i][FC].Code==NONE || Game.Board[FR-i][FC].PieceColor==WHITE && isValidMove(Game,Move)==true)
                {
                    if(isfacingCheckW(Game,BLACK)==true)
                    {
                        Flag=1;
                        return true;
                    }
                }

                if(Game.Board[FR-i][FC+j].Code==NONE || Game.Board[FR-i][FC+j].PieceColor==WHITE && isValidMove(Game,Move)==true)
                {
                    if(isfacingCheckW(Game,BLACK)==true)
                    {
                        Flag=1;
                        return true;
                    }

                }

                 if(Game.Board[FR-i][FC-j].Code==NONE || Game.Board[FR-i][FC-j].PieceColor==WHITE && isValidMove(Game,Move)==true)
                {
                    if(isfacingCheck(Game,BLACK)==true)
                    {
                        Flag=1;
                        return true;
                    }

                }

                 if(Game.Board[FR+i][FC].Code==NONE || Game.Board[FR+i][FC].PieceColor==WHITE && isValidMove(Game,Move)==true)
                {
                    if(isfacingCheckW(Game,BLACK)==true)
                    {
                        Flag=1;
                        return true;
                    }
                }

                 if(Game.Board[FR+i][FC+j].Code==NONE || Game.Board[FR+i][FC+j].PieceColor==WHITE && isValidMove(Game,Move)==true)
                {
                    if(isfacingCheckW(Game,WHITE)==true)
                    {
                        Flag=1;
                        return true;
                    }

                }

                 if(Game.Board[FR+i][FC-j].Code==NONE || Game.Board[FR+i][FC-j].PieceColor==WHITE && isValidMove(Game,Move)==true)
                {
                    if(isfacingCheckW(Game,WHITE)==true)
                    {
                        Flag=1;
                        return true;
                    }

                }

                 if(Game.Board[FR][FC+j].Code==NONE || Game.Board[FR][FC+j].PieceColor==WHITE && isValidMove(Game,Move)==true)
                {
                    if(isfacingCheckW(Game,WHITE)==true)
                    {
                        Flag=1;
                        return true;
                    }

                }

                 if(Game.Board[FR][FC-j].Code==NONE || Game.Board[FR][FC-j].PieceColor==WHITE && isValidMove(Game,Move)==true)
                {
                    if(isfacingCheckW(Game,WHITE)==true)
                    {
                        Flag=1;
                        return true;
                    }

                }

        }
        }
    }
    Flag=0;
    return false;

}

int SaveGame(GameData& Game, string FileName){
    //Function to save a game data into a file.
   ofstream OUT(FileName);
        for(int r=0; r<8; r++)
        {
            for(int c=0; c<8; c++){
                OUT<<(int) Game.Board[r][c].PieceColor;
                OUT<<(int) Game.Board[r][c].Code<<"\t";
            }
            OUT<<endl;
        }
        OUT.close();
    return 0;
}



int LoadGame(GameData& Game, string FileName){
    // function to load games data from a file

    ifstream IN(FileName);
    int a, n, m;
    for(int r=0; r<8; r++)
    {
        for(int c=0; c<8; c++)
        {
            IN>>a;
            n=a/10;
            m=a%10;

            if(n==0) Game.Board[r][c].PieceColor=BLACK;
            if(n==1) Game.Board[r][c].PieceColor=WHITE;

            if(m==0) Game.Board[r][c].Code=NONE;
            if(m==1) Game.Board[r][c].Code=PAWN;
            if(m==2) Game.Board[r][c].Code=ROOK;
            if(m==3) Game.Board[r][c].Code=BISHOP;
            if(m==4) Game.Board[r][c].Code=KNIGHT;
            if(m==5) Game.Board[r][c].Code=QUEEN;
            if(m==6) Game.Board[r][c].Code=KING;
        }
    }
    IN.close();

    return 0;
}
