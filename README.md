# Sfgr
 Класс для рисования графиков АЧХ слышимого звукового диапазона<br>
 Используется библиотека <a href="https://www.sfml-dev.org/index.php">SFML</a>, и для корректной работы она должна быть правильно <a href="https://www.sfml-dev.org/tutorials/2.5/">установлена</a>.<br>
 По оси X используется логарифмическая шкала, по оси Y используется линейная (предполагается, что логарифмическими будут ее значения).
 ### Порядок использования:
 1. Подключить библиотеку SFML, нужные компоненты: sfml-graphics, sfml-window, sfml-system. Не забыть скопировать ее .dll'и в каталог c exe-файлом.
 2. Создать экземпляр класса Sfgr: ``` Sfgr graph;```
 3. Произвести необходимые настройки конфигурации: ```graph.cfg.Title=L"Заголовок"; graph.cfg.XDimMax=15000;``` etc
 4. Произвести дальнейшие автонастройки и запустить оконный тред: ```graph.Start();``` (выход - q)
 5. Создать экземпляр слоя для рисования на области графика: ```Layer* f = graph.NewLayer();```
 6. Рисовать графики:
 ```c
 gpoint GraphArray[1000]; // Выделяем 1000 точечный массив X-Y
 for (int i=0; i<1000; ++i)
 { // Заполняем массив данными Xvalue и YValue }
 f->AddPlotArray(GraphArray, 1000, sf::Color:Blue); // Рисуем график на слое
 ```
 Примечание: рисование начинается с минимального значения по X и не более 1 графика на слой.<br>
 Слоев может быть сколько угодно.<br>
 7. Опубликовать слой ```f``` на отображаемом окне: ```graph.FinLayer(f);```<br>
 8. Удалить слой из окна (перед публикацией следующего кадра): ```graph.DelLayer(f);```<br>
 9. Можно так же рисовать точки: ```f->AddPoint(20, -40, 3, sf::Color::Red, L"Метка", 16);```<br>
 10. И линии:<br>
 ```
 f->AddHLine(-30, 1, sf::Color::Red, L"порог", 14);
 f->AddVLine(1000, 1, sf::Color::Red, L"1КГц", 14);
 ```
 11. Можно снимать скриншоты кнопкой PageDown (если задан каталог куда их класть ```graph.cfg.ScrShotDir="c:\\results";```)
 
 Живой пример можно посмотреть в main.cpp
