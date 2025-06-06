#ifndef TP_ALSDD_LIB_H
#define TP_ALSDD_LIB_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct reg_date{
    int mm,dd,yyyy;
}reg_date;

typedef struct GameQuestion{
    int question_num;
    char question_answer[50];
    bool is_favourite;
    int question_score;
}GameQuestion;

typedef struct Question{
    int number;
    char subject_area[20];
    char degree_of_difficulty[10];
    char content_of_the_question[100];
    char correct_answer[50];
    struct Question* next_question;
}Question;
typedef struct Player{
    int ID;
    char pseudoname[20];
    reg_date registration_date;
    int fav_num;
    char favourite_areas[10][20];
    int number_of_games_played;
    int total_score;
    struct Player* next_player;
}Player;

typedef struct Game{
    int player_ID;
    int game_level;
    GameQuestion questions_list[15];
    int game_score;
    struct Game* next_game;
}Game;


Question* random_question(char* domain,Question* Difficulty);
void add_question(Question** Questions_List_Head,int num,char *domain,char *difficulty,char *question,char *answer);
void load_questions_from_the_file(Question** Questions_List_Head);
void delete_question(Question** Questions_List_Head,int question_num);
void register_player(Player** Players_List_Head,int id,char *pseudo,int day,int month,int year,int favourite_num,char *domains[],int favs[],int gamesnum,int totalscore);
void delete_player(Player** Players_List_Head,int id);
void split_questions_difficulty_level(Question* Questions_list_head,Question **Easy,Question **Medium,Question **Hard);
int question_score(GameQuestion* question,Question* Questions_List_head);
void easy_question_display(Question* quest,char *suggestions[],char easy_choices[2][50]);
void medium_question_display(Question* quest,char *suggestions[],char medium_choices[4][50]);
int total_game_score(GameQuestion questions[15]);
void add_game(Game** Games_List_Head,int id,int level,GameQuestion list[15],int score);
int player_score(Game* Games_List_Head,int player_id);
void sorting_by_nof_games(Player* Players_List_Head );
void sorting_by_score(Player* Players_List_Head );
void load_test_players_from_file(Player** Players_List_Head,char *domains[]);
void load_test_games_from_file(Game** Games_List_Head);
void esi_interface();
void clearScreen();
void easy_ascii();
void medium_ascii();
void hard_ascii();
void welcome_ascii();
void see_you_ascii();
void register_page();
void our_names();
void login_page();
void list_of_players();
void add_a_question();
void delete_a_question();
void game_header();
void sorting_games();
void sorting_score();
void player_removal();


#endif