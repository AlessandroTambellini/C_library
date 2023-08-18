#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "utils.h"
#include "output_style.h"

#define DATAFILE "/var/chance.data"

struct user {
    int uid;
    int credits;
    int highscore;
    char name[100];
    int (*current_game)();
};

int get_player_data(void);
void register_new_player(void);
void update_player_data(void);
void show_highscore(void);
void jackpot(void);
void input_name(void);
void print_cards(char *, char *, int);
int take_wager(int, int);
void play_the_game(void);

// games
int pick_a_number(void);
int dealer_no_match(void);
int find_the_ace(void);

void fatal(char *);

// global player
struct user player;

int main(void)
{
    int choice, last_game;

    srand(time(0));

    if (get_player_data() == -1)
        register_new_player();

    while (choice != 7) {
        printf("\n%s%s== [ Game Of Chance ] ==%s\n", BOLD, RED, RESET);
        printf("1 - play the \"%sPick A Number%s\" game\n", BOLD, RESET);
        printf("2 - play the \"%sNo Match Dealer%s\" game\n", BOLD, RESET);
        printf("3 - play the \"%sFind The Ace%s\" game\n", BOLD, RESET);
        printf("4 - view current high score\n");
        printf("5 - change your user name\n");
        printf("6 - reset your account at 100 credits\n");
        printf("7 - quit\n\n");

        printf("[name: %s]\n", player.name);
        printf("[you have %u credits]\n\n -> ", player.credits);

        scanf("%d", &choice);

        if (choice < 1 || choice > 7)
            printf("%s[!]%s the number %d is invalid", RED, RESET, choice);
        else if (choice < 4) {
            if (choice != last_game) {
                if (choice == 1)
                    player.current_game = pick_a_number;
                if (choice == 2)
                    player.current_game = dealer_no_match;
                if (choice == 3)
                    player.current_game = find_the_ace;
            }
            play_the_game();
        } else if (choice == 4)
            show_highscore();
        else if (choice == 5) {
            printf("\nenter your new name: ");
            input_name();
            printf("you name has been changed. New name: %s", player.name);
        } else if (choice == 6) {
            player.credits = 100;
            printf("your account has been reset with %d credits.", player.credits);
        }
    }

    update_player_data();
    printf("\nThanks for playing! Bye.\n\n");
}

int get_player_data(void)
{
    int fd, uid, read_bytes;
    struct user entry;

    uid = getuid(); // built in function?

    fd = open(DATAFILE, O_RDONLY);
    if (fd == -1)
        return -1;

    read_bytes = read(fd, &entry, sizeof(struct user));
    // loop until proper uid if found and make sure read_bytes is working
    while (entry.uid != uid && read_bytes > 0)
        read_bytes = read(fd, &entry, sizeof(struct user));

    close(fd);
    // end of file was reached
    if (read_bytes < sizeof(struct user))
        return -1;
    else
        player = entry;
    return 1;
}

