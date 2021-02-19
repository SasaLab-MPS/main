#include "inputs.hpp"
#include "functions.hpp"

// バケット構造を生成する関数
void AlcBkt(void)
{
    r = PCL_DST * 2.1; //影響半径
    r2 = r * r;
    DB = r * (1.0 + CRT_NUM); // バケット1辺の長さ，クーラン数だけ広げている
    DB2 = DB * DB;
    DBinv = 1.0 / DB;
    // バケットを外側に広げることで常に27個のバケットで計算する．条件分岐を減らすテクニック
    nBx = (int)((MAX_X - MIN_X) * DBinv) + 3; //解析領域内のx方向のバケット数
    nBy = (int)((MAX_Y - MIN_Y) * DBinv) + 3; //解析領域内のy方向のバケット数
    nBz = (int)((MAX_Z - MIN_Z) * DBinv) + 3; //解析領域内のz方向のバケット数
    nBxy = nBx * nBy;
    nBxyz = nBx * nBy * nBz; //解析領域内のバケット数
    printf("nBx:%d  nBy:%d  nBz:%d  nBxy:%d  nBxyz:%d\n", nBx, nBy, nBz, nBxy, nBxyz);
    bfst = (int *)malloc(sizeof(int) * nBxyz); //バケットに格納された先頭の粒子番号
    blst = (int *)malloc(sizeof(int) * nBxyz); //バケットに格納された最後尾の粒子番号
    nxt = (int *)malloc(sizeof(int) * nP);     //同じバケット内の次の粒子番号
}
