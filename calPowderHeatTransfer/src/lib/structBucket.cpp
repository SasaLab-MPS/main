/*=====================================================================
  structBkt.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  解析領域にバケット領域を生成する関数
  Last update: Feb 10, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/constants.hpp"

void structBucket(void)
{
    double reB = 3.3 * PARTICLE_DISTANCE;    
    DB = reB * (1.0 + CRT_NUM);             // バケット一辺の長さ
    DB2 = DB * DB;
    DBinv = 1.0 / DB;
    // バケット数を計算
    double MAX[3], MIN[3];                  //バケットを構築する最大座標
    MAX[0] = x_MAX + PARTICLE_DISTANCE * 4; // x座標
    MAX[1] = y_MAX + PARTICLE_DISTANCE * 4; // y座標
    MAX[2] = z_MAX + PARTICLE_DISTANCE * 4; // z座標
    for (int i = 0; i < 3; i++) {
        MIN[i] = Pos_MIN[i] - PARTICLE_DISTANCE * 4;
    }

    nBx = (int)((MAX[0] - MIN[0]) * DBinv) + 3; // 解析領域のx方向のバケット数
    nBy = (int)((MAX[1] - MIN[1]) * DBinv) + 3; // 解析領域のy方向のバケット数
    nBz = (int)((MAX[2] - MIN[2]) * DBinv) + 3; // 解析領域のz方向のバケット数

    nBxy = nBx * nBy;
    nBxyz = nBx * nBy * nBz;

    // バケットの総数
    if (DIM == 2) {
        buckets = nBxy;
        nBxy = 0;
    } else {
        buckets = nBxyz;
    }
    // バケットリストの作成，初期化はcalBucketで実行
}