#include<bits/stdc++.h>
//#include<ctime>
//#include<conio>
using namespace std;
class board                         //class for the board
{  
    void add(int i)                 //to add snakes or ladders in your personallized board
    {
        int start,end;
        cout<<"\nAdd a ";
        if(i==1)    cout<<"ladder ";
        if(i==-1)   cout<<"snake ";
        cout<<"between which two places on the board?\n";
        cin>>start>>end;
        if(start>end)
        {
            int x=end;
            end=start;
            start=x;
            if(end>size){cout<<"\nError cannot excede size of board\n";return;}
        }
        if(i==1)    ladder.push_back(make_pair(start,end));
        if(i==-1)   snake.push_back(make_pair(start,end));
        return;
    }
    void del(int i)             //to delete snakes or laddes in your personalized board
    {
        vector<pair<int,int>>::iterator itr;
        int slno=1,choice;
        cout<<"\nChoose which one you want to delete from this list\nEnter only the Sl.no\n\n";
        if(i==1)
        {
            for(itr=ladder.begin();itr!=ladder.end();slno++,itr++)
                cout<<slno<<" "<<itr->first<<" to "<<itr->second<<"\n";
            cin>>choice;
            if(choice>slno)
            {
                cout<<"\nError sl no inncorrect\n";
                return;
            }
            itr=ladder.begin();
            itr+=choice-1;
            itr->first=0;
            itr->second=0;
        }
        if(i==-1)
        {
            for(itr=snake.begin();itr!=snake.end();slno++,itr++)
                cout<<slno<<" "<<itr->first<<" to "<<itr->second<<"\n";
            cin>>choice;
            if(choice>slno)
            {
                cout<<"\nError sl no inncorrect\n";
                return;
            }
            itr=snake.begin();
            itr+=choice-1;
            itr->first=0;
            itr->second=0;
        }
        return;
    }
    void makeboard(int s)                       //function to make a custom board
    {
        int choice=0;
        while(1)
        {   cout<<"\nMake your custom board using this menu\n1.Add snake\n2.Delete snake\n3.Add ladder\n4.Delete ladder\n5.Display snakes and ladders \n6.Go back\n\n";
            cin>>choice;
            //switch(choice)
            {
                if(choice==1) add(-1);
                if(choice==2) del(-1);
                if(choice==3) add(1);
                if(choice==4) del(1);
                if(choice==6) return;
                if(choice==5) printboard();
            }
        }
    }
    protected:                                      //to inherit into class game
        int size=100;
        vector<pair<int,int>> snake,ladder;
    public:
    void printboard()           //prints all the snakes and ladders
    {
        vector<pair<int,int>>::iterator itr;
        cout<<"\nSize of the board is: "<<size;
        cout<<"\nSnakes are: \n";
        int slno=1;
        for(itr=snake.begin();itr!=snake.end();itr++,slno++)   cout<<slno<<" "<<itr->second<<" to "<<itr->first<<"\n";
        slno=1;
        cout<<"\nLadders are: \n";
        for(itr=ladder.begin();itr!=ladder.end();itr++,slno++)   cout<<slno<<" "<<itr->first<<" to "<<itr->second<<"\n";
        return;
    }
    board()
    {
        int choice;
        cout<<"Do you want to make a custom board or do you want to play with a pre-set board?\nEnter 1 to make a board\nEnter anything else to play a pre-set board\n";
        cin>>choice;
        if(choice==1)
        {
            cout<<"\n Enter size of board\n";
            cin>>size;
            makeboard(size);    //call to make a custom board
        }
        else    // hardcoding to make a pre-set board
        {
            snake.push_back(make_pair(79,98));snake.push_back(make_pair(75,95));snake.push_back(make_pair(73,93));snake.push_back(make_pair(36,87));snake.push_back(make_pair(60,64));snake.push_back(make_pair(19,62));snake.push_back(make_pair(34,54));snake.push_back(make_pair(7,17));
            ladder.push_back(make_pair(80,99));ladder.push_back(make_pair(72,91));ladder.push_back(make_pair(28,84));ladder.push_back(make_pair(51,67));ladder.push_back(make_pair(21,43));ladder.push_back(make_pair(2,38));ladder.push_back(make_pair(9,31));ladder.push_back(make_pair(4,14));
        }
    }
};
class game:public board
{
    vector<pair<int,int>> player;
    void match()                                        //function for a match
    {
        int t=2,k=turn(1);
        while(k==0)
        {
            k=turn(t);
            t++;
        }
        //clrscr();
        cout<<"\n\n\n\n\nThe winner is player "<<k<<"\nTotal turns played are "<<t;             //could add this in a destructor if you want to but I wrote it here
        return;
    }
    int turn(int turnno)                                //function for a turn
    {
        int die;
        char dummy;
        //clrscr();
        cout<<"\n\n\n\n\nThis is turn number "<<turnno<<"\nPress any key to proceed";
        cin>>dummy;
        vector<pair<int,int>>::iterator itr_p,itr_s,itr_l;
        for(itr_p=player.begin();itr_p!=player.end();itr_p++)
        {
            //clrscr();
            cout<<"\n\n\n\n\n\nPlayer "<<itr_p->first<<"\'s turn\nPress any key to roll dice\n";
            cin>>dummy;
            die=rand();             //tried by giving limiting coditions, forgot how to, so worked around it
            die=die%6+1;
            cout<<"\nInitial position: "<<itr_p->second<<" Dice roll: "<<die;//<<"New position: "<<(itr_p->second+die);
            cout<<"\nPress any key to continue\n";
            cin>>dummy;
            itr_p->second+=die;
            if(itr_p->second>=size)
                return itr_p->first;
            for(itr_s=snake.begin();itr_s!=snake.end();itr_s++)
            {    
                if(itr_p->second==itr_s->second)
                {
                    itr_p->second=itr_s->first;
                    cout<<"Oops a snake ate you :'/ your new location is: "<<itr_p->second;
                    break;
                }
            }
            for(itr_l=ladder.begin();itr_l!=ladder.end();itr_l++)
            {
                if(itr_p->second==itr_l->first)
                {
                    itr_p->second=itr_l->second;
                    cout<<"You reached a ladder yay! Youre new position is: "<<itr_p->second;
                    break;
                }
            }
            cout<<"\nYour final position after this round is: "<<itr_p->second<<"\n press any key to proceed\n";
            cin>>dummy;
        }
        return 0;
    }
    public:
    game()
    {  
        //clrscr();
        int noofplayers;
        cout<<"\n\n\n\n\n\nEnter number of players\n";
        cin>>noofplayers;
        if(noofplayers==0) ;        //if you dont wanna play the code wont run :0
        else {
        for(int i=1;i<=noofplayers;++i) player.push_back(make_pair(i,0));cout<<"\n\nStarting match with the board: ";printboard();
        match();}
    }
};
int main()                      //pretty much has nothing in it, just calls game's constructor
{
    srand(59732893);            //tried doing seed value by time, forgot how to, worked around it
    int in=1;
    while(in==1)
    {
        game G;
        cout<<"\nThank you for playing snakes and ladders\n\nTo start a new game enter 1\nTo exit press any other key\n\n\nGame developed by Aditya Subramanian\n\n\n\n";
        cin>>in;
    }
    return 0;
}