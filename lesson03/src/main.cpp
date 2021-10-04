#include <iostream>
#include <filesystem> // это нам понадобится чтобы создать папку для результатов
#include <libutils/rasserts.h>

#include "helper_functions.h"

#include <opencv2/highgui.hpp> // подключили часть библиотеки OpenCV, теперь мы можем читать и сохранять картинки

void task1() {

    cv::Mat imgUnicorn = cv::imread("lesson03/data/unicorn.png");  // загружаем картинку с единорогом
    rassert(!imgUnicorn.empty(), 3428374817241); // проверяем что картинка загрузилась (что она не пустая)

    // TODO выведите в консоль разрешение картинки (ширина x высота)
    int width = imgUnicorn.rows; // как в ООП - у картинки есть поля доступные через точку, они называются cols и rows - попробуйте их
    int height = imgUnicorn.cols;
    std::cout << "Unicorn image loaded: " << width << "x" << height << std::endl;

    // создаем папку в которую будем сохранять результаты - lesson03/resultsData/
    std::string resultsDir = "lesson03/resultsData/";
    if (!std::filesystem::exists(resultsDir)) { // если папка еще не создана
        std::filesystem::create_directory(resultsDir); // то создаем ее
    }

    cv::Mat blueUnicorn = makeAllBlackPixelsBlue(imgUnicorn.clone()); // TODO реализуйте функцию которая каждый пиксель картинки который близок к белому - делает синим
    std::string filename = resultsDir + "01_blue_unicorn.jpg"; // удобно в начале файла писать число, чтобы файлы были в том порядке в котором мы их создали
    cv::imwrite(filename, blueUnicorn);

    cv::Mat invertedUnicorn = invertImageColors(imgUnicorn.clone());
    filename = resultsDir + "02_inv_unicorn.jpg";
    cv::imwrite(filename, invertedUnicorn);
    // TODO реализуйте функцию которая каждый цвет картинки инвертирует
    // TODO сохраните резльутат в ту же папку, но файл назовите "02_inv_unicorn.jpg"

    cv::Mat castle = cv::imread("lesson03/data/castle.png");// TODO считайте с диска картинку с замком - castle.png
    rassert(!castle.empty(), "castle is empty");
    cv::Mat unicornInCastle = addBackgroundInsteadOfBlackPixels(imgUnicorn.clone(), castle.clone());// TODO реализуйте функцию которая все черные пиксели картинки-объекта заменяет на пиксели с картинки-фона
    filename = resultsDir + "03_unicorn_castle.jpg";
    cv::imwrite(filename, unicornInCastle);
    // TODO сохраните результат в ту же папку, назовите "03_unicorn_castle.jpg"

    cv::Mat largeCastle = cv::imread("lesson03/data/castle_large.jpg"); // TODO считайте с диска картинку с большим замком - castle_large.png

    cv::Mat unicornInLargeCastle = addBackgroundInsteadOfBlackPixelsLargeBackground(imgUnicorn, largeCastle); // TODO реализуйте функцию так, чтобы нарисовался объект ровно по центру на данном фоне, при этом черные пиксели объекта не должны быть нарисованы
    filename = resultsDir + "04_unicorn_large_castle.jpg";
    cv::imwrite(filename, unicornInLargeCastle);
    // TODO сохраните результат - "04_unicorn_large_castle.jpg"

    // TODO сделайте то же самое, но теперь пусть единорог рисуется N раз (случайно выбранная переменная от 0 до 100)
    int n = rand()%101;
    cv::Mat largeCastle1 = cv::imread("lesson03/data/castle_large.jpg");
    cv::Mat lotsOfUnicorns = multiplyUnicorns(imgUnicorn.clone(), largeCastle1.clone(), n);
    filename = resultsDir + "05_unicorns_take.jpg";
    cv::imwrite(filename, lotsOfUnicorns);
    // функцию вам придется объявить самостоятельно, включая:
    // 1) придумывание ее имени
    // 2) добавление декларации в helper_functions.h (три аргумента - объект, фон, число рисований объекта)
    // 3) добавление реализации в helper_functions.cpp (список аргументов должен совпадать со списком в декларации)
    // 4) как генерировать случайные числа - найдите самостоятельно через гугл, например "c++ how to random int"
    // 5) при этом каждый единорог рисуется по случайным координатам
    // 6) результат сохраните - "05_unicorns_take.jpg"
     width = largeCastle.cols;
     height = largeCastle.rows;
     cv::Scalar color(0,0,0);
     cv::Mat myNewImage(height, width, CV_8UC3, color);
     cv::Mat stretched = stretch(myNewImage, imgUnicorn.clone());
     filename = resultsDir + "06_unicorns_upscale.jpg";
     cv::imwrite(filename, stretched);

     // TODO растяните картинку единорога так, чтобы она заполнила полностью большую картинку с замком "06_unicorn_upscale.jpg"
}

