// Prim's Algorithm, adjacency matrix
// IN dla grafów 2 kierunkowych, np 0->1, 1->0, program mozna przerobic dla grafow 1-kierunkowych
// Brak petli wokol wlasnego wierzcholka, wykluczylem od razu
// Fajny opis: https://www.youtube.com/watch?v=Pn874kEc3IA&ab_channel=YusufShakeel

//WADA - program moglby byc podzielony na funkcje i klasy

#include <iostream>
#include <ctime>
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
    cout<<", Waga: "<<d<<endl;
}

int main()
{
    srand(time(NULL));

    // densityGraph = 1 Graf pelny w 100%
    // densityGraph = 0.75 Graf pelny w 75%
    // densityGraph = 0.5 Graf pelny w 50%

    //IN
    double densityGraph=1;
    int sizeMatrix=5;
    int startVertex=0;

    //OUT
    int sizeLinks=((sizeMatrix*(sizeMatrix-1))/2)*densityGraph;
    int minWeight[sizeMatrix];
    bool *visited=new bool[sizeMatrix];

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
        minWeight[i]=MAX;
        visited[i]=false;
        for(int j=0; j<sizeMatrix; j++)
        {
            matrix[i][j]=0;
        }
    }

    // WYPELNIENIE WARTOSCIAMI MACIERZY
    int stop=sizeLinks;
    int s, w, f;

    while(stop>0)
    {
        s=rand()%sizeMatrix;
        w=(rand()%9)+1;
        f=rand()%sizeMatrix;

        if(matrix[s][f]==0 && f!=s)
        {
            matrix[s][f]=w;
            matrix[f][s]=w;
            stop--;
        }
    }

    // WYPISZ MACIERZ, adjacency matrix
    cout<<"Macierz:"<<endl;
    for(int i=0; i<sizeMatrix; i++)
    {
        for(int j=0; j<sizeMatrix; j++)
            cout<<matrix[i][j]<<" ";
        cout<<endl;
    }

    // WYPISZ KRAWEDZIE GRAFU
    cout<<endl<<"Krawedzie Grafu: "<<endl;
    for(int i=0, k=1; i<sizeMatrix; i++)
    {
        for(int j=0; j<sizeMatrix; j++)
        {
            if(matrix[i][j]!=0&&i<=j)
            {
                show(k, i, j, matrix[i][j]);
                k++;
            }
        }
    }

    // PRIM
    cout<<endl;
    int row=startVertex;
    int column=0;
    minWeight[row]=0;
    visited[row]=true;

    int End=1;
    int cost;

    int col[sizeMatrix];

    cout<<"MST:"<<endl;
    while(End!=sizeMatrix)
    {
        for(int i=0; i<sizeMatrix; i++)
        {
            if(matrix[row][i]!=0)
            {
                if(visited[i]!=true)
                {
                    if(minWeight[i]>matrix[row][i])
                    {
                        minWeight[i]=matrix[row][i];
                        col[i]=row;
                    }
                }
            }
        }

        cost=MAX;
        for(int i=0; i<sizeMatrix; i++)
        {
            if(visited[i]==false)
            {
                if(minWeight[i]<cost)
                {
                    cost=minWeight[i];
                    column=col[i];
                    row=i;
                }
            }
        }

        End++;
        visited[row]=true;

        if(row<column)
            show(End-1, row, column, cost);
        else
            show(End-1, column, row, cost);
    }

    cost=0;
    for(int i=0; i<sizeMatrix; i++)
        cost+=minWeight[i];

    cout<<endl<<"Koszt/dystans: "<<cost<<endl;
    return 0;
}
