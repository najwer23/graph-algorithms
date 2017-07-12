// Brak petli wokol wlasnego wierzcholka, wykluczenie od razu
// dwukierunkowosc

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
    cout<<", Waga: "<<d<<endl;
}

int main()
{
    srand(time(NULL));

    // densityGraph = 1 Graf pelny w 100%
    // densityGraph = 0.75 Graf pelny w 75%
    // densityGrah = 0.5 Graf pelny w 50%

    //IN
    double densityGraph=0.75;
    int sizeMatrix=1000;
    int startVertex=0;

    //OUT
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
    int s, w, f;

    while(stop>0)
    {
        s=rand()%sizeMatrix;
        w=(rand()%9)+1;
        f=rand()%sizeMatrix;

        if(matrix[s][f]==0 && f!=s)
        {
            matrix[s][f]=w;
            //matrix[f][s]=w;
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
            if(matrix[i][j]!=0/*&&i<=j*/)
            {
                show(k, i, j, matrix[i][j]);
                k++;
            }
        }
    }

    // DIJKSTRA
    int **costDijkstra=new int*[sizeMatrix];
    for (int i = 0; i < sizeMatrix; i++)
        costDijkstra[i] = new int [sizeMatrix];

    for(int i=0; i<sizeMatrix; i++)
        for(int j=0; j<sizeMatrix; j++)
            costDijkstra[i][j]=0;

    int distance[sizeMatrix];
    int prev[sizeMatrix];
    int visited[sizeMatrix];
    int END;
    int midDistance;
    int nextVertex;
    int x;

    // INICJALIZACJA
    for(int i=0; i<sizeMatrix; i++)
        for(int j=0; j<sizeMatrix; j++)
            if(matrix[i][j]==0)
                costDijkstra[i][j]=MAX;
            else
                costDijkstra[i][j]=matrix[i][j];

    for(int i=0; i<sizeMatrix; i++)
    {
        distance[i]=costDijkstra[startVertex][i];
        prev[i]=startVertex;
        visited[i]=0;
    }

    // INICJALIZACJA DLA WEKTORA USTALONEGO Z GORY
    distance[startVertex]=0;
    visited[startVertex]=1;
    END=0;

    //ALGORYTM
    while(END<sizeMatrix)
    {
        midDistance=MAX;

        for(int i=0; i<sizeMatrix; i++)
            if(distance[i]<midDistance&&!visited[i])
            {
                midDistance=distance[i];
                nextVertex=i;
            }

        visited[nextVertex]=1;
        for(int i=0; i<sizeMatrix; i++)
            if(!visited[i])
                if(midDistance+costDijkstra[nextVertex][i]<distance[i])
                {
                    distance[i]=midDistance+costDijkstra[nextVertex][i];
                    prev[i]=nextVertex;
                }
        END++;
    }

    // PROPAGACJA ROZWIAZANIA

    //vector do odwrocenia kolejnosci
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
                x=prev[x];
                invertedSolution.push_back(x);
            }
            while(x!=startVertex);

            cout<<endl<<"Sciezka: ";
            for(int i=invertedSolution.size()-1; i>=0; i--)
                cout<<invertedSolution[i]<<" ";

            invertedSolution.clear();
            cout<<endl<<endl;
        }

    delete [] matrix;
    return 0;
}

// praise the sun
// z malymi problemami i telefonami do przyjaciela, ale mimo wszystko moze komus sie przyda

// References
//http://www.geeksforgeeks.org/printing-paths-dijkstras-shortest-path-algorithm/
//http://www.programming-techniques.com/2012/01/implementation-of-dijkstras-shortest.html

