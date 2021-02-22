/*=====================================================================
  searchBkt.cpp   
  Yota INOUE (2021) 
  関数実装ファイル 
  NS方程式右辺第二項を計算
  Last update: Feb 21, 2021
=======================================================================*/
#include "../../include/functions.hpp"
#include "../../include/inputs.hpp"

void searchBkt(int i) {
  int particle;
  neghPar.clear(); // 要素の全削除
  /* バケット法による粒子の探索効率向上 */
  // 粒子iの所属するバケットのid
  int bktid[3]; // 0:x, 1:y, 2:z
  bktid[0] = (int)((position[i].x - Pos_MIN[0]) * DBinv) + 1;
  bktid[1] = (int)((position[i].y - Pos_MIN[1]) * DBinv) + 1;
  bktid[2] = (int)((position[i].z - Pos_MIN[2]) * DBinv) + 1;

  // 対象のバケット周辺の粒子のみを探索 3*3*3=27
  for (int jz = bktid[2] - 1; jz <= bktid[2] + 1; jz++) {
    for (int jy = bktid[1] - 1; jy <= bktid[1] + 1; jy++) {
      for (int jx = bktid[0] - 1; jx <= bktid[0] + 1; jx++) {
        // バケットのidを計算, 2次元のときnBxy = 0としている
        int id = jz * nBxy + jy * nBx + jx;
        if (bkt[id][0] == -1) // バケット内に粒子が存在しない
        {
          continue;
        }
        for(int k = 0; k < bkt[id].size(); k++) {
          particle = bkt[id][k];
          neghPar.push_back(particle);
        }
      }
    }
  }

}