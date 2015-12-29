#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_primitives.h>
#include <iostream>
#include <cmath>
 
#define ScreenWidth 1600	
#define ScreenHeight 900

using namespace std;

bool Collision(ALLEGRO_BITMAP *player, ALLEGRO_BITMAP *enemy, float x, float y, float ex, float ey, int width, int height)
{
	if( (x + width < ex) || (x > ex + width) || (y + height < ey) || (y > ey + height) )
		return false;

	else
	{
		int top = max(y, ey);
		int bottom = min(y + height, ey + height);
		int lt = max(x, ex);
		int rt = min(x + width, ex + width);

		for (int i = top; i < bottom; i++)
		{
			for(int j = lt; j < rt; j++)
			{
				al_lock_bitmap(player, al_get_bitmap_format(player), ALLEGRO_LOCK_READONLY);
				al_lock_bitmap(enemy, al_get_bitmap_format(enemy), ALLEGRO_LOCK_READONLY);
				ALLEGRO_COLOR color = al_get_pixel(player, j - x, i - y);
				ALLEGRO_COLOR color2 = al_get_pixel(enemy, j - ex, i - ey);

				if(color.a != 0 && color2.a != 0)
					return true;
			}
		}
	}
	return false;   
}

int main()
{
	ALLEGRO_DISPLAY *display;
	const float FPS = 60;

	if( !al_init() )
        al_show_native_message_box(NULL, "Error", NULL, "Could not Initialize Allegro", NULL, NULL); 

	display = al_create_display(ScreenWidth, ScreenHeight);
	if(!display)
        al_show_native_message_box(NULL, "Error", NULL, "Could not create Allegro Display", NULL, NULL);
 
	al_set_window_position(display, 0, 0);

	bool done = false;
    int x = 800, y = 450;

	al_install_audio();
    al_install_mouse();
	al_install_keyboard();
	al_init_image_addon();
	al_init_acodec_addon();
	
	ALLEGRO_BITMAP *background = al_load_bitmap("sprites/deathstar.png");
	ALLEGRO_BITMAP *player = al_load_bitmap("sprites/xwing.png");
	ALLEGRO_BITMAP *enemy = al_load_bitmap("sprites/astroid.png");
	ALLEGRO_BITMAP *crash = al_load_bitmap("sprites/crash.png");

	ALLEGRO_SAMPLE *exitScreen = al_load_sample("audio/exitScreen.wav");
	ALLEGRO_SAMPLE *song = al_load_sample("audio/StarWars.wav");
	al_reserve_samples(2);
	
	ALLEGRO_SAMPLE_INSTANCE *songInstance= al_create_sample_instance(song);
	al_set_sample_instance_playmode(songInstance,ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(songInstance,al_get_default_mixer());
	
	ALLEGRO_KEYBOARD_STATE keyState;

	ALLEGRO_TIMER *timer= al_create_timer(1.0/FPS);

	ALLEGRO_EVENT_QUEUE *event_queue= al_create_event_queue();

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_hide_mouse_cursor(display);

	al_play_sample_instance(songInstance);

	al_start_timer(timer);

	while(!done)
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);

		if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			done = true;

		else if(events.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if(al_key_down(&keyState,ALLEGRO_KEY_ESCAPE))
				done = true;
		}

		else if(events.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			x = events.mouse.x;
			y = events.mouse.y;
		}

		else if(events.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY)
			al_play_sample(exitScreen, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

		al_draw_bitmap(background, 0, 0, NULL);

		if(Collision(player, enemy, x, y, 200, 200, al_get_bitmap_width(player), al_get_bitmap_height(player)))
		{
			al_play_sample(exitScreen, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
			al_draw_bitmap(crash, x, y, NULL);
		}
		else
		{
			al_draw_bitmap(player, x, y, NULL);
			al_draw_bitmap(enemy, 200, 200, NULL);
		}
		
        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));
    }
	
    al_destroy_display(display);
    al_destroy_timer(timer);
	al_destroy_bitmap(player);
	al_destroy_bitmap(background);
	al_destroy_sample(exitScreen);
	al_destroy_sample(song);
	al_destroy_sample_instance(songInstance);
    al_destroy_event_queue(event_queue);

	return 0;
}