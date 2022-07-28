#include <iostream>
#include <math.h>

int main()
{
    // gyroscope data
    double data[10][3] = {
        -1.07761367200000, -0.0316569890000000, 1.42161709700000,
        -0.854200598000000, 0.251783428000000, 1.67855073700000,
        -0.632536703000000, 0.248501854000000, 1.71443714800000,
        -0.449975489000000, -0.0473337250000000, 1.44042730900000,
        -0.0847380910000000, -0.774319697000000, 0.962126567000000,
        0.182800025000000, -1.56475014100000, 0.461543371000000,
        0.456295310000000, -2.05308475600000, -0.326379857000000,
        0.825959496000000, -2.34036753200000, -0.821455668000000,
        1.12616863200000, -1.79507662300000, -0.967248971000000,
        1.74725191900000, -1.55064817400000, -1.06787789100000};

    int n = 10; // number of rows of data

    double quat[4] = {1.0, 0.0, 0.0, 0.0}; // initial quaternion
    double dT = 1.0 / 128.0;               // sampling period

    // Your code goes here
    for (int i = 0; i < n; i++)
    {
        double idx11 = 1;
        double idx12 = -0.5 * data[i][0] * dT;
        double idx13 = -0.5 * data[i][1] * dT;
        double idx14 = -0.5 * data[i][2] * dT;

        double idx21 = 0.5 * data[i][0] * dT;
        double idx22 = 1;
        double idx23 = 0.5 * data[i][2] * dT;
        double idx24 = -0.5 * data[i][1] * dT;

        double idx31 = 0.5 * data[i][1] * dT;
        double idx32 = -0.5 * data[i][2] * dT;
        double idx33 = 1;
        double idx34 = 0.5 * data[i][0] * dT;

        double idx41 = 0.5 * data[i][2] * dT;
        double idx42 = 0.5 * data[i][1] * dT;
        double idx43 = -0.5 * data[i][0] * dT;
        double idx44 = 1;

        double A = idx11 * quat[0] + idx12 * quat[1] + idx13 * quat[2] + idx14 * quat[3];
        double B = idx21 * quat[0] + idx22 * quat[1] + idx23 * quat[2] + idx24 * quat[3];
        double C = idx31 * quat[0] + idx32 * quat[1] + idx33 * quat[2] + idx34 * quat[3];
        double D = idx41 * quat[0] + idx42 * quat[1] + idx43 * quat[2] + idx44 * quat[3];

        double quatmag = sqrt(pow(A, 2) + pow(B, 2) + pow(C, 2) + pow(D, 2));

        quat[0] = A / quatmag;
        quat[1] = B / quatmag;
        quat[2] = C / quatmag;
        quat[3] = D / quatmag;
    }

    // Hopefully your output matches the following:
    // 0.999121, 0.00618785, -0.0372197, 0.0182653
    std::cout << quat[0] << ", " << quat[1] << ", " << quat[2] << ", " << quat[3] << std::endl;
}
