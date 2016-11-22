#include "player_sprites.h"
#define min_x 60
#define max_x (255-60)
#define min_y 60
#define max_y (240-60)

const static char item_target_x[4] = {108, 148, 108, 148};
const static char item_target_y[4] = {99, 140, 139, 99};

void __fastcall__ tick_players(void)
{
    /*
    int_temp0 = 120;
    int_temp0 <<= 1;
    int_temp0 -= scr_x;

    temp0 = int_temp0;

    int_temp0 = 120;
    int_temp0 <<= 1;
    int_temp0 -= scr_y;
    temp1 = int_temp0;
    spr = oam_spr(temp0, temp1, 0x2, 0x2, spr);
*/
    
    switch(player_hp[0]){
        default:
            spr = oam_spr(0x10, 0x10, 0x60, 0x0, spr);
            spr = oam_spr(0x10, 0x20, 0x60, 0x0, spr);
        break;
        case 3:
            spr = oam_spr(0x10, 0x10, 0x62, 0x0, spr);
            spr = oam_spr(0x10, 0x20, 0x60, 0x0, spr);
        break;
        case 2:
            spr = oam_spr(0x10, 0x10, 0x64, 0x0, spr);
            spr = oam_spr(0x10, 0x20, 0x60, 0x0, spr);
        break;
        case 1:
            spr = oam_spr(0x10, 0x10, 0x64, 0x0, spr);
            spr = oam_spr(0x10, 0x20, 0x62, 0x0, spr);
        break;
        case 0:
            spr = oam_spr(0x10, 0x10, 0x64, 0x0, spr);
            spr = oam_spr(0x10, 0x20, 0x64, 0x0, spr);
        break;
    }
    if(!single_player)
    {
        switch(player_hp[1]){
            default:
                spr = oam_spr(0xE8, 0x10, 0x60, 0x1, spr);
                spr = oam_spr(0xE8, 0x20, 0x60, 0x1, spr);
            break;
            case 3:
                spr = oam_spr(0xE8, 0x10, 0x62, 0x1, spr);
                spr = oam_spr(0xE8, 0x20, 0x60, 0x1, spr);
            break;
            case 2:
                spr = oam_spr(0xE8, 0x10, 0x64, 0x1, spr);
                spr = oam_spr(0xE8, 0x20, 0x60, 0x1, spr);
            break;
            case 1:
                spr = oam_spr(0xE8, 0x10, 0x64, 0x1, spr);
                spr = oam_spr(0xE8, 0x20, 0x62, 0x1, spr);
            break;
            case 0:
                spr = oam_spr(0xE8, 0x10, 0x64, 0x1, spr);
                spr = oam_spr(0xE8, 0x20, 0x64, 0x1, spr);
            break;
        }
    }
    to_scroll_x = 0;
    to_scroll_y = 0;
    
    for(i=0; i<2; ++i)
    {
        if(player_god_mode[i])
        {
            if((frame&2) == 0)
            {
                player_god_mode[i]--;
                pal_col(16+(i<<2)+3, palette[16+(i<<2)+3]);
                pal_col(16+(i<<2)+1, palette[16+(i<<2)+1]);
            }
            else
            {
                pal_col(16+(i<<2)+3, 0x20);
                pal_col(16+(i<<2)+1, 0xD);
            }
        }
        if(player_hp[i] == 0){
            continue;
        }
        int_temp0 = player_x[i];
        int_temp0 <<= 1;
        int_temp0 -= scr_x;
        
        temp0 = int_temp0;
        
        int_temp0 = player_y[i];
        int_temp0 <<= 1;
        int_temp0 -= scr_y;
        
        temp1 = int_temp0;
        
        temp2 = pad_poll(i);
        
        draw_player();
        
        if(temp0<min_x && scr_x > 0)
        {
            to_scroll_x = (min_x-temp0)>>1;
            if(to_scroll_x > scr_x)
            {
                to_scroll_x = scr_x;
            }
            to_scroll_x_neg = 1;
        } else if(temp0 > max_x && scr_x < 255)
        {
            to_scroll_x =  (temp0-max_x)>>1;
            
            if(to_scroll_x > 254-scr_x)
            {
                to_scroll_x = 254-scr_x;
            }
            to_scroll_x_neg = 0;
        }
        
        #
        if(temp1<min_y && scr_y > 0)
        {
            to_scroll_y = (min_y-temp1)>>1;
            if(to_scroll_y > scr_y)
            {
                to_scroll_y = scr_y;
            }
            to_scroll_y_neg = 1;
        } else if(temp1 > max_y && scr_y < 255)
        {
            to_scroll_y =  (temp1-max_y)>>1;
            
            if(to_scroll_y > 238-scr_y)
            {
                to_scroll_y = 238-scr_y;
            }
            to_scroll_y_neg = 0;
        }
    
        
        if(temp2 & PAD_B)
        {
            if(player_carry[i] == 0xFF)
            {
                temp4 = player_x[i];
                temp5 = player_y[i];
                
                if(player_dir[i] == PAD_LEFT) temp4 -= 4;
                else if(player_dir[i] == PAD_RIGHT) temp4 += 4;
                
                if(player_dir[i] == PAD_UP)  temp5 -= 4;
                else if(player_dir[i] == PAD_DOWN) temp5 += 2;
            
                for(j=0; j<4; j++)
                {
                    if(item_placed[j])
                    {
                        continue;
                    }
                    if(item_x[j]-4 <temp4 && item_x[j]+4>temp4)
                    {
                        if(item_y[j]-5 <temp5 && item_y[j]+5>temp5)
                        {
                            if(player_carry[1-i] != j || player_carry_dir[1-i] != player_dir[i])
                            {
                                player_carry[i] = j;
                                player_carry_dir[i] = player_dir[i];

								// Item pickup SFX
								sfx_play(5, 3);
                            }
                        }
                    }
                }
            }
        }
        else
        {
            player_carry[i] = 0xFF;

        }
        
        if(player_attack_tick[i] < 3 && (temp2 & (PAD_A))){
            player_attack_tick[i] = 16;
        }
        
        temp1 = 1-i;
    
        temp6 = 0;
        if(player_carry[i] != 0xFF)
        {
            temp6++;
            if(player_carry[temp1] == player_carry[i])
            {
                temp6++;
            }
        }
        
        
        if(temp6 == 2)
        {
            if(i==0 && (frame&3) == 0)
            {
                temp2 = pad_poll(0)&pad_poll(1);
                
                      
                if(temp2 & PAD_LEFT)
                {
                    if(isBlocked(player_x[0]-1, player_y[0]) == 0 && isBlocked(player_x[1]-1, player_y[1]) == 0){
                        --player_x[0];
                        --player_x[1];
                        --item_x[player_carry[i]];
                    }
                } 
                else if(temp2 & PAD_RIGHT)
                {
                    if(isBlocked(player_x[0]+1, player_y[0]) == 0 && isBlocked(player_x[1]+1, player_y[1]) == 0){
                        ++player_x[0];
                        ++player_x[1];
                        ++item_x[player_carry[i]];
                    }
                }
                
                if(temp2 & PAD_UP)
                {
                    if(isBlocked(player_x[0], player_y[0]-1) == 0 && isBlocked(player_x[1], player_y[1]-1) == 0){
                        --player_y[0];
                        --player_y[1];
                        --item_y[player_carry[i]];
                    }
                } 
                else if(temp2 & PAD_DOWN)
                {
                    if(isBlocked(player_x[0], player_y[0]+1) == 0 && isBlocked(player_x[1], player_y[1]+1) == 0){
                        ++player_y[0];
                        ++player_y[1];
                        ++item_y[player_carry[i]];
                    }
                }
                
            }
        }
        else if((temp6 == 0 ||(frame&7) == i) && (frame&1)== i)
        {
            if(!(player_dir[i] & temp2))
            {
                if(temp2 & PAD_LEFT)
                {
                    player_dir[i] = PAD_LEFT;
                }
                else if(temp2 & PAD_RIGHT)
                {
                    player_dir[i] = PAD_RIGHT;
                }
                else if(temp2 & PAD_DOWN)
                {
                    player_dir[i] = PAD_DOWN;
                }
                else if(temp2 & PAD_UP)
                {
                    player_dir[i] = PAD_UP;
                }
            }
            temp4 = player_x[i];
            temp5 = player_y[i];
            
            if(temp2 & PAD_LEFT)
            {
                if((player_hp[temp1] == 0 || player_x[temp1] < player_x[i] || player_x[temp1]-player_x[i] < 60))
                {
                    --player_x[i];
                }    
            } 
            else if(temp2 & PAD_RIGHT)
            {
                if(player_hp[temp1] == 0 ||player_x[i] < 250 && (player_x[temp1] > player_x[i] || player_x[i]-player_x[temp1] < 60))
                {
                    ++player_x[i];
                }
            }
            
            if(isBlocked(player_x[i], player_y[i])){
                player_x[i] = temp4;
            }
            else if(player_carry[i] != 0xFF)
            {
                item_x[player_carry[i]] += player_x[i]-temp4;
            }
            if(temp2 & PAD_UP)
            {
                if((player_hp[temp1] == 0 ||player_y[temp1] < player_y[i] || player_y[temp1]-player_y[i] < 60))
                {
                    --player_y[i];
                }    
            }
            else if( temp2 & PAD_DOWN)
            {
                if((player_hp[temp1] == 0 || player_y[temp1] > player_y[i] || player_y[i]-player_y[temp1] < 60))
                {
                    ++player_y[i];
                } 
            }
            if(isBlocked(player_x[i], player_y[i])){
                player_y[i] = temp5;
            }
            else if(player_carry[i] != 0xFF)
            {
                item_y[player_carry[i]] += player_y[i]-temp5;
            }
        }
        
        if(player_attack_tick[i] == 10)
        {
            temp0 = player_x[i];
            temp1 = player_y[i];
            temp6 = 5;
            temp7 = 5;
            
            if(player_dir[i] == PAD_LEFT) temp0 -= 4, temp6 = 8;
            else if(player_dir[i] == PAD_RIGHT) temp0 += 4, temp6 = 8;
            
            if(player_dir[i] == PAD_UP)  temp1 -= 4, temp7 = 8;
            else if(player_dir[i] == PAD_DOWN) temp1 += 3, temp7 = 8;
            dx = temp0;
            dy = temp1;
            if(isBlocked(temp0, temp1) == 0){
                took_damage();
            }
        }
    }
    
    temp2 = 0;
    for(i=0; i<4; i++)
    {
        if(item_placed[i]  == 0)
        {
            if(item_x[i] - item_target_x[i] < 2 || -item_x[i] + item_target_x[i]<2)
            {
                if(item_y[i] - item_target_y[i] < 2 || -item_y[i] + item_target_y[i]<2)
                {
                    item_placed[i] = 1;
                    item_x[i] = item_target_x[i];
                    item_y[i] = item_target_y[i];
                    if(player_carry[0] == i)
                    {
                        player_carry[0] = 0xFF;
                    }
                    if(player_carry[1] == i)
                    {
                        player_carry[1] = 0xFF;
                    }
								
					// Item placed SFX
					sfx_play(2, 3);
                }
            }
        }
        
        if(item_placed[i] == 0)
        {
            temp2 = 1;
        }
        int_temp0 = item_x[i];
        int_temp0 <<= 1;
        int_temp0 -= scr_x;
        
        if(int_temp0>255) continue;
        
        temp0 = int_temp0;

        int_temp0 = item_y[i];
        int_temp0 <<= 1;
        int_temp0 -= scr_y;
        if(int_temp0>255) continue;

        
        temp1 = int_temp0;
        
        spr = oam_spr(temp0-4, temp1-8, 0xC0+(item_type[i]<<1), 0x3, spr);
    }
    
    if(temp2 == 0)
    {
        next_level = 1;
	}
}
