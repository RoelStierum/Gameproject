#pragma once

//Screen resolution "MOET ALTIJD 16:9 ZIJN"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

//The game's update and handle input refresh rate are locked at 60 fps
#define FPS 60.0f

//Splash state with background
#define SPLASH_STATE_SHOW_TIME 2.0f
#define SPLASH_SCREEN_BACKGROUND_FILEPATH "Images/game_splash_screen_spacex.png"

//Main Menu
#define MAIN_MENU_BACKGROUND_FILEPATH "Images/game_background2.png"
#define MAIN_MENU_TITLE_FILEPATH "Images/game_title_white.png"
#define MAIN_MENU_PLAY_BUTTON_FILEPATH "Images/game_play_button.png"
#define MAIN_MENU_PLAY_BUTTON_HOVER_FILEPATH "Images/game_play_button_hover.png"
#define MAIN_MENU_QUIT_BUTTON_FILEPATH "Images/game_quit_button.png"
#define MAIN_MENU_QUIT_BUTTON_HOVER_FILEPATH "Images/game_quit_button_hover.png"
#define MUTE_FILEPATH "Images/soundMute.png"
#define UNMUTE_FILEPATH "Images/soundUnMute.png"

//instructions
#define INSTRUCTIONS_BUTTON "Images/instructions_title.png"
#define INSTRUCTIONS_BUTTON_HOVER "Images/instructions_title_hover.png"
#define INSTRUCTIONS "Images/instructions.png"
#define BACK_BUTTON "Images/back_button.png"
#define BACK_BUTTON_HOVER "Images/back_button_hover.png"

//Sound effects
#define JUMP_SOUND_FILEPATH "Audio/jump.wav"
#define JUMP_SOUND_VOLUME 10
#define CLICK_SOUND_FILEPATH "Audio/click.wav"
#define CLICK_SOUND_VOLUME 100
#define DEATH_SOUND_FILEPATH "Audio/Death.wav"
#define DEATH_SOUND_VOLUME 15
#define WIN_SOUND_FILEPATH "Audio/win1.wav"
#define WIN_SOUND_VOLUME 100
#define POWERUP_SOUND_FILEPATH "Audio/powerup.wav"
#define POWERUP_SOUND_VOLUME 40

//Music
#define MUSIC_FILEPATH "Audio/music.ogg"
#define MUSIC_VOLUME 20

//Levels
#define LEVEL_AMOUNT 2
#define LEVEL_BACKGROUND_FILEPATH "Images/game_background_long.png"
#define PAUSE_BUTTON_FILEPATH "Images/pause.png"
#define PLATFORM_GRASS_FILEPATH "Images/game_platform.png"
#define PLATFORM_GREY_FILEPATH "Images/platform_horizontal.png"
#define PLATFORM_GREY_VERTICAL_FILEPATH "Images/platform_vertical.png"
#define FORCEFIELD_VERTICAL_FILEPATH "Images/forcefield.png"
#define DOUBLEJUMP_FILEPATH "Images/doublejump.png"
#define LOW_GRAVITY_FILEPATH "Images/low_gravity.png"
#define LEVEL_FLAG_FILEPATH "Images/vlag.png"
#define FINISH_FLAG_WAIT 1.5f
#define DOUBLE_JUMP_TIME 10
#define LOW_GRAVITY_TIME 11

//Character
#define CHARACTER_FILEPATH "Images/Character.png"
#define CHARACTER_FLIP_FILEPATH "Images/Character_flip.png"
#define CHARACTER_RUN_RIGHT_FILEPATH "Images/run_right.png"
#define CHARACTER_RUN_RIGHT2_FILEPATH "Images/run_right2.png"
#define CHARACTER_RUN_LEFT_FILEPATH "Images/run_left.png"
#define CHARACTER_RUN_LEFT2_FILEPATH "Images/run_left2.png"

//PauseState
#define PAUSE_BACKGROUND_FILEPATH "Images/game_background.png"
#define PAUSE_PAUSED_TITLE_FILEPATH "Images/paused_title.png"
#define PAUSE_RESUME_BUTTON_FILEPATH "Images/resume_button.png"
#define PAUSE_RESUME_BUTTON_HOVER_FILEPATH "Images/resume_button_hover.png"
#define PAUSE_MAIN_MENU_PLAY_BUTTON_FILEPATH "Images/main_menu_button.png"
#define PAUSE_MAIN_MENU_PLAY_BUTTON_HOVER_FILEPATH "Images/main_menu_button_hover.png"
#define PAUSE_QUIT_BUTTON_FILEPATH "Images/game_quit_button.png"
#define PAUSE_QUIT_BUTTON_HOVER_FILEPATH "Images/game_quit_button_hover.png"

//FinishState
#define FINISH_BACKGROUND_FILEPATH "Images/wallpaperfinish.jpg"
#define FINISH_NEXT_LEVEL_BUTTON_FILEPATH "Images/next_level_button.png"
#define FINISH_NEXT_LEVEL_BUTTON_HOVER_FILEPATH "Images/next_level_button_hover.png"
#define FINISH_MAIN_MENU_PLAY_BUTTON_FILEPATH "Images/main_menu_button.png"
#define FINISH_MAIN_MENU_PLAY_BUTTON_HOVER_FILEPATH "Images/main_menu_button_hover.png"
#define FINISH_QUIT_BUTTON_FILEPATH "Images/game_quit_button.png"
#define FINISH_QUIT_BUTTON_HOVER_FILEPATH "Images/game_quit_button_hover.png"
#define HIGHSCORE_FILENAME "Highscore/Highscore"

//Fonts
#define FONT_FILEPATH "Fonts/RussoOne-Regular.ttf"

