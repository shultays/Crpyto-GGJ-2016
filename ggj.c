#include "neslib.h"

#include "defines.h"
#include "globals.h"
#include "debugger.h"
#include "bg.h"
#include "temp_control.h"
#include "enemies.h"
#include "players.h"


void __fastcall__ init(void){
    oam_size(1);
    bank_spr(0);
    bank_bg(1);
	
	vram_adr(NAMETABLE_A);
	vram_unrle(bg_top_left);
	vram_adr(NAMETABLE_B);
	vram_unrle(bg_top_right);
	vram_adr(NAMETABLE_C);
	vram_unrle(bg_bottom_left);
	vram_adr(NAMETABLE_D);
	vram_unrle(bg_bottom_right);
	
	ppu_on_all();
    
    difficulty = 0;
    next_level = 0;
    single_player = 1;
}

void __fastcall__ reset(void){
    next_level = 0;
	frame=0;
    
    player_dir[0] = PAD_UP;
    player_dir[1] = PAD_UP;
    
    player_hp[0] = 4;
    if(single_player)
    {
        player_hp[1] = 0;
    }
    else
    {
        player_hp[1] = 4;
    }
    
    scr_x = 128;
    scr_y = 128;
    
    player_x[0] = 120;
    player_y[0] = 120;
    player_x[1] = 136;
    player_y[1] = 120;
    
    player_attack_tick[0] = 0;
    player_attack_tick[1] = 0;
    
    
    
	for(i=0; i<8; ++i)
	{
        if (single_player){
            enemies_enemy[i] = PLAYER_1;
        } else {
            enemies_enemy[i] = (i&2)?PLAYER_1:PLAYER_2;
        }
		enemies_health[i] = 1;
        enemies_dir[i] = PAD_UP;
        enemy_leg[i] = (i&1);
		enemies_type[i] = (i&1);
        enemy_attack_timer[i] = 0;
	}

	enemy_spawn_points_x[0] = 184;
	enemy_spawn_points_y[0] = 24;
	enemy_spawn_points_x[1] = 232;
	enemy_spawn_points_y[1] = 72;
	enemy_spawn_points_x[2] = 232;
	enemy_spawn_points_y[2] = 168;
	enemy_spawn_points_x[3] = 184;
	enemy_spawn_points_y[3] = 216;
	enemy_spawn_points_x[4] = 72;
	enemy_spawn_points_y[4] = 217;
	enemy_spawn_points_x[5] = 24;
	enemy_spawn_points_y[5] = 167;
	enemy_spawn_points_x[6] = 24;
	enemy_spawn_points_y[6] = 73;
	enemy_spawn_points_x[7] = 72;
	enemy_spawn_points_y[7] = 24;

	for(i=0; i<8; ++i)
    {
		enemies_x[i] = enemy_spawn_points_x[i];
		enemies_y[i] = enemy_spawn_points_y[i];
        enemy_push_timer[i] = 0;
	}

    item_type[0] = 1;
    item_x[0] = 128;
    item_y[0] = 88;
    
    item_type[1] = 2;
    item_x[1] = 128;
    item_y[1] = 108;
    
    item_type[2] = 3;
    item_x[2] = 128;
    item_y[2] = 128;
    
    item_type[3] = 4;
    item_x[3] = 128;
    item_y[3] = 148;
    
    for(i=0; i<4; i++)
    {
        temp0 = rand8()&0xFE;
    
        item_x[i] = spawn[temp0]<<3;
        item_y[i] = spawn[temp0+1]<<3;
        for(j=0; j<i; j++)
        {
            if(item_x[i] == item_x[j] && item_y[i] == item_y[j])
            {
                i--;
                break;
            }
        }
    }
    
    
    for(i=0; i<4; i++)
    {
        item_x[i] += 2 + (rand8()&0x1) + (rand8()&0x1);
        item_y[i] += 2 + (rand8()&0x1) + (rand8()&0x1);
        
    }
    
    
    player_carry[0] = 0xFF;
    player_carry[1] = 0xFF;
    
    item_placed[0] = 0;
    item_placed[1] = 0;
    item_placed[2] = 0;
    item_placed[3] = 0;

    player_god_mode[0] = 0;
    player_god_mode[1] = 0;
    
	difficulty++;
    if(difficulty == 1)
    {
        enemy_speed = 2;
		enemy_damage_modifier = 60;
        spawn_hp = 1;
    }
    else if(difficulty == 2)
    {
        enemy_speed = 2;
		enemy_damage_modifier = 50;
        spawn_hp = 2;
    }
    else if(difficulty == 4)
    {
        enemy_speed = 3;
		enemy_damage_modifier = 40;
        spawn_hp = 2;
    }
    else if(difficulty == 6)
    {
        enemy_speed = 3;
		enemy_damage_modifier = 35;
        spawn_hp = 3;
    } 
    else if(difficulty == 7)
    {
        enemy_speed = 3;
		enemy_damage_modifier = 30;
        spawn_hp = 4;
    }
    else if(difficulty == 8)
    {
        enemy_speed = 4;
		enemy_damage_modifier = 25;
        spawn_hp = 5;
    }
    else if(difficulty == 9)
    {
        enemy_speed = 4;
		enemy_damage_modifier = 25;
        spawn_hp = 6;
    }
    else if(difficulty >= 10)
    {
        enemy_speed = 5;
		enemy_damage_modifier = 20;
        spawn_hp = 6 + (difficulty-10);
    }
    scroll(scr_x, scr_y);
}

