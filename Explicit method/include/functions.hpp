
//#include "functions.hpp"
#ifndef FUNCTIONS_HPP_20210215_160510_
#define FUNCTIONS_HPP_20210215_160510_
#include "inputs.hpp"

/* 関数定義 */
void RdDat(void);           // 入力ファイルを読み込む関数
void ChkPcl(int i);         // 解析領域から出た粒子を計算対象外にする関数
void WrtDat(void);          // 計算結果をファイルに出力する関数
void AlcBkt(void);          // バケット構造を生成する関数
void SetPara(void);         // 初期パラメータを計算する関数
void MkBkt(void);           // バケット構造を更新する関数
void VscTrm(void);          // 粘性項を計算する関数
void UpPcl1(void);          // 仮の位置と速度を計算する関数
void ChkCol(void);          // 接触反発計算を行う関数
void MkPrs(void);           // 仮の圧力を求める関数
void PrsGrdTrm(void);       // 圧力勾配を計算する関数
void UpPcl2(void);          // 加速度の修正量から位置と速度を求める関数
void ClcEMPS(void);         // シミュレーションの中心となる時間発展計算するための関数
double get_dtime(void);     // 計算時間を測る関数

#endif // FUNCTIONS_HPP_20210215_160510_