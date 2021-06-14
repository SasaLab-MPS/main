/*=====================================================================
  calScangPath.cpp   
  Yota INOUE (2021) 
  走査パターンを計算
  Last update: June 3, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void calScanPath(string strategy, double length)
{
    /* レーザの中心座標を返すようにした方が良いか? */
    cout << "call calScanPath" << endl;

    double travelDistance = Time * SCAN_SPEED;      // 合計の走査距離
    double hatch = SCAN_PITCH;
    int totalRepetition = travelDistance / length;  // レーザが折り返した総数
    

    if (strategy == "Island")
    {
        int numOfLine = length/hatch;       // アイランド内のライン本数
        int Lx = x_MAX / length;   // Lx: x方向一列のブロック数, Ly: y方向一列のブロック数
        //int nX = Ix, nY = Iy * nX;
        int scanBlocks = totalRepetition / numOfLine;   // 走査済みのアイランド数
        int low = scanBlocks / Lx;          // 走査済みの列数
        int n = scanBlocks - low * Lx;      // その列での走査済みのブロック数

        double x, y;    // 基準座標，そのアイランドの左下を基準座標にする

        x = (double)n * length;
        y = (double)low * length;

        if (n%2 == 0)   
        {
            /* 偶数ならx方向 */
            // そのアイランドでの走査済み本数
            int ix = totalRepetition - scanBlocks * numOfLine;
            double lx;      // x = x + lx みたいにしたい
            lx = travelDistance - (double)totalRepetition * length;

            if (ix%2 == 0)
            {
                /* 偶数なら左方向に走査 */
                x = x + lx;
            }
            else
            {
                /* 奇数なら右方向に走査 */
                x = x + length - lx;
            }
            y = y + ix * hatch;
            
        }
        else
        {
            /* 奇数ならy方向 */
            int iy = totalRepetition - scanBlocks * numOfLine;
            double ly; 
            ly = travelDistance - (double)totalRepetition * length;

            if (iy % 2 == 0)
            {
                /* 偶数なら上方向に走査 */
                y = y + ly;
            }
            else
            {
                /* 奇数なら下方向に走査 */
                y = y + length - ly;
            }
            x = x + iy * hatch;
        }

        centerOfLaser.x = x;
        centerOfLaser.y = y;
        centerOfLaser.z = z_MAX;
    }
    else if (strategy == "Stripe") {
        int ny; // y 方向に繰り返せる最大数

        int k, l;
        double Y = y_MAX;

        ny = Y / hatch;
        l = totalRepetition / ny;       // 短冊の総数
        k = totalRepetition - l * ny;   // そのストライプの中でレーザが行き来した回数
        
        /* レーザの中心座標の計算 */
        double tx = travelDistance - (double)totalRepetition * length;
        double ty = (double)k * hatch;
        // x 座標の計算
        if (k % 2 == 1) {
            centerOfLaser.x = (double)(l+1) * length - tx;
        } else {
            centerOfLaser.x = (double)l * length + tx;
        }
        // y 座標の計算
        if (tx > 0 && tx < Y) {
            centerOfLaser.y = ty + hatch;
        } else {
            centerOfLaser.y = ty;
        }
        
        centerOfLaser.z = z_MAX;
    }
    else {
        /* code */
    }
}