// Brak petli wokol wlasnego wierzcholka, wykluczenie od razu
// Brak podwojnych petli w grafie, wykluczenie od razu
// Fajny opis: https://www.youtube.com/watch?v=5XkK88VEILk&ab_channel=YusufShakeel

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
    int *visited=new int [sizeMatrix];
    int sizeLinks=((sizeMatrix*(sizeMatrix-1))/2)*densityGraph;

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
        visited[i]=0;
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

    // KRUSKAL

    cout<<endl;
    cout<<"MST:"<<endl;
    int END;
    int cost=0;
    int minWeight;
    int A, B, a, b;
    while(END<sizeMatrix-1)
    {
        minWeight=MAX;
        //ZNAJDZ MINIMUM
        for(int i=0; i<sizeMatrix; i++)
            for(int j=0; j<i; j++)
            {
                if(matrix[i][j]<minWeight&&matrix[i][j]>0)
                {
                    minWeight=matrix[i][j];
                    A=a=i;
                    B=b=j;
                }

            }
        //SPRAWDZ CZY ROBI CYKLE
        if(visited[a]!=0)
            a=visited[a];

        if(visited[b]!=0)
            b=visited[b];

        if(a!=b)
        {
            END++;
            cost+=minWeight;
            show(END, B, A, minWeight);
            visited[b]=a;
        }
        matrix[A][B]=matrix[B][A]=MAX;
    }
    cout<<endl<<"Koszt/dystans: "<<cost<<endl;
    return 0;
}