void task2() {
    cv::Mat imgUnicorn = cv::imread("lesson03/data/unicorn.png");
    rassert(!imgUnicorn.empty(), 3428374817241);

    // cv::waitKey - функция некоторое время ждет не будет ли нажата кнопка клавиатуры, если да - то возвращает ее код
    int updateDelay = 10; // указываем сколько времени ждать нажатия кнопки клавиатуры - в миллисекундах
    while (cv::waitKey(updateDelay) != 32) {
        // поэтому если мы выполняемся до тех пор пока эта функция не вернет код 32 (а это код кнопки "пробел"), то достаточно будет нажать на пробел чтобы закончить работу программы

        // кроме сохранения картинок на диск (что часто гораздо удобнее конечно, т.к. между ними легко переключаться)
        // иногда удобно рисовать картинку в окне:

        // TODO сделайте функцию которая будет все черные пиксели (фон) заменять на случайный цвет (аккуратно, будет хаотично и ярко мигать, не делайте если вам это противопоказано)
        cv::Mat task2 = randomColors(imgUnicorn.clone());
        cv::imshow("lesson03 window", task2);
    }


}

struct MyVideoContent {
    cv::Mat frame;
    int lastClickX;
    int lastClickY;
    int lastClickXR;
    int lastClickYR;
};
bool b;
bool c;
void onMouseClick(int event, int x, int y, int flags, void *pointerToMyVideoContent) {
    MyVideoContent &content = *((MyVideoContent*) pointerToMyVideoContent);
    b = false;
    c = false;
    if (event == cv::EVENT_LBUTTONDOWN) { // если нажата левая кнопка мыши
        //std::cout << "Left click at x=" << x << ", y=" << y << std::endl;
        content.lastClickX = x;
        content.lastClickY = y;
        b = true;

    }
    if (event == cv::EVENT_RBUTTONDOWN) {
        //std::cout << "Left rClick at x=" << x << ", y=" << y << std::endl;
        content.lastClickXR = x;
        content.lastClickYR = y;
        c = true;
    }
}

