#include <iostream>
#include "Sfgr.h"

using namespace std;

int main()
{
    double pre2PI = 2.d*M_PI;
    unsigned Amplitude = 25;


    Sfgr graph;
    graph.cfg.ScrshotDir="a:\\CPP\\Sfgr";
    graph.cfg.Title=L"Пример синусоидного графика";
    graph.Start();
    int GraphSize = graph.cfg.XDimMax-graph.cfg.XDimMin;

    Sfgr::Frame* d = graph.NewFrame(GraphSize);
    Sfgr::Frame* f = graph.NewFrame(GraphSize);

    graph.ShowFrame(d);
    graph.ShowFrame(f);

    d->GraphColor=sf::Color::Blue;
    f->GraphColor=sf::Color::Magenta;

    graph.AddPoint(f, 20, -5, 3, sf::Color::Red, "Point description", 10);
    graph.AddVLine(f, 1500, 1, sf::Color::Red, "1500", 12);
    graph.AddHLine(f, -30, 1, sf::Color::Red, "center", 12);
    graph.AddHText(f, graph.cfg.Vidmode.width, 20, "GS=" + std::to_string(GraphSize), 16, sf::Color::Blue, sf::Text::Regular, Sfgr::TextPos::LEFTER);


    for(int a=500; a>5; a--)
    {
        double SineLength = 1.d*200000/a;

        graph.HideFrame(f);
        graph.HideFrame(d);

        d->ArrayGraph.clear();
        f->ArrayGraph.clear();

        for (int i=0; i<GraphSize; i++)
        {
            Sfgr::point pnt1;
            Sfgr::point pnt2;
            pnt1.XValue=pnt2.XValue=10+i;


            pnt1.YValue=float(-30+Amplitude*sin(i*pre2PI/SineLength));
            d->ArrayGraph.push_back(pnt1);

            pnt2.YValue=float(-30-Amplitude*sin(i*pre2PI/SineLength));
            f->ArrayGraph.push_back(pnt2);
        }

        graph.ShowFrame(d);
        graph.ShowFrame(f);

        sf::sleep(sf::milliseconds(50));
    }
    cout << "Done" << endl;
    cin.ignore();
    graph.DeleteFrame(f);
    graph.DeleteFrame(d);
    graph.Stop();
    return 0;
}
