#ifndef SFGR_H
#define SFGR_H
#include <string>
#include <vector>
#include <iostream>
#include <windows.h>
#include <thread>
#include <math.h>
#include <map>
#include "SFML/Graphics.hpp"


/*
 Mih.M.Belovolov, 2021
 Класс для отображения графиков.
 По оси Х используется логарифмическая шкала,
 По оси Y используется линейная (предполагается что логарифмическими будут ее значения).
 Использование класса:
    1. Подключить библиотеку SFML https://www.sfml-dev.org/tutorials/2.5/start-cb.php
        нужные компоненты: sfml-graphics, sfml-window, sfml-system
    2. Создать экземпляр класса Sfgr                                Sfgr graph;
        произвести необходимые настройки конфига                    graph.cfg.Title=L"Заголовок"; graph.cfg.XDimMax=15000; и т.д.
    3. Произвести дальнейшие автонастройки и запустить оконный тред graph.Start();
    4. Создать экземпляр слоя для рисования на области графика      Layer* f = graph.NewLayer();
        Важно: на одном слое может быть не более 1 графика
        Рисовать линии или графики                                  f->AddHLine(-30, 2, sf::Color::Green);
                                                                    gpoint GraphArray[1000];
                                                                    for (int i=0; i<1000; ++i) { заполняем массив данными XValue и YValue )
                                                                    f->AddPlotArray(GraphArray, 1000, sf::Color::Blue);
        Важно: рисование графика начинается с минимального значения по Х!
    5. Опубликовать созданный слой на отображаемом окне             graph.FinLayer(f);
    6. Удалить слой перед публикацией следующего                    graph.DelLayer(f);
 Выход из оконного треда осуществляется закрытием окна или нажатием клавиши q
 Снятие скриншота по клавише PageDown (если задан каталог куда их сохранять => graph.cfg.ScrshotDir)*/

struct gpoint{ float    XValue =  0,
                        YValue = -60;
};

enum class TextPos { LEFTER, RIGHTER, UPPER, UNDER, CENTER };
struct Sfgr_Configuration{
    float           XDimMin = 10,
                    XDimMax = 20000,
                    YDimMin = -60,
                    YDimMax = 0;
    sf::VideoMode   Vidmode;
    sf::Font        Font;
    sf::Color       BGCol, TitleCol, AxisCol, GridCol;
    unsigned        TitleFontSize, AxisTitleFontSize, AxisMarksFontSize, AxisBold, GridBold;
    unsigned        LMargin, RMargin, TMargin, BMargin;
    std::string     WindowTitle, ScrshotDir;
    sf::String      Title, Xtitle, YTitle;
    std::vector<float> XGrid, YGrid;
    std::map<float, sf::String> XMarks, YMarks;
    void Init();
    sf::Font        getFontNamed(std::string FontName);
    };

    struct Layer {
    size_t              LayerNumber;
    Sfgr_Configuration  c;
    std::vector<sf::Drawable*> Objects;
    void    AddPoint(float XValue, float YValue, unsigned Radius, sf::Color Col, sf::String txt, unsigned MarkCharSize);
    void    AddPlotArray(const gpoint* gArray, size_t gArrayCount, sf::Color Col);
    void    AddText(sf::String text, unsigned FontSize, sf::Color Col, sf::Text::Style style, TextPos Pos, float Xpos, float Ypos);
    void    AddText270(sf::String text, unsigned FontSize, sf::Color Col, sf::Text::Style style, float Xpos, float Ypos);
    void    AddVLine(float XValue, unsigned Bold, sf::Color Col);
    void    AddVLine(float XValue, unsigned Bold, sf::Color Col, sf::String text, unsigned MarkCharSize);
    void    AddHLine(float YValue, unsigned Bold, sf::Color Col);
    void    AddHLine(float YValue, unsigned Bold, sf::Color Col, sf::String text, unsigned MarkCharSize);
    void    AddYMark(float YValue, unsigned Bold, sf::Color Col);
    void    AddXMark(float XValue, unsigned Bold, sf::Color Col);
    float   YValToCoord(float YValue);
    float   XValToCoord(float XValue);
    void    Draw(sf::RenderTarget &tgt);
    void    ClearObjects();
    Layer();
    private:
    sf::Vector2f        PrevPoint;
    };

class Sfgr{
    size_t              LayerCounter = 0;
    sf::RenderWindow    Window;
    std::vector<Layer*> Layers;
    bool                Layers_busy = false;
    std::thread*        t;
    void                winloop();
public:
    Sfgr();
    Sfgr_Configuration  cfg;
    void    Start();
    Layer*  NewLayer();
    void    FinLayer(Layer* LayerPtr);
    void    DelLayer(Layer* LayerPtr);
    ~Sfgr();
};
#endif // SFGR_H
