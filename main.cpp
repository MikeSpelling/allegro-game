#include <allegro.h>

BITMAP* buffer;
BITMAP* map;
BITMAP* car;

void init();
void setup();
void move();
void detect();

int x = 1304;
int y = 2537;

int dir = 1;
int wait_corner = 0;
int wait_acc = 0;
int acc = -15;
int corner = -25;
int speed = 10;
int forward = 1;

int main() {
    
	init();
	
	setup();
	
	while (!key[KEY_ESC])
    {        
        move();
        blit(map, buffer, x - (SCREEN_W / 2), y - (SCREEN_H / 2), 0, 0, SCREEN_W, SCREEN_H);
        draw_sprite(buffer, car, SCREEN_W / 2, SCREEN_H / 2); 
        draw_sprite(screen, buffer, 0, 0);
        rest(speed); 
	}

	return 0;
}
END_OF_MAIN()

void init() 
{
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT, 1440, 900, 0, 0);
	if (res != 0) {	allegro_message(allegro_error);	exit(-1);}
	install_timer();
	install_keyboard();
	install_mouse();
}

void setup()
{
    buffer = create_bitmap(SCREEN_W,SCREEN_H);
    map = load_bitmap("map.bmp", NULL); 
    car = load_bitmap("car_u.bmp",NULL);
    blit(map, buffer, x - (SCREEN_W / 2), y - (SCREEN_H / 2), 0, 0, SCREEN_W, SCREEN_H);
    draw_sprite(buffer, car, SCREEN_W / 2, SCREEN_H / 2); 
    draw_sprite(screen, buffer, 0, 0);
    readkey();
}

void move()
{    
    clear_keybuf();
    
    detect();
    
    // Change direction (Forwards or backwards)
    if(key[KEY_W] && forward == -1)
    {
        forward = 1;
        speed =10;
    }
    
    if(key[KEY_S] && forward == 1)
    {
        forward = -1;
        speed =10;
    }
    
    wait_corner++;
    wait_acc++;
    
    if(key[KEY_UP] && speed > 0 && wait_acc > 0)
    {
        if(forward == 1) speed--;
        else speed++;
        
        if(speed >= 15)forward *= -1;
        
        wait_acc = acc;
    }
    else if(key[KEY_DOWN] && wait_acc > 0)
    {
        if(forward == 1) speed++;
        else speed--;
        
        if(speed >= 15)forward *= -1;
        
        wait_acc = acc;
    }    
    
    switch(dir)
    {
        case 1:
        {
            y-=forward;

            if(key[KEY_RIGHT] && wait_corner > 0)
            {
                dir++;
                car = load_bitmap("car_ur.bmp",NULL);
                wait_corner = corner;
            }
            else if(key[KEY_LEFT] && wait_corner > 0)
            {
                dir=8;
                car = load_bitmap("car_ul.bmp",NULL);
                wait_corner = corner;
            }
            break;
        }
        case 2:
        {
            y-=forward; x+=forward;

            if(key[KEY_RIGHT] && wait_corner > 0)
            {
                dir++;
                car = load_bitmap("car_r.bmp",NULL);
                wait_corner = corner;
            }
            else if(key[KEY_LEFT] && wait_corner > 0)
            {
                dir--;
                car = load_bitmap("car_u.bmp",NULL);
                wait_corner = corner;
            }
            break;
        }
        case 3:
        {
            x+=forward;

            if(key[KEY_RIGHT] && wait_corner > 0)
            {
                dir++;
                car = load_bitmap("car_dr.bmp",NULL);
                wait_corner = corner;
            }
            else if(key[KEY_LEFT] && wait_corner > 0)
            {
                dir--;
                car = load_bitmap("car_ur.bmp",NULL);
                wait_corner = corner;
            }
            break;
        }
        case 4:
        {
            y+=forward; x+=forward;

            if(key[KEY_RIGHT] && wait_corner > 0)
            {
                dir++;
                car = load_bitmap("car_d.bmp",NULL);
                wait_corner = corner;
            }
            else if(key[KEY_LEFT] && wait_corner > 0)
            {
                dir--;
                car = load_bitmap("car_r.bmp",NULL);
                wait_corner = corner;
            }
            break;
        }
        case 5:
        {
            y+=forward;

            if(key[KEY_RIGHT] && wait_corner > 0)
            {
                dir++;
                car = load_bitmap("car_dl.bmp",NULL);
                wait_corner = corner;
            }
            else if(key[KEY_LEFT] && wait_corner > 0)
            {
                dir--;
                car = load_bitmap("car_dr.bmp",NULL);
                wait_corner = corner;
            }
            break;
        }
        case 6:
        {
            y+=forward; x-=forward;

            if(key[KEY_RIGHT] && wait_corner > 0)
            {
                dir++;
                car = load_bitmap("car_l.bmp",NULL);
                wait_corner = corner;
            }
            else if(key[KEY_LEFT] && wait_corner > 0)
            {
                dir--;
                car = load_bitmap("car_d.bmp",NULL);
                wait_corner = corner;
            }
            break;
        }
        case 7:
        {
            x-=forward;

            if(key[KEY_RIGHT] && wait_corner > 0)
            {
                dir++;
                car = load_bitmap("car_ul.bmp",NULL);
                wait_corner = corner;
            }
            else if(key[KEY_LEFT] && wait_corner > 0)
            {
                dir--;
                car = load_bitmap("car_dl.bmp",NULL);
                wait_corner = corner;
            }
            break;
        }
        case 8:
        {
            y-=forward; x-=forward;

            if(key[KEY_RIGHT] && wait_corner > 0)
            {
                dir=1;
                car = load_bitmap("car_u.bmp",NULL);
                wait_corner = corner;
            }
            else if(key[KEY_LEFT] && wait_corner > 0)
            {
                dir--;
                car = load_bitmap("car_l.bmp",NULL);
                wait_corner = corner;
            }
            break;
        }
    }                
}

