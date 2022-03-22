# Sfgr
Класс для рисования графиков АЧХ слышимого звукового диапазона<br>
Используется библиотека <a href="https://www.sfml-dev.org/index.php">SFML</a>, и для корректной работы она должна быть правильно <a href="https://www.sfml-dev.org/tutorials/2.5/">установлена</a>.<br>
По оси X используется логарифмическая шкала, по оси Y используется линейная (предполагается, что логарифмическими будут ее значения).
### Порядок использования:
1. Подключить библиотеку SFML, нужные компоненты: sfml-graphics, sfml-window, sfml-system. Не забыть скопировать ее .dll'и в каталог c exe-файлом.
2. Создать экземпляр класса Sfgr: ``` Sfgr graph;```
3. Произвести необходимые настройки конфигурации: ```graph.cfg.Title=L"Заголовок"; graph.cfg.XDimMax=15000;``` etc
4. Произвести дальнейшие автонастройки и запустить оконный тред: ```graph.Start();``` (выход - q, снимок - PageDown)
5. Ввести константу размера массива под графики: ```const int GraphSize = graph.cfg.XDimMax-graph.cfg.XDimMin;```
6. Создать кадр для рисования на области графика: ```Frame* f = graph.NewFrame(GraphSize);```
7. Рисовать графики:
```c
 f->ArrayGraph.clear();           // Очищаем график
 f->GraphColor = sf::Color::Red;  // Устанавливаем цвет графика
 for (int i=0; i<GraphSize; ++i)  // В цикле добавляем точки графика
 {
  Sfgr::point pnt;                 // Точка это структура из 2 float: XValue и YValue
  pnt.XValue = graph.cfg.XDimMin + i; // По оси X простой инкремент
  pnt.YValue = function(...);      // По оси Y что-то другое
  f->ArrayGraph.push_pack(pnt);    // Добавляем точку в вектор точек
 }
```
Примечание: рисование начинается с минимального значения по X и не более 1 графика на кадр.<br>
Кадров может быть сколько угодно.<br>
8. Можно так же рисовать точки: ```f->AddPoint(20, -40, 3, sf::Color::Red, L"Метка", 16);```<br>
9. Линии:<br>
```
f->AddHLine(-30, 1, sf::Color::Red, L"порог", 14);
f->AddVLine(1000, 1, sf::Color::Red, L"1КГц", 14);
```
10. Текстовые метки:<br>
```
f->AddHText(f, graph.cfg.Vidmode.width, 20, "Метка", 16, sf::Color::Blue, sf::Text::Regular, Sfgr::TextPos::LEFTER);
```
11. Опубликовать кадр ```f``` на отображаемом окне: ```graph.ShowFrame(f);```<br>
12. Удалить кадр из окна (перед публикацией следующего кадра): ```graph.DeleteFrame(f);```<br>
13. Можно делать снимки кнопкой PageDown (если задан каталог куда их класть ```graph.cfg.ScrShotDir="c:\\results";```)
 
 Живой пример можно посмотреть в main.cpp<br>
 <img src="graf.jpg" width=100%>
