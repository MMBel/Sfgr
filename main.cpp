#include <iostream>
#include "sfgr.h"
using namespace std;

int main()
{

    unsigned SineFreq = 5000;
    double pre2PI = 2.d * M_PI;
    double SineLength = 1.d*200000/SineFreq;
    unsigned Amplitude=25;

    Sfgr g;
    g.cfg.ScrshotDir="a:\\CPP\\Sfgr";
    g.cfg.Title=L"Пример графика синусоиды в логарифмическом масштабе";
    g.Start();
    Layer* n = g.NewLayer();
    int ArraySize=19900;
    gpoint gArray[ArraySize];
    for(int i=0; i<ArraySize; ++i)
    {
        gArray[i].XValue=float(i+10);
        gArray[i].YValue=float(-30+Amplitude*sin(i*pre2PI/SineLength));
    }
    n->AddPlotArray(gArray, ArraySize, sf::Color::Blue);
    g.FinLayer(n);
    Layer* f = g.NewLayer();
    f->AddPoint(20, -40, 5, sf::Color::Red, L"Тчк", 16);
    f->AddVLine(4000, 1, sf::Color::Red, L"4КГц", 14);
    f->AddHLine(-30, 1, sf::Color::Red, L"метка", 14);
    f->AddText(L"Sine frequency = 5000", 16, sf::Color::Blue, sf::Text::Regular, TextPos::LEFTER, g.cfg.Vidmode.width, 20);
    g.FinLayer(f);
    cin.ignore();
    g.DelLayer(n);
    cin.ignore();
    g.Stop();
    return 0;
}
