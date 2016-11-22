#include "enemy_sprites.h"

unsigned char isBlocked(unsigned char x, unsigned char y){
    if((x>122 && x<134 && y > 114 && y < 125))
    {
        return 1;
    }
    if(x<128){
        if(y<120){
            return collision_top_left[(x>>3)+((y>>3)<<4)];
        }else{
            y-=120;
            return collision_bottom_left[(x>>3)+((y>>3)<<4)];
        }
    }else{
        x -= 128;
        if(y<120){
            return collision_top_right[(x>>3)+((y>>3)<<4)];
        }else{
            y-=120;
            return collision_bottom_right[(x>>3)+((y>>3)<<4)];
        }
    }
}

void __fastcall__ took_damage(void)
{
	#define DAMAGE_POSITION_X temp0
	#define DAMAGE_POSITION_Y temp1
    
	#define DAMAGE_W temp6
	#define DAMAGE_H temp7
    
	#define ENEMY_POSITION_X temp2
	#define ENEMY_POSITION_Y temp3
	#define DAMAGE_DIFF_X temp4
	#define DAMAGE_DIFF_Y temp5
    
	#define k temp5

	for(j=0; j<8; ++j)
	{
		if(enemies_health[j] == 0)
		{
			continue;
		}

		ENEMY_POSITION_X = enemies_x[j];
		ENEMY_POSITION_Y = enemies_y[j];

		if(DAMAGE_POSITION_X > ENEMY_POSITION_X)
		{
			DAMAGE_DIFF_X = DAMAGE_POSITION_X - ENEMY_POSITION_X;
		}
		else
		{
			DAMAGE_DIFF_X = ENEMY_POSITION_X - DAMAGE_POSITION_X;
		}

		if(DAMAGE_POSITION_Y > ENEMY_POSITION_Y)
		{
			DAMAGE_DIFF_Y = DAMAGE_POSITION_Y - ENEMY_POSITION_Y;
		}
		else
		{
			DAMAGE_DIFF_Y = ENEMY_POSITION_Y - DAMAGE_POSITION_Y;
		}

		if((DAMAGE_DIFF_X < DAMAGE_W) && (DAMAGE_DIFF_Y < DAMAGE_H))
		{
			enemies_health[j]--;
            if(enemies_health[j])
            {
                enemy_push_timer[j] = 4;
                enemy_push_dir[j] = player_dir[i];
            }
			else
			{
				// Killed enemy SFX
				sfx_play(1, 0);
			}
			break;
		}
	}
}

