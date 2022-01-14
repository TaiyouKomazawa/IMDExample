/**
 * @file motor_drive.cpp
 * @author Taiyou Komazawa (taiyou24690@gmail.com)
 * @brief モータを指定速度で動かす例
 * @version 0.1
 * @date 2022-01-14
 * 
 */

#include <stdio.h>

#include "IMDController/IMDController.hpp"

#define ENC_CPR     64 	    //count per revolution
#define GEAR_RATIO  50.0 	//50:1 gear ratio
#define MAX_RPS     3.333   //output max speed [rps] (200rpm)

/* MCP2210のシリアルナンバーとチップセレクトを指定して宣言 */
IMDController md(L"0001312251", MCP2210Linux::GP0);
/* モータパラメータを入れる構造体を宣言 */
IMDController::motor_param_t p[2];

int main()
{
    /* モータやエンコーダに合わせて指定する。 */
    p[0].encoder_cpr = ENC_CPR;     //エンコーダのCPR
    p[0].gear_ratio = GEAR_RATIO;   //ギア比
    p[0].max_rps = MAX_RPS;         //指定速度最大値
    p[0].dir_reverse = true;        //モータの回転方向
    /* モータの速度特性に合わせて係数は任意で調整する */
    p[0].vel.kp = 0.38;
    p[0].vel.ki = 0.3;
    p[0].vel.kd = 0.00001;
    /* モータのトルク特性に合わせて係数は任意で調整する */
    p[0].cur.kp = 0.1;
    p[0].cur.ki = 0.0;
    p[0].cur.kd = 0.00001;

    p[1] = p[0];    //接続されたモータの仕様は同じなのでコピー
    /* 制御開始 */
    md.ctrl_begin(p);

    while(1){
        /** モータの目標速度を指定する
         * @note 扱われている速度の単位が回転毎秒であることに注意
         */
        float m1_speed = 15 / 360.0; //15 deg/s
        float m2_speed = -45 / 360.0; //-45 deg/s
        md.set_speed(IMDController::M1, m1_speed);
        md.set_speed(IMDController::M2, m2_speed);

        if(md.state_updated()){ //もし状態が更新されたら
            /** 現在の状態を示す
             * @note 扱われている速度の単位が回転毎秒であるので度に単位変換している
             */
            printf("[%d] M1: %6.2f deg, %2.3f deg/s, %4d mA\tM2: %6.2f deg, %2.3f deg/s, %4d mA\n",
            md.get_state().frame_id,
            md.get_state().angle[IMDController::M1] * 360,
            md.get_state().velocity[IMDController::M1] * 360,
            md.get_state().current[IMDController::M1],
            md.get_state().angle[IMDController::M2] * 360,
            md.get_state().velocity[IMDController::M2] * 360,
            md.get_state().current[IMDController::M2]);
        }
        /** データを更新(受送信が行われる) 
         * @note データの更新は必ずループ内で行うこと
         */
        md.update();
        /* 10ミリ秒待つことを推奨(IMDの受信が追いつかないため) */
        usleep(10000);
    }

    return 0;
}
