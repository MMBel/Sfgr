#include <iostream>
#include "Sfgr.h"

using namespace std;

int main()
{
    unsigned Amplitude = 25;

    Sfgr graph;
    graph.cfg.ScrshotDir="a:\\CPP\\Sfgr";
    graph.cfg.Title=L"Пример синусоидного графика";
    graph.cfg.WinHeightPercent=50;
    graph.cfg.WinWidthPercent=50;
    graph.cfg.LMargin = 80;
    graph.cfg.RMargin = 30;
    graph.cfg.TMargin = 60;
    graph.cfg.BMargin = 60;
    graph.Start();
    int GraphSize = graph.cfg.XDimMax-graph.cfg.XDimMin;

    Sfgr::Frame* z;
    Sfgr::Frame* d = graph.NewFrame(GraphSize);
    Sfgr::Frame* f = graph.NewFrame(GraphSize);


    graph.ShowFrame(d);
    graph.ShowFrame(f);

    graph.AddPoint(f, 20, -5, 3, sf::Color::Red, "Point description", 10);
    graph.AddVLine(f, 1500, 1, sf::Color::Red, "1500", 12);
    graph.AddHLine(f, -30, 1, sf::Color::Red, "center", 12);


    for(int a=3000; a>1; a--)
    {
        z = graph.NewFrame(GraphSize);
        graph.AddHText(z, graph.cfg.Vidmode.width, 20, "A=" + std::to_string(a), 16, sf::Color::Blue, sf::Text::Regular, Sfgr::TextPos::LEFTER);

        double SineLength = 1.d*200000/a;

        d->ArrayGraph.clear();
        f->ArrayGraph.clear();

        for (int i=0; i<GraphSize; i++)
        {
            Sfgr::point pnt1;
            Sfgr::point pnt2;

            float SineVal = 1.f*Amplitude*sin(i*2.f*M_PI/SineLength);

            pnt1.XValue = 10+i;
            pnt2.XValue = pnt1.XValue;

            pnt1.YValue=-30+SineVal;
            pnt2.YValue=-30-SineVal;

            d->ArrayGraph.push_back(pnt1);
            f->ArrayGraph.push_back(pnt2);

        }
        graph.ShowFrame(z);
        sf::sleep(sf::milliseconds(5));
        graph.DeleteFrame(z);

    }
    cout << "Done" << endl;
    cin.ignore();
    graph.DeleteFrame(f);
    graph.DeleteFrame(d);
    graph.Stop();
    return 0;
}
