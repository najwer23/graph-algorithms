

#include <iostream>
#include <ctime>
#include <queue>

using namespace std;

class Link
{
public:
    int start;
    int finish;
    int weight;
};

//REKURENCJA PRZESZUKIWANIE W GLAB
void BFS(int w, bool *visited, int **matrix, int sizeMatrix)
{
    queue < int > neighbors;
    neighbors.push(w);

    int mainW;
    visited[w] = true;

    while(!neighbors.empty())
    {
        mainW = neighbors.front();
        neighbors.pop();

        for(int i = 0; i < sizeMatrix; i++)
            if((matrix[mainW][i]>= 1) && !visited[i])
            {
                visited[i] = true;
                neighbors.push(i);
            }
    }
}

int main()
{
    srand(time(NULL));
    // IN dla grafów 2 kierunkowych, np 0->1, 1->0
    // brak petli wokol wlasnego wierzcholka
    // densityGraph = 2 Graf pelny w 100%
    // densityGraph = 1.5 Graf pelny w 75%
    // densityGraph = 1 Graf pelny w 50%

    double densityGraph=2;
    int sizeMatrix=5;

    // KRAWEDZIE
    int sizeLinks=((sizeMatrix*(sizeMatrix-1))/2)*densityGraph;
    cout<<"Liczba wierzcholkow: "<<sizeMatrix<<endl;
    cout<<"Liczba krawedzi: "<<sizeLinks<<endl;
    cout<<"Gestosc: "<<densityGraph<<endl<<endl;

    // MACIERZ SASIEDZTWA
    int **matrix=new int*[sizeMatrix];
    for (int i = 0; i < sizeMatrix; i++)
        matrix[i] = new int [sizeMatrix];

    // POLACZENIA
    Link *links;
    links=new Link [sizeLinks];

    //ODWIEDZENIA
    bool * visited;
    visited = new bool[sizeMatrix];

    // WYPELNIENIE ZERAMI MACIERZ i FALSE TABLICY ODWIEDZIN
    for(int i=0; i<sizeMatrix; i++)
    {
        visited[i] = false;
        for(int j=0; j<sizeMatrix; j++)
            matrix[i][j]=0;
    }

    // WYPELNIENIE WARTOSCIAMI MACIERZY
    int stop=sizeLinks;
    int s, w, f;
    int iteratorLinks=0;
    while(stop>0)
    {
        s=rand()%sizeMatrix;
        w=(rand()%9)+1;
        f=rand()%sizeMatrix;

        if(matrix[s][f]==0 && f!=s)
        {
            //if(f>=s) //macierz górna trojkatna
            {
                //WCZYTANIE KRAWEDZI DO KLASY
                links[iteratorLinks].start=s;
                links[iteratorLinks].weight=w;
                links[iteratorLinks].finish=f;

                iteratorLinks++;
                matrix[s][f]=w;
                stop--;
            }

        }
    }


    // WYPISZ MACIERZ
    for(int i=0; i<sizeMatrix; i++)
    {
        for(int j=0; j<sizeMatrix; j++)
            cout<<matrix[i][j]<<" ";
        cout<<endl;
    }

    // BFS
    cout<<endl;
    BFS(0,visited,matrix,sizeMatrix);

    // SPRAWDZ CZY GRAF JEST SPOJNY
    int counter=0;
    for(int i=0; i<sizeMatrix; i++)
    {
        if(visited[i]==true)
        {
            counter++;
        }
    }

    if(counter==sizeMatrix)
        cout<<"BFS -> Graf jest spojny"<<endl;
    else
        cout<<"BFS -> Graf nie jest spojny"<<endl;

    // WYPISZ KRAWEDZIE GRAFU
    cout<<endl<<"Graf: "<<endl;
    for(int i=0; i<sizeLinks; i++)
    {
        cout.width(2);
        cout<<i+1<<". S:"<<links[i].start<<" W:"<<links[i].weight<<" F:"<<links[i].finish<<endl;
    }

}
