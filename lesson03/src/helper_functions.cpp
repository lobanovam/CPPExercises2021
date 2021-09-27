#include "helper_functions.h"

#include <libutils/rasserts.h>


cv::Mat makeAllBlackPixelsBlue(cv::Mat image) {
    // TODO реализуйте функцию которая каждый черный пиксель картинки сделает синим

    // ниже приведен пример как узнать цвет отдельного пикселя - состоящий из тройки чисел BGR (Blue Green Red)
    // чем больше значение одного из трех чисел - тем насыщеннее его оттенок
    // всего их диапазон значений - от 0 до 255 включительно
    // т.е. один байт, поэтому мы используем ниже тип unsigned char - целое однобайтовое неотрицательное число
    cv::Vec3b color = image.at<cv::Vec3b>(13, 5); // взяли и узнали что за цвет в пикселе в 14-ом ряду (т.к. индексация с нуля) и 6-ой колонке
    unsigned char blue = color[0]; // если это число равно 255 - в пикселе много синего, если равно 0 - в пикселе нет синего
    unsigned char green = color[1];
    unsigned char red = color[2];

    // как получить белый цвет? как получить черный цвет? как получить желтый цвет?
    // поэкспериментируйте! например можете всю картинку заполнить каким-то одним цветом

    // пример как заменить цвет по тем же координатам

    // запустите эту версию функции и посмотрите на получившуюся картинку - lesson03/resultsData/01_blue_unicorn.jpg
    // какой пиксель изменился? почему он не чисто красный?
    for (int i = 0; i< image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            cv::Vec3b color = image.at<cv::Vec3b>(i, j);
            if (color[0] < 1 && color[1] <1 && color[2] <1) {
                image.at<cv::Vec3b>(i, j) = cv::Vec3b(255, green, red);
            }

        }
    }


    return image;
}

cv::Mat invertImageColors(cv::Mat image) {
    // TODO реализуйте функцию которая каждый цвет картинки инвертирует:
    // т.е. пусть ночь станет днем, а сумрак рассеется
    // иначе говоря замените каждое значение яркости x на (255-x) (т.к находится в диапазоне от 0 до 255)
    for (int i = 0; i< image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            cv::Vec3b color = image.at<cv::Vec3b>(i, j);
            unsigned char blue = color[0];
            unsigned char green = color[1];
            unsigned char red = color[2];
            image.at<cv::Vec3b>(i, j) = cv::Vec3b(255 - blue, 255 - green,255 - red);
            }

        }


    return image;
}

cv::Mat addBackgroundInsteadOfBlackPixels(cv::Mat object, cv::Mat background) {
    // TODO реализуйте функцию которая все черные пиксели картинки-объекта заменяет на пиксели с картинки-фона
    // т.е. что-то вроде накладного фона получится
    // гарантируется что размеры картинок совпадают - проверьте это через rassert, вот например сверка ширины:
    rassert(object.cols == background.cols, 341241251251351);
    for (int i = 0; i< object.rows; i++) {
        for (int j = 0; j < object.cols; j++) {
            cv::Vec3b color = object.at<cv::Vec3b>(i, j);
            cv::Vec3b color1 = background.at<cv::Vec3b>(i, j);
            if (color[0] < 1 && color[1] <1 && color[2] <1) {
                object.at<cv::Vec3b>(i, j) = cv::Vec3b(color1[0],color1[1],color1[2]);
            }
        }

    }

    return object;
}

cv::Mat addBackgroundInsteadOfBlackPixelsLargeBackground(cv::Mat object, cv::Mat largeBackground) {

    // теперь вам гарантируется что largeBackground гораздо больше - добавьте проверок этого инварианта (rassert-ов)

    // TODO реализуйте функцию так, чтобы нарисовался объект ровно по центру на данном фоне, при этом черные пиксели объекта не должны быть нарисованы
    int rowdif = largeBackground.rows - object.rows;
    int coldif = largeBackground.cols - object.cols;

    for (int i = 0; i< object.rows; i++) {
        for (int j = 0; j < object.cols; j++) {
            cv::Vec3b color = object.at<cv::Vec3b>(i, j);
            if (color[0] < 1 && color[1] <1 && color[2] <1) {
                continue;
            } else {
                largeBackground.at<cv::Vec3b>(i+rowdif/2, j+coldif/2) = cv::Vec3b(color[0],color[1],color[2]);
            }
        }

    }


    return largeBackground;
}
cv::Mat multiplyUnicorns(cv::Mat object, cv::Mat largeBackground, int n) {
    int rowdif = largeBackground.rows - object.rows;
    int coldif = largeBackground.cols - object.cols;
    for (int k = 0; k<n; k++) {

        int nrows = rand() % (rowdif+1);
        int(ncols) = rand() % (coldif+1);
        for (int i = 0; i < object.rows; i++) {
            for (int j = 0; j < object.cols; j++) {
                cv::Vec3b color = object.at<cv::Vec3b>(i, j);
                if (color[0] < 1 && color[1] < 1 && color[2] < 1) {
                    continue;
                } else {
                    largeBackground.at<cv::Vec3b>(i+nrows, j+ncols) = cv::Vec3b(color[0], color[1], color[2]);
                }
            }
        }

    }
    return largeBackground;

}
