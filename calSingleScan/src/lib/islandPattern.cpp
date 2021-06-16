/*=====================================================================
  islandPattern.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  アイランドスキャンのレーザ照射点を計算
  Last update: June 13, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void islandPattern(void) {

    double travelDistance = Time * SCAN_SPEED; // 合計の走査距離
    double hatch = SCAN_PITCH;
    double scanVectorLength = SCAN_VECTOR_LENGTH;
    int totalRepetition = travelDistance / scanVectorLength; // レーザが折り返した総数

    int numOfLine = scanVectorLength / hatch; // アイランド内のライン本数
    int Lx = x_MAX / scanVectorLength;        // Lx: x方向一列のブロック数, Ly: y方向一列のブロック数
    //int nX = Ix, nY = Iy * nX;
    int scanBlocks = totalRepetition / numOfLine; // 走査済みのアイランド数
    int low = scanBlocks / Lx;                    // 走査済みの列数
    int n = scanBlocks - low * Lx;                // その列での走査済みのブロック数

    double x, y; // 基準座標，そのアイランドの左下を基準座標にする

    x = (double)n * scanVectorLength;
    y = (double)low * scanVectorLength;

    if (n % 2 == 0)
    {
        /* 偶数ならx方向 */
        // そのアイランドでの走査済み本数
        int ix = totalRepetition - scanBlocks * numOfLine;
        double lx; // x = x + lx みたいにしたい
        lx = travelDistance - (double)totalRepetition * scanVectorLength;

        if (ix % 2 == 0)
        {
            /* 偶数なら左方向に走査 */
            x = x + lx;
        }
        else
        {
            /* 奇数なら右方向に走査 */
            x = x + scanVectorLength - lx;
        }
        y = y + ix * hatch;
    }
    else
    {
        /* 奇数ならy方向 */
        int iy = totalRepetition - scanBlocks * numOfLine;
        double ly;
        ly = travelDistance - (double)totalRepetition * scanVectorLength;

        if (iy % 2 == 0)
        {
            /* 偶数なら上方向に走査 */
            y = y + ly;
        }
        else
        {
            /* 奇数なら下方向に走査 */
            y = y + scanVectorLength - ly;
        }
        x = x + iy * hatch;
    }

    centerOfLaser.x = x;
    centerOfLaser.y = y;
}