#include<iostream>
#include<string>
#include<conio.h>
#include<fstream>

#include "GameData.cpp"
int s;
using namespace std;


struct Chess{
    GameData GameState;
    string PlayerNames[2];
    bool GameActive = false;
} Game;

string getPlayerinfo(){
    string Name="";
    cout<< "\nEnter Player Name\n";
    do{
        cin.clear();
        fflush(stdin);
        getline(cin, Name);
    }while(Name.length() == 0);
    return Name;
}

int SaveGame(){
    // If we have an active game then save it for future along with player names
    // The function will ask the user to specify a file name and save the entire game into it
    string FileName;
    cout<<"Enter your file name: ";
    cin>>FileName;
    SaveGame(Game.GameState, FileName);
    cout<<"File saved by name "<<FileName<<endl<<endl;
    return 0;
}


   int LoadGame(){
    // The function will ask the user to specify a file name and save the entire game into it
    string FileName;
    cout<<"Enter your file name: ";
    cin>>FileName;
    LoadGame(Game.GameState, FileName);
    cout<<"File loaded successfully"<<endl;
    return 0;

}

void ShowGame(){

    cout<< Game.PlayerNames[1]<<"\tvs\t"<<Game.PlayerNames[0]<<endl;

    for(int r = 0; r < 8; r++ ){
        cout<<endl<<r;
        for(int c = 0; c < 8; c++){
            switch(Game.GameState.Board[r][c].Code){
                case NONE:
                    cout<<"\t..";
                break;
                default:
                    cout<<"\t";
                    if(Game.GameState.Board[r][c].PieceColor == BLACK)
                        cout<<"B";
                    else
                        cout<<"W";

                    switch(Game.GameState.Board[r][c].Code){
                    case PAWN:
                        cout<<"P";
                    break;

                    case ROOK:
                        cout<<"R";
                    break;

                    case KNIGHT:
                        cout<<"kN";
                    break;

                    case BISHOP:
                        cout<<"B";
                    break;

                    case QUEEN:
                        cout<<"Q";
                    break;

                    case KING:
                        cout<<"K";
                    break;
                    }
                break;
            }
        }
        cout<<endl<<endl;
    }
    cout<<endl;
    for(int c = 0; c< 8; c++)
        cout<<"\t"<<c;
    cout<<"\n";
}

void initNewGame(){
    cout<<"Enter First(WHITE) Player's Info"<<endl;
    Game.PlayerNames[1] = getPlayerinfo();
    cout<<"\n\nEnter Second(BLACK) Player's Info"<<endl;
    Game.PlayerNames[0] = getPlayerinfo();
    initGame(Game.GameState);
}

int PlayGame(){
    chessMove Move;
    ShowGame();

    while(!isCheckmate(Game.GameState, Game.GameState.TurningPlayer) ){
        cout<<Game.PlayerNames[Game.GameState.TurningPlayer];
        if(Game.GameState.TurningPlayer == WHITE)
            cout<<" (WHITE) To Move";
        else
            cout<<" (BLACK) To Move";

        cout<<"\n\n"<<"Please enter your move  (use format FROM (Row# Column#) TO (Row# Column#) ) {Negative Value to move to the main menu}"<<endl;


        cin >> Move.FromRow>>Move.FromColumn;
        cin>>Move.ToRow>>Move.ToColumn;

        if(Move.FromRow < 0 || Move.FromColumn < 0 || Move.ToColumn < 0 || Move.ToRow < 0){
            cout<< "Moving to main menu \n";
            return 0;
        }

        s = MakeMove(Game.GameState, Move);
        if(s==4){
            cout<<"Check Mate \nWhite Player wins"<<endl<<endl;
            break;
        }
        if(s==5){
            cout<<"Check Mate \nBlack Player wins"<<endl<<endl;
            break;
        }
        if(s == 1){
            cout<<"Invalid move! Try again"<<endl<<endl;
        }
        else{
            if(s==2 || s==3){
                if(s==2) cout<<"CHECK! \nBLACK IS FACING CHECK"<<endl;
                if(s==3) cout<<"CHECK! \nWHITE IS FACING CHECK"<<endl;
                ShowGame();
            }
            else{
            ShowGame();
            }
        }

}
    return 0;

}


int main(){
	{
   cout << "    ======================================\n";
   cout << "       _____ _    _ ______  _____ _____\n";
   cout << "      / ____| |  | |  ____|/ ____/ ____|\n";
   cout << "     | |    | |__| | |__  | (___| (___ \n";
   cout << "     | |    |  __  |  __|  \\___ \\\\___ \\ \n";
   cout << "     | |____| |  | | |____ ____) |___) |\n";
   cout << "      \\_____|_|  |_|______|_____/_____/\n\n";
   cout << "    ======================================\n";
   cout<<" <<<< WELCOME TO THE CHESS OF YOUTHFUL POETS >>>>"<<endl;
   cout<<"      // CREATED BY FIZZA AND RABIA //        "<<endl;
   cout<<"Let's Play Chess! "<<endl;
}
    int choice = 0;
    do{
        do{
            cout<<"1. New Game\n2. Restart Game\n3. Save Game\n4. Load Game\n5. Exit\n\n Enter Your Choice(1-5) ";
            cin>>choice;
        }while(choice< 1 || choice > 5);

        switch(choice){
        case 1:
            initNewGame();
            PlayGame();
        break;
        case 2:
            PlayGame();
        break;
        case 3:
            SaveGame();
        break;
        case 4:
            LoadGame();
        break;
        case 5:
            return 0;
        break;
        }
    }while(1);

    return 0;
}
