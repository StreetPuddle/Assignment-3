#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include "Enemy.h"
#include "Player.h"
#include "Cannon.h"

//renders the start menu before gameplay
void printStartScreen(ALLEGRO_BITMAP* menuImage, ALLEGRO_FONT* font1, ALLEGRO_FONT* font2, int screenWidth, int screenHeight);

//prints when the player no longer has lives and displays their score
void printEndScreen(ALLEGRO_FONT* font, int hits);

int main()
{
    const float FPS = 60;
    const int screenWidth = 850;
    const int screenHeight = 1064;
    const int MAX_ENEMIES = 8;
    bool redraw = true;
    bool keyLeft = false;
    bool keyRight = false;
    bool gameOver = false;
    bool done = false;
    bool startMenu = true;

    if (!al_init()) {
        al_show_native_message_box(nullptr, "Error", "ALLEGRO ISSUE", "Could not initialize Allegro", nullptr, 0);
        return -1;
    }

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_BITMAP* bgImage = NULL;
    ALLEGRO_BITMAP* menuImage = NULL;
    ALLEGRO_FONT* font1 = NULL;
    ALLEGRO_FONT* font2 = NULL;

    al_init_image_addon();
    al_install_keyboard();
    al_init_native_dialog_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    timer = al_create_timer(1.0 / FPS);//timer set to 60 ticks per second
    if (!timer) {
        al_show_native_message_box(nullptr, "ERROR", "ALLEGRO ISSUE", "Could not initialize timer", nullptr, 0);
        return -1;
    }
    display = al_create_display(screenWidth, screenHeight);
    if (!display) {
        al_show_native_message_box(nullptr, "ERROR", "ALLEGRO ISSUE", "Could not initialize display", nullptr, 0);
        return -1;
    }
    event_queue = al_create_event_queue();
    if (!event_queue) {
        al_show_native_message_box(nullptr, "ERROR", "ALLEGRO ISSUE", "Could not initialize event queue", nullptr, 0);
        return -1;
    }
    font1 = al_load_font("NiseJSRF.TTF", 30, 0);
    if (!font1) {
        al_show_native_message_box(nullptr, "ERROR", "ALLEGRO ISSUE", "Could not load font 'NiseJSRF.TTF'", nullptr, 0);
        return -1;
    }
    font2 = al_load_font("NiseJSRF.TTF", 100, 0);
    if (!font2) {
        al_show_native_message_box(nullptr, "ERROR", "ALLEGRO ISSUE", "Could not load font 'NiseJSRF.TTF'", nullptr, 0);
        return -1;
    }
    bgImage = al_load_bitmap("background.png");
    if (!bgImage) {
        al_show_native_message_box(nullptr, "ERROR", "ALLEGRO ISSUE", "Could not load background.png", nullptr, 0);
        return -6;
    }
    menuImage = al_load_bitmap("menu.jpg");
    if (!menuImage) {
        al_show_native_message_box(nullptr, "ERROR", "ALLEGRO ISSUE", "Could not load menu.jpg", nullptr, 0);
        return -6;
    }

    //registering event sources
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);//starts the timer

    Enemy enemies[MAX_ENEMIES];
    Player myPlayer(screenHeight);
    Cannon myCannon(screenWidth, screenHeight);

    //Gameplay stars here
    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        
        //timer event
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            for (int i = 0; i < MAX_ENEMIES; i++) {
                enemies[i].startEnemy(screenWidth, screenHeight);
                enemies[i].updateEnemy(&myPlayer);
            }
            myCannon.updateCannonShots(screenWidth, screenHeight);
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
            }
            else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) {//continuous rotation
                keyRight = true;
            }

            if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {//fires bullets
                myCannon.fireCannon();
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT) {//stops rotation
                keyLeft = false;
            }
            else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) {//stops rotation
                keyRight = false;
            }
        }

        //renders the graphics
        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;

            //main menu
            while (startMenu) {
                printStartScreen(menuImage, font1, font2, screenWidth, screenHeight);
                while (true) {
                    al_wait_for_event(event_queue, &ev);
                    if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {//any key to continue
                        startMenu = false;
                        break;
                    }
                }
            }

            //gameplay
            if (!gameOver) {

                al_draw_scaled_bitmap(bgImage, 0, 0, al_get_bitmap_width(bgImage), al_get_bitmap_height(bgImage), 0, 0, screenWidth, screenHeight, 0);
                al_draw_filled_rectangle(0, 64, screenWidth, 0, al_map_rgb(255, 180, 80));//upper banner
                for (int i = 0; i < MAX_ENEMIES; i++) {
                    enemies[i].drawEnemy();
                }
                myPlayer.drawPlayer();
                myPlayer.drawHUD(font1, myCannon.getHits());
                myCannon.drawCannon();
                al_flip_display();
            }
            //gameover
            else if (gameOver) {

                printEndScreen(font1, myCannon.getHits());
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
    al_destroy_bitmap(menuImage);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font1);
    al_destroy_font(font2);
}

//renders the start menu before gameplay
void printStartScreen(ALLEGRO_BITMAP* menuImage, ALLEGRO_FONT* font1, ALLEGRO_FONT* font2, int screenWidth, int screenHeight) { 
    al_draw_scaled_bitmap(menuImage, 0, 0, al_get_bitmap_width(menuImage), al_get_bitmap_height(menuImage), 0, 0, screenWidth, screenHeight, 0);
    al_draw_text(font2, al_map_rgb(255, 0, 120), 175, 250, 0, "S");
    al_draw_text(font2, al_map_rgb(255, 255, 255), 290, 250, 0, "pace");
    al_draw_text(font2, al_map_rgb(0, 255, 120), 75, 375, 0, "D");
    al_draw_text(font2, al_map_rgb(255, 255, 255), 203, 375, 0, "efense");
    al_draw_text(font1, al_map_rgb(255, 255, 255), 155, 750, 0, "Press Any Key to Play");
    al_flip_display();
}

//prints when the player no longer has lives and displays their score
void printEndScreen(ALLEGRO_FONT* font1, int hits) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(font1, al_map_rgb(255, 0, 0), 275, 350, 0, "Game Over");
    al_draw_textf(font1, al_map_rgb(255, 255, 255), 175, 450, 0, "Enemies Defeated: %d", hits);
    al_draw_text(font1, al_map_rgb(255, 255, 255), 115, 550, 0, "Press any key to close");
    al_flip_display();
}