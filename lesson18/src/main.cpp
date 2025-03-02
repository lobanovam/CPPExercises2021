#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <set>
#include <chrono>
#include <iostream>
#include <filesystem>
#include <memory>

#include <libutils/rasserts.h>
#include <libutils/fast_random.h>


int estimateQuality(cv::Mat mat, cv::Mat mask, int j, int i, int ny, int nx);

// Эта функция говорит нам правда ли пиксель отмаскирован, т.е. отмечен как "удаленный", т.е. белый
bool isPixelMasked(cv::Mat mask, int j, int i) {

    if (mask.at<cv::Vec3b>(j, i) == cv::Vec3b(255, 255, 255)) {
        return true;
    }
    else return false;
}

void run(int caseNumber, std::string caseName) {
    std::cout << "_________Case #" << caseNumber << ": " << caseName << "_________" << std::endl;

    cv::Mat original = cv::imread(
            "lesson18/data/" + std::to_string(caseNumber) + "_" + caseName + "/" + std::to_string(caseNumber) +
            "_original.jpg");
    cv::Mat mask = cv::imread(
            "lesson18/data/" + std::to_string(caseNumber) + "_" + caseName + "/" + std::to_string(caseNumber) +
            "_mask.png");
    //rassert(!original.empty(), 324789374290018);
    //rassert(!mask.empty(), 378957298420019);
    // std::cout << "Image resolution: " << ... << std::endl;

    // создаем папку в которую будем сохранять результаты - lesson18/resultsData/ИМЯ_НАБОРА/
    std::string resultsDir = "lesson18/resultsData/";
    if (!std::filesystem::exists(resultsDir)) { // если папка еще не создана
        std::filesystem::create_directory(resultsDir); // то создаем ее
    }
    resultsDir += std::to_string(caseNumber) + "_" + caseName + "/";
    if (!std::filesystem::exists(resultsDir)) { // если папка еще не создана
        std::filesystem::create_directory(resultsDir); // то создаем ее
    }

    // сохраняем в папку с результатами оригинальную картинку и маску
    cv::imwrite(resultsDir + "0original.png", original);
    cv::imwrite(resultsDir + "1mask.png", mask);


    int sum = 0;
    for (int j = 0; j < original.rows; j++) {
        for (int i = 0; i < original.cols; i++) {
            if (isPixelMasked(mask, j, i)) {
                original.at<cv::Vec3b>(j, i) = cv::Vec3b(255, 255, 255);
                sum++;
            }
        }
    }
    cv::imwrite(resultsDir + "2_original_cleaned.png", original);

    std::cout << "number of masked pixels " << sum << std::endl;

    FastRandom random(32542341); // этот объект поможет вам генерировать случайные гипотезы
    cv::Mat shifts(original.rows, original.cols, CV_32SC2, cv::Scalar(0, 0));
    cv::Mat image = original;

    std::cout << "Image resolution: " << original.cols << "x" << original.rows << std::endl;

    std::vector<cv::Mat> pyramid; // здесь будем хранить пронумерованные версии картинки разного разрешения
    cv::Mat img = original.clone();
    const int PYRAMID_MIN_SIZE = 20; // до какой поры уменьшать картинку? давайте уменьшать пока картинка больше 20 пикселей
    while (img.rows > PYRAMID_MIN_SIZE &&
    img.cols > PYRAMID_MIN_SIZE) { // или пока больше (2 * размер окна для оценки качества)
        pyramid.insert(pyramid.begin(),
                       img); // мы могли бы воспользоваться push_back но мы хотим вставлять картинки в начало вектора
                       cv::pyrDown(img, img); // эта функция уменьшает картинку в два раза
    }

    std::vector<cv::Mat> pyramidMask; // здесь будем хранить пронумерованные версии картинки разного разрешения
    cv::Mat img1 = mask.clone();
    while (img1.rows > PYRAMID_MIN_SIZE &&
    img1.cols > PYRAMID_MIN_SIZE) { // или пока больше (2 * размер окна для оценки качества)
        pyramidMask.insert(pyramidMask.begin(),
                           img1); // мы могли бы воспользоваться push_back но мы хотим вставлять картинки в начало вектора
                           cv::pyrDown(img1, img1); // эта функция уменьшает картинку в два раза
    }

    std::vector<cv::Mat> pyramidShifts; // здесь будем хранить пронумерованные версии картинки разного разрешения
    cv::Mat img2 = shifts.clone();
    while (img2.rows > PYRAMID_MIN_SIZE &&
    img2.cols > PYRAMID_MIN_SIZE) { // или пока больше (2 * размер окна для оценки качества)
        pyramidShifts.insert(pyramidShifts.begin(),
                             img2); // мы могли бы воспользоваться push_back но мы хотим вставлять картинки в начало вектора
                             cv::pyrDown(img2, img2); // эта функция уменьшает картинку в два раза
    }

    for (int h = 0; h < pyramid.size(); h++) {
        cv::Mat image = pyramid[h];
        cv::Mat mmask = pyramidMask[h];
        cv::Mat sshifts = pyramidShifts[h];
        int k = 100;
        while (k > 0) {
            for (int j = 0; j < image.rows - 3; j++) {
                for (int i = 0; i < image.cols - 3; i++) {
                    if (!isPixelMasked(mmask, j, i)) {
                        continue;
                    }
                    cv::Vec2i dxy = sshifts.at<cv::Vec2i>(j, i);
                    int nx = i + dxy[1];
                    int ny = j + dxy[0];
                    int currentQuality = estimateQuality(image, mmask, j, i, ny, nx);
                    bool b = true;
                    int rand_x = 0;
                    int rand_y = 0;
                    while (b) {
                        rand_x = random.next(2, image.cols - 4);
                        rand_y = random.next(2, image.rows - 4);
                        if (!isPixelMasked(mmask, rand_y, rand_x)) {
                            b = false;
                        }
                    }
                    int randomQuality = estimateQuality(image, mmask, j, i, rand_y, rand_x);
                    if (randomQuality < currentQuality || currentQuality == 0) {
                        currentQuality = randomQuality;
                        sshifts.at<cv::Vec2i>(j, i)[0] = rand_y - j;
                        sshifts.at<cv::Vec2i>(j, i)[1] = rand_x - i;
                        image.at<cv::Vec3b>(j, i) = image.at<cv::Vec3b>(rand_y, rand_x);
                    }
                    // int nqualleft = estimateQuality(image, mmask, j, i, j + sshifts.at<cv::Vec2i>(j, i - 1)[0], i + shifts.at<cv::Vec2i>(j, i - 1)[1]);
                    // int nqualup = estimateQuality(image, mmask, j, i, j + sshifts.at<cv::Vec2i>(j - 1, i)[0], i + shifts.at<cv::Vec2i>(j - 1, i)[1]);

                    // if (nqualleft < currentQuality) {
                    //     currentQuality = nqualleft;
                    //    shifts.at<cv::Vec2i>(j, i) = shifts.at<cv::Vec2i>(j, i - 1);
                    //     image.at<cv::Vec3b>(j, i) = image.at<cv::Vec3b>(j + shifts.at<cv::Vec2i>(j, i)[0], i + shifts.at<cv::Vec2i>(j, i)[1]);
                    //  }
                    // if (nqualup < currentQuality) {
                    //   shifts.at<cv::Vec2i>(j, i) = shifts.at<cv::Vec2i>(j - 1, i);
                    //  image.at<cv::Vec3b>(j, i) = image.at<cv::Vec3b>(j + shifts.at<cv::Vec2i>(j, i)[0], i + shifts.at<cv::Vec2i>(j, i)[1]);
                    // }
                }
            }

            k--;
        }
        if (h != (pyramid.size() - 1)) {
            for (int i = 0; i < pyramidShifts[h].rows - 1; i++) {
                for (int j = 0; j < pyramidShifts[h].cols - 1; j++) {
                    if (2*i +1 <= pyramidShifts[h+1].cols && 2*j+1 <= pyramidShifts[h+1].rows) {
                        pyramidShifts[h + 1].at<cv::Vec2i>(2 * j, 2 * i)[0] =
                                pyramidShifts[h].at<cv::Vec2i>(j, i)[0] * 2;
                        pyramidShifts[h + 1].at<cv::Vec2i>(2 * j, 2 * i)[1] =
                                pyramidShifts[h].at<cv::Vec2i>(j, i)[1] * 2;

                        pyramidShifts[h + 1].at<cv::Vec2i>(2 * j + 1, 2 * i + 1)[0] =
                                pyramidShifts[h].at<cv::Vec2i>(j, i)[0] * 2;
                        pyramidShifts[h + 1].at<cv::Vec2i>(2 * j + 1, 2 * i + 1)[1] =
                                pyramidShifts[h].at<cv::Vec2i>(j, i)[1] * 2;

                        pyramidShifts[h + 1].at<cv::Vec2i>(2 * j + 1, 2 * i)[0] =
                                pyramidShifts[h].at<cv::Vec2i>(j, i)[0] * 2;
                        pyramidShifts[h + 1].at<cv::Vec2i>(2 * j + 1, 2 * i)[1] =
                                pyramidShifts[h].at<cv::Vec2i>(j, i)[1] * 2;

                        pyramidShifts[h + 1].at<cv::Vec2i>(2 * j, 2 * i + 1)[0] =
                                pyramidShifts[h].at<cv::Vec2i>(j, i)[0] * 2;
                        pyramidShifts[h + 1].at<cv::Vec2i>(2 * j, 2 * i + 1)[1] =
                                pyramidShifts[h].at<cv::Vec2i>(j, i)[1] * 2;
                    }
                }
            }
            for (int i = 0; i < pyramidShifts[h + 1].rows - 1; i++) {
                for (int j = 0; j < pyramidShifts[h + 1].cols - 1; j++) {
                    pyramid[h + 1].at<cv::Vec3b>(j, i) = pyramid[h + 1].at<cv::Vec3b>(
                            j + pyramidShifts[h + 1].at<cv::Vec2i>(j, i)[0],
                            i + pyramidShifts[h + 1].at<cv::Vec2i>(j, i)[1]);
                }
            }
        }
    }


    cv::imwrite(resultsDir + "3mask.png", image);
}
int estimateQuality(cv::Mat image, cv::Mat mask, int j, int i, int ny, int nx) {
    int sum0 = 0;
    int sum1 = 0;
    int sum2 = 0;

    for (int k = -2; k < 3; ++k) {
        for (int l = -2; l < 3; ++l) {

            if (isPixelMasked(mask, ny + k, nx + l)) {
                return 100000000;
            }


            sum0 += (image.at<cv::Vec3b>(j + k, i + l)[0] - image.at<cv::Vec3b>(ny + k, nx + l)[0]) *
                    (image.at<cv::Vec3b>(j + k, i + l)[0] - image.at<cv::Vec3b>(ny + k, nx + l)[0]);
            sum1 += (image.at<cv::Vec3b>(j + k, i + l)[1] - image.at<cv::Vec3b>(ny + k, nx + l)[1]) *
                    (image.at<cv::Vec3b>(j + k, i + l)[1] - image.at<cv::Vec3b>(ny + k, nx + l)[1]);
            sum2 += (image.at<cv::Vec3b>(j + k, i + l)[2] - image.at<cv::Vec3b>(ny + k, nx + l)[2]) *
                    (image.at<cv::Vec3b>(j + k, i + l)[2] - image.at<cv::Vec3b>(ny + k, nx + l)[2]);
        }
    }
    return (sum0 + sum1 + sum2);
}


int main() {
    try {
        run(1, "mic");
        // TODO протестируйте остальные случаи:
        // run(2, "flowers");
        //        run(3, "baloons");
        //        run(4, "brickwall");
        //        run(5, "old_photo");
        //        run(6, "your_data"); // TODO придумайте свой случай для тестирования (рекомендуется не очень большое разрешение, например 300х300)

        return 0;
    } catch (const std::exception &e) {
        std::cout << "Exception! " << e.what() << std::endl;
        return 1;
    }
}