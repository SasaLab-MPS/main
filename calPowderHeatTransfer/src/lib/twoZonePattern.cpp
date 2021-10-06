/*=====================================================================
  twoZonePattern.cpp   
  Yota INOUE (2021) 
  twoZonePatternの走査パターンを計算
  Last update: June 3, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/constants.hpp"

void twoZonePattern(void) {
    Coordinate P1, P2, Ref; // 移動前のレーザ中心:P1，移動後:P2，そのストラテジーの照射開始点:Ref
    P1.x = centerOfLaser.x;
    P1.y = centerOfLaser.y;
    Ref.x = referencePoint.x;
    Ref.y = referencePoint.y;

    double hatch, scanSpeed, scanVectorLength;  // 造形条件
    hatch = SCAN_PITCH;
    scanSpeed = SCAN_SPEED;
    scanVectorLength = SCAN_VECTOR_LENGTH;

    // 照射中心の更新
    double edgeOfX, edgeOfY;       // そのストラテジーで照射できるxとy方向の端
    int direction = ScanDirection; // レーザ走査方向
    int max_strategyNum = (int)(y_MAX / scanVectorLength);  // 走査領域の最大数

    /* 走査経路の計算 */
    int NOS = NumOfStrategy % max_strategyNum;
    int flag = 0;    // 走査領域が切り替わったかを判定 
    edgeOfX = x_MAX;

    if (ScanDirection == Y_FORWARD)
    {
        P2.x = P1.x;
        P2.y = P1.y + scanSpeed * DT;

        edgeOfY = NOS * scanVectorLength + scanVectorLength;

        // yの端に到達したとき
        if ((edgeOfY + EPS) < P2.y || (y_MAX + EPS) < P2.y) {
            P2.x = P1.x + hatch;
            P2.y = P1.y;
            direction = Y_REVERSE;
        }

        // xの端に到達したとき
        if ((edgeOfX + EPS) < P2.x) {
            NumOfStrategy++; // ストライプ番号の更新
            flag = 1;        // 走査領域の更新があった
            P2.x = Ref.x;
            if (NOS % 2 == 1) {
                direction = Y_REVERSE;
                P2.y = NOS * scanVectorLength + scanVectorLength;
            }
            else
            {
                direction = Y_FORWARD;
                P2.y = NOS * scanVectorLength;
            }

            if (P2.y > (y_MAX + EPS)) {
                P2.y = y_MAX;
            }

            // 後処理
            referencePoint.x = P2.x;
            referencePoint.y += scanVectorLength;
        }
    }
    else
    {
        P2.x = P1.x;
        P2.y = P1.y - scanSpeed * DT;

        edgeOfY = NOS * scanVectorLength;

        // yの端に到達したとき
        if (P2.y < (edgeOfY - EPS) || P2.y < (Pos_MIN[1] - EPS)) {
            P2.x = P1.x + hatch;
            P2.y = Ref.y;
            direction = Y_FORWARD;
        }

        // xの端に到達したとき
        if ((edgeOfX + EPS) < P2.x) {
            NumOfStrategy++; // ストライプ番号の更新
            flag = 1;        // 走査領域の更新があった
            P2.x = Ref.x;
            if (NOS % 2 == 1) {
                direction = Y_REVERSE;
                P2.y = NOS * scanVectorLength + scanVectorLength;
            }
            else
            {
                direction = Y_FORWARD;
                P2.y = NOS * scanVectorLength;
            }

            if (P2.y > (y_MAX + EPS)) {
                P2.y = y_MAX;
            }

            // 後処理
            referencePoint.x = P2.x;
            referencePoint.y += scanVectorLength;
        }
    }

    /* 照射中心の更新 */
    ScanDirection = direction;
    centerOfLaser.x = P2.x;
    centerOfLaser.y = P2.y;
    if (DIM == 2) {
        centerOfLaser.z = 0.0;
    } else {
        centerOfLaser.z = z_MAX;
    }

    /* 例外処理 */
    // 二度目の照射を開始するとき(左下の原点に戻る)
    if (flag == 1 && NumOfStrategy == max_strategyNum) {
        centerOfLaser.x = hatch; // テキトウな場所に中心を飛ばす
        centerOfLaser.y = 0;
        ScanDirection = Y_FORWARD;
    }
    // 二度目に計算領域の端に到達したときの処理(右上に到達した場合の処理)
    if (NumOfStrategy >= 2 * max_strategyNum) {
        centerOfLaser.x = 10 * x_MAX; // テキトウな場所に中心を飛ばす
        centerOfLaser.y = 10 * y_MAX;
    }
}