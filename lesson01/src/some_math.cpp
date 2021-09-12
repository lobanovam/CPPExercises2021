#include "some_math.h"
#include <limits>
#include <math.h>
#include <vector>

void max(double x1, double x2);

int fibbonachiRecursive(int n) {
    // TODO 03 реализуйте функцию которая считает числа Фибоначчи - https://ru.wikipedia.org/wiki/%D0%A7%D0%B8%D1%81%D0%BB%D0%B0_%D0%A4%D0%B8%D0%B1%D0%BE%D0%BD%D0%B0%D1%87%D1%87%D0%B8
    return 0;

}

int fibbonachiFast(int n) {
    // TODO 04 реализуйте быструю функцию Фибоначчи с использованием std::vector
    std::vector<int> fib;

    return(0);
}

double solveLinearAXB(double a, double b) {
    // TODO 10 решите линейное уравнение a*x+b=0 а если решения нет - верните наибольшее значение double - найдите как это сделать в интернете по запросу "so cpp double max value" (so = stackoverflow = сайт где часто можно найти ответы на такие простые запросы), главное НЕ КОПИРУЙТЕ ПРОСТО ЧИСЛО, ПОЖАЛУЙСТААаа
    // если решений сколь угодно много - верните максимальное значение со знаком минус
    double x = 0;
    if (a!=0) {
        x = -b/a;
    }else{
        x = std::numeric_limits<double>::max();
    }
    return x;
}

std::vector<double> solveSquare(double a, double b, double c) {
    // TODO 20 решите квадратное уравнение вида a*x^2+b*x+c=0
    // если корня два - они должны быть упорядочены по возрастанию
    double d = b*b - 4*a*c;

    double x1 = (b*(-1)+sqrt(d))/2*a;
    double x2 = (b*(-1)-sqrt(d))/2*a;


    std::vector<double> results;
    // чтобы добавить в вектор элемент - нужно вызвать у него метод push_back:
    if(x1!=x2) {
        results.push_back(std::min(x1,x2));
        results.push_back(std::max(x1,x2));
    }else {
        results.push_back(x2);
    }
    return results;
}


