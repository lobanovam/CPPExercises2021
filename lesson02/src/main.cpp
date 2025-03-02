#include <vector>
#include <iostream>
#include <libutils/rasserts.h>

#include "helper_function.h" // подключаем функцию print2DArray(...) из соседнего файла


void task1() {
    std::vector<int> a; // динамический массив (автоматически увеличивается по мере добавления объектов)
    a.push_back(10); // добавляем в конец число 10, тем самым увеличивая этот динамический массив
    std::cout << "current size is " << a.size() << std::endl; // печатаем в консоль текущий размер

    // чтобы продолжить выполнение задания - раскомментируйте следующие строчки - проще всего это сделать выделив их все мышкой, а затем нажать Ctrl+/ (так же можно и комментировать строки)
    rassert(a.size() == 1,3412421421); // это способ проверить некоторый факт в программе, например здесь мы ожидали бы что размер вектора 1 - давайте явно это проверим, указав код ошибки на случай если это будет не так
    rassert(a.size() == 1, "vector a should of size 3!"); // можно вместо числа писать текст описывающий проблему, но на мой взгляд это слишком долго и лениво
//    // TODO 11 запустите программу, увидьте ошибку, была кинота ошибка с кодом из предыдущей строки - почему? поправьте ее
//
    a.resize(5); // изменяем размер массива, пусть он будет хранить пять чисел
   for (int i = 0; i < 5; ++i) {
        a[i] = i; // тогда мы сможем сразу в каждую из его пяти ячеек что-то положить, например числа от 0 до 4
    }
    std::cout << "current size is " << a.size() << std::endl; // печатаем в консоль текущий размер
    // TODO 12 до запуска подумайте какой бы размер массива должен быть? добавьте сюда проверку через rassert что размер вектора тот что вы бы ожидали
    rassert(a.size() == 5, "wrong size" );
}

void task2() {
    std::vector<std::vector<int>> array2d; // это динамический массив в котором каждый элемент - тоже динамический массив
    // TODO 21 добавьте rassert проверяющий размер этого двумерного вектора, как вы считаете какого размера он должен быть?
    rassert(array2d.size()==0, "wrong size");

    std::vector<int> row0; // первый ряд чисел для нашего двумерного массива (row = ряд)
    row0.push_back(5);
    row0.push_back(8);
    row0.push_back(10);

    // TODO 22 добавьте rassert проверяющий размер этого вектора row0
    rassert(row0.size()==3,"wrong size");
    array2d.push_back(row0);

    // TODO 23 добавьте rassert проверяющий размер этого двумерного вектора array2d, как вы считаете какого размера он должен быть?
    rassert(array2d.size()==1, "wrong size");

    std::cout << "print2DArray(array2d)" << std::endl;
    print2DArray(array2d);// TODO 24,25: откройте соседний файл - helper_function.cpp и реализуйте там эту функцию, можете туда быстро попасть через телепорт - держите нажатым CTRL->и кликните по этой функции

     //чтобы продолжить выполнение задания - раскомментируйте следующие строчки - проще всего это сделать выделив их все мышкой, а затем нажать Ctrl+/ (так же можно и комментировать строки)
    // теперь давайте добавим еще один ряд чисел но другим способом:
    std::vector<int> row1;
    row1.resize(3);
    row1[0] = 23;
    row1[1] = 24;
    row1[2] = 42;
    array2d.push_back(row1);
//    // TODO 26 добавьте два rassert-а - чтобы удостовериться что размеры двух динамических массивов которые мы только что изменили - совпадают с вашим ожиданием
    rassert(row1.size() ==3, "wrong size");
    rassert(array2d.size()==2,"wrong size");

    std::cout << "print2DArray(array2d):" << std::endl;
    print2DArray(array2d);
//
//    // TODO 27 добавьте еще один ряд чисел, но на этот раз из 10 чисел от 0 до 9 включительно (воспользуйтесь for-ом)
    std::vector<int>row2;
    row2.resize(10);
    for (int i = 0; i< 10; ++i) {
        row2[i] = i;
    }
    array2d.push_back(row2);
    std::cout << "print2DArray(array2d):" << std::endl;
    print2DArray(array2d);
}

void task3() {
    // TODO 31 напишите следующую программу:

    // TODO 32 попросите пользователя ввести два натуральных числа rows, cols (число рядов и число колонок) (от 1 до 20 включительно каждое)

    // TODO 33 проверьте с помощью rassert что оба числа в корректном диапазоне (от 1 до 20), проверьте что если ввести плохое число - проверка срабатывает и пишет ошибку (можете использовать как число, так и сообщение)

    // TODO 34 создайте двумерный массив состоящий из rows векторов

    // TODO 35 сделайте так чтобы каждый из этих rows векторов был размера cols (используйте resize)

    // TODO 36 как думаете какие элементы сейчас лежат в двумерном массиве? проверьте выведя его в консоль

    // TODO 37 ваша программа должна считывать пары чисел i, j в вечном цикле до тех пор пока i и j не отрицательны
    std::cout<<"input 2 numbers (rows and cols), each 1<=...<=20"<<std::endl;
    int rows;
    int cols;
    std::cin>> rows >> cols;
    rassert(rows>=1 && rows <=20, "wrong");
    rassert(cols>=1 && cols <=20, "wrong");
    std::vector<std::vector<int>>array;
    array.resize(rows);

    for (int i = 0; i< rows; i++) {
        array[i].resize(cols);
    }
    std::cout << "print2DArray(array2d):" << std::endl;
    print2DArray(array);


    while (true) {
        int i;
        int j;
        int br = 0;
        std::cin>> i >> j;
        if (i<0||j<0) {
            break;
        }
        array[i][j] = 1;
        std::cout << "print2DArray(array2d):" << std::endl;
        print2DArray(array);

        for (int k = 0; k<rows;k++) {
           bool b = true;
           for (int p = 0; p<cols; p++) {
               if (array[k][p] !=1) {
                   b = false;
               }
           }
           if (b) {
               std::cout<<"OX-XO-XO"<<std::endl;
               br++;
               break;
           }
        }

        for (int c = 0; c<cols; c++) {
            bool v = true;
            for ( int r = 0; r < rows; r++ ) {
                if (array[r][c]!= 1) {
                    v = false;
                }
            }
            if (v){
                std::cout<<"AX-XA-XA"<<std::endl;
                br++;
                break;
            }
        }
        if (br>0) {
            break;
        }


    }
//        // TODO 38 считав очередное i, j - увеличьте ячейку в думерном массиве находящуюся в j-ой колонке, в i-ом ряду
//        // TODO 39 выведите в консоль текущее состояние двумерного массива
//        // TODO 40 добавьте проверку что если пользователь заполнил единицами хотя бы один ряд - то выводится сообщение "OX-XO-XO" и программа завершается
//        // TODO 41 добавьте проверку что если пользователь заполнил единицами хотя бы одну колонку - то выводится сообщение "AX-XA-XA" и программа завершается
//    }

}


int main() {
    try {
   //     task1(); // TODO 13 когда выполните первое задание - закомментируйте эту строку чтобы эта функция перестала вызываться (добавьте перед нею двойной слэш - / или просто нажмите Ctrl+/)
      //  task2(); // TODO 20 раскомментируйте эту строку чтобы начать выполнять второе задание (или просто поставьте каретку в эту строку и нажмите Ctrl+/)
         task3(); // TODO 30 закомментируйте предыдущие две строки и раскоментируйте эту чтобы начать выполнять третье задание
        return 0;
    } catch (const std::exception &e) {
        std::cout << "Exception! " << e.what() << std::endl;
        return 1;
    }
}
