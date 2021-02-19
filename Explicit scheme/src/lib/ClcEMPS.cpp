#include "inputs.hpp"
#include "functions.hpp"

void ClcEMPS(void)
{
    while (1)
    {
        if (iLP % 100 == 0)     // 100回に一回計算ログを出力
        {
            int p_num = 0;
            for (int i = 0; i < nP; i++)
            {
                if (Typ[i] != GST)  // ゴースト粒子で無ければカウント
                    p_num++;
            }
            printf("%5d th TIM: %lf / p_num: %d\n", iLP, TIM, p_num);
        }
        if (iLP % OPT_FQC == 0) // ファイルの出力頻度を決める
        {
            WrtDat();           // ファイルを出力
            if (TIM >= FIN_TIM) // 設定時間を超えたら終了
            {
                break;
            }
        }
        MkBkt();        // バケットに粒子を格納
        VscTrm();       // 粘性項と重力から仮の加速度を計算
        UpPcl1();       // 粒子の仮の位置と速度を計算
        ChkCol();       // 粒子の剛体衝突計算
        MkPrs();        // 仮の圧力を計算
        PrsGrdTrm();    // 圧力勾配から加速度の修正量を計算
        UpPcl2();       // 加速度の修正量から位置と速度を決定
        MkPrs();        // 圧力を決定
        for (int i = 0; i < nP; i++)
        {
            pav[i] += Prs[i];
        }
        iLP++;
        TIM += DT;
    }
}