void register_new_player(void)
{
    int fd;

    printf("new player registration\n");
    printf("enter your name: ");
    input_name();

    player.uid = getuid();
    player.highscore = player.credits = 100;

    fd = open(DATAFILE, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if (fd == -1)
        fatal("in register_new_player() while opening file"); // not need for return, fatal exit with -1

    write(fd, &player, sizeof(struct user));
    close(fd);

    printf("\n%s, welcome to the game of change", player.name);
}

// mainly to update the score
void update_player_data(void)
{
    int fd, i, read_iud;
    char burned_byte;

    fd = open(DATAFILE, O_RDWR);
    if (fd == -1)
        fatal("in update_player_data() while opening file");
    read(fd, &read_iud, 4); // read the uid from the first struct
    while (read_iud != player.uid) {
        // way to pass to the next user
        for (i = 0; i < sizeof(struct user) - 4; i++)
            read(fd, &burned_byte, 1);
        read(fd, &read_iud, 4); // read the uid from the next user
    }
    write(fd, &(player.credits), 4);
    write(fd, &(player.highscore), 4);
    write(fd, &(player.name), 100);
    close(fd);
}

void show_highscore(void)
{
    uint32_t top_score = 0;
    char top_name[100];
    struct user entry;

    printf("\n============ | HIGH SCORE | ============\n");
    int fd = open(DATAFILE, O_RDONLY);
    if (fd == -1)
        fatal("in show_highscore() while opening file");

    // loop until end of file
    while (read(fd, &entry, sizeof(struct user)) > 0) {
        if (entry.highscore > top_score) {
            top_score = entry.highscore;
            strcpy(top_name, entry.name);
        }
    }
    close(fd);

    if (top_score > player.highscore)
        printf("%s has the highscore of %u", top_name, top_score);
    else
        printf("you currently have the highscore of %u credits!", player.highscore);
    printf("\n========================================\n");
}

void jackpot(void)
{
    printf("\n+*+*+*+*+*+* JACKPOT +*+*+*+*+*+*\n");
    printf("you won the jackpot of 100 credits!\n");
    player.credits += 100;
}

// this function is used to get the player name, since scanf() will stop input at the first space
void input_name(void)
{
    char *name_ptr, input_char = '\n';
    while (input_char == '\n')
        scanf("%c", &input_char);

    name_ptr = (char *)&(player.name);
    while (input_char != '\n') {
        *name_ptr = input_char;
        scanf("%c", &input_char);
        name_ptr++;
    }
    *name_ptr = 0;
}

void print_cards(char *message, char *cards, int user_pick)
{
    int i;

    printf("\n\t*** %s ***\n", message);
    printf("    \t._.\t._.\t._.\n");
    printf("cards:\t|%s%c%s|\t|%s%c%s|\t|%s%c%s|\n\t", RED, cards[0], RESET, RED, cards[1], RESET, RED, cards[2], RESET);
    if (user_pick == -1)
        printf(" 1 \t 2 \t 3 \n\n");
    else {
        for (i = 0; i < user_pick; i++)
            printf("\t");
        printf(" ^-- your pick\n\n");
    }
}

int take_wager(int avaiable_credits, int previous_wager)
{
    int wager, total_wager;

    printf("how many of your %d credits would you like to wager? ", avaiable_credits);
    scanf("%d", &wager);
    if (wager < 1) {
        printf("\nnice try, but I need a positive number :)\n");
        return -1;
    }

    total_wager = previous_wager + wager;
    if (total_wager > avaiable_credits) {
        printf("your total wager of %d is more than what you have!\n", total_wager);
        printf("you have %d credits, please try again.\n", avaiable_credits);
        return -1;
    }
    return wager;
}

void play_the_game(void)
{
    int play_again = 1;
    int (*game)();
    char selection;

    while (play_again) {
        printf("\n[DEBUG], current game pointer @ %p\n", player.current_game);
        if (player.current_game() != -1) {
            if (player.credits > player.highscore) // a new highscore is set
                player.highscore = player.credits;
            printf("\nyou now have %d credits\n", player.credits);
            update_player_data();
            printf("would you like to play again? (y/n) ");
            selection = '\n';
            while (selection == '\n')
                scanf("%c", &selection);
            if (selection == 'n')
                play_again = 0;
        } else
            play_again = 0;
    }
}

int pick_a_number(void)
{
    int pick, winning_number;

    printf("\n###### Pick A Number ######\n");
    printf("This game costs 10 credits to play.\n");
    printf("Simply pick a number between 1 and 20, \n");
    printf("and if you pick the winning number,\n");
    printf("you will win the jackpot of 100 credits!\n\n");

    winning_number = (rand() % 20) + 1;

    if (player.credits < 10) {
        printf("you only have %d credits. That's not enough to play!", player.credits);
        return -1;
    }
    player.credits -= 10;
    printf("10 credits have been deducted from your account.\n");
    printf("pick a number between 1 and 20: ");
    scanf("%d", &pick);

    printf("\nthe winning number is: %d\n", winning_number);
    if (pick == winning_number)
        jackpot();
    else
        printf("sorry, you didn't win :)\n");
    return 0;
}

int dealer_no_match(void)
{
    int i, j, numbers[16], wager = -1, match = -1;

    printf("\n::::::::::: No Match Dealer ::::::::::::\n");
    printf("In this game you can wager up to all of your credits.\n");
    printf("The dealer will deal out 16 random numbers between 0 and 99\n");
    printf("if there're no matches among them, you double your money!\n\n");

    if (player.credits == 0) {
        printf("you don't have any credits to wager!\n");
        return -1;
    }
    while (wager == -1)
        wager = take_wager(player.credits, 0);

    printf("\n\t::::: dealing out 16 random numbers ::::::\n");
    for (i = 0; i < 16; i++) {
        numbers[i] = rand() % 100;
        printf("%2d\t", numbers[i]);
        if (i % 8 == 7) // print a line break every 8 numbers
            printf("\n");
    }
    for (i = 0; i < 15; i++) {
        j = i + 1;
        while (j < 16) {
            if (numbers[i] == numbers[j])
                match = numbers[i];
            j++;
        }
    }

    if (match != -1) {
        printf("the dealer matched the number %d\n", match);
        printf("you lose %d credits.\n", wager);
        player.credits -= wager;
    } else {
        printf("\nthere were no matches!\nyou win %d credits!\n", wager);
        player.credits += wager;
    }
    return 0;
}

int find_the_ace(void)
{
    int i, ace, total_wager;
    int invalid_choice, pick = -1, wager_one = -1, wager_two = -1;
    char choice_two, cards[3] = { 'X', 'X', 'X' };

    ace = rand() % 3; // place the ace randomly

    printf("\n*********** Find The Ace ************\n");
    printf("In this game you can wager up to all of your credits.\n");
    printf("3 cards will be dealt out, 2 Queens and 1 Ace.\n");
    printf("If you find the ace, you will win the wager.\n");
    printf("After choosing the card, one of the queens will be revealed,\n");
    printf("at this point, you may either select a different card or \n");
    printf("increase your wager.\n\n");

    if (player.credits == 0) {
        printf("Sry, you have no credits :(\n");
        return -1;
    }

    while (wager_one == -1)
        wager_one = take_wager(player.credits, 0);

    print_cards("Dealing cards", cards, -1);
    pick = -1;
    while ((pick < 1) || (pick > 3)) {
        printf("Select a card: 1, 2, or 3: ");
        scanf("%d", &pick);
    }
    pick--;
    i = 0;
    while (i == ace || i == pick)
        i++;
    cards[i] = 'Q';
    print_cards("Revealing a queen", cards, pick);
    invalid_choice = 1;

    while (invalid_choice) {
        printf("would you like to: \n[c]hange your pick\tor\t[i]ncrease your wager?\n");
        printf("select c or i: ");
        choice_two = '\n';
        while (choice_two == '\n') // flush extra new lines
            scanf("%c", &choice_two);
        if (choice_two == 'i') {
            invalid_choice = 0;
            while (wager_two == -1)
                wager_two = take_wager(player.credits, wager_one);
        }
        if (choice_two == 'c') {
            i = invalid_choice = 0;
            while (i == pick || cards[i] == 'Q')
                i++;
            pick = i;
            printf("your card pick have been changed to card %d\n", pick + 1);
        }
    }

    for (i = 0; i < 3; i++) {
        if (ace == i)
            cards[i] = 'A';
        else
            cards[i] = 'Q';
    }
    print_cards("end result", cards, pick);

    if (pick == ace) {
        printf("you won %d credits from your first wager.\n", wager_one);
        player.credits += wager_one;
        if (wager_two != -1) {
            printf("and an additional %d credits from your second wager!\n", wager_two);
            player.credits += wager_two;
        }
    }
    // loss
    else {
        printf("you lost %d credits from your first wager.\n", wager_one);
        player.credits -= wager_one;
        if (wager_two != -1) {
            printf("and an additional %d credits from your second wager ;)\n", wager_two);
            player.credits -= wager_two;
        }
    }

    return 0;
}
