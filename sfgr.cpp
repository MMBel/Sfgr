#include "sfgr.h"

void            Sfgr_Configuration::Init(){
    using namespace std;
    WindowTitle = "Graphic";
    Title = L"Амплитудно-частотная характеристика";
    YTitle = L"Амплитуда, dBa";
    Xtitle = L"Частота, Гц";
    Vidmode = sf::VideoMode::getDesktopMode();
//    Vidmode.width-=Vidmode.width*0.05;
//    Vidmode.height-=Vidmode.height*0.15;
    Font = getFontNamed("tahoma");
    ScrshotDir = "";
    if(Font.getInfo().family=="") cout << "SFGR: Font not loaded!" << endl;
    BGCol=sf::Color(235,235,235);
    TitleCol=sf::Color::Black;
    AxisCol=sf::Color::Black;
    GridCol=sf::Color(200,200,200,128);
    TitleFontSize=22;
    AxisTitleFontSize=18;
    AxisMarksFontSize=16;
    AxisBold=3;
    GridBold=3;
    LMargin=RMargin=Vidmode.width*0.05;
    TMargin=BMargin=Vidmode.height*0.1;
    XGrid.clear();
    for(int i=20; i<100; i+=10) XGrid.push_back(i);
    for(int i=100; i<1000; i+=100) XGrid.push_back(i);
    for(int i=1000; i<=10000; i+=1000) XGrid.push_back(i);
    XGrid.push_back(20000.f);
    YGrid.clear();
    for(int i=-55; i<=0; i+=5) YGrid.push_back(i);
    YMarks.insert(make_pair(-55.f, L"-55"));
    YMarks.insert(make_pair(-50.f, L"-50"));
    YMarks.insert(make_pair(-45.f, L"-45"));
    YMarks.insert(make_pair(-40.f, L"-40"));
    YMarks.insert(make_pair(-35.f, L"-35"));
    YMarks.insert(make_pair(-30.f, L"-30"));
    YMarks.insert(make_pair(-25.f, L"-25"));
    YMarks.insert(make_pair(-20.f, L"-20"));
    YMarks.insert(make_pair(-15.f, L"-15"));
    YMarks.insert(make_pair(-10.f, L"-10"));
    YMarks.insert(make_pair(-5.f,  L"-5 "));
    YMarks.insert(make_pair(0,     L"0 "));
    XMarks.insert(make_pair(10.f,  L"10 Гц"));
    XMarks.insert(make_pair(100.f, L"100 Гц"));
    XMarks.insert(make_pair(1000.f, L"1 КГц"));
    XMarks.insert(make_pair(10000.f, L"10 КГц"));
    XMarks.insert(make_pair(20000.f, L"20 КГц"));
}
sf::Font        Sfgr_Configuration::getFontNamed(std::string FontName){
    TCHAR wdir[MAX_PATH];
    GetWindowsDirectory(wdir, MAX_PATH);
    std::string fontpath;
    #ifndef UNICODE
        fontpath=wdir;
    #else
        wstring wwdir = fontpath;
        wdir=string(wwdir.begin(), wwdir.end());
    #endif // UNICODE
    fontpath+="\\Fonts\\";
    fontpath+=FontName;
    fontpath+=".ttf";
    sf::Font fnt;
    fnt.loadFromFile(fontpath);
    return fnt;
}
        Layer::Layer(){ PrevPoint.x=0; }
void    Layer::AddPoint(float XValue, float YValue, unsigned Radius, sf::Color Col, sf::String txt, unsigned MarkCharSize){
    if(XValue==0 || YValue==0) return;
    sf::Vector2f Position;
    Position.x = this->XValToCoord(XValue);
    Position.y = this->YValToCoord(YValue);
    sf::CircleShape* s = new sf::CircleShape;
    s->setRadius(float(Radius));
    s->setFillColor(Col);
    sf::FloatRect r = s->getLocalBounds();
    s->setOrigin(r.width/2, r.height/2);
    s->setPosition(Position);
    Objects.push_back(s);
    if(txt=="") return;
    AddText(txt, MarkCharSize, sf::Color::Black, sf::Text::Style::Regular, TextPos::RIGHTER, Position.x, Position.y);
    }
