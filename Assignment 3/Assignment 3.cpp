#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include "Enemy.h"
#include "Player.h"
#include "Cannon.h"

void printEndScreen(ALLEGRO_FONT* font, int hits);

int main()
{
    const float FPS = 60;
    const int screenWidth = 850;
    const int screenHeight = 1000;
    bool redraw = true;
    bool keyLeft = false;
    bool keyRight = false;
    bool gameOver = false;
    bool done = false;

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_BITMAP* bgImage = NULL;
    ALLEGRO_FONT* font = NULL;

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
    al_init_native_dialog_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    bgImage = al_load_bitmap("background.png");
    font = al_load_font("NiseJSRF.TTF",30, 0);

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
    Player myPlayer(screenHeight);
    Cannon myCannon(screenWidth, screenHeight);

    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        //timer event
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            for (int i = 0; i < MAX_ENEMIES; i++) {
                enemies[i].StartEnemy(screenWidth, screenHeight);
                enemies[i].UpdateEnemy(&myPlayer);
            }
            myCannon.Update(screenWidth, screenHeight);
            myCannon.killedEnemy(enemies, MAX_ENEMIES);
            if (keyLeft) {
                myCannon.rotateLeft();
            }
            else if (keyRight) {
                myCannon.rotateRight();
            }
            if (myPlayer.getLives() <= 0) {//when player runs out of lives, start game over screen
                gameOver = true;
            }
            redraw = true;
        }

        //key press events
        else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT) {//continuous rotation
                keyLeft = true;
                //myCannon.rotateLeft();
            }
            else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) {//continuous rotation
                keyRight = true;
                //myCannon.rotateRight();
            }

            if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {//fires bullets
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

        //renders the graphics
        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            
            if (!gameOver) {
                al_draw_scaled_bitmap(bgImage, 0, 0, al_get_bitmap_width(bgImage), al_get_bitmap_height(bgImage), 0, 0, screenWidth, screenHeight, 0);
                for (int i = 0; i < MAX_ENEMIES; i++) {
                    enemies[i].DrawEnemy();
                }
                myPlayer.DrawPlayer();
                myPlayer.drawLives(font, myCannon.getHits());
                myCannon.Draw();
                al_flip_display();
            }
            else if (gameOver) {

                printEndScreen(font, myCannon.getHits());
                while (true) {
                    al_wait_for_event(event_queue, &ev);
                    if (ev.type == ALLEGRO_EVENT_KEY_DOWN || ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {//any key to close
                        done = true;
                        break;
                    }
                }
            }
            //close upon escape key
            else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                break;
            }
        }
    }
    al_destroy_bitmap(bgImage);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
}

//prints when the player no longer has lives and displays score
void printEndScreen(ALLEGRO_FONT* font, int hits) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(font, al_map_rgb(255, 0, 0), 275, 350, 0, "Game Over");
    al_draw_textf(font, al_map_rgb(255, 255, 255), 175, 450, 0, "Enemies Defeated: %d", hits);
    al_draw_text(font, al_map_rgb(255, 255, 255), 115, 550, 0, "Press any key to close");
    al_flip_display();
    //std::cout << "TEST3" << std::endl;
}