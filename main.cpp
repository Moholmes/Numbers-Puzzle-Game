#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <fstream>
#include <windows.h>
using namespace std;


//*****Structure used*****
struct position
{
position *previous;
char number;
position *next;
}*head=NULL,*tail=NULL ;

class Hash
{
  int *table;
  
public:
  int po;
  Hash(int x);

  void insertItem(int no_of_indexes);

  void deleteItem(int key);

  int hashFunction(int x)
  {
    return (x % po);
  }

  bool searchItem(int num);

  ~Hash()
  {
    for (int i = 0; i < po; i++)
  {
    table[i] = 0;
  }
  }
};
Hash::Hash(int no_of_index)
{
  this->po = no_of_index;
  table = new int[po];
  for (int i = 0; i < po; i++)
  {
    table[i] = 0;
  }
}

void Hash::insertItem(int position)
{
  int index = hashFunction(position);
  table[index]++;
}

bool Hash::searchItem(int num)
{
  int index = hashFunction(num);
  if (table[index] > 1)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

Hash nodepos(8);
//---------------------

//********Global variables********
bool upwardmovability;   // to check if the empty tile can move upward
bool downwardmovability; // to check if the empty tile can move downward
bool rightmovability;    // to check if the empty tile can move right
bool leftmovability;     // to check if the empty tile can move left
bool back_to_menu;       // to make the player to go back to main menu
bool restart_game;       // to restart game
bool p;                  // to restart game from the pause menu
bool pa;                 // to go back to main menu from the pause menu
bool resume;             // to resume game
bool play_again;         // to play again
int chances;             // to give the player chances based on the difficulty the player chooses
bool didnt_win;          // to check if the player won
int score;               // to calculate the score of the player
int scoring;             // to set scale for giving scores based on the difficulty selected
//-------------------------------

//********Functions used*****
void main_menu();                        // to display the main menu
bool checknumbers(position *newvalue);   // To avoid the repetition of random number generated new node.newvalue receives the value of newnode
void setempty();                         // to put the empty tile randomly in a position
void setnumbers();                       // To set the numbers randomly when the game starts
void difficulty();                       // to set the difficulty of the game
void game_interface();                   // to display the game
void help();                             // to display instructions to let the player know about the game
void pause();                            // to pause the game;
int read_score();                        // to read the highest score
void write_highscore(int current_score); // to store the score if it breaks the highest score
void move_empty_tile();                  // to move the empty tile
void winner();                           // to check if the player won the game
void looser();                           // to tell the player he/she lost the game
void start_game();                       // to start the game
//----------------------------------
int main()
{
 do
  {
   char choice;
   bool invalid=1;
   do
   {
     main_menu();
     choice=getch();
     switch(choice)
      {
        case '1':
         start_game();
         invalid=0;
          break;         
         case '3':
         exit(1);
         break;
      }
   }while(invalid);
 }while(back_to_menu);

    return 0;
}


void main_menu()
{
    system("CLS");
    cout<<"\n\n\t_______________________________________________________________\n";
    cout<<"\t\twelcome to the number slider puzzle game!!!!\n";
    cout<<"\t_______________________________________________________________\n\n\n\n";

    cout<<"\t\t *  *  *  *  *  *  *  *  *  *  *  *  *  * * \n";
    cout<<"\t\t*                                          *\n";
    cout<<"\t\t*  \t\tMAIN MENU\t\t   *\n";
    cout<<"\t\t*                                          *\n";
    cout<<"\t\t*                                          *\n";
    cout<<"\t\t*  \tStart game --> press 1\t\t   *\n";
    cout<<"\t\t*                                          *\n";
    cout<<"\t\t*  \texit --> press 3\t\t   *\n";
    cout<<"\t\t *  *  *  *  *  *  *  *  *  *  *  *  *  * * \n\n";

}

bool checknumbers(position* newvalue)
{
  int num = newvalue->number;
  bool x = nodepos.searchItem(num);
  return x;
}

void setempty()
{
    char location;//insert after the location specified
    position * temp=head;
    position * emptynode=new position;
    emptynode->number=' ';


    location=(1+(rand()%8));
    while(temp->number!=location&&temp!=NULL)
      {
        temp=temp->next;

      }

    if(temp->next==NULL)
      {
          tail=emptynode;
      }
    else
      {
          (temp->next)->previous=emptynode;
      }

      emptynode->next=temp->next;
      emptynode->previous=temp;
      temp->next=emptynode;


}

void setnumbers()
{
  srand(time(0));
  for (int i = 0; i < 8; i++)
  {
    position *newnode = new position;
    newnode->previous = NULL;
    do
    {
      newnode->number = (1 + (rand() % 8));
      nodepos.insertItem(newnode->number);
    } while (checknumbers(newnode));

    if (head == NULL)
    {
      newnode->next = NULL;
      head = newnode;
      tail = newnode;
    }

    else
    {
      newnode->next = head;
      head->previous = newnode;
      head = newnode;
    }
  }

  setempty();
}
void difficulty()
{

  char key;
  bool invalid = 1;
  do
  {
    system("CLS");
    cout << "\n\n\n\n\n\t_________________________________\n";
    cout << "\t|\t   Difficulty\t\t|\n";
    cout << "\t|                      \t\t|\n";
    cout << "\t|\tEasy (Press E)\t\t|\n";
    cout << "\t|                      \t\t|\n";
    cout << "\t|\tModerate (Press M)\t|\n";
    cout << "\t|                      \t\t|\n";
    cout << "\t|\tHard (Press H)\t\t|\n";
    cout << "\t|                      \t\t|\n";
    cout << "\t---------------------------------\n"; 
    key = getch();
    if (key == 'E' || key == 'e')
    {
      chances = 80;
      scoring = 10;
      invalid = 0;
    }

    if (key == 'M' || key == 'm')
    {
      chances = 60;
      scoring = 100;
      invalid = 0;
    }

    if (key == 'H' || key == 'h')
    {
      chances = 40;
      scoring = 1000;
      invalid = 0;
    }

  } while (invalid);
}

void game_interface()
{

 system("CLS");
 position *temp=head;
 cout<<"\n\n\n\n\t\t\t\t\t\tChances left:"<<chances<<endl;
 cout<<"\n\t\t\t\t\t\tYour score  :"<<score<<endl;
 for(int i=0;i<3;i++)
  {

   cout<<"\t-------------------------\n";
   cout<<"\t|\t|\t|       |\n";
    for(int j=0;j<3;j++)
      {
        if((int)temp->number==32)
          cout<<"\t|   "<<temp->number<<" ";
        else
          cout<<"\t|   "<<(int)temp->number<<" ";
        if(j==2)
            cout<<"  |";
        temp=temp->next;
      }

        cout<<endl;
  }
   cout<<"\t-------------------------\n";

}


void pause()
{

 char key;
 bool invalid=1;
 do{
    system("CLS");
    cout<<"\n\n\n\n\n\t_________________________________\n";
    cout<<"\t|\t   Pause\t\t|\n";
    cout<<"\t|                      \t\t|\n";
    cout<<"\t|\tContinue(Press C)\t|\n";
    cout<<"\t|                      \t\t|\n";
    cout<<"\t|\tRestart game(Press R)\t|\n";
    cout<<"\t|                      \t\t|\n";
    cout<<"\t|\tMain menu(Press M)\t|\n";
    cout<<"\t|                      \t\t|\n";
    cout<<"\t|\tExit(Press E)\t\t|\n";
    cout<<"\t|                      \t\t|\n";
    cout<<"\t---------------------------------\n";
    key=getch();
    if(key=='C'||key=='c')
    {
        resume=1;
        didnt_win=1;
        invalid=0;
    }
    else
    {
        didnt_win=0;
        resume=0;
    }

    if(key=='R'||key=='r')
    {
        restart_game=1;
        play_again=1;
        p=1;
        head=NULL;
        invalid=0;
    }
    else
    {
        restart_game=0;
        play_again=0;
        p=0;
    }

    if(key=='M'||key=='m')
    {
        back_to_menu=1;
        head=NULL;
        pa=1;
        invalid=0;
    }
    else
    {
        back_to_menu=0;
        pa=0;
    }

    if(key=='E'||key=='e')
    {
        exit(1);
    }

  }while(invalid);
}

void write_highscore(int current_score)
{
  ofstream store;
  store.open("high scores.txt", ios::app);
  if (store.fail())
  {
    cout << "Error storing the score!!!!";
  }
  store << current_score << endl;
  store.close();
}

int read_score()
{
  int scores;
  int highest_score;
  ifstream read_score;
  read_score.open("high scores.txt", ios::in);
  if (read_score.fail())
  {
    write_highscore(0);
    return 0;
  }
  read_score >> scores;
  highest_score = scores;
  read_score.seekg(0, ios::beg);
  while (read_score >> scores)
  {
    if (highest_score < scores)
    {
      highest_score = scores;
    }
  }
  return highest_score;
}

void move_empty_tile()
{
 int row,column;
 position *temp=head;
 for(int i=0;i<3;i++)
  {

    bool exit_second_loop=0;
    for(int j=0;j<3;j++)
     {
        if((int)temp->number==32)
         {
          row=i;
          column=j;
          exit_second_loop=1;
          break;
         }

        temp=temp->next;
     }

    if(exit_second_loop)
        break;
  }

 if(row>0)
    upwardmovability=1;
 else
    upwardmovability=0;

 if(row<2)
    downwardmovability=1;
 else
    downwardmovability=0;

 if(column<2)
    rightmovability=1;
 else
    rightmovability=0;

 if(column>0)
    leftmovability=1;
 else
    leftmovability=0;

 bool invalid=1;
 char control;
 do{
     control=getch();
     if(upwardmovability&&(control=='W'||control=='w'))
          invalid=0;
     if(downwardmovability&&(control=='S'||control=='s'))
          invalid=0;
     if(leftmovability&&(control=='A'||control=='a'))
          invalid=0;
     if(rightmovability&&(control=='D'||control=='d'))
          invalid=0;
     if(control=='P'||control=='p')
          invalid=0;
   }while(invalid);

 switch(control)
 {
  position * swapper;
  char store;

  case 'W':
  case 'w':
     swapper=temp->previous;
     for(int i=1;i<=2;i++)
        swapper=swapper->previous;

     store=temp->number;
     temp->number=swapper->number;
     swapper->number=store;
     chances--;
     p=0;
     pa=0;
    break;
  case 'S':
  case 's':
     swapper=temp->next;
     for(int i=1;i<=2;i++)
        swapper=swapper->next;

     store=temp->number;
     temp->number=swapper->number;
     swapper->number=store;
     chances--;
     p=0;
     pa=0;
    break;
  case 'A':
  case 'a':
     swapper=temp->previous;
     store=temp->number;
     temp->number=swapper->number;
     swapper->number=store;
     chances--;
     p=0;
     pa=0;
    break;
  case 'D':
  case 'd':
     swapper=temp->next;
     store=temp->number;
     temp->number=swapper->number;
     swapper->number=store;
     chances--;
     p=0;
     pa=0;
    break;
  case 'P':
  case 'p':
     pause();
   break;
 }

}


void winner()
{

  position *temp = head;
  for (int i = 1; i <= 8; i++)
  {
    if ((int)temp->number != i)
    {
      didnt_win = 1;
      resume = 1;
      break;
    }
    else
    {
      didnt_win = 0;
      resume = 0;

      if (!didnt_win && i == 8)
      {
        char key;
        bool invalid;
        system("CLS");
        game_interface();
        cout << "\n\n\t\tYou you won the game !!!!!\n\n";
        cout << "\t\tYour score is: " << score;
        if (score > read_score())
        {
          cout << "\n\n\t\tCongratulations!!! You have bitten the highest score\n\n";
        }
        else
        {
          cout << "\n\n\t\tThe highest score is: " << read_score();
          cout << "\n\t\tBit the highest score and prove yourself !! \n\n";
        }
        write_highscore(score);
        Sleep(6000);
        exit(1);
      }
    }
    temp = temp->next;
  }
}

void looser()
{
  char key;
  bool invalid;
  system("CLS");
  cout << "\n\n\t\tYou are a looser !!!!!";
  cout << "\n\n\t\tThe highest score is: " << read_score();
  cout << "\n\t\tBit the highest score and prove yourself !! \n\n";
     Sleep(6000);
     exit(1);

}

void start_game()
{
  do{
    difficulty();
    setnumbers();
    nodepos.~Hash();

    do{

        score=chances*scoring;
        game_interface();
        move_empty_tile();

        if(chances==0)
        {
         didnt_win=0;
         resume=0;
         looser();
        }
        else
        {
          if(restart_game&&p)
          {
            resume=0;
            didnt_win=0;
          }
          else if(back_to_menu&&pa)
          {
            resume=0;
            didnt_win=0;
            restart_game=0;
            play_again=0;
          }
          else
          winner();
        }

      }while(didnt_win && resume);


   }while(restart_game&&play_again);

}


