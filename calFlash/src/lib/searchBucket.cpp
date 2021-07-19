/*=====================================================================
  searchBkt.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  対象粒子の周辺にある粒子を探索するプログラム
  Last update: Feb 21, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void searchBucket(int i) {
  int particleID;
  int id;   // バケットのid
  neghPar.clear(); // 要素の全削除
  /* バケット法による粒子の探索効率向上 */
  // 粒子iの所属するバケットのid
  int bktid[3];   // 0:x, 1:y, 2:z
  double MIN[3];  // 領域の最小値
  for (int j = 0; j < 3; j++) {
    MIN[j] = Pos_MIN[j] - PARTICLE_DISTANCE * 4;
  }

  bktid[0] = (int)((particle[i].x - MIN[0]) * DBinv) + 1;
  bktid[1] = (int)((particle[i].y - MIN[1]) * DBinv) + 1;
  bktid[2] = (int)((particle[i].z - MIN[2]) * DBinv) + 1;

  // 対象粒子i周辺の粒子をバケット法により探索 3*3*3=27
  for (int jz = bktid[2] - 1; jz <= bktid[2] + 1; jz++) {
    for (int jy = bktid[1] - 1; jy <= bktid[1] + 1; jy++) {
      for (int jx = bktid[0] - 1; jx <= bktid[0] + 1; jx++) {
        // バケットのidを計算, 2次元のときnBxy = 0としている
        id = jz * nBxy + jy * nBx + jx;
        for (int j = 0; j < (int)bucket[id].size(); j++) {
          particleID = bucket[id][j];
          neghPar.emplace_back(particleID);
        }
      }
    }
  }

  // 重複を削除
  sort(neghPar.begin(), neghPar.end());
  neghPar.erase(unique(neghPar.begin(), neghPar.end()), neghPar.end());
}