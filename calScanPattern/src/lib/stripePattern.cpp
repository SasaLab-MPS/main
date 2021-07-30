/*=====================================================================
  stripePattern.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  ストライプスキャンのレーザ照射点を計算
  Last update: June 13, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void stripePattern(void) {
    Coordinate P1, P2, Ref; // 移動前のレーザ中心:P1，移動後:P2，そのストラテジーの照射開始点:Ref
    P1.x = centerOfLaser.x;
    P1.y = centerOfLaser.y;
    Ref.x = referencePoint.x;
    Ref.y = referencePoint.y;

    double hatch, scanSpeed, scanVectorLength;
    hatch = SCAN_PITCH;
    scanSpeed = SCAN_SPEED;
    scanVectorLength = SCAN_VECTOR_LENGTH;

    // 照射中心の更新
    double edgeOfX, edgeOfY;               // そのストラテジーで照射できるxとy方向の端
    int direction = ScanDirection;         // レーザ走査方向
   
    /* 走査経路の計算 */
    edgeOfX = x_MAX;

    if (ScanDirection == Y_FORWARD)
    {
        P2.x = P1.x;
        P2.y = P1.y + scanSpeed * DT;

        edgeOfY = NumOfStrategy * scanVectorLength + scanVectorLength;
        
        // yの端に到達したとき
        if ((edgeOfY + EPS) < P2.y || (y_MAX + EPS) < P2.y) {
            P2.x = P1.x + hatch;
            P2.y = P1.y;
            direction = Y_REVERSE;
        }

        // xの端に到達したとき
        if ((edgeOfX + EPS) < P2.x) {
            NumOfStrategy++; // ストライプ番号の更新
            P2.x = Ref.x;
            if (NumOfStrategy % 2 == 1) {
                direction = Y_REVERSE;
                P2.y = NumOfStrategy * scanVectorLength + scanVectorLength;
            } else {
                direction = Y_FORWARD;
                P2.y = NumOfStrategy * scanVectorLength;
            }

            if (P2.y > (y_MAX + EPS) ) {
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

        edgeOfY = NumOfStrategy * scanVectorLength;

        // yの端に到達したとき
        if (P2.y < (edgeOfY - EPS) || P2.y < (Pos_MIN[1] - EPS)) {
            P2.x = P1.x + hatch;
            P2.y = Ref.y;
            direction = Y_FORWARD;
        }

        // xの端に到達したとき
        if ((edgeOfX + EPS) < P2.x) {
            NumOfStrategy++; // ストライプ番号の更新
            P2.x = Ref.x;
            if (NumOfStrategy % 2 == 1) {
                direction = Y_REVERSE;
                P2.y = NumOfStrategy * scanVectorLength + scanVectorLength;
            } else {
                direction = Y_FORWARD;
                P2.y = NumOfStrategy * scanVectorLength;
            }

            if (P2.y > (y_MAX + EPS) ) {
                P2.y = y_MAX;
            }

            // 後処理         
            referencePoint.x = P2.x;
            referencePoint.y += scanVectorLength;
        }
    }
    
   
    // 照射中心の更新
    ScanDirection = direction;
    centerOfLaser.x = P2.x;
    centerOfLaser.y = P2.y;
    if (DIM == 2) {
        centerOfLaser.z = 0.0;
    } else {
        centerOfLaser.z = z_MAX;
    }

    /* 計算領域の端に到達したときの処理(右上に到達した場合の処理) */
    int max_strategyNum = (int)(y_MAX / scanVectorLength);
    if (NumOfStrategy >= max_strategyNum) {
        centerOfLaser.x = 10 * x_MAX;
        centerOfLaser.y = 10 * y_MAX;
    }
}