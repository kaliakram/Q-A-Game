////////////////////////////////////////////////////////////////////////////////////////
//libraries needed to implement the functions and procedures for the game
////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "TP_ALSDD_LIB.h"
////////////////////////////////////////////////////////////////////////////////////////
Question* random_question(char* domain,Question* Difficulty){
    Question* temp=Difficulty;
    int counter=0;
    while(temp!=NULL){
        if(strcmp(temp->subject_area,domain)==0){
            counter++;
        }
        temp=temp->next_question;
    }
    int find=(rand()%counter)+1;
    temp=Difficulty;
    counter=0;
    while(temp!=NULL){
        if(strcmp(temp->subject_area,domain)==0){
            counter++;
        }
        if(counter==find){
            return temp;
        }
        temp=temp->next_question;
    }
}
////////////////////////////////////////////////////////////////////////////////////////
void add_question(Question** Questions_List_Head,int num,char *domain,char *difficulty,char *question,char *answer){

    Question* newquestion=(Question*)malloc(sizeof(Question));
    newquestion->number=num;
    strcpy(newquestion->subject_area,domain);
    strcpy(newquestion->degree_of_difficulty,difficulty);
    strcpy(newquestion->content_of_the_question,question);
    strcpy(newquestion->correct_answer,answer);
    newquestion->next_question=NULL;
    if((*Questions_List_Head)==NULL){
        *Questions_List_Head=newquestion;
        return;
    }
    Question* temp=(*Questions_List_Head);
    while(temp->next_question!=NULL){
        temp=temp->next_question;
    }
    temp->next_question=newquestion;
}
////////////////////////////////////////////////////////////////////////////////////////
void load_questions_from_the_file(Question** Questions_List_Head){

    FILE* reading_file;
    char loaded_line[300];
    int questionNum;
    char prefered_domain[20];
    char difficulty[20];
    char question[100];
    char questionAnswer[50];
    reading_file=fopen("questions.txt","r");
    while(fgets(loaded_line,300,reading_file)){
        sscanf(loaded_line,"%d %s %s %s %s",&questionNum,prefered_domain,difficulty,question,questionAnswer);
        int o=0;
        while(question[o]!='\0'){
            if (question[o]=='_')
            {
                question[o]=' ';
            }
            o++;
        }
        add_question(Questions_List_Head,questionNum,prefered_domain,difficulty,question,questionAnswer);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
void delete_question(Question** Questions_List_Head,int question_num){
    Question* temp=*Questions_List_Head;
    Question* removed_question;
    bool removed=false;
    if(*Questions_List_Head!=NULL){
    if ((temp->number==question_num) && (temp==*Questions_List_Head)){
        *Questions_List_Head=temp->next_question;
        free(temp);
        removed=true;
    }
    while((temp->next_question!=NULL) && (removed==false)){
        if(((temp->next_question)->number)==question_num){
            removed_question=temp->next_question;
            temp->next_question=(temp->next_question)->next_question;
            free(removed_question);
            removed=true;
        }
        if(removed==false){
            temp=temp->next_question;
        }

    }
}
}
////////////////////////////////////////////////////////////////////////////////////////
void register_player(Player** Players_List_Head,int id,char *pseudo,int day,int month,int year,int favourite_num,char *domains[],int favs[],int gamesnum,int totalscore){
    Player* newplayer=(Player*)malloc(sizeof(Player));
    newplayer->ID=id;
    strcpy(newplayer->pseudoname,pseudo);
    (newplayer->registration_date).mm=month;
    (newplayer->registration_date).dd=day;
    (newplayer->registration_date).yyyy=year;
    newplayer->number_of_games_played=gamesnum;
    newplayer->total_score=totalscore;
    for(int i=0;i<favourite_num;i++){
        strcpy(newplayer->favourite_areas[i],domains[favs[i]]);
    }
    newplayer->fav_num=favourite_num;
    newplayer->next_player=NULL;
    if((*Players_List_Head)==NULL){
        *Players_List_Head=newplayer;
        return;
    }
    Player* temp=(*Players_List_Head);
    while(temp->next_player!=NULL){
        temp=temp->next_player;
    }
    temp->next_player=newplayer;
}

////////////////////////////////////////////////////////////////////////////////////////
void delete_player(Player** Players_List_Head,int id){
    Player* temp=*Players_List_Head;
    Player* removed_player;
    bool removed=false;
    if(*Players_List_Head!=NULL){
    if ((temp->ID==id) && (temp==*Players_List_Head)){
        *Players_List_Head=temp->next_player;
        free(temp);
        removed=true;
    }
    while((temp->next_player!=NULL) && (removed==false)){
        if(((temp->next_player)->ID)==id){
            removed_player=temp->next_player;
            temp->next_player=(temp->next_player)->next_player;
            free(removed_player);
            removed=true;
        }
        if(removed==false){
            temp=temp->next_player;
        }
    }
}
}

void split_questions_difficulty_level(Question* Questions_list_head,Question **Easy,Question **Medium,Question **Hard){
    Question* temp=Questions_list_head;
    while (temp!=NULL){
        if(strcmp(temp->degree_of_difficulty,"easy")==0){
            add_question(Easy,temp->number,temp->subject_area,"easy",temp->content_of_the_question,temp->correct_answer);
        }
        if(strcmp(temp->degree_of_difficulty,"medium")==0){
            add_question(Medium,temp->number,temp->subject_area,"medium",temp->content_of_the_question,temp->correct_answer);
        }
        if(strcmp(temp->degree_of_difficulty,"hard")==0){
            add_question(Hard,temp->number,temp->subject_area,"hard",temp->content_of_the_question,temp->correct_answer);
        }
        temp=temp->next_question;
    }
}   
////////////////////////////////////////////////////////////////////////////////////////
int question_score(GameQuestion* question,Question* Questions_List_head){
    Question* temp=Questions_List_head;
    int result=0;
    while (temp!=NULL){
        if ((question->question_num)==(temp->number)){
            break;
        }
        temp=temp->next_question;
    }
    if(strcmp(temp->correct_answer,question->question_answer)==0){
        if(strcmp(temp->degree_of_difficulty,"easy")==0){
            if(question->is_favourite==true){
                result=1;
            }
            else{
                result=2;
            }
        }
        else if(strcmp(temp->degree_of_difficulty,"medium")==0){
            if(question->is_favourite==true){
                result=2;
            }
            else{
                result=3;   
            }
        }
        else{
            if(question->is_favourite==true){
                result=4;
            }
            else{
                result=5;
            }
        }
    }
    return result;
}
/////////////////////////////////////////////////////////////
void easy_question_display(Question* quest,char *suggestions[],char easy_choices[2][50]){
printf("%s\n",quest->content_of_the_question);
printf("please enter your answer:\n");
char answer[50];
int ran=rand()%2;
int sugg_ind=0;
for(int a=0;a<2;a++){
    if (a==ran)
    {
        strcpy(easy_choices[a],quest->correct_answer);
    }else{
        sugg_ind=rand()%50;
        strcpy(easy_choices[a],suggestions[sugg_ind]);
    }
}
for (int m = 0; m < 2; m++)
{
    printf("%d-%s\n",(m+1),easy_choices[m]);
}
}
/////////////////////////////////////////////////////////////
void medium_question_display(Question* quest,char *suggestions[],char medium_choices[4][50]){
    printf("%s\n",quest->content_of_the_question);
    printf("please enter your answer:\n");
    char answer[50];
    int ran=rand()%4;
    int sugg_ind=0;
    for(int a=0;a<4;a++){
        if (a==ran)
        {
            strcpy(medium_choices[a],quest->correct_answer);
        }else{
            sugg_ind=rand()%50;
            strcpy(medium_choices[a],suggestions[sugg_ind]);
        }
    }
    for (int m = 0; m < 4; m++)
    {
        printf("%d-%s\n",(m+1),medium_choices[m]);
    }
    }
/////////////////////////////////////////////////////////////
int total_game_score(GameQuestion questions[15]){
    int result=0;
    for(int n=0;n<15;n++){
        result+=questions[n].question_score;
    }
    return result;
}
////////////////////////////////////////////////////////////////////////////////////////
void add_game(Game** Games_List_Head,int id,int level,GameQuestion list[15],int score){
    Game* newgame=(Game*)malloc(sizeof(Game));
    newgame->player_ID=id;
    newgame->game_level=level;
    newgame->game_score=score;
    for(int i=0;i<15;i++){
        newgame->questions_list[i].is_favourite=list[i].is_favourite;
        newgame->questions_list[i].question_num=list[i].question_num;
        newgame->questions_list[i].question_score=list[i].question_score;
        strcpy(newgame->questions_list[i].question_answer,list[i].question_answer);
    }
    newgame->next_game=NULL;
    if((*Games_List_Head)==NULL){
        *Games_List_Head=newgame;
        return;
    }
    Game* temp=(*Games_List_Head);
    while(temp->next_game!=NULL){
        temp=temp->next_game;
    }
    temp->next_game=newgame;
}
////////////////////////////////////////////////////////////////////////////////////////
int player_score(Game* Games_List_Head,int player_id){
    int result=0;
    Game* game=Games_List_Head;
    while(game!=NULL){
        if(game->player_ID==player_id){
            result+=game->game_score;
        }
        game=game->next_game;
    }
    return result;
}
/////////////////////////////////////////////////////////////////////////////////////////
void sorting_by_nof_games(Player* Players_List_Head ){ 
    if (Players_List_Head== NULL) return;
    
    int temp1,temp2;
    char temp_psuedoname[20],temp2_psuedoname[10][20];
    Player* current=Players_List_Head;
    Player* next_current= Players_List_Head->next_player;
    Player* new_last_sorted = NULL;
    bool found;
    int temp_num_domains=0;
    do {
      found= false;
      current=Players_List_Head;
      next_current=current->next_player;
        while (current->next_player != new_last_sorted) {
            if (current->number_of_games_played < next_current->number_of_games_played) {
                temp1=current->number_of_games_played;
                temp2=current->total_score;
                temp_num_domains=current->fav_num;
                current->total_score=next_current->total_score;
                next_current->total_score=temp2;
                current->fav_num=next_current->fav_num;
                next_current->fav_num=temp_num_domains;
                for (int i=0;i<10;i++){
                 strcpy(temp2_psuedoname[i],current->favourite_areas[i]);
                 strcpy(current->favourite_areas[i],next_current->favourite_areas[i]);
                 strcpy(next_current->favourite_areas[i],temp2_psuedoname[i]);
                }
                strcpy(temp_psuedoname,current->pseudoname);
                strcpy(current-> pseudoname,next_current-> pseudoname);
                strcpy(next_current->pseudoname,temp_psuedoname);
                current->number_of_games_played = next_current->number_of_games_played;
                next_current->number_of_games_played=temp1;
                reg_date temp_date= current->registration_date ;
                next_current->registration_date=current->registration_date;
                next_current->registration_date=temp_date;
                
                found=true;
            }
            current = current->next_player;
            next_current=next_current->next_player;
        }
        new_last_sorted = current;
    }while(found==true);
} 
/////////////////////////////////////////////////////////////////////////////////////////
void sorting_by_score(Player* Players_List_Head ){ 
    if (Players_List_Head== NULL) return;
    
    int temp1,temp2;
    char temp_psuedoname[20],temp2_psuedoname[10][20];
    Player* current=Players_List_Head;
    Player* next_current= Players_List_Head->next_player;
    Player* new_last_sorted = NULL;
    bool found;
    int temp_num_domains=0;
    do {
      found= false;
      current=Players_List_Head;
      next_current=current->next_player;
        while (current->next_player != new_last_sorted) {
            if (current->total_score < next_current->total_score) {
                temp1=current->number_of_games_played;
                temp2=current->total_score;
                temp_num_domains=current->fav_num;
                current->total_score=next_current->total_score;
                next_current->total_score=temp2;
                current->fav_num=next_current->fav_num;
                next_current->fav_num=temp_num_domains;
                for (int i=0;i<10;i++){
                 strcpy(temp2_psuedoname[i],current->favourite_areas[i]);
                 strcpy(current->favourite_areas[i],next_current->favourite_areas[i]);
                 strcpy(next_current->favourite_areas[i],temp2_psuedoname[i]);
                }
                strcpy(temp_psuedoname,current->pseudoname);
                strcpy(current-> pseudoname,next_current-> pseudoname);
                strcpy(next_current->pseudoname,temp_psuedoname);
                current->number_of_games_played = next_current->number_of_games_played;
                next_current->number_of_games_played=temp1;
                reg_date temp_date= current->registration_date ;
                next_current->registration_date=current->registration_date;
                next_current->registration_date=temp_date;
                
                found=true;
            }
            current = current->next_player;
            next_current=next_current->next_player;
        }
        new_last_sorted = current;
    }while(found==true);
} 
/////////////////////////////////////////////////////////////////////////////////////////
void load_test_players_from_file(Player** Players_List_Head,char *domains[]){
    FILE* reading_file;
    char loaded_line[300];
    int fav[]={0};
    int id;
    char pseudo[20];
    int day;
    int month;
    int year;
    int numgames;
    int total_score;
    char question[100];
    char questionAnswer[50];
    reading_file=fopen("players.txt","r");
    while(fgets(loaded_line,300,reading_file)){
        sscanf(loaded_line,"%d %s %d %d %d %d %d",&id,pseudo,&day,&month,&year,&numgames,&total_score);
        register_player(Players_List_Head,id,pseudo,day,month,year,1,domains,fav,numgames,total_score);
    }

}
// /////////////////////////////////////////////////////////////////////////////////////////
void load_test_games_from_file(Game** Games_List_Head){
    FILE* reading_file;
    char loaded_line[300];
    int playerid;
    int gamelevel;
    int gamescore;
        GameQuestion list[15];
    reading_file=fopen("games.txt","r");
    while(fgets(loaded_line,300,reading_file)){
        sscanf(loaded_line,"%d %d %d",&playerid,&gamelevel,&gamescore);
        for(int o=0;o<15;o++){
            if(o==0){
                list[o].question_score=gamescore;
            }
            else{
                list[o].question_score=0;
            }
        }
        add_game(Games_List_Head,playerid,gamelevel,list,gamescore);
    }
}