void task3() {
    cv::VideoCapture video(0);
    rassert(video.isOpened(), 3423948392481); // проверяем что видео получилось открыть
    MyVideoContent content;

    std::vector<int> clickX;
    std::vector<int> clickY;
    std::vector<int> clickXR;
    std::vector<int> clickYR;

    while (cv::waitKey(10) != 32 && cv::waitKey(10) != 27) {
        bool isSuccess = video.read(content.frame); // считываем из видео очередной кадр
        cv::setMouseCallback("video", onMouseClick, &content); // делаем так чтобы функция выше (onMouseClick) получала оповещение при каждом клике мышкой
        rassert(isSuccess, 348792347819); // проверяем что считывание прошло успешно
        rassert(!content.frame.empty(), 3452314124643); // проверяем что кадр не пустой
        // TODO добавьте завершение программы в случае если нажат пробел
        // TODO добавьте завершение программы в случае если нажат Escape (придумайте как нагуглить)
        // TODO сохраняйте в вектор (std::vector<int>) координаты всех кликов мышки
        if(b) {
            clickX.push_back(content.lastClickX);
            clickY.push_back(content.lastClickY);
        }
        if(c) {
            clickXR.push_back(content.lastClickXR);
            clickYR.push_back(content.lastClickYR);
        }
        //std::cout<<clickX.size()<<std::endl;
        //std::cout<<clickY.size()<<std::endl;
        // TODO и перед отрисовкой очередного кадра - заполняйте все уже прокликанные пиксели красным цветом
        // TODO сделайте по правому клику мышки переключение в режим "цвета каждого кадра инвертированы" (можете просто воспользоваться функцией invertImageColors)
        cv:: Mat nframe = NewFrame(clickX, clickY, content.frame);
        cv:: Mat rframe = rFrame(clickXR, clickYR, content.frame);
        cv::imshow("video", nframe);
        cv::imshow("video", rframe);

    }
}

void task4() {
    cv::VideoCapture video(0);
    rassert(video.isOpened(), 3423948392481); // проверяем что видео получилось открыть
    MyVideoContent content;

    std::vector<int> clickX;
    std::vector<int> clickY;

    cv::Mat largeCastle = cv::imread("lesson03/data/castle_large.jpg");
    rassert(!largeCastle.empty(), 3428374817241);
    int width = content.frame.cols;
    int height = content.frame.rows;
    cv::Scalar color(0,0,0);
    cv::Mat myNewImage(height, width, CV_8UC3, color);
    cv::Mat scaledCastle = stretch(myNewImage,largeCastle.clone());
    //std::string resultsDir = "lesson03/resultsData/";
    //std::string filename = resultsDir + "07_castle.jpg";
   // cv::imwrite(filename, scaledCastle);

    while (cv::waitKey(10) != 32 && cv::waitKey(10) != 27) {
        bool isSuccess = video.read(content.frame); // считываем из видео очередной кадр
        cv::setMouseCallback("video", onMouseClick, &content); // делаем так чтобы функция выше (onMouseClick) получала оповещение при каждом клике мышкой
        rassert(isSuccess, 348792347819); // проверяем что считывание прошло успешно
        rassert(!content.frame.empty(), 3452314124643); // проверяем что кадр не пустой
        if(b) {
            clickX.push_back(content.lastClickX);
            clickY.push_back(content.lastClickY);
        }

        cv:: Mat nframe = transparent(clickX, clickY, content.frame, scaledCastle);
        cv::imshow("video", nframe);

    }

    // TODO на базе кода из task3 (скопируйте просто его сюда) сделайте следующее:
    // при клике мышки - определяется цвет пикселя в который пользователь кликнул, теперь этот цвет считается прозрачным (как было с черным цветом у единорога)
    // и теперь перед отрисовкой очередного кадра надо подложить вместо прозрачных пикселей - пиксель из отмасштабированной картинки замка (castle_large.jpg)

    // TODO попробуйте сделать так чтобы цвет не обязательно совпадал абсолютно для прозрачности (чтобы все пиксели похожие на тот что был кликнут - стали прозрачными, а не только идеально совпадающие)

    // TODO подумайте, а как бы отмаскировать фон целиком несмотря на то что он разноцветный?
    // а как бы вы справились с тем чтобы из фотографии с единорогом и фоном удалить фон зная как выглядит фон?
    // а может сделать тот же трюк с вебкой - выйти из вебки в момент запуска программы, и первый кадр использовать как кадр-эталон с фоном который надо удалять (делать прозрачным)
}

int main() {
    try {
    //task1();
    //task2();
    //task3();
    task4();
        return 0;
    } catch (const std::exception &e) {
        std::cout << "Exception! " << e.what() << std::endl;
        return 1;
    }
}
