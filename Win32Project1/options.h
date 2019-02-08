#pragma once
#include <Windows.h>
#pragma comment(lib, "msimg32.lib")

//플레이어
#define PlayerHPMAX 500
#define Player_speed 3
#define Player_limit_left 140
#define Player_limit_right 4500
#define Animation_speed 1
#define state_walk 5
#define heavy_cool 9
#define state_jump 25
#define check 5
#define missile_count 30

#define setstate_stand 0
#define setstate_walk 1
#define setstate_jump 2
#define setstate_shot 3
#define setstate_duck 4
#define setstate_knife 5
#define setstate_granade 6
#define setstate_dead 8

#define Player_right_coll 50
#define Player_down_coll 50

#define mp_regen 0.2;
#define jumpdec_speed 0
#define player_dmg 20

#define fireball_cooltime 3
#define fireball_regen -20
#define fireball_speed 40

#define windcut_cooltime 80
#define windcut_cost 200
#define windcut_speed 50


#define tornado_time 50
#define tornado_cooltime 600
#define tornado_cost 200
#define tornado_dmg 5
#define tornado_final_dmg 100

#define buff_time 150
#define buff_regen 1
#define buff_cooltime 800
//몬스터

#define boss_max_hp 1500
#define boss_dmg 200

#define monster_right_coll 50
#define moster_down_coll 50


#define boss_dash_speed 20

//카메라
#define Camera_min_speed 1
#define Camera_max_speed 10
#define Camera_distance 20
#define Camera_max_object 50
#define Camera_high 80
//투사체
#define bloodfield_dmg 10
#define bloodcoil_dmg 10
#define bloodfield_time 200
#define bloodcoil_time 200
#define bloodcoil_regen 20
#define boss_hit 70
#define missile_speed 10
#define missile_deacttimer 30
#define missile_shotgunrange 2

//유닛
#define max_jumpcount 1
#define Unit_limit_left 500
#define Unit_limit_right 4500
#define Unit_angle_speed 10
#define PI 3.1415926535

#define Unit_right_coll 50
#define Unit_down_coll 50

//월드
#define gravity_speed 0.5
#define gravity_max 2
#define jumppower 6
#define mapsizeX 200
#define mapsizeY 144
#define cmapsizeX 100
#define cmapsizeY 72
#define mapMaxsizeX 5000
#define mapMaxsizeY 720
#define screensizeX 1000
#define screensizeY 720
#define FPS 60
#define Unit_Max_Count 100