void detect()
{
    //  Detect Collision
    switch(dir)
    {
        case 1:
        case 5:
        {
            //  Detect Grey Boundary
            if( (getr(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2)) == 128 && getg(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2)) == 128 &&
            getb(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2)) == 128) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 23, SCREEN_H / 2)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 23, SCREEN_H / 2)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 23, SCREEN_H / 2)) == 128) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2 + 39)) == 128 && getg(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2 + 39)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2 + 39)) == 128) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 23, SCREEN_H / 2 + 39)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 23, SCREEN_H / 2 + 39)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 23, SCREEN_H / 2 + 39)) == 128))
            {
                if(dir == 1) 
                {
                    y+=forward;
                    speed = 10;
                    readkey();
                }
                else
                {
                    y-=forward;
                    speed = 10;
                    readkey();
                }
            }
            //  Detect Grass
            if((getr(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2)) == 128 && getg(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2)) == 255 &&
            getb(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2)) == 0) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 23, SCREEN_H / 2)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 23, SCREEN_H / 2)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 23, SCREEN_H / 2)) == 0) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2 + 39)) == 128 && getg(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2 + 39)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2 + 39)) == 0) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 23, SCREEN_H / 2 + 39)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 23, SCREEN_H / 2 + 39)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 23, SCREEN_H / 2 + 39)) == 0))
            {
                if(dir == 1) 
                {
                    y+=forward;
                    speed = 10;
                    readkey();
                }
                else
                {
                    y-=forward;
                    speed = 10;
                    readkey();
                }
            }
            break;
        }
        case 3:
        case 7:
        {
            //  Detect Grey Boundary
            if((getr(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2)) == 128 && getg(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2)) == 128) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2)) == 128) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2 + 23)) == 128 && getg(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2 + 23)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2 + 23)) == 128) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2 + 23)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2 + 23)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2 + 23)) == 128))
            {
                if(dir == 3) 
                {
                    x-=forward;
                    speed = 10;
                    readkey();
                }
                else
                {
                    x+=forward;
                    speed = 10;
                    readkey();
                }
            }
            //  Detect Grass
            if((getr(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2)) == 128 && getg(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2)) == 0) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2)) == 0) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2 + 23)) == 128 && getg(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2 + 23)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2 + 23)) == 0) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2 + 23)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2 + 23)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2 + 23)) == 0))
            {
                if(dir == 3) 
                {
                    x-=forward;
                    speed = 10;
                    readkey();
                }
                else
                {
                    x+=forward;
                    speed = 10;
                    readkey();
                }
            }
            break;
        }        
        case 4:        
        {
            //  Detect Grey Boundary
            if((getr(getpixel(buffer, SCREEN_W / 2 - 1, SCREEN_H / 2 + 17)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 - 1, SCREEN_H / 2 + 17)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2 - 1, SCREEN_H / 2 + 17)) == 128) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 15, SCREEN_H / 2 - 1)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 15, SCREEN_H / 2 - 1)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 15, SCREEN_H / 2 - 1))== 128) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 21, SCREEN_H / 2 + 38)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 21, SCREEN_H / 2 + 38)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 21, SCREEN_H / 2 + 38)) == 128) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 37, SCREEN_H / 2 + 20)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 37, SCREEN_H / 2 + 20)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 37, SCREEN_H / 2 + 20))) == 128)
            {
                if(dir == 4) 
                {
                    y-=forward; x-=forward;
                    speed = 10;
                    readkey();
                }
                else
                {
                    y+=forward; x+=forward;
                    speed = 10;
                    readkey();
                }
            }
            
            //  Detect Grass
            if((getr(getpixel(buffer, SCREEN_W / 2 - 1, SCREEN_H / 2 + 17)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 - 1, SCREEN_H / 2 + 17)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2 - 1, SCREEN_H / 2 + 17)) == 0) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 15, SCREEN_H / 2 - 1)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 15, SCREEN_H / 2 - 1)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 15, SCREEN_H / 2 - 1)) == 0) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 21, SCREEN_H / 2 + 38)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 21, SCREEN_H / 2 + 38)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 21, SCREEN_H / 2 + 38)) == 0) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 37, SCREEN_H / 2 + 20)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 37, SCREEN_H / 2 + 20)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 37, SCREEN_H / 2 + 20) == 0)))
            {
                if(dir == 4) 
                {
                    y-=forward; x-=forward;
                    speed = 10;
                    readkey();
                }
                else
                {
                    y+=forward; x+=forward;
                    speed = 10;
                    readkey();
                }
            }
            break;
        }
        case 8:        
        {
            //  Detect Grey Boundary
            if((getr(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2 + 17)) == 128 && getg(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2 + 17)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2 + 17)) == 128) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 19, SCREEN_H / 2)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 19, SCREEN_H / 2)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 19, SCREEN_H / 2))== 128) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 23, SCREEN_H / 2 + 39)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 23, SCREEN_H / 2 + 39)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 23, SCREEN_H / 2 + 39)) == 128) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2 + 23)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2 + 23)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2 + 23))) == 128)
            {
                if(dir == 4) 
                {
                    y-=forward; x-=forward;
                    speed = 10;
                    readkey();
                }
                else
                {
                    y+=forward; x+=forward;
                    speed = 10;
                    readkey();
                }
            }
            
            //  Detect Grass
            if((getr(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2 + 17)) == 128 && getg(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2 + 17)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2, SCREEN_H / 2 + 17)) == 0) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 19, SCREEN_H / 2)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 19, SCREEN_H / 2)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 19, SCREEN_H / 2)) == 0) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 23, SCREEN_H / 2 + 39)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 23, SCREEN_H / 2 + 39)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 23, SCREEN_H / 2 + 39)) == 0) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2 + 23)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2 + 23)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2 + 23) == 0)))
            {
                if(dir == 4) 
                {
                    y-=forward; x-=forward;
                    speed = 10;
                    readkey();
                }
                else
                {
                    y+=forward; x+=forward;
                    speed = 10;
                    readkey();
                }
            }
            break;
        }
        case 2:
        {
            //  Detect Grey Boundary
            if((getr(getpixel(buffer, SCREEN_W / 2 + 20, SCREEN_H / 2)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 20, SCREEN_H / 2)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 20, SCREEN_H / 2)) == 128) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 38, SCREEN_H / 2 + 11)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 38, SCREEN_H / 2 + 11)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 38, SCREEN_H / 2 + 11))== 128) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 1, SCREEN_H / 2 + 29)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 1, SCREEN_H / 2 + 29)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 1, SCREEN_H / 2 + 29)) == 128) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 20, SCREEN_H / 2 + 39)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 20, SCREEN_H / 2 + 39)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 20, SCREEN_H / 2 + 39))) == 128)
            {
                if(dir == 2) 
                {
                    y+=forward; x-=forward;
                    speed = 10;
                    readkey();
                }
                else
                {
                    y-=forward; x+=forward;
                    speed = 10;
                    readkey();
                }
            }
            
            //  Detect Grass
            if((getr(getpixel(buffer, SCREEN_W / 2 + 20, SCREEN_H / 2)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 20, SCREEN_H / 2)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 20, SCREEN_H / 2)) == 0) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 38, SCREEN_H / 2 + 11)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 38, SCREEN_H / 2 + 11)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 38, SCREEN_H / 2 + 11))== 0) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 1, SCREEN_H / 2 + 29)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 1, SCREEN_H / 2 + 29)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 1, SCREEN_H / 2 + 29)) == 0) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 20, SCREEN_H / 2 + 39)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 20, SCREEN_H / 2 + 39)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 20, SCREEN_H / 2 + 39))) == 0)
            {
                if(dir == 2) 
                {
                    y+=forward; x-=forward;
                    speed = 10;
                    readkey();
                }
                else
                {
                    y-=forward; x+=forward;
                    speed = 10;
                    readkey();
                }
            }
            break;
        }
         case 6:
        {
            //  Detect Grey Boundary
            if((getr(getpixel(buffer, SCREEN_W / 2 + 18, SCREEN_H / 2 - 1)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 18, SCREEN_H / 2 - 1)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 18, SCREEN_H / 2 - 1)) == 128) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2 + 10)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2 + 10)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2 + 10))== 128) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 - 1, SCREEN_H / 2 + 22)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 - 1, SCREEN_H / 2 + 22)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2 - 1, SCREEN_H / 2 + 22)) == 128) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 19, SCREEN_H / 2 + 38)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 19, SCREEN_H / 2 + 38)) == 128 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 19, SCREEN_H / 2 + 38))) == 128)
            {
                if(dir == 2) 
                {
                    y+=forward; x-=forward;
                    speed = 10;
                    readkey();
                }
                else
                {
                    y-=forward; x+=forward;
                    speed = 10;
                    readkey();
                }
            }
            
            //  Detect Grass
            if((getr(getpixel(buffer, SCREEN_W / 2 + 18, SCREEN_H / 2 - 1)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 18, SCREEN_H / 2 - 1)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 18, SCREEN_H / 2 - 1)) == 0) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2 + 10)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2 + 10)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 39, SCREEN_H / 2 + 10))== 0) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 - 1, SCREEN_H / 2 + 22)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 - 1, SCREEN_H / 2 + 22)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2 - 1, SCREEN_H / 2 + 22)) == 0) || 
            
            (getr(getpixel(buffer, SCREEN_W / 2 + 19, SCREEN_H / 2 + 38)) == 128 && getg(getpixel(buffer, SCREEN_W / 2 + 19, SCREEN_H / 2 + 38)) == 255 && 
            getb(getpixel(buffer, SCREEN_W / 2 + 19, SCREEN_H / 2 + 38))) == 0)
            {
                if(dir == 2) 
                {
                    y+=forward; x-=forward;
                    speed = 10;
                    readkey();
                }
                else
                {
                    y-=forward; x+=forward;
                    speed = 10;
                    readkey();
                }
            }
            break;
        }
    }
}