void __fastcall__ tick_enemies(void)
{
	#define SELECTED_AXIS temp0
	#define SELECTED_PLAYER temp1
	#define SELECTED_ENEMY temp2
	#define SELECTED_DIRECTION temp3
	#define SELECTED_SPAWN_POINT temp4
	#define COLLISION_RESULT temp5
	#define DIRECTION_RANDOMNESS temp6
	#define DIFF_X stemp0
	#define DIFF_Y stemp1
	
	SELECTED_SPAWN_POINT = rand8() & 7;

	for(i=0; i<8; ++i)
    {
		if(enemies_health[i] == 0 && (frame&7) == i)
		{
            enemy_attack_timer[i] = 60;
			enemies_x[i] = enemy_spawn_points_x[SELECTED_SPAWN_POINT];
			enemies_y[i] = enemy_spawn_points_y[SELECTED_SPAWN_POINT];
            enemy_push_timer[i] = 0;
            enemies_health[i] = spawn_hp;
			enemies_type[i] = (i&1);
			return;
		}
	}
    
	SELECTED_ENEMY = frame & 7;
    enemy_leg[SELECTED_ENEMY] = 1-enemy_leg[SELECTED_ENEMY];
	SELECTED_PLAYER = enemies_enemy[SELECTED_ENEMY];

	// Decide on the direction
	DIRECTION_RANDOMNESS = rand8() & 3;
    if(DIRECTION_RANDOMNESS == 0)
	{
		DIRECTION_RANDOMNESS = rand8() & 3;
		switch(DIRECTION_RANDOMNESS)
		{
		case 0:
			SELECTED_DIRECTION = PAD_LEFT;
			break;
		case 1:
			SELECTED_DIRECTION = PAD_RIGHT;
			break;
		case 2:
			SELECTED_DIRECTION = PAD_UP;
			break;
		case 3:
			SELECTED_DIRECTION = PAD_DOWN;
			break;
		default:
			SELECTED_DIRECTION = PAD_LEFT;
		}
		
	}
	else if(DIRECTION_RANDOMNESS == 1)
	{
		SELECTED_DIRECTION = enemies_dir[SELECTED_ENEMY];
	}
	else
	{
		SELECTED_AXIS = rand8() & 1;
		if(SELECTED_AXIS)
		{
			if(enemies_x[SELECTED_ENEMY] > player_x[SELECTED_PLAYER])
			{
				SELECTED_DIRECTION = PAD_LEFT;
			}
			else
			{
				SELECTED_DIRECTION = PAD_RIGHT;
			}
		}
		else
		{
			if(enemies_y[SELECTED_ENEMY] > player_y[SELECTED_PLAYER])
			{
				SELECTED_DIRECTION = PAD_UP;
			}
			else
			{
				SELECTED_DIRECTION = PAD_DOWN;
    		}
		}
	}
	
    enemies_dir[SELECTED_ENEMY] = SELECTED_DIRECTION; 
    temp6 = enemies_x[SELECTED_ENEMY];
    temp7 = enemies_y[SELECTED_ENEMY];
    
    if(enemy_push_timer[SELECTED_ENEMY])
    {
    }
    else if(SELECTED_DIRECTION == PAD_RIGHT)
    {
		enemies_x[SELECTED_ENEMY] += enemy_speed;
    }
    else if(SELECTED_DIRECTION == PAD_LEFT)
    {
		enemies_x[SELECTED_ENEMY] -= enemy_speed;
    }
    else if(SELECTED_DIRECTION == PAD_UP)
    {
		enemies_y[SELECTED_ENEMY] -= enemy_speed;
    }
    else if(SELECTED_DIRECTION == PAD_DOWN)
    {
		enemies_y[SELECTED_ENEMY] += enemy_speed;
    }
    
	// Check collisions with level
	COLLISION_RESULT = isBlocked(enemies_x[SELECTED_ENEMY], enemies_y[SELECTED_ENEMY]);
    
    if(COLLISION_RESULT)
    {
        enemies_x[SELECTED_ENEMY] = temp6;
        enemies_y[SELECTED_ENEMY] = temp7;
    }
    else
    {
        // Check collisions with other enemies
        for(i=0; i<8; ++i)
        {
            if(SELECTED_ENEMY == i)
                continue;
    
            if(enemies_x[i] - 6 < enemies_x[SELECTED_ENEMY] && enemies_x[i] + 6 > enemies_x[SELECTED_ENEMY])
            {
                if(enemies_y[i] - 6 < enemies_y[SELECTED_ENEMY] && enemies_y[i] + 6 > enemies_y[SELECTED_ENEMY])
                {
                    enemies_x[SELECTED_ENEMY] = temp6;
                    enemies_y[SELECTED_ENEMY] = temp7;
                }
            }
        }
    }


	// Draw
    for(i=0; i<8; ++i)
    {
        if(enemy_push_timer[i] && (frame&3))
        {
            if(frame&1)
            {
                enemy_push_timer[i]--;
                temp6 = enemies_x[i];
                temp7 = enemies_y[i];
                switch(enemy_push_dir[i])
                {
                    case PAD_LEFT:
                        enemies_x[i]-=2;
                        break;
                    case PAD_RIGHT:
                        enemies_x[i]+=2;
                        break;
                    case PAD_UP:
                        enemies_y[i]-=2;
                        break;
                    case PAD_DOWN:
                        enemies_y[i]+=2;
                        break;
                }
                if(isBlocked(enemies_x[i], enemies_y[i]))
                {
                    enemies_x[i] = temp6;
                    enemies_y[i] = temp7;
                }
            }
           
        }
        
        
        COLLISION_RESULT = 0;
        if(enemy_attack_timer[i])
        {
            --enemy_attack_timer[i];
        }
        else
        {
            for(j=0; j<2; j++){
                if(enemies_x[i] - 5 < player_x[j] && enemies_x[i] + 5 > player_x[j])
                {
                    if(enemies_y[i] - 5 < player_y[j] && enemies_y[i] + 5 > player_y[j])
                    {
                        if(player_hp[j] && player_god_mode[j] == 0)
						{
                            COLLISION_RESULT = 1;
                            player_hp[j]--;
                            player_god_mode[j] = 4;
							
							// Took Damage SFX
							sfx_play(0, 1);
                            enemy_attack_timer[i] = enemy_damage_modifier;
                        }
                        if(player_hp[j] == 0 && enemies_enemy[i] == j){
                            enemies_enemy[i] = 1-enemies_enemy[i];
                        }
                    }
                }
            }
        }
        
        int_temp0 = enemies_x[i];
        int_temp0 <<= 1;
        int_temp0 -= scr_x;
        
        if(int_temp0 > 255)
			continue;

        temp0 = int_temp0;
        
        int_temp0 = enemies_y[i];
        int_temp0 <<= 1;
        int_temp0 -= scr_y;
        
        if(int_temp0 > 255)
			continue;
        
		temp1 = int_temp0;
        if(enemy_push_timer[i]&1)
        {       
            if(COLLISION_RESULT)
            {
				if(enemies_type[i] == 0)
				{
					switch(enemies_dir[i])
					{
						default:
						case PAD_UP:
							spr = oam_meta_spr(temp0, temp1-2, spr, spider_damaged_attack_up);
						break;
						case PAD_DOWN:
							spr = oam_meta_spr(temp0, temp1+2, spr, spider_damaged_attack_down);
						break;
						case PAD_LEFT:
							spr = oam_meta_spr(temp0-2, temp1, spr, spider_damaged_attack_left);
						break;
						case PAD_RIGHT:
							spr = oam_meta_spr(temp0+2, temp1, spr, spider_damaged_attack_right);
						break;
					}
				}
				else
				{
					switch(enemies_dir[i])
					{
						default:
						case PAD_UP:
							spr = oam_meta_spr(temp0, temp1-2, spr, bat_damaged_attack_up);
						break;
						case PAD_DOWN:
							spr = oam_meta_spr(temp0, temp1+2, spr, bat_damaged_attack_down);
						break;
						case PAD_LEFT:
							spr = oam_meta_spr(temp0-2, temp1, spr, bat_damaged_attack_left);
						break;
						case PAD_RIGHT:
							spr = oam_meta_spr(temp0+2, temp1, spr, bat_damaged_attack_right);
						break;
					}
				}
            }
            else
            {
                if(enemy_leg[i])
                {
					if(enemies_type[i] == 0)
					{
						switch(enemies_dir[i])
						{
							default:
							case PAD_UP:
								spr = oam_meta_spr(temp0, temp1, spr, spider_damaged_leg_0_up);
							break;
							case PAD_DOWN:
								spr = oam_meta_spr(temp0, temp1, spr, spider_damaged_leg_0_down);
							break;
							case PAD_LEFT:
								spr = oam_meta_spr(temp0, temp1, spr, spider_damaged_leg_0_left);
							break;
							case PAD_RIGHT:
								spr = oam_meta_spr(temp0, temp1, spr, spider_damaged_leg_0_right);
							break;
						}
					}
					else
					{
						switch(enemies_dir[i])
						{
							default:
							case PAD_UP:
								spr = oam_meta_spr(temp0, temp1, spr, bat_damaged_leg_0_up);
							break;
							case PAD_DOWN:
								spr = oam_meta_spr(temp0, temp1, spr, bat_damaged_leg_0_down);
							break;
							case PAD_LEFT:
								spr = oam_meta_spr(temp0, temp1, spr, bat_damaged_leg_0_left);
							break;
							case PAD_RIGHT:
								spr = oam_meta_spr(temp0, temp1, spr, bat_damaged_leg_0_right);
							break;
						}
					}
                }
                else
                {
					if(enemies_type[i] == 0)
					{
						switch(enemies_dir[i])
						{
							default:
							case PAD_UP:
								spr = oam_meta_spr(temp0, temp1, spr, spider_damaged_leg_1_up);
							break;
							case PAD_DOWN:
								spr = oam_meta_spr(temp0, temp1, spr, spider_damaged_leg_1_down);
							break;
							case PAD_LEFT:
								spr = oam_meta_spr(temp0, temp1, spr, spider_damaged_leg_1_left);
							break;
							case PAD_RIGHT:
								spr = oam_meta_spr(temp0, temp1, spr, spider_damaged_leg_1_right);
							break;
						}
					}
					else
					{
						switch(enemies_dir[i])
						{
							default:
							case PAD_UP:
								spr = oam_meta_spr(temp0, temp1, spr, bat_damaged_leg_1_up);
							break;
							case PAD_DOWN:
								spr = oam_meta_spr(temp0, temp1, spr, bat_damaged_leg_1_down);
							break;
							case PAD_LEFT:
								spr = oam_meta_spr(temp0, temp1, spr, bat_damaged_leg_1_left);
							break;
							case PAD_RIGHT:
								spr = oam_meta_spr(temp0, temp1, spr, bat_damaged_leg_1_right);
							break;
						}
					}
                }
            }
        }
        else
        {
            if(COLLISION_RESULT)
            {
				if(enemies_type[i] == 0)
				{
					switch(enemies_dir[i])
					{
						default:
						case PAD_UP:
							spr = oam_meta_spr(temp0, temp1-2, spr, spider_attack_up);
						break;
						case PAD_DOWN:
							spr = oam_meta_spr(temp0, temp1+2, spr, spider_attack_down);
						break;
						case PAD_LEFT:
							spr = oam_meta_spr(temp0-2, temp1, spr, spider_attack_left);
						break;
						case PAD_RIGHT:
							spr = oam_meta_spr(temp0+2, temp1, spr, spider_attack_right);
						break;
					}
				}
				else
				{
					switch(enemies_dir[i])
					{
						default:
						case PAD_UP:
							spr = oam_meta_spr(temp0, temp1-2, spr, bat_attack_up);
						break;
						case PAD_DOWN:
							spr = oam_meta_spr(temp0, temp1+2, spr, bat_attack_down);
						break;
						case PAD_LEFT:
							spr = oam_meta_spr(temp0-2, temp1, spr, bat_attack_left);
						break;
						case PAD_RIGHT:
							spr = oam_meta_spr(temp0+2, temp1, spr, bat_attack_right);
						break;
					}
				}
            }
            else
            {
                if(enemy_leg[i])
                {
					if(enemies_type[i] == 0)
					{
						switch(enemies_dir[i])
						{
							default:
							case PAD_UP:
								spr = oam_meta_spr(temp0, temp1, spr, spider_leg_0_up);
							break;
							case PAD_DOWN:
								spr = oam_meta_spr(temp0, temp1, spr, spider_leg_0_down);
							break;
							case PAD_LEFT:
								spr = oam_meta_spr(temp0, temp1, spr, spider_leg_0_left);
							break;
							case PAD_RIGHT:
								spr = oam_meta_spr(temp0, temp1, spr, spider_leg_0_right);
							break;
						}
					}
					else
					{
						switch(enemies_dir[i])
						{
							default:
							case PAD_UP:
								spr = oam_meta_spr(temp0, temp1, spr, bat_leg_0_up);
							break;
							case PAD_DOWN:
								spr = oam_meta_spr(temp0, temp1, spr, bat_leg_0_down);
							break;
							case PAD_LEFT:
								spr = oam_meta_spr(temp0, temp1, spr, bat_leg_0_left);
							break;
							case PAD_RIGHT:
								spr = oam_meta_spr(temp0, temp1, spr, bat_leg_0_right);
							break;
						}
					}
                }
                else
                {
					if(enemies_type[i] == 0)
					{
						switch(enemies_dir[i])
						{
							default:
							case PAD_UP:
								spr = oam_meta_spr(temp0, temp1, spr, spider_leg_1_up);
							break;
							case PAD_DOWN:
								spr = oam_meta_spr(temp0, temp1, spr, spider_leg_1_down);
							break;
							case PAD_LEFT:
								spr = oam_meta_spr(temp0, temp1, spr, spider_leg_1_left);
							break;
							case PAD_RIGHT:
								spr = oam_meta_spr(temp0, temp1, spr, spider_leg_1_right);
							break;
						}
					}
					else
					{
						switch(enemies_dir[i])
						{
							default:
							case PAD_UP:
								spr = oam_meta_spr(temp0, temp1, spr, bat_leg_1_up);
							break;
							case PAD_DOWN:
								spr = oam_meta_spr(temp0, temp1, spr, bat_leg_1_down);
							break;
							case PAD_LEFT:
								spr = oam_meta_spr(temp0, temp1, spr, bat_leg_1_left);
							break;
							case PAD_RIGHT:
								spr = oam_meta_spr(temp0, temp1, spr, bat_leg_1_right);
							break;
						}
					}
                }
            }
        }
    }
}
