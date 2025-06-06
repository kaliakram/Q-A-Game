#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "TP_ALSDD_LIB.h"

int main(){                                                                                                                                                                
            esi_interface();                                                                                                                                                    
            system("pause");
            clearScreen();
            our_names();
            system("pause");
            clearScreen();
    
    char *domains[]={
        "biology","religion","math","history","geography","chemistry","physics","literature","sports","computer"
    };
    char *suggestions[] = {
        "photosynthesis", "2", "3.14", "Washington", "Pacific", "H2O", "300000", "Shakespeare", "11",
        "cell", "zoology", "chlorophyll", "mitochondria", "Tripitaka", "Muhammad", "Buddha", "Vedas", "15", "12",
        "25", "56", "1945", "Armstrong", "Ares", "Columbus", "Pompeii", "Africa", "Paris", "Japan",
        "Nile", "Sahara", "O", "6", "Na", "Au", "Fe", "kilogram", "gravity", "proton",
        "Newton", "c", "Orwell", "Homer", "Tolstoy", "Dostoevsky", "RAM", "motherboard", "HDD", "ENIAC",
        "HTML"
    };
    bool quit=false;
    bool is_loaded=false;
    int choice=0;
    int playerid=0;
    int h=1;
    Player* player=NULL;
    bool logged=false;
    Question *Questions_List=NULL;
    Player *Players_List=NULL;
    Game *Games_List=NULL;
    Question *easy,*medium,*hard;
    load_test_players_from_file(&Players_List,domains);
    load_test_games_from_file(&Games_List);
    easy=medium=hard=NULL;
    Player* temp=NULL;
    while(quit==false){
        welcome_ascii();
        printf("Please choose one of the following functions:\n");
        printf("1-Login as a player\n");
        printf("2-Register a new player\n");
        printf("3-Load the questions from the file\n");
        printf("4-Show the list of players\n");
        printf("5-Add a question\n");
        printf("6-Delete a question\n");
        printf("7-Start a game\n");
        printf("8-Get the total score of a player\n");
        printf("9-Sort the players by the number of games played\n");
        printf("10-Sort the players by the total score\n");
        printf("11-Delete a player\n");
        printf("12-Exit\n");
        printf("enter your choice:");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
        clearScreen();
        login_page();
            if (logged==true)
            {
                printf("\x1b[32m(you are being logged out !)\x1b[0m\n");
                logged=false;
                system("pause");
            }
            
            printf("please enter your id:");
            scanf("%d",&playerid);
            temp=Players_List;
            bool found=false;
            while(temp!=NULL){
                if(temp->ID==playerid){
                    found=true;
                    player=temp;
                    playerid=player->ID;
                }
                temp=temp->next_player;
            }
            if (found==true){
                logged=true;
                printf("\x1b[32mwelcome,%s,you are logged in again\x1b[0m\n",player->pseudoname);
                found=false;
            }
            else{
                playerid=0;
                printf("\x1b[31m(invalid login.there is no player with such an id ! try registering as a new player)\x1b[0m\n");
            }
            break;
        case 2:
        clearScreen();
        register_page();
            printf("enter your id:\n");
            int id=0;
            char pseudo[20];
            int fav_num=0;
            int fav[10];
            int mm,dd,yyyy;
            bool invalid=false;
            temp=Players_List;
            scanf("%d",&id);
            while(temp!=NULL){
                if(temp->ID==id){
                    printf("\x1b[31m(this id already exists/invalid, try another id)\x1b[0m\n");
                    invalid=true;
                    break;
                }
                temp=temp->next_player;
            }
            if (invalid==false)
            {          
            printf("enter your pseudoname:\n");
            scanf("%s",pseudo);
            temp=Players_List;
            while (temp!=NULL)
            {
                if(strcmp(temp->pseudoname,pseudo)==0){
                    printf("\x1b[31m(this pseudoname already exists,try another pseudoname)\x1b[0m\n");
                    invalid=true;
                }
                temp=temp->next_player;
            }
            }

            if(invalid==false){
                printf("how many preffered domains do you have(choose between 1 and 10):\n");
                scanf("%d",&fav_num);
                while((fav_num<1) || (fav_num>10)){
                    printf("\x1b[31mplease enter a valid number of favourite domains:\x1b[0m");
                    scanf("%d",&fav_num);
                }
                printf("please choose your preffered domains from here:\n");
                for(int k=0;k<10;k++){
                    printf("%d-%s\n",(k+1),domains[k]);
                }
                for(int l=0;l<fav_num;l++){
                    scanf("%d",&fav[l]);
                    while((fav[l]<1) || (fav[l]>10)){
                        printf("\x1b[31mplease enter a valid choice for the favourite domains:\x1b[0m\n");
                        scanf("%d",&fav[l]);
                    }
                    fav[l]=fav[l]-1;
                }
                printf("enter your registration date:\n");
                printf("enter your day of registration:");
                scanf("%d",&dd);
                printf("enter your month of registration:");
                scanf("%d",&mm);
                printf("enter your year of registration:");
                scanf("%d",&yyyy);
                register_player(&Players_List,id,pseudo,dd,mm,yyyy,fav_num,domains,fav,0,0);
                logged=true;
                playerid=id;
                temp=Players_List;
                while (temp!=NULL)
                {
                    if (temp->ID==playerid){
                        player=temp;
                    }
                    temp=temp->next_player;
                }
                printf("\x1b[32mwelcome!\x1b[0m\n");
                
            }
            break;
        case 3:
            printf("Loading the questions from the file:\n");
            Question** head=&Questions_List;
            load_questions_from_the_file(head);
            system("pause");
            printf("\x1b[32m(loading is completed successfully !)\x1b[0m\n");
            printf("splitting the list into 3 sublists according to the difficulty:\n");
            split_questions_difficulty_level(Questions_List,&easy,&medium,&hard);
            system("pause");
            printf("\x1b[32myour list of questions have been splitted succesfully!\x1b[0m\n");
            is_loaded=true;
            break;
        case 4:
        clearScreen();
        list_of_players();
            if (Players_List==NULL){
                printf("\x1b[31mthere is no registered player for now :)\x1b[0m\n");
            }
            else{
                temp=Players_List;
                int i=1;
                while(temp!=NULL){
                    printf("%d\n",i);
                    printf("pseudoname:%s\n",temp->pseudoname);
                    printf("id:%d\n",temp->ID);
                    printf("registration date:%d/%d/%d\n",temp->registration_date.dd,temp->registration_date.mm,temp->registration_date.yyyy);
                    printf("favourite areas:\n");
                    for(int z=0;z<temp->fav_num;z++){
                        printf("%s\n",temp->favourite_areas[z]);
                    }
                    printf("number of games played:%d\n",temp->number_of_games_played);
                    printf("total score:%d\n",temp->total_score);
                    printf("-------------------------------------------\n");
                    temp=temp->next_player;
                    i++;
                }
            }
            break;
        case 5:
            clearScreen();
            int quest_num;
            int subject_num=0;
            char degree[10];
            char question_content[100];
            char correct[50];
            bool invalid_question=false;
            add_a_question();
            printf("enter the number of the question:");
            scanf("%d",&quest_num);
            Question* temp_=Questions_List;
            while (temp_!=NULL)
            {
                if (temp_->number==quest_num){
                    printf("\x1b[31mthis number is already used for another question\x1b[0m\n");
                    invalid_question=true;
                }
                temp_=temp_->next_question;
            }
            if(invalid_question==false){
                printf("enter the subject area of the question from the following domains:\n");
                for(int k=0;k<10;k++){
                    printf("%d-%s\n",(k+1),domains[k]);
                }
                scanf("%d",&subject_num);
                while((subject_num<1) || (subject_num>10)){
                    printf("\x1b[31menter a valid option:\x1b[0m\n");
                    scanf("%d",&subject_num);
                }
                printf("enter the degree of difficulty of the question:");
                scanf("%s",degree);
                if((strcmp(degree,"hard")!=0)&&(strcmp(degree,"easy")!=0)&&(strcmp(degree,"medium"))){
                    printf("\x1b[31mplease enter a valid difficulty level:\x1b[0m");
                    scanf("%s",degree);
                }
                printf("enter the content of the question:\n");
                getchar();
                fgets(question_content,100,stdin);
                printf("enter the correct answer for the question:\n");
                getchar();
                fgets(correct,50,stdin);
                add_question(&Questions_List,quest_num,domains[subject_num-1],degree,question_content,correct);
                printf("\x1b[32myour question have been added successfully!\x1b[0m");
    
            }

            break;
        case 6:
            clearScreen();
            delete_a_question();
            int ques_num=0;
            printf("enter the number of the question:\n");
            scanf("%d",&ques_num);
            if (Questions_List==NULL){
                printf("\x1b[31m(there are no question to remove!)\x1b[0m\n");
            }else{
                temp_=Questions_List;
                bool found_question=false;
                while ((temp_!=NULL)&&(found_question==false))
                {   
                    if(temp_->number==ques_num){
                        found_question=true;
                    }
                    temp_=temp_->next_question;
                }
                if(found_question==true){
                    delete_question(&Questions_List,ques_num);
                    printf("\x1b[32m(the question has been deleted successfully!)\x1b[0m\n");
                    
            Question* tempm=Questions_List;
                }else{
                    printf("\x1b[31m(no question with such a number has been found!)\x1b[0m\n");
                }
            }
            break;
        case 7:
        if(is_loaded==false){
            printf("Loading the questions from the file:\n");
            Question** head=&Questions_List;
            load_questions_from_the_file(head);
            system("pause");
            printf("\x1b[32m(loading is completed successfully !)\n");
            printf("splitting the list into 3 sublists according to the difficulty:\n");
            split_questions_difficulty_level(Questions_List,&easy,&medium,&hard);
            system("pause");
            printf("\x1b[32myour list of questions have been splitted succesfully!\x1b[0m\n");
            is_loaded=true;

        }
        clearScreen();
        game_header();
        if(logged==true){
            GameQuestion questions[15];
            printf("enter a level for the game:");
            int level;
            scanf("%d",&level);
            int gamescore=0;
            bool quit_game=false;
            Question* quest=NULL;
            char domainchoice;
            int not_pref_choice=0;
            char easy_choices[2][50];
            int easychoice=0;
            int random=0;
            char medium_choices[4][50];
            bool found_not_preffered=false;
            int mediumchoice=0;
            char hard_answer[50];
            while (quit_game!=true)
            {
                switch (level)
                {
                case 1:
                easy_ascii();
                    for(int i=1;i<=6;i++){
                        system("pause");
                        printf("do you want a question from one of your preffered domains?(y/n):");
                        scanf(" %c",&domainchoice);
                        while ((domainchoice!='y')&&(domainchoice!='n'))
                        {
                            printf("\x1b[31menter a valid choice:\x1b[0m");
                            scanf(" %c",&domainchoice);
                        }
                        if(domainchoice=='y'){
                            srand(time(0));
                            questions[i-1].is_favourite=true;
                            random=rand()%player->fav_num;
                            quest=random_question(player->favourite_areas[random],easy);
                            easy_question_display(quest,suggestions,easy_choices);
                            scanf("%d",&easychoice);
                            if(strcmp(quest->correct_answer,easy_choices[easychoice-1])==0){
                                printf("\x1b[32mtrue\x1b[0m\n");
                            }else{
                                printf("\x1b[31mfalse\x1b[0m\n");
                            }
                        }else{
                            questions[i-1].is_favourite=false;
                            found_not_preffered=false;
                            not_pref_choice=0;
                            while(found_not_preffered==false){
                                found_not_preffered=true;
                                not_pref_choice=rand()%10;
                                for(int y=0;y<player->fav_num;y++){
                                    if(strcmp(player->favourite_areas[y],domains[not_pref_choice])==0){
                                        found_not_preffered=false;
                                    }
                                }  
                            }
                            quest=random_question(domains[not_pref_choice],easy);
                            easy_question_display(quest,suggestions,easy_choices);
                            scanf("%d",&easychoice);
                            if(strcmp(quest->correct_answer,easy_choices[easychoice-1])==0){
                                printf("\x1b[32mtrue\x1b[0m\n");

                            }else{
                                printf("\x1b[31mfalse\x1b[0m\n");
                            }
                        }
                        strcpy(questions[i-1].question_answer,easy_choices[easychoice-1]);
                        questions[i-1].question_num=quest->number;
                        questions[i-1].question_score=question_score(&questions[i-1],Questions_List);
                    }

/////////////////////////////////////////////////////////////////////////////////////////////////////////


                    medium_ascii();
                    for(int i=1;i<=6;i++){
                        system("pause");
                        printf("do you want a question from one of your preffered domains?(y/n):");
                        scanf(" %c",&domainchoice);
                        while ((domainchoice!='y')&&(domainchoice!='n'))
                        {
                            printf("\x1b[31menter a valid choice:\x1b[0m");
                            scanf(" %c",&domainchoice);
                        }
                        if(domainchoice=='y'){
                            questions[i+5].is_favourite=true;
                            srand(time(0));
                            random=rand()%player->fav_num;
                            quest=random_question(player->favourite_areas[random],medium);
                            medium_question_display(quest,suggestions,medium_choices);
                            scanf("%d",&mediumchoice);
                            if(strcmp(quest->correct_answer,medium_choices[mediumchoice-1])==0){
                                printf("\x1b[32mtrue\x1b[0m\n");

                            }else{
                                printf("\x1b[31mfalse\x1b[0m\n");
                            }
                        }else{
                            questions[i+5].is_favourite=false;
                            found_not_preffered=false;
                            not_pref_choice=0;
                            while(found_not_preffered==false){
                                found_not_preffered=true;
                                not_pref_choice=rand()%10;
                                for(int y=0;y<player->fav_num;y++){
                                    if(strcmp(player->favourite_areas[y],domains[not_pref_choice])==0){
                                        found_not_preffered=false;
                                    }
                                }  
                            }
                            quest=random_question(domains[not_pref_choice],medium);
                            medium_question_display(quest,suggestions,medium_choices);
                            scanf("%d",&mediumchoice);
                            if(strcmp(quest->correct_answer,medium_choices[mediumchoice-1])==0){
                                printf("\x1b[32mtrue\x1b[0m\n");

                            }else{
                                printf("\x1b[31mfalse\x1b[0m\n");
                            }
                        }
                        strcpy(questions[i+5].question_answer,medium_choices[mediumchoice-1]);
                        questions[i+5].question_num=quest->number;
                        questions[i+5].question_score=question_score(&questions[i+5],Questions_List);
                    }
                        
/////////////////////////////////////////////////////////////////////////////////////////////////////////



                    hard_ascii();
                    for(int i=1;i<=3;i++){
                        srand(time(0));
                        printf("do you want a question from one of your preffered domains?(y/n):");
                        scanf(" %c",&domainchoice);
                        while ((domainchoice!='y')&&(domainchoice!='n'))
                        {
                            printf("\x1b[31menter a valid choice:\x1b[0m");
                            scanf(" %c",&domainchoice);
                        }
                        if(domainchoice=='y'){
                            questions[i+11].is_favourite=true;
                            random=rand()%player->fav_num;
                            quest=random_question(player->favourite_areas[random],hard);
                            printf("%s\n",quest->content_of_the_question);
                            printf("please enter your answer:");
                            getchar();
                            fgets(hard_answer,50,stdin);
                            if((strlen(hard_answer)>0)&&(hard_answer[strlen(hard_answer)-1]=='\n')){
                                hard_answer[strlen(hard_answer)-1]='\0';
                            }
                            if(strcmp(quest->correct_answer,hard_answer)==0){
                                printf("\x1b[32mtrue\x1b[0m\n");
                            }else{
                                printf("\x1b[31mfalse\x1b[0m\n");
                            }

                        }else{
                            questions[i+11].is_favourite=false;
                            found_not_preffered=false;
                            not_pref_choice=0;
                            while(found_not_preffered==false){
                                found_not_preffered=true;
                                not_pref_choice=rand()%10;
                                for(int y=0;y<player->fav_num;y++){
                                    if(strcmp(player->favourite_areas[y],domains[not_pref_choice])==0){
                                        found_not_preffered=false;
                                    }
                                }  
                            }
                            quest=random_question(domains[not_pref_choice],hard);
                            printf("%s\n",quest->content_of_the_question);
                            printf("please enter your answer:");
                            getchar();
                            fgets(hard_answer,50,stdin);
                            if((strlen(hard_answer)>0)&&(hard_answer[strlen(hard_answer)-1]=='\n')){
                                hard_answer[strlen(hard_answer)-1]='\0';
                            }
                            if(strcmp(quest->correct_answer,hard_answer)==0){
                                printf("\x1b[32mtrue\x1b[0m\n");
                            }else{
                                printf("\x1b[31mfalse\x1b[0m\n");
                            }

                        }

                        strcpy(questions[i+11].question_answer,hard_answer);
                        questions[i+11].question_num=quest->number;
                        questions[i+11].question_score=question_score(&questions[i+11],Questions_List);
                    }

                    gamescore=total_game_score(questions);
                    player->number_of_games_played++;
                    add_game(&Games_List,playerid,level,questions,gamescore);
                    Game* temp_game=Games_List;
                    quit_game=true;
                    break;
                case 2://level 2
                easy_ascii();
                for(int i=1;i<=5;i++){
                    system("pause");
                    printf("do you want a question from one of your preffered domains?(y/n):");
                    scanf(" %c",&domainchoice);
                    while ((domainchoice!='y')&&(domainchoice!='n'))
                    {
                        printf("\x1b[31menter a valid choice:\x1b[0m");
                        scanf(" %c",&domainchoice);
                    }
                    if(domainchoice=='y'){
                        srand(time(0));
                        questions[i-1].is_favourite=true;
                        random=rand()%player->fav_num;
                        quest=random_question(player->favourite_areas[random],easy);
                        easy_question_display(quest,suggestions,easy_choices);
                        scanf("%d",&easychoice);
                        if(strcmp(quest->correct_answer,easy_choices[easychoice-1])==0){
                            printf("\x1b[32mtrue\x1b[0m\n");
                        }else{
                            printf("\x1b[31mfalse\x1b[0m\n");
                        }
                    }else{
                        questions[i-1].is_favourite=false;
                        found_not_preffered=false; // this is a comment using vim while trying t learn it using my lab work
                        not_pref_choice=0;
                        while(found_not_preffered==false){
                            found_not_preffered=true;
                            not_pref_choice=rand()%10;
                            for(int y=0;y<player->fav_num;y++){
                                if(strcmp(player->favourite_areas[y],domains[not_pref_choice])==0){
                                    found_not_preffered=false;
                                }
                            }  
                        }
                        quest=random_question(domains[not_pref_choice],easy);
                        easy_question_display(quest,suggestions,easy_choices);
                        scanf("%d",&easychoice);
                        if(strcmp(quest->correct_answer,easy_choices[easychoice-1])==0){
                            printf("\x1b[32mtrue\x1b[0m\n");

                        }else{
                            printf("\x1b[31mfalse\x1b[0m\n");
                        }
                    }
                    strcpy(questions[i-1].question_answer,easy_choices[easychoice-1]);
                    questions[i-1].question_num=quest->number;
                    questions[i-1].question_score=question_score(&questions[i-1],Questions_List);
                }

/////////////////////////////////////////////////////////////////////////////////////////////////////////


                medium_ascii();
                for(int i=1;i<=5;i++){
                    system("pause");
                    printf("do you want a question from one of your preffered domains?(y/n):");
                    scanf(" %c",&domainchoice);
                    while ((domainchoice!='y')&&(domainchoice!='n'))
                    {
                        printf("\x1b[31menter a valid choice:\x1b[0m");
                        scanf(" %c",&domainchoice);
                    }
                    if(domainchoice=='y'){
                        questions[i+4].is_favourite=true;
                        srand(time(0));
                        random=rand()%player->fav_num;
                        quest=random_question(player->favourite_areas[random],medium);
                        medium_question_display(quest,suggestions,medium_choices);
                        scanf("%d",&mediumchoice);
                        if(strcmp(quest->correct_answer,medium_choices[mediumchoice-1])==0){
                            printf("\x1b[32mtrue\x1b[0m\n");

                        }else{
                            printf("\x1b[31mfalse\x1b[0m\n");
                        }
                    }else{
                        questions[i+4].is_favourite=false;
                        found_not_preffered=false;
                        int not_pref_choice=0;
                        while(found_not_preffered==false){
                            found_not_preffered=true;
                            not_pref_choice=rand()%10;
                            for(int y=0;y<player->fav_num;y++){
                                if(strcmp(player->favourite_areas[y],domains[not_pref_choice])==0){
                                    found_not_preffered=false;
                                }
                            }  
                        }
                        quest=random_question(domains[not_pref_choice],medium);
                        medium_question_display(quest,suggestions,medium_choices);
                        scanf("%d",&mediumchoice);
                        if(strcmp(quest->correct_answer,medium_choices[mediumchoice-1])==0){
                            printf("\x1b[32mtrue\x1b[0m\n");

                        }else{
                            printf("\x1b[31mfalse\x1b[0m\n");
                        }
                    }
                    strcpy(questions[i+4].question_answer,medium_choices[mediumchoice-1]);
                    questions[i+4].question_num=quest->number;
                    questions[i+4].question_score=question_score(&questions[i+4],Questions_List);
                }
                    
/////////////////////////////////////////////////////////////////////////////////////////////////////////



                hard_ascii();
                for(int i=1;i<=5;i++){
                    srand(time(0));
                    printf("do you want a question from one of your preffered domains?(y/n):");
                    scanf(" %c",&domainchoice);
                    while ((domainchoice!='y')&&(domainchoice!='n'))
                    {
                        printf("\x1b[31menter a valid choice:\x1b[0m");
                        scanf(" %c",&domainchoice);
                    }
                    if(domainchoice=='y'){
                        questions[i+9].is_favourite=true;
                        random=rand()%player->fav_num;
                        quest=random_question(player->favourite_areas[random],hard);
                        printf("%s\n",quest->content_of_the_question);
                        printf("please enter your answer:");
                        getchar();
                        fgets(hard_answer,50,stdin);
                        if((strlen(hard_answer)>0)&&(hard_answer[strlen(hard_answer)-1]=='\n')){
                            hard_answer[strlen(hard_answer)-1]='\0';
                        }
                        if(strcmp(quest->correct_answer,hard_answer)==0){
                            printf("\x1b[32mtrue\x1b[0m\n");
                        }else{
                            printf("\x1b[31mfalse\x1b[0m\n");
                        }

                    }else{
                        questions[i+9].is_favourite=false;
                        found_not_preffered=false;
                        not_pref_choice=0;
                        while(found_not_preffered==false){
                            found_not_preffered=true;
                            not_pref_choice=rand()%10;
                            for(int y=0;y<player->fav_num;y++){
                                if(strcmp(player->favourite_areas[y],domains[not_pref_choice])==0){
                                    found_not_preffered=false;
                                }
                            }  
                        }
                        quest=random_question(domains[not_pref_choice],hard);
                        printf("%s\n",quest->content_of_the_question);
                        printf("please enter your answer:");
                        getchar();
                        fgets(hard_answer,50,stdin);
                        if((strlen(hard_answer)>0)&&(hard_answer[strlen(hard_answer)-1]=='\n')){
                            hard_answer[strlen(hard_answer)-1]='\0';
                        }
                        if(strcmp(quest->correct_answer,hard_answer)==0){
                            printf("\x1b[32mtrue\x1b[0m\n");
                        }else{
                            printf("\x1b[31mfalse\x1b[0m\n");
                        }

                    }

                    strcpy(questions[i+9].question_answer,hard_answer);
                    questions[i+9].question_num=quest->number;
                    questions[i+9].question_score=question_score(&questions[i+9],Questions_List);
                }

                gamescore=total_game_score(questions);
                player->number_of_games_played++;
                add_game(&Games_List,playerid,level,questions,gamescore);
                quit_game=true;
                break;
                    break;
                case 3:
                easy_ascii();
                for(int i=1;i<=2;i++){
                    system("pause");
                    printf("do you want a question from one of your preffered domains?(y/n):");
                    scanf(" %c",&domainchoice);
                    while ((domainchoice!='y')&&(domainchoice!='n'))
                    {
                        printf("\x1b[31menter a valid choice:\x1b[0m");
                        scanf(" %c",&domainchoice);
                    }
                    if(domainchoice=='y'){
                        srand(time(0));
                        questions[i-1].is_favourite=true;
                        random=rand()%player->fav_num;
                        quest=random_question(player->favourite_areas[random],easy);
                        easy_question_display(quest,suggestions,easy_choices);
                        scanf("%d",&easychoice);
                        if(strcmp(quest->correct_answer,easy_choices[easychoice-1])==0){
                            printf("\x1b[32mtrue\x1b[0m\n");
                        }else{
                            printf("\x1b[31mfalse\x1b[0m\n");
                        }
                    }else{
                        questions[i-1].is_favourite=false;
                        found_not_preffered=false;
                        not_pref_choice=0;
                        while(found_not_preffered==false){
                            found_not_preffered=true;
                            not_pref_choice=rand()%10;
                            for(int y=0;y<player->fav_num;y++){
                                if(strcmp(player->favourite_areas[y],domains[not_pref_choice])==0){
                                    found_not_preffered=false;
                                }
                            }  
                        }
                        quest=random_question(domains[not_pref_choice],easy);
                        easy_question_display(quest,suggestions,easy_choices);
                        scanf("%d",&easychoice);
                        if(strcmp(quest->correct_answer,easy_choices[easychoice-1])==0){
                            printf("\x1b[32mtrue\x1b[0m\n");

                        }else{
                            printf("\x1b[31mfalse\x1b[0m\n");
                        }
                    }
                    strcpy(questions[i-1].question_answer,easy_choices[easychoice-1]);
                    questions[i-1].question_num=quest->number;
                    questions[i-1].question_score=question_score(&questions[i-1],Questions_List);
                }

/////////////////////////////////////////////////////////////////////////////////////////////////////////


                medium_ascii();
                for(int i=1;i<=5;i++){
                    system("pause");
                    printf("do you want a question from one of your preffered domains?(y/n):");
                    scanf(" %c",&domainchoice);
                    while ((domainchoice!='y')&&(domainchoice!='n'))
                    {
                        printf("\x1b[31menter a valid choice:\x1b[0m");
                        scanf(" %c",&domainchoice);
                    }
                    if(domainchoice=='y'){
                        questions[i+1].is_favourite=true;
                        srand(time(0));
                        random=rand()%player->fav_num;
                        quest=random_question(player->favourite_areas[random],medium);
                        medium_question_display(quest,suggestions,medium_choices);
                        scanf("%d",&mediumchoice);
                        if(strcmp(quest->correct_answer,medium_choices[mediumchoice-1])==0){
                            printf("\x1b[32mtrue\x1b[0m\n");

                        }else{
                            printf("\x1b[31mfalse\x1b[0m\n");
                        }
                    }else{
                        questions[i+1].is_favourite=false;
                        found_not_preffered=false;
                        not_pref_choice=0;
                        while(found_not_preffered==false){
                            found_not_preffered=true;
                            not_pref_choice=rand()%10;
                            for(int y=0;y<player->fav_num;y++){
                                if(strcmp(player->favourite_areas[y],domains[not_pref_choice])==0){
                                    found_not_preffered=false;
                                }
                            }  
                        }
                        quest=random_question(domains[not_pref_choice],medium);
                        medium_question_display(quest,suggestions,medium_choices);
                        scanf("%d",&mediumchoice);
                        if(strcmp(quest->correct_answer,medium_choices[mediumchoice-1])==0){
                            printf("\x1b[32mtrue\x1b[0m\n");

                        }else{
                            printf("\x1b[31mfalse\x1b[0m\n");
                        }
                    }
                    strcpy(questions[i+1].question_answer,medium_choices[mediumchoice-1]);
                    questions[i+1].question_num=quest->number;
                    questions[i+1].question_score=question_score(&questions[i+1],Questions_List);
                }
                    
/////////////////////////////////////////////////////////////////////////////////////////////////////////
                hard_ascii();
                for(int i=1;i<=8;i++){
                    srand(time(0));
                    printf("do you want a question from one of your preffered domains?(y/n):");
                    scanf(" %c",&domainchoice);
                    while ((domainchoice!='y')&&(domainchoice!='n'))
                    {
                        printf("\x1b[31menter a valid choice:\x1b[0m");
                        scanf(" %c",&domainchoice);
                    }
                    if(domainchoice=='y'){
                        questions[i+6].is_favourite=true;
                        random=rand()%player->fav_num;
                        quest=random_question(player->favourite_areas[random],hard);
                        printf("%s\n",quest->content_of_the_question);
                        printf("please enter your answer:");
                        getchar();
                        fgets(hard_answer,50,stdin);
                        if((strlen(hard_answer)>0)&&(hard_answer[strlen(hard_answer)-1]=='\n')){
                            hard_answer[strlen(hard_answer)-1]='\0';
                        }
                        if(strcmp(quest->correct_answer,hard_answer)==0){
                            printf("\x1b[32mtrue\x1b[0m\n");
                        }else{
                            printf("\x1b[31mfalse\x1b[0m\n");
                        }

                    }else{
                        questions[i+6].is_favourite=false;
                        found_not_preffered=false;
                        not_pref_choice=0;
                        while(found_not_preffered==false){
                            found_not_preffered=true;
                            not_pref_choice=rand()%10;
                            for(int y=0;y<player->fav_num;y++){
                                if(strcmp(player->favourite_areas[y],domains[not_pref_choice])==0){
                                    found_not_preffered=false;
                                }
                            }  
                        }
                        quest=random_question(domains[not_pref_choice],hard);
                        printf("%s\n",quest->content_of_the_question);
                        printf("please enter your answer:");
                        getchar();
                        fgets(hard_answer,50,stdin);
                        if((strlen(hard_answer)>0)&&(hard_answer[strlen(hard_answer)-1]=='\n')){
                            hard_answer[strlen(hard_answer)-1]='\0';
                        }
                        if(strcmp(quest->correct_answer,hard_answer)==0){
                            printf("\x1b[32mtrue\x1b[0m\n");
                        }else{
                            printf("\x1b[31mfalse\x1b[0m\n");
                        }

                    }

                    strcpy(questions[i+6].question_answer,hard_answer);
                    questions[i+6].question_num=quest->number;
                    questions[i+6].question_score=question_score(&questions[i+6],Questions_List);
                }

                gamescore=total_game_score(questions);
                player->number_of_games_played++;
                player->total_score+=gamescore;
                add_game(&Games_List,playerid,level,questions,gamescore);
                quit_game=true;
                break;
                
                default:
                    printf("\x1b[31mplease enter a valid choice\x1b[0m\n");
                    system("pause");
                    clearScreen();
                    break;
                }
            }

        }else{
            printf("\x1b[31m(you should log in as a player in order to start a game!)\x1b[0m\n");
        }
        break;
        case 8:
            printf("Getting the total score of a player:\n");
            printf("enter the id of the user:");
            int playerscoreid=0;
            int playerscore=0;
            scanf("%d",&playerscoreid);
            temp=Players_List;
            bool foundplayer=false;
            while(temp!=NULL){
                if(temp->ID==playerscoreid){
                    foundplayer=true;
                    break;
                }
                temp=temp->next_player;
            }
            if(foundplayer==true){
                playerscore=player_score(Games_List,playerscoreid);
                printf("the score of player with id:%d is:%d\n",playerscoreid,playerscore);
                temp->total_score=playerscore;
            }else{
                printf("\x1b[31mthere is no player with such an id!\x1b[0m\n");
            }
            break;
        case 9:
            clearScreen();
            sorting_games();
            sorting_by_nof_games(Players_List);
            temp=Players_List;
            h=1;
            while(temp!=NULL){
                printf("%d-%s:%d->games number:%d\n",h,temp->pseudoname,temp->ID,temp->number_of_games_played);
                printf("------------------------------------\n");
                h++;
                temp=temp->next_player;
            }
            break;
        case 10:
        clearScreen();
            sorting_score();
            sorting_by_score(Players_List);
            temp=Players_List;
            h=1;
            while(temp!=NULL){
                printf("%d-%s:%d->score:%d\n",h,temp->pseudoname,temp->ID,temp->total_score);
                h++;
                printf("------------------------------------\n");
                temp=temp->next_player;
            }
            break;
        case 11:
            clearScreen();
            player_removal();
            int idid;
            printf("enter the id of the player you want to remove:\n");
            scanf("%d",&idid);
            bool found_user=false; 
            temp=Players_List;
            while(temp!=NULL){
                if(temp->ID==idid){
                    found_user=true;
                }
                temp=temp->next_player;
            }
            if (found_user==true){
                if(idid==playerid){
                    printf("(loggin out)\n");
                    logged=false;
                    player=NULL;
                }
                system("pause");
                delete_player(&Players_List,idid);
                printf("\x1b[32m(the user with id:%d have been removed successfully!)\x1b[0m\n",idid);
            }
            else{
                printf("\x1b[31m(there is no user with such an id!)\x1b[0m\n");
            }

            break;
        case 12:
        clearScreen();
        see_you_ascii();
            quit=true;
            break;
        default:
            printf("\x1b[31mThis wasn't a valid choice !\x1b[0m\n");
            break;
        }
        system("pause");
        clearScreen();
    }

    return 0;
}
