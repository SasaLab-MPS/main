/*=====================================================================
  structBkt.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  解析領域にバケット領域を生成する関数
  Last update: Feb 10, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

double DB, DB2, DBinv;            // バケット一辺の長さ，その二乗，逆数
int nBx, nBy, nBz, nBxy, nBxyz;   // x, y, z方向のバケット数とその積
double re, re2;                   // 影響半径，影響半径の二乗
vector<vector<int>> bkt;          // バケットid，structBktで定義
vector<int> Pid;                  // 粒子が所属するバケット番号

void structBkt(void) {
  re = 2.1 * PARTICLE_DISTANCE; // 影響半径を初期粒子間距離の2.1倍とする
  re2 = re * re;
  DB = re * (1.0 + CRT_NUM); // バケット一辺の長さ
  DB2 = DB * DB;
  DBinv = 1.0 / DB;

  // バケット数を計算
  double MAX[3];                          //バケットを構築する最大座標
  MAX[0] = x_MAX + PARTICLE_DISTANCE * 3; // x座標
  MAX[1] = y_MAX + PARTICLE_DISTANCE * 3; // y座標
  MAX[2] = z_MAX + PARTICLE_DISTANCE * 3; // z座標
  x_MIN = 0.0 - PARTICLE_DISTANCE * 3;
  y_MIN = 0.0 - PARTICLE_DISTANCE * 3;
  z_MIN = 0.0 - PARTICLE_DISTANCE * 3;

  nBx = (int)((MAX[0] - x_MIN) * DBinv) + 3; // 解析領域のx方向のバケット数
  nBy = (int)((MAX[1] - y_MIN) * DBinv) + 3; // 解析領域のy方向のバケット数
  nBz = (int)((MAX[2] - z_MIN) * DBinv) + 3; // 解析領域のz方向のバケット数

  nBxy = nBx * nBy;
  nBxyz = nBx * nBy * nBz;

  // バケットの総数
  int bkts; 
  if (DIM == 2)
  {
    bkts = nBxy;
  }
  else
  {
    bkts = nBxyz;
  }

  // バケットリストの作成
  bkt.resize(bkts);
  Pid.resize(NumberOfParticles);
  // 全てのバケットを-1:粒子が無い状態に
  fill(bkt.begin(), bkt.end(), -1);
  fill(Pid.begin(), Pid.end(), -1);
}