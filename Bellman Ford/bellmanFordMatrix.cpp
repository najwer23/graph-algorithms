// Brak petli wokol wlasnego wierzcholka, wykluczenie od razu
// Brak podwojnych petli w grafie, wykluczenie od razu

// BEZ podzialu na funkcje, zeby mozna bylo latwiej korzystac czesci programu w innych programach

#include <iostream>
#include <ctime>
#include <vector>
#define MAX 999999

using namespace std;

void show(int a, int b, int c, int d)
{
    cout.width(4);
    cout<<a<<". Start:";
    cout.width(4);
    cout<<b;
    cout<<", Stop: ";
    cout.width(4);
    cout<<c;
    cout<<", Waga: ";
    cout.width(3);
    cout<<d<<endl;
}

int main()
{
    srand(time(NULL));

    // densityGraph = 1 Graf pelny w 100%
    // densityGraph = 0.75 Graf pelny w 75%
    // densityGrah = 0.5 Graf pelny w 50%

    //IN
    double densityGraph=0.75;
    int sizeMatrix=5;
    int startVertex=0;

    //OUT
    //zmienic krawedzie, moga byc dwukierunkowe?
    int sizeLinks=((sizeMatrix*(sizeMatrix-1))/*/2*/)*densityGraph;

    cout<<"IN"<<endl;
    cout<<"Liczba wierzcholkow: "<<sizeMatrix<<endl;
    cout<<"Liczba krawedzi: "<<sizeLinks<<endl;
    cout<<"Gestosc: "<<densityGraph*100<<"%"<<endl<<endl;

    cout<<"OUT"<<endl;

    //MACIERZ WIERZCHOLKOW
    int **matrix=new int*[sizeMatrix];
    for (int i = 0; i < sizeMatrix; i++)
        matrix[i] = new int [sizeMatrix];

    // WYPELNIENIE ZERAMI MACIERZ i FALSE TABLICY ODWIEDZIN
    for(int i=0; i<sizeMatrix; i++)
    {
        for(int j=0; j<sizeMatrix; j++)
        {
            matrix[i][j]=0;
        }
    }

    // WYPELNIENIE WARTOSCIAMI MACIERZY
    int stop=sizeLinks;
    int s, w, f, symbol;

    while(stop>0)
    {
        s=rand()%sizeMatrix;
        symbol=(rand()%(2*sizeMatrix));
        // mocno dziwny algorytm do losowania liczb, do przemyslenia
        if(symbol==0)
            w=((rand()%5)+1)*-1;
        else
            w=((rand()%20)+6);

        f=rand()%sizeMatrix;

        if(matrix[s][f]==0 && f!=s)
        {
            matrix[s][f]=w;
            //matrix[f][s]=w;
            stop--;
        }
    }

    //ZAMIAST WHILE z rand monzna uzyc tej macierzy testowej
    /*
    matrix[0][1]=-1;
    matrix[0][2]=4;
    matrix[1][2]=3;
    matrix[1][3]=2;
    matrix[1][4]=2;
    matrix[3][2]=5;
    matrix[3][1]=1;
    matrix[4][3]=-3;
    */

    // WYPISZ MACIERZ, adjacency matrix
    cout<<"Macierz:"<<endl;
    for(int i=0; i<sizeMatrix; i++)
    {
        for(int j=0; j<sizeMatrix; j++)
        {
            cout.width(3);
            cout<<matrix[i][j]<<" ";
        }

        cout<<endl;
    }

    // WYPISZ KRAWEDZIE GRAFU
    cout<<endl<<"Krawedzie Grafu: "<<endl;
    for(int i=0, k=1; i<sizeMatrix; i++)
    {
        for(int j=0; j<sizeMatrix; j++)
        {
            if(matrix[i][j]!=0/*&&i<=j*/)
            {
                show(k, i, j, matrix[i][j]);
                k++;
            }
        }
    }

    // BELLMAN FORD MATRIX

    int distance[sizeMatrix];
    int previous[sizeMatrix];

    // INICJALIAZACJA
    for (int i=0; i<sizeMatrix; i++)
    {
        distance[i]=MAX;
        previous[i]=-1;
    }

    distance[startVertex] = 0;
    int END=sizeMatrix;

    // RELAKSACJA
    while (END>0)
    {
        for(int i=0, k=1; i<sizeMatrix; i++)
        {
            for(int j=0; j<sizeMatrix; j++)
            {
                if(matrix[i][j]!=0)
                {
                    s=i;
                    f=j;
                    w=matrix[i][j];
                    if (distance[s]!=MAX && distance[s]+w<distance[f])
                    {
                        distance[f]=distance[s]+w;
                        previous[f]=s;
                    }
                    k++;
                }
            }
        }
        END--;
    }

    // RELAKSACJA DLA UJEMNYCH WAG
    for(int i=0, k=1; i<sizeMatrix; i++)
    {
        for(int j=0; j<sizeMatrix; j++)
        {
            if(matrix[i][j]!=0)
            {
                s=i;
                f=j;
                w=matrix[i][j];
                if (distance[s]!=MAX && distance[s]+w<distance[f])
                {
                    cout<<endl<< "Ujemny cykl!!"<<endl;
                    return 0;
                }
                k++;
            }
        }
    }

    int x;
    vector < int > invertedSolution;
    cout<<endl;
    for(int i=0; i<sizeMatrix; i++)
        if(i!=startVertex)
        {
            cout<<startVertex<<" --> "<<i<<endl;
            cout<<"Dystans/koszt: "<<distance[i];

            invertedSolution.push_back(i);
            x=i;
            do
            {
                x=previous[x];
                invertedSolution.push_back(x);
            }
            while(x!=startVertex);

            cout<<endl<<"Sciezka: ";
            for(int i=invertedSolution.size()-1; i>=0; i--)
                cout<<invertedSolution[i]<<" ";

            invertedSolution.clear();
            cout<<endl<<endl;
        }
    return 0;
}