void main(void){
	init();
    
    music_play(0);
    oam_clear();

    while(1){
        pal_all(paused_palette);
        scroll(0, 0);
        ppu_wait_frame();
        
        
        ppu_off();
        vram_adr(NAMETABLE_A);
        vram_unrle(bg_menu);
        ppu_on_all();
        
        pal_all(palette);
        ppu_wait_frame();
        
        
        ppu_wait_frame();
        
        
        j = 0;
        while(1){
            spr = 0;
            frame++;
                
            spr=12;
            oam_clear();
            for(i=0; i<7; i++){
                spr = oam_spr(0x66 + (i<<3), 0xA4, 0xCC+(i<<1), 0x1, spr);
                if (i){
                   spr = oam_spr(0x66 + (i<<3), 0xB4, 0xCC+(i<<1), 0x1, spr);
                } else {
                   spr = oam_spr(0x66 + (i<<3), 0xB4, 0xCA+(i<<1), 0x1, spr);
                }
                spr = oam_spr(0x66 + (i<<3), 0xC4, 0x6E+(i<<1), 0x1, spr);
                if (i<4){
                    spr = oam_spr(0x6C + (i<<3), 0xD4, 0xF8+(i<<1), 0x1, spr);
                }else if (i < 6){
                    spr = oam_spr(0x6C + (i<<3), 0xD4, 0xD2+(i<<1), 0x1, spr);
                }
            }
            
            if(frame&8)
            {
                oam_spr(120, 135, 0x66, 0x3, 0);
                oam_spr(120 + 8, 135, 0x68, 0x3, 4);
            }
            else
            {
                oam_spr(120, 135, 0x6A, 0x3, 0);
                oam_spr(120 + 8, 135, 0x6C, 0x3, 4);
            }
        
            oam_spr(0x5A, 0x9F + (j<<4), 0x1A, 0x3, 8);
            
            i = pad_trigger(0)|pad_trigger(1);
            
            if(i&PAD_UP)
            {
                j--;
                if(j == 255) j = 2;
            }
            else if(i&(PAD_DOWN|PAD_SELECT))
            {
                j++;
                if(j == 3) j = 0;
            }
            
            if(i&(PAD_A|PAD_B|PAD_START))
            {
                sfx_play(3, 2);
                
                if (j == 2){
                    oam_clear();
                    pal_all(paused_palette);
                    ppu_wait_frame();
                    
                    
                    ppu_off();
                    vram_adr(NAMETABLE_A);
                    vram_unrle(bg_credits);
                    
                    *((unsigned char*)0x8000) = 2; 
                    *((unsigned char*)0x8001) = 8; 
                    *((unsigned char*)0x8000) = 3; 
                    *((unsigned char*)0x8001) = 9; 
                    *((unsigned char*)0x8000) = 4; 
                    *((unsigned char*)0x8001) = 10; 
                    *((unsigned char*)0x8000) = 5; 
                    *((unsigned char*)0x8001) = 11; 
                
                    ppu_on_all();
                    
                    pal_all(palette);
                    while(1){
                        ppu_wait_frame();
                        if((pad_trigger(0)|pad_trigger(1)) & (PAD_START|PAD_A|PAD_B)) break;
                    
                    }
                    
                    oam_clear();
                    pal_all(palette);
                    ppu_wait_frame();
                    
                    ppu_off();
                    vram_adr(NAMETABLE_A);
                    vram_unrle(bg_menu);
                    
                    *((unsigned char*)0x8000) = 2; 
                    *((unsigned char*)0x8001) = 4; 
                    *((unsigned char*)0x8000) = 3; 
                    *((unsigned char*)0x8001) = 5; 
                    *((unsigned char*)0x8000) = 4; 
                    *((unsigned char*)0x8001) = 6; 
                    *((unsigned char*)0x8000) = 5; 
                    *((unsigned char*)0x8001) = 7; 
                    
                    ppu_on_all();
                }else{
                    break;
                }
            }
            ppu_wait_frame();
        }
        difficulty = 0;
        next_level = 1;
        single_player = !j;

        
        
        oam_clear();
        pal_all(paused_palette);
        ppu_wait_frame();
        
        
        ppu_off();
        vram_adr(NAMETABLE_A);
        vram_unrle(bg_top_left);
        ppu_on_all();
        
        
        spr = 0;
        oam_clear();
        ppu_wait_frame();
    
        set_rand(frame);
        while(1){
            ppu_wait_frame();
            spr=0;
            oam_clear();
            
            
            if(next_level)
            {
                // Next level SFX
                sfx_play(3, 2);

                reset();
                
                spr = 0;
                oam_clear();
                pal_all(paused_palette);
                spr = oam_spr(100, 114, 0xF4, 0x1, spr);
                spr = oam_spr(108, 114, 0xEA, 0x1, spr);
                spr = oam_spr(116, 114, 0xF6, 0x1, spr);
                spr = oam_spr(124, 114, 0xEA, 0x1, spr);
                spr = oam_spr(132, 114, 0xF4, 0x1, spr);
                if(difficulty<10)
                {
                    spr = oam_spr(148, 114, 0x04+(difficulty<<1), 0x1, spr);
                }
                else
                {
                    spr = oam_spr(148, 114, 0x05+(difficulty/10), 0x1, spr);
                    spr = oam_spr(156, 114, 0x04+(difficulty%10), 0x1, spr);
                }

                spr = 0;
                frame = 0;
                while(1)
                {
                    ppu_wait_frame();
                    frame++;
                    if((frame > 100) && (frame == 255 || ((pad_trigger(0)|pad_trigger(1))&(PAD_A|PAD_B|PAD_START))))
                    {
                        spr++;
                        break;
                    }
                }

                pal_all(palette);
                spr = 0;
                oam_clear();
            }

            if(player_hp[0] == 0 || (single_player == 0 && player_hp[1] == 0))
            {
                // Game Over SFX
                sfx_play(4, 2);

                difficulty = 0;
                next_level = 0;
                reset();
                
                spr = 0;
                oam_clear();
                pal_all(paused_palette);
                spr = oam_spr(92, 114, 0xEE, 0x1, spr);
                spr = oam_spr(100, 114, 0xE4, 0x1, spr);
                spr = oam_spr(108, 114, 0xF0, 0x1, spr);
                spr = oam_spr(116, 114, 0xEA, 0x1, spr);
                
                spr = oam_spr(132, 114, 0x04, 0x1, spr);
                spr = oam_spr(140, 114, 0xF6, 0x1, spr);
                spr = oam_spr(148, 114, 0xEA, 0x1, spr);
                spr = oam_spr(156, 114, 0xF2, 0x1, spr);
                
                spr = 0;
                frame = 0;
                while(1)
                {
                    ppu_wait_frame();
                    frame++;
                    if(frame == 255)
                    {
                        spr++;
                    }
                    if((spr == 4) || (spr >= 1 && ((pad_trigger(0)|pad_trigger(1))&(PAD_A|PAD_B|PAD_START))))
                    {
                        break;
                    }
                }

                pal_all(palette);
                spr = 0;
                oam_clear();
                break;
            }

            temp1 = pad_trigger(0) | pad_trigger(1);
            if(temp1 & PAD_START)
            {
                spr = 0;
                oam_clear();
                pal_all(paused_palette);
                spr = oam_spr(104, 114, 0xE2, 0x1, spr);
                spr = oam_spr(112, 114, 0xE4, 0x1, spr);
                spr = oam_spr(120, 114, 0xE6, 0x1, spr);
                spr = oam_spr(128, 114, 0xE8, 0x1, spr);
                spr = oam_spr(136, 114, 0xEA, 0x1, spr);
                spr = oam_spr(144, 114, 0xEC, 0x1, spr);

                ppu_wait_frame();
                while(!((pad_trigger(0)|pad_trigger(1))& PAD_START))
                {
                    ppu_wait_frame();
                }

                pal_all(palette);
                spr = 0;
                oam_clear();
            }

            int_temp0 = 124;
            int_temp0 <<= 1;
            int_temp0 -= scr_x;
            
            if(int_temp0 <= 255)
            {
                temp0 = int_temp0;
            
                int_temp0 = 116;
                int_temp0 <<= 1;
                int_temp0 -= scr_y;
            
                if(int_temp0 <= 255)
                {
                    temp1 = int_temp0;
                    if(frame&8)
                    {
                        spr = oam_spr(temp0, temp1 - 1, 0x66, 0x3, spr);
                        spr = oam_spr(temp0 + 8, temp1 - 1, 0x68, 0x3, spr);
                    }
                    else
                    {
                        spr = oam_spr(temp0, temp1 - 1, 0x6A, 0x3, spr);
                        spr = oam_spr(temp0 + 8, temp1 -1, 0x6C, 0x3, spr);
                    }
                }
            }
            
            tick_players();
            tick_enemies();
            
            temp0 = 0;
            
            if(to_scroll_x){
                if(to_scroll_x_neg){
                    scr_x -= to_scroll_x;
                }else{
                    scr_x += to_scroll_x;
                }
            }
            if(to_scroll_y){
                if(to_scroll_y_neg){
                    scr_y -= to_scroll_y;
                }else{
                    scr_y += to_scroll_y;
                }
            }
            scroll(scr_x, scr_y);
            ++frame;
            
             
        }
	}
}