void    Layer::AddPlotArray(const gpoint* gArray, size_t gArrayCount, sf::Color Col){
    sf::VertexArray* line = new sf::VertexArray(sf::LineStrip, gArrayCount);
    sf::Vector2f ppos;
    for(size_t i=0; i<gArrayCount; ++i)
    {
        ppos.x = this->XValToCoord(gArray[i].XValue);
        ppos.y = this->YValToCoord(gArray[i].YValue);
        (*line)[i].position = ppos;
        (*line)[i].color = Col;
    }
    Objects.push_back(line);
}
void    Layer::AddText(sf::String text, unsigned FontSize, sf::Color Col, sf::Text::Style style, TextPos Pos, float Xpos, float Ypos){
    if(Xpos==0 || Ypos==0 ) return;
    sf::Vector2f Position = sf::Vector2f(Xpos, Ypos);
    sf::Text* txt = new sf::Text;
    txt->setFont(this->c.Font);
    txt->setFillColor(Col);
    txt->setCharacterSize(FontSize);
    txt->setStyle(style);
    txt->setString("X");
    sf::FloatRect r = txt->getLocalBounds();
    Position.x -= r.width/2;
    Position.y -= r.height/2;
    txt->setString(text);
    r = txt->getLocalBounds();
    switch (Pos)
    {
    case (TextPos::CENTER):  { txt->setOrigin(r.width/2, r.height/2); } break;
    case (TextPos::LEFTER):  { txt->setOrigin(r.width+r.width/2, r.top); } break;
    case (TextPos::RIGHTER): { text="  "+text; txt->setString(text); r=txt->getLocalBounds(); txt->setOrigin(r.left, r.top); } break;
    case (TextPos::UPPER):   { Position.y -= this->c.Font.getLineSpacing(FontSize); txt->setOrigin(r.left, r.top); } break;
    case (TextPos::UNDER):   { txt->setOrigin(r.width/2, r.top); Position.y +=this->c.Font.getLineSpacing(FontSize); } break;
    }
    txt->setPosition(Position);
    Objects.push_back(txt);
}
void    Layer::AddText270(sf::String text, unsigned FontSize, sf::Color Col, sf::Text::Style style, float Xpos, float Ypos){
    if(Xpos==0 || Ypos==0 ) return;
    sf::Text* txt = new sf::Text;
    txt->setFont(this->c.Font);
    txt->setCharacterSize(FontSize);
    txt->setString(text);
    txt->setFillColor(Col);
    txt->setStyle(style);
    sf::FloatRect r = txt->getLocalBounds();
    txt->setOrigin(r.width/2, r.height/2);
    txt->setRotation(270.f);
    txt->setPosition(sf::Vector2f(Xpos, Ypos));
    Objects.push_back(txt);
}
void    Layer::AddVLine(float XValue, unsigned Bold, sf::Color Col){
    static const float VLineLength = float(this->c.Vidmode.height - this->c.TMargin - this->c.BMargin);
    static const float VLinePos = float(this->c.TMargin);
    sf::RectangleShape* s = new sf::RectangleShape(sf::Vector2f(VLineLength, float(Bold)));
    s->setFillColor(Col);
    sf::FloatRect r = s->getLocalBounds();
    s->setOrigin(0, r.height/2);
    s->setRotation(90.f);
    s->setPosition(sf::Vector2f(this->XValToCoord(XValue), VLinePos));
    Objects.push_back(s);
}
void    Layer::AddVLine(float XValue, unsigned Bold, sf::Color Col, sf::String text, unsigned MarkCharSize){
    sf::Text t;
    t.setFont(this->c.Font);
    t.setCharacterSize(MarkCharSize);
    t.setString(text);
    sf::FloatRect rt = t.getLocalBounds();
    float Xcoord = this->XValToCoord(XValue);
    float VLineLength = float(this->c.Vidmode.height - this->c.TMargin - this->c.BMargin - rt.height*2);
    float VLinePos = float(VLineLength + this->c.TMargin);
    sf::RectangleShape* s = new sf::RectangleShape(sf::Vector2f(VLineLength, float(Bold)));
    s->setFillColor(Col);
    sf::FloatRect r = s->getLocalBounds();
    s->setOrigin(0, r.height/2);
    s->setRotation(270.f);
    s->setPosition(sf::Vector2f(Xcoord, VLinePos));
    Objects.push_back(s);
    AddText(text, MarkCharSize, this->c.AxisCol, sf::Text::Regular, TextPos::CENTER, Xcoord, VLinePos + rt.height);
}
void    Layer::AddHLine(float YValue, unsigned Bold, sf::Color Col){
    float Ypos=this->YValToCoord(YValue);
    static const float HLineLength = float(this->c.Vidmode.width - this->c.LMargin - this->c.RMargin);
    static const float HLinePos = float(this->c.LMargin);
    sf::RectangleShape* s = new sf::RectangleShape(sf::Vector2f(HLineLength, float(Bold)));
    s->setFillColor(Col);
    sf::FloatRect r = s->getLocalBounds();
    s->setOrigin(0, r.height/2);
    s->setPosition(sf::Vector2f(HLinePos, Ypos));
    Objects.push_back(s);
}
void    Layer::AddHLine(float YValue, unsigned Bold, sf::Color Col, sf::String text, unsigned MarkCharSize){
    text+="  ";
    sf::Text t;
    t.setFont(this->c.Font);
    t.setCharacterSize(MarkCharSize);
    t.setString(text);
    sf::FloatRect rt = t.getLocalBounds();
    float Ypos = this->YValToCoord(YValue);
    float HLineLength = float(this->c.Vidmode.width - this->c.LMargin - this->c.RMargin - rt.width);
    float HLinePos = float(this->c.LMargin);
    sf::RectangleShape* s = new sf::RectangleShape(sf::Vector2f(HLineLength, float(Bold)));
    s->setFillColor(Col);
    sf::FloatRect r = s->getLocalBounds();
    s->setOrigin(0, r.height/2);
    s->setPosition(sf::Vector2f(HLinePos + rt.width, Ypos));
    Objects.push_back(s);
    AddText(text, MarkCharSize, this->c.AxisCol, sf::Text::Regular, TextPos::RIGHTER, HLinePos, Ypos );
}
void    Layer::AddYMark(float YValue, unsigned Bold, sf::Color Col){
    float Ypos = this->YValToCoord(YValue);
    static const float YMarkLength = float(this->c.AxisBold*3);
    static const float YmarkXpos = float(this->c.LMargin) - YMarkLength;
    sf::RectangleShape* s = new sf::RectangleShape(sf::Vector2f(YMarkLength, Bold));
    s->setFillColor(Col);
    sf::FloatRect r = s->getLocalBounds();
    s->setOrigin(0, r.height/2);
    s->setPosition(sf::Vector2f(YmarkXpos, Ypos));
    Objects.push_back(s);
}
void    Layer::AddXMark(float XValue, unsigned Bold, sf::Color Col){
    float Xpos = this->XValToCoord(XValue);
    static const float XMarkLength = float(this->c.AxisBold*3);
    static const float XmarkYpos = float(this->c.Vidmode.height - this->c.BMargin) + XMarkLength;
    sf::RectangleShape* s = new sf::RectangleShape(sf::Vector2f(XMarkLength, Bold));
    s->setFillColor(Col);
    sf::FloatRect r = s->getLocalBounds();
    s->setOrigin(0, r.height/2);
    s->setRotation(270.f);
    s->setPosition(sf::Vector2f(Xpos, XmarkYpos));
    Objects.push_back(s);
}
float   Layer::YValToCoord(float YValue){
    float ymin = this->c.TMargin;
    float ymax = this->c.Vidmode.height - this->c.BMargin;
    static const float YRatio = float(ymax - this->c.TMargin)/float(this->c.YDimMax - this->c.YDimMin);
    float result = ymin - YValue*YRatio;
    if (result < ymin) result=ymin;
    if (result > ymax) result=ymax;
    return result;
}
float   Layer::XValToCoord(float XValue){
    // X0 = a + b * log10(xmin)
    // X1 = a + b * log10(xmax)
    // b = (X1 - X0) / log10 (xmax/xmin)
    // a = X0 - b * log10(xmin)
    float X0, X1, xmin, xmax;
    xmin = this->c.XDimMin;
    xmax = this->c.XDimMax;
    X0 = this->c.LMargin;
    X1 = this->c.Vidmode.width - this->c.RMargin;
    static const float b = (X1-X0)/log10(xmax/xmin);
    static const float a = X0 - b * log10(xmin);
    float result = a + b * log10(XValue);
    if (result < X0) result = X0;
    if (result > X1) result = X1;
    return result;
}
void    Layer::Draw(sf::RenderTarget &tgt){
    if(Objects.empty()) return;
    for(const auto& drawable : Objects) tgt.draw(*drawable);
}
void    Layer::ClearObjects(){
    for(auto& drawable : Objects) delete drawable;
    Objects.clear();
}
Sfgr::Sfgr(){
    cfg.Init();
}
void    Sfgr::winloop(){
    unsigned ScrshotsCount = 0;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 5;
    Window.create(cfg.Vidmode, cfg.WindowTitle, sf::Style::Close, settings);
    Window.setFramerateLimit(40);
    Window.setVerticalSyncEnabled(true);
    sf::RenderTexture MTexture;
    MTexture.create(cfg.Vidmode.width, cfg.Vidmode.height);
    MTexture.clear(cfg.BGCol);
    Layers[0]->Draw(MTexture);
    MTexture.display();
    sf::Sprite msp;
    msp.setTexture(MTexture.getTexture());
    while(Window.isOpen()){
        if(Layers.empty()) { Window.close(); return; }
        sf::Event event;
        while(Window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) { Window.close(); return; }
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Q) { Window.close(); return; }
                if(event.key.code == sf::Keyboard::PageDown){
                    sf::Texture sshot;
                    sshot.create(Window.getSize().x, Window.getSize().y);
                    sshot.update(Window);
                    if(cfg.ScrshotDir!="") sshot.copyToImage().saveToFile(cfg.ScrshotDir+"\\Image_"+std::to_string(ScrshotsCount++)+".jpg");
                }
            }
        }
    Window.draw(msp);
    if(!Layers_busy) for(unsigned i=1; i<Layers.size(); i++) Layers[i]->Draw(Window);
    Window.display();
    }
}
void    Sfgr::Start(){
    if(Window.isOpen()) return;
    if(!Layers.empty()) return;
    Layers.clear();
    Layer* m = NewLayer();
    m->AddText(cfg.Title, cfg.TitleFontSize, cfg.TitleCol, sf::Text::Regular, TextPos::CENTER, cfg.Vidmode.width/2, cfg.TMargin/2);
    m->AddText270(cfg.YTitle, cfg.AxisTitleFontSize, cfg.AxisCol, sf::Text::Regular, cfg.LMargin/3, cfg.Vidmode.height/2);
    m->AddText(cfg.Xtitle, cfg.AxisTitleFontSize, cfg.AxisCol, sf::Text::Regular, TextPos::CENTER, cfg.Vidmode.width/2, cfg.Vidmode.height-cfg.TMargin/2);
    m->AddHLine(cfg.YDimMin, cfg.AxisBold, cfg.AxisCol);
    m->AddVLine(0, cfg.AxisBold, cfg.AxisCol);
    for(float G : m->c.YGrid) {
        m->AddYMark(G, m->c.AxisBold, m->c.AxisCol);
        m->AddHLine(G, m->c.GridBold, m->c.GridCol);
    }
    for(float G : m->c.XGrid) {
        m->AddXMark(G, m->c.AxisBold, m->c.AxisCol);
        m->AddVLine(G, m->c.GridBold, m->c.GridCol);
    }
    std::map<float, sf::String>::iterator it = m->c.XMarks.begin();
    while(it!=m->c.XMarks.end()){
        m->AddText(it->second, m->c.AxisMarksFontSize, m->c.AxisCol, sf::Text::Regular, TextPos::UNDER, m->XValToCoord(it->first), m->YValToCoord(m->c.YDimMin));
        it++;
    }
    it = m->c.YMarks.begin();
    while(it!=m->c.YMarks.end()){
        m->AddText(it->second, m->c.AxisMarksFontSize, m->c.AxisCol, sf::Text::Regular, TextPos::LEFTER, m->XValToCoord(m->c.XDimMin), m->YValToCoord(it->first));
        it++;
    }
    FinLayer(m);
    t = new std::thread([this]() {winloop();});
}
void    Sfgr::Stop(){
    Layers_busy=true;
    for(std::vector<Layer*>::iterator it = Layers.begin(); it != Layers.end(); it++){
        Layer* f = *it;
        f->ClearObjects();
        delete f;
    }
    Layers.clear();
}
Layer*  Sfgr::NewLayer(){
    Layer* n = new Layer();
    n->LayerNumber=++LayerCounter;
    n->c = cfg;
    return n;
}
void    Sfgr::FinLayer(Layer* LayerPtr ){
    Layers.push_back(LayerPtr);
}
void    Sfgr::DelLayer(Layer* LayerPtr){
    Layers_busy=true;
    for(std::vector<Layer*>::iterator it = Layers.begin(); it!=Layers.end(); it++){
        Layer* f = *it;
        if(f->LayerNumber == LayerPtr->LayerNumber){
            f->ClearObjects();
            delete f;
            Layers.erase(it);
            Layers_busy=false;
            return;
        }
    }
    Layers_busy=false;
}
Sfgr::~Sfgr(){
if(!t) { t->join(); delete t; }
}





