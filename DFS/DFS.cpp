#include <iostream>
#include <ctime>

using namespace std;

class Link
{
public:
    int start;
    int finish;
    int weight;
};

//REKURENCJA PRZESZUKIWANIE W GLAB
void DFS(int w, bool *visited, int **matrix, int sizeMatrix)
{
    visited[w] = true;
    for(int i = 0; i < sizeMatrix; i++)
        if((matrix[w][i] >= 1) && !visited[i])
            DFS(i,visited,matrix,sizeMatrix);
}

int main()
{
    // IN
    srand(time(NULL));
    double densityGraph=1;
    int sizeMatrix=8;

    // KRAWEDZIE
    int sizeLinks=((sizeMatrix*(sizeMatrix-1))/2)*densityGraph;
    cout<<"Liczba wierzcholkow: "<<sizeMatrix<<endl;
    cout<<"Liczba krawedzi: "<<sizeLinks<<endl<<endl;

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
            if(f>=s)
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

    // DFS
    cout<<endl;
    DFS(0,visited,matrix,sizeMatrix);

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
        cout<<"DFS -> Graf jest spojny"<<endl;
    else
        cout<<"DFS -> Graf nie jest spojny"<<endl;

    // WYPISZ KRAWEDZIE GRAFU
    cout<<endl<<"Graf: "<<endl;
    for(int i=0; i<sizeLinks; i++)
    {
        cout.width(2);
        cout<<i+1<<". S:"<<links[i].start<<" W:"<<links[i].weight<<" F:"<<links[i].finish<<endl;
    }

}
