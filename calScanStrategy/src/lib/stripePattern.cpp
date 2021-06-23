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
            ScanDirection = Y_REVERSE;
        }

        // xの端に到達したとき
        if ((edgeOfX + EPS) < P2.x) {
            NumOfStrategy++; // ストライプ番号の更新
            P2.x = Ref.x;
            if (NumOfStrategy % 2 == 1) {
                ScanDirection = Y_REVERSE;
                P2.y = edgeOfY + scanVectorLength;
            } else {
                ScanDirection = Y_FORWARD;
                P2.y = edgeOfY;
            }
            
            if (P2.y > y_MAX) {
                P2.y = y_MAX;
            }           
            
            // 後処理
            referencePoint.x = P2.x;
            referencePoint.y = P2.y;
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
            ScanDirection = Y_FORWARD;
        }

        // xの端に到達したとき
        if ((edgeOfX + EPS) < P2.x) {
            NumOfStrategy++; // ストライプ番号の更新
            P2.x = Ref.x;
            if (NumOfStrategy % 2 == 1) {
                ScanDirection = Y_REVERSE;
                edgeOfY = edgeOfY + 2 * scanVectorLength;
            } else {
                ScanDirection = Y_FORWARD;
                edgeOfY = edgeOfY + scanVectorLength;
            }

            if (P2.y > y_MAX) {
                P2.y = y_MAX;
            }

            // 後処理         
            referencePoint.x = P2.x;
            referencePoint.y = P2.y;
        }
    }
    
   
    // 照射中心の更新
    centerOfLaser.x = P2.x;
    centerOfLaser.y = P2.y;
    if (DIM == 2) {
        centerOfLaser.z = 0.0;
    } else {
        centerOfLaser.z = z_MAX;
    }
    
}