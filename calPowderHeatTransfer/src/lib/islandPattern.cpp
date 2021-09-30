/*=====================================================================
  islandPattern.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  アイランドスキャンのレーザ照射点を計算
  Last update: June 13, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/constants.hpp"

void islandPattern(void) {

    Coordinate P1, P2, Ref;     // 移動前のレーザ中心:P1，移動後:P2，そのストラテジーの照射開始点:Ref
    P1.x = centerOfLaser.x;
    P1.y = centerOfLaser.y;
    Ref.x = referencePoint.x;
    Ref.y = referencePoint.y;

    double hatch, scanSpeed, scanVectorLength;
    hatch = SCAN_PITCH;
    scanSpeed = SCAN_SPEED;
    scanVectorLength = SCAN_VECTOR_LENGTH;

    // 照射中心の更新
    double rowX;       // 行:rowX，列:columnY，それぞれの方向で存在できるストラテジーの個数
    double edgeOfX, edgeOfY;    // そのストラテジーで照射できるxとy方向の端
    rowX = ceil(x_MAX / scanVectorLength);  // 天井関数を使用
    //columnY = ceil(y_MAX / scanVectorLength);

    /* 走査経路の計算 */
    int direction = ScanDirection;  // レーザの走査方向
    if ( ScanDirection == X_FORWARD )
    {
        // x方向への順走査
        P2.x = P1.x + scanSpeed * DT;
        P2.y = P1.y;

        edgeOfX = (NumOfStrategy % (int)rowX) * scanVectorLength + scanVectorLength;
        edgeOfY = (NumOfStrategy / (int)rowX) * scanVectorLength + scanVectorLength;

        if ((edgeOfX + EPS) < P2.x || (x_MAX + EPS) < P2.x)
        {
            // x方向の端に到達した場合の処理
            P2.x = P1.x;
            P2.y = P1.y + hatch;
            direction = X_REVERSE; // 走査方向の更新
        }

        if ((edgeOfY + EPS) < P2.y || (y_MAX + EPS) < P2.y)
        {
            // y方向の上端に到達した場合の処理，アイランドの移動
            NumOfStrategy += 1;
            direction = Y_FORWARD; // 走査方向の更新
            if (NumOfStrategy % (int)rowX == 0) // x列の終端に達した時
            {
                P2.x = Pos_MIN[0];
                P2.y = edgeOfY + hatch;
                // 次の走査方向のつじつま合わせ，x列に並ぶアイランドの個数が偶数のとき
                if ((int)rowX % 2 == 0) {
                    direction = X_FORWARD; // 走査方向の更新
                }
            }
            else
            {
                P2.x = P1.x + hatch;
                P2.y = Ref.y;
            }

            // 後処理
            referencePoint.x = P2.x;
            referencePoint.y = P2.y;
            // ifを抜けたい
        }
    }
    else if ( ScanDirection == X_REVERSE )
    {
        // x方向への逆走査
        P2.x = P1.x - scanSpeed * DT;
        P2.y = P1.y;

        edgeOfX = (NumOfStrategy % (int)rowX) * scanVectorLength;
        edgeOfY = (NumOfStrategy / (int)rowX) * scanVectorLength + scanVectorLength;

        if (P2.x < (edgeOfX - EPS) || P2.x < (Pos_MIN[0] - EPS))
        {
            P2.x = Ref.x;
            P2.y = P1.y + hatch;
            direction = X_FORWARD; // 走査方向の更新
        }

        if ((edgeOfY + EPS) < P2.y || (y_MAX + EPS) < P2.y)
        {
            // y方向の上端に到達した場合の処理，アイランドの移動
            NumOfStrategy += 1;
            direction = Y_FORWARD; // 走査方向の更新
            if (NumOfStrategy % (int)rowX == 0)
            {
                P2.x = Pos_MIN[0];
                P2.y = edgeOfY + hatch;
                // 次の走査方向のつじつま合わせ
                if ((int)rowX % 2 == 0) {
                    direction = X_FORWARD; // 走査方向の更新
                }
            }
            else
            {
                P2.x = edgeOfX + scanVectorLength + hatch;
                P2.y = Ref.y;
            }

            // 後処理
            referencePoint.x = P2.x;
            referencePoint.y = P2.y;
        }
    }
    else if (ScanDirection == Y_FORWARD)
    {
        // y方向への順走査
        P2.x = P1.x;
        P2.y = P1.y + scanSpeed * DT;

        edgeOfX = (NumOfStrategy % (int)rowX) * scanVectorLength + scanVectorLength;
        edgeOfY = (NumOfStrategy / (int)rowX) * scanVectorLength + scanVectorLength;

        if ((edgeOfY + EPS) < P2.y || (y_MAX + EPS) < P2.y)
        {
            P2.x = P1.x + hatch;
            P2.y = P1.y;
            direction = Y_REVERSE; // 走査方向の更新
        }

        if ((edgeOfX + EPS) < P2.x || (x_MAX + EPS) < P2.x)
        {
            NumOfStrategy += 1;
            direction = X_FORWARD; // 走査方向の更新
            if (NumOfStrategy % (int)rowX == 0)
            {
                P2.x = Pos_MIN[0];
                P2.y = edgeOfY + hatch;
                // 次の走査方向のつじつま合わせ
                if ((int)rowX % 2 == 0) {
                    direction = Y_FORWARD;
                }
            }
            else
            {
                P2.x = P1.x + hatch;
                P2.y = Ref.y;
            }
            // 後処理
            referencePoint.x = P2.x;
            referencePoint.y = P2.y;
        }
    }
    else
    {
        // y方向への逆走査
        P2.x = P1.x;
        P2.y = P1.y - scanSpeed * DT;

        edgeOfX = (NumOfStrategy % (int)rowX) * scanVectorLength + scanVectorLength;
        edgeOfY = (NumOfStrategy / (int)rowX) * scanVectorLength;

        if (P2.y < (edgeOfY - EPS) || P2.y < (Pos_MIN[1] - EPS))
        {
            P2.x = P1.x + hatch;
            P2.y = Ref.y;
            direction = Y_FORWARD; // 走査方向の更新
        }

        if ((edgeOfX + EPS) < P2.x || (x_MAX + EPS) < P2.x)
        {
            NumOfStrategy += 1;
            direction = X_FORWARD; // 走査方向の更新
            if (NumOfStrategy % (int)rowX == 0)
            {
                P2.x = Pos_MIN[0];
                P2.y = edgeOfY + scanVectorLength + hatch;
                // 次の走査方向のつじつま合わせ
                if ((int)rowX % 2 == 0) {
                    direction = Y_FORWARD;
                }
            }
            else
            {
                P2.x = P1.x + hatch;
                P2.y = Ref.y;
            }

            // 後処理
            referencePoint.x = P2.x;
            referencePoint.y = P2.y;
        }
    }   
    

    /* 諸々の更新 */
    ScanDirection = direction;
    centerOfLaser.x = P2.x;
    centerOfLaser.y = P2.y;
    if (DIM == 2) {
        centerOfLaser.z = 0.0;
    } else {
        centerOfLaser.z = z_MAX;
    }

    /* 計算領域の端に到達したときの処理(右上に到達した場合の処理) */
    int max_strategyNum = (int)(x_MAX / scanVectorLength) * (int)(y_MAX / scanVectorLength);
    if (NumOfStrategy > max_strategyNum){
        centerOfLaser.x = 10 * x_MAX;
        centerOfLaser.y = 10 * y_MAX;
    }
}