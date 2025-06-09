#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "Enemy.h"
#include "Player.h"
#include "Cannon.h"

int main()
{
    const float FPS = 60;
    const int screenWidth = 850;
    const int screenHeight = 1000;
    bool redraw = true;
    bool keyLeft = false;
    bool keyRight = false;

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_BITMAP* bgImage = NULL;

    if (!al_init())
        return -1;

    timer = al_create_timer(1.0 / FPS);                             //timer set to 60 ticks per second
    if (!timer)
        return -1;

    display = al_create_display(screenWidth, screenHeight);
    if (!display) {
        al_destroy_timer(timer);
        return -1;
    }

    al_set_target_bitmap(al_get_backbuffer(display));
    al_init_image_addon();
    al_install_keyboard();
    bgImage = al_load_bitmap("background.png");                     //setting background

    event_queue = al_create_event_queue();
    if (!event_queue) {
        al_destroy_bitmap(bgImage);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(timer);                                             //starts the timer

    const int MAX_ENEMIES = 8;
    Enemy enemies[MAX_ENEMIES];
    player myPlayer(screenHeight);
    Cannon myCannon(screenWidth, screenHeight);

    while (1) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_TIMER) {
            for (int i = 0; i < MAX_ENEMIES; i++) {
                enemies[i].StartEnemy(screenWidth, screenHeight);
                enemies[i].UpdateEnemy();
            }
            myCannon.Update(screenWidth, screenHeight);
            if (keyLeft) {
                myCannon.rotateLeft();
            }
            else if (keyRight) {
                myCannon.rotateRight();
            }
            redraw = true;
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT) {//continuous rotation
                keyLeft = true;
                //myCannon.rotateLeft();
            }
            else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) {//continuous rotation
                keyRight = true;
                //myCannon.rotateRight();
            }

            if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                myCannon.Fire();
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                keyLeft = false;
            }
            else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                keyRight = false;
            }
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {//renders the graphics
            redraw = false;
            
            al_draw_scaled_bitmap(bgImage, 0, 0, al_get_bitmap_width(bgImage), al_get_bitmap_height(bgImage), 0, 0, screenWidth, screenHeight, 0);
            for (int i = 0; i < MAX_ENEMIES; i++) {
                enemies[i].DrawEnemy();
            }
            myPlayer.DrawPlayer();
            myCannon.Draw();
            al_flip_display();
        }
    }
    al_destroy_bitmap(bgImage);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}
