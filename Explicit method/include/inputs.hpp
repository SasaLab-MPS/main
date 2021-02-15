
//#include "inputs.hpp"
#ifndef INPUTS_HPP_20210215_160210_
#define INPUTS_HPP_20210215_160210_

#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;

/* 変数定義 */
#define IN_FILE "../mk_particle/dambreak.prof"
#define PCL_DST 0.02               //平均粒子間距離
#define MIN_X (0.0 - PCL_DST * 3)  //解析領域のx方向の最小値
#define MIN_Y (0.0 - PCL_DST * 3)  //解析領域のy方向の最小値
#define MIN_Z (0.0 - PCL_DST * 3)  //解析領域のz方向の最小値
#define MAX_X (1.0 + PCL_DST * 3)  //解析領域のx方向の最大値
#define MAX_Y (0.2 + PCL_DST * 3)  //解析領域のy方向の最大値
#define MAX_Z (0.6 + PCL_DST * 30) //解析領域のz方向の最大値

#define GST -1                            //計算対象外粒子の種類番号
#define FLD 0                             //流体粒子の種類番号
#define WLL 1                             //壁粒子の種類番号
#define NUM_TYP 2                         //粒子の種類数
#define DNS_FLD 1000                      //流体粒子の密度
#define DNS_WLL 1000                      //壁粒子の密度
#define DT 0.0005                         //時間刻み幅
#define FIN_TIM 1.0                       //時間の上限
#define SND 22.0                          //音速
#define OPT_FQC 100                       //出力間隔を決める反復数
#define KNM_VSC 0.000001                  //動粘性係数
#define DIM 3                             //次元数
#define CRT_NUM 0.1                       //クーラン条件数
#define COL_RAT 0.2                       //接近した粒子の反発率
#define DST_LMT_RAT 0.9                   //これ以上の粒子間の接近を許さない距離の係数
#define G_X 0.0                           //重力加速度のx成分
#define G_Y 0.0                           //重力加速度のy成分
#define G_Z -9.8                          //重力加速度のz成分
#define WEI(dist, re) ((re / dist) - 1.0) //重み関数

/* グローバル変数定義 */
extern FILE *fp;
extern char filename[256];
extern int iLP, iF;
extern double TIM;
extern int nP;
extern double *Acc, *Pos, *Vel, *Prs, *pav;
extern int *Typ;
extern double r, r2;
extern double DB, DB2, DBinv;
extern int nBx, nBy, nBz, nBxy, nBxyz;
extern int *bfst, *blst, *nxt;
extern double n0, lmd, A1, A2, A3, rlim, rlim2, COL;
extern double Dns[NUM_TYP], invDns[NUM_TYP];

#endif // INPUTS_HPP_20210215_160210_