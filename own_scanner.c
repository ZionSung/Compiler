#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXLENGTH 100
#define TOKENS 1000
#define NUMBER 50
#define CATEGORY 20
#define NORMAL 10

int main( void ){
    
    int test2 = 0;
    int five = 5;
    int j = 0;
    char check_word[NORMAL];
    int i = 0; // counter
    // declare
    int total;
    
    int reserved_word_total, library_name_total, comment_total, identifier_total, constant_total, operator_total;
    int comparator_total, bracket_total, format_specifier_total, pointer_total, address_total, punctuation_total, printed_token_total;
    int confirm = 0;
    // punctuation
    char punctuation[CATEGORY];
    int punctuation_cat = 0;
    int punctuation_num[6];
    
    for( i = 0; i < CATEGORY; i++ ){
        punctuation[i] = '\0';
    }
    for( i = 0; i < 6; i++ ){
        punctuation_num[i] = 0;
    }
    // reserved word
    char check_reserved_word[NORMAL];
    char reserved_word[CATEGORY][NORMAL];
    int reserved_word_cat = 0;
    int reserved_word_num[16];
    
    for( i = 0; i < NORMAL; i++ ){
        check_reserved_word[i] = '\0';
    }
    for( i = 0; i < CATEGORY; i++ ){
        for( j = 0; j < NORMAL; j++ ){
            reserved_word[i][j] = '\0';
        }
    }
    for( i = 0; i < 16; i++ ){
        reserved_word_num[i] = 0;
    }
    
    // library name
    char library_name[CATEGORY][NORMAL];
    for( i = 0; i < CATEGORY; i++ ){
        for( j = 0; j < NORMAL; j++ ){
            library_name[i][j] = '\0';
        }
    }
    // comments
    char comment[NUMBER][MAXLENGTH];
    // identifier
    char identifier[CATEGORY][NORMAL];
    char check_identifier[NORMAL];
    int identifier_cat;
    int identifier_num[CATEGORY];
    int identifier_key; // if there have been declared, the key will be open
    // pointer
    char pointer[CATEGORY][NORMAL];
    int pointer_cat;
    int pointer_num[CATEGORY];
    // constant
    char constant[NUMBER][NORMAL];
    // operator
    char operator[11][3];
    char check_operator[3];
    int operator_cat;
    int operator_num[11];
    // comparator
    char comparator[6][3];
    char check_comparator[3];
    int comparator_cat;
    int comparator_num[6];
    // bracket
    char bracket[CATEGORY];
    int bracket_cat;
    int bracket_num[6];
    // format specifier
    char format_specifier[CATEGORY][3];
    char check_format_specifier[3];
    int format_specifier_cat;
    int format_specifier_num[CATEGORY];
    // pointer
    char address[CATEGORY][NORMAL];
    int address_cat;
    int address_num[CATEGORY];
    // printed token
    char printed_token[NUMBER][NORMAL];
    int printed_token_confirm = 0;
    
    char buf[MAXLENGTH];
    char word[TOKENS][MAXLENGTH];

    // initialize check_word
    for( i = 0; i < NORMAL; i++ ){
        check_word[i] = '\0';
    } 
    
    // initialize printed token
    for( i = 0; i < NUMBER; i++ ){
        for( j = 0; j < NORMAL; j++ ){
            printed_token[i][j] = '\0';
        }
    }
    
    // initialize address
    for( i = 0; i < CATEGORY; i++ ){
        for( j = 0; j < NORMAL; j++ ){
            address[i][j] = '\0';
        }
    }
    
    for( i = 0; i < CATEGORY; i++ ){
        address_num[i] = 0;
    }
    
    // initialize format specifier
    for( i = 0; i < CATEGORY; i++ ){
        for( j = 0; j < 3; j++ ){
            format_specifier[i][j] = '\0';
        }
    }
    
    for( i = 0; i < CATEGORY; i++ ){
        format_specifier_num[i] = 0;
    }
    
    // initialize bracket
    for( i = 0; i < CATEGORY; i++ ){
        bracket[i] = '\0';
    }
    for(i = 0; i < 6; i++ ){
        bracket_num[i] = 0;
    }
    
    // initialize comparator
    for( i = 0; i < 6; i++ ){
        for( j = 0; j < 3; j++ ){
            comparator[i][j] = '\0';
        }
    }
    
    for( i = 0; i < 6; i++ ){
        comparator_num[i] = 0;
    }
    
    
    // initialize identifier
    for( i = 0; i < CATEGORY; i++ ){
        for( j = 0; j < NORMAL; j++ ){
            identifier[i][j] = '\0';
        }
    }
    
    for( i = 0; i < CATEGORY; i++ ){
        identifier_num[i] = 0;
    }
    
    // initialize pointer
    for( i = 0; i < CATEGORY; i++ ){
        for( j = 0; j < NORMAL; j++ ){
            pointer[i][j] = '\0';
        }
    }
    
    for( i = 0; i < CATEGORY; i++ ){
        pointer_num[i] = 0;
    }
    
    // initialize constant
    for( i = 0; i < CATEGORY; i++ ){
        for( j = 0; j < NORMAL; j++ ){
            constant[i][j] = '\0';
        }
    }
    
    // initialize operator
    for( i = 0; i < 11; i++ ){
        for( j = 0; j < 3; j++ ){
            operator[i][j] = '\0';
        }
    }
    
    for( i = 0; i < 11; i++ ){
        operator_num[i] = 0;
    }
    
    // initialize comment
    for( i = 0; i < NUMBER; i++ ){
        for( j = 0; j < MAXLENGTH; j++ ){
            comment[i][j] = '\0';
        }
    }
    
    
    FILE *file;
    
    // read file
    file = fopen("test.txt", "r" );
    char ch;
    
    for( i = 0; i < 6; i++ ){
        punctuation_num[i] = 0;
    }
    
    while(!feof(file)){
        ch = getc(file);
        
        
        // Reserved word
        if( (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ){
            
            for( i = 0;  (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '1' && ch <= '9') || ch == '_'; i++ ){
                check_word[i] = ch;
                check_reserved_word[i] = tolower(ch);
                ch = getc(file);
            }
            
            
            // Identifier ( after declaring )
            for( i = 0; i < identifier_cat; i++ ){
                if(!strcmp(check_word, identifier[i])){
                    identifier_num[i]++;
                    identifier_total++;
                }
            }
            
            // Comfirm whether is reserved word
            // We need to add '!', because while it they are equal, the value would be 0, but we want 1
            if(!strcmp(check_reserved_word, "include") || !strcmp(check_reserved_word, "main") || !strcmp(check_reserved_word, "char") ||
               !strcmp(check_reserved_word, "int") || !strcmp(check_reserved_word, "float") || !strcmp(check_reserved_word, "if") ||
               !strcmp(check_reserved_word, "else") || !strcmp(check_reserved_word, "elseif") || !strcmp(check_reserved_word, "for") ||
               !strcmp(check_reserved_word, "while") || !strcmp(check_reserved_word, "do") || !strcmp(check_reserved_word, "return") ||
               !strcmp(check_reserved_word, "switch") || !strcmp(check_reserved_word, "case") || !strcmp(check_reserved_word, "printf") ||
               !strcmp(check_reserved_word, "scanf")){
                
                
                // Library name
                if(!strcmp(check_reserved_word, "include")){
                    //ch = getc(file);
                    if( ch == '<'){
                        for( i = 0; (ch = getc(file)) != '>'; i++ ){
                            library_name[library_name_total][i] = ch;
                        }
                        library_name_total++;
                    }
                    ch = getc(file); // avoid '>' being seen as an operator
                }
                
                // Printed token
                if(!strcmp(check_reserved_word, "printf")){
                    do{
                        if(ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}'){
                            // check whether this token has been in the array
                            for( i = 0; i < bracket_cat; i++ ){
                                if(bracket[i] == ch){
                                    bracket_num[i]++;
                                    bracket_total++;
                                    confirm = 1;
                                    break;
                                }
                            }
                            // add new category
                            if(confirm == 0){
                                bracket[bracket_cat] = ch;
                                bracket_num[bracket_cat]++;
                                bracket_cat++;
                                bracket_total++;
                            }
                            confirm = 0;
                        }
                        ch = getc(file);
                        // Punctuation
                        if(ch == ',' || ch == ';' || ch == ':' || ch == '#' || ch == '"' || ch == '\''){
                            // check whether this token has been in the array
                            for( i = 0; i < punctuation_cat; i++ ){
                                if(punctuation[i] == ch){
                                    punctuation_num[i]++;
                                    punctuation_total++;
                                    confirm = 1;
                                    break;
                                }
                            }
                            // add new category
                            if(confirm == 0){
                                punctuation[punctuation_cat] = ch;
                                punctuation_num[punctuation_cat]++;
                                punctuation_cat++;
                                punctuation_total++;
                            }
                            confirm = 0;
                        }
                    }while( ch != '"' );
                    ch = getc(file);
                    
                    while( ch != '"'){
                        for( i = 0; ch != ' '; i++ ){
                            // Format specifier
                            if( ch == '%' || ch == '\\' ){
                                if( ch == '%'){
                                    check_format_specifier[0] = ch;
                                    check_operator[0] = ch;
                                    ch = getc(file);
                                    if( ch == 'c' || ch == 'd' || ch == 'f'){
                                        check_format_specifier[1] = ch;
                                        // check whether this token has been in the array
                                        for( i = 0; i < format_specifier_cat; i++ ){
                                            if( (strcmp(check_format_specifier, format_specifier[i] )) == 0 ){  // if == 0, means equal
                                                format_specifier_num[i]++;
                                                format_specifier_total++;
                                                confirm = 1;
                                                break;
                                            }
                                        }
                                        // add new category
                                        if(confirm == 0){
                                            strcpy( format_specifier[format_specifier_cat], check_format_specifier );
                                            format_specifier_num[format_specifier_cat]++;
                                            format_specifier_cat++;
                                            format_specifier_total++;
                                        }
                                        confirm = 0;
                                    }
                                    else{ // it is operator
                                        // check whether this token has been in the array
                                        for( i = 0; i < operator_cat; i++ ){
                                            if( (strcmp(check_operator, operator[i] )) == 0 ){  // if == 0, means equal
                                                operator_num[i]++;
                                                operator_total++;
                                                confirm = 1;
                                                break;
                                            }
                                        }
                                        // add new category
                                        if(confirm == 0){
                                            strcpy( operator[operator_cat], check_operator );
                                            operator_num[operator_cat]++;
                                            operator_cat++;
                                            operator_total++;
                                        }
                                        confirm = 0;
                                    }
                                }
                                else{
                                    check_format_specifier[0] = ch;
                                    ch = getc(file);
                                    check_format_specifier[1] = ch;
                                    // check whether this token has been in the array
                                    for( i = 0; i < format_specifier_cat; i++ ){
                                        if( (strcmp(check_format_specifier, format_specifier[i] )) == 0 ){  // if == 0, means equal
                                            format_specifier_num[i]++;
                                            format_specifier_total++;
                                            confirm = 1;
                                            break;
                                        }
                                    }
                                    // add new category
                                    if(confirm == 0){
                                        strcpy( format_specifier[format_specifier_cat], check_format_specifier );
                                        format_specifier_num[format_specifier_cat]++;
                                        format_specifier_cat++;
                                        format_specifier_total++;
                                    }
                                    confirm = 0;
                                }
                            }
                            else{
                                if( ch == '"')break;
                                printed_token[printed_token_total][i] = ch;
                                ch = getc(file);
                                printed_token_confirm = 1;
                            }
                        }
                        if( ch == '"')break;
                        if(printed_token_confirm == 1)printed_token_total++;
                        printed_token_confirm = 0;
                        ch = getc(file);
                    }
                }
                
                // Identifier & Pointer in Declare
                if(!strcmp(check_reserved_word, "int") || !strcmp(check_reserved_word, "float") || !strcmp(check_reserved_word, "char")){
                    
                    ch = getc(file);
                    
                    while(1){
                        // identifier
                        if( (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ){
                            for( i = 0;  (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_' || ( ch >= '1' && ch <= '9'); i++ ){
                                identifier[identifier_cat][i] = ch;
                                ch = getc(file);
                            }
                            if(!strcmp(identifier[identifier_cat], "main")){
                                // check whether this token has been in the array
                                for( i = 0; i < reserved_word_cat; i++ ){
                                    if( (strcmp(identifier[identifier_cat], reserved_word[i] )) == 0 ){  // if == 0, means equal
                                        reserved_word_num[i]++;
                                        reserved_word_total++;
                                        confirm = 1;
                                        break;
                                    }
                                }
                                // add new category
                                if(confirm == 0){
                                    strcpy( reserved_word[reserved_word_cat], identifier[identifier_cat] );
                                    reserved_word_num[reserved_word_cat]++;
                                    reserved_word_cat++;
                                    reserved_word_total++;
                                }
                                confirm = 0;
                                
                                // initialize identifier
                                for( i = 0; i < CATEGORY; i++ ){
                                    for( j = 0; j < NORMAL; j++ ){
                                        identifier[i][j] = '\0';
                                    }
                                }
                                
                                break;
                            }
                            identifier_num[identifier_cat]++;
                            identifier_cat++;
                            identifier_total++;
                            
                            // Punctuation
                            if(ch == ','){
                                // check whether this token has been in the array
                                for( i = 0; i < punctuation_cat; i++ ){
                                    if(punctuation[i] == ch){
                                        punctuation_num[i]++;
                                        punctuation_total++;
                                        confirm = 1;
                                        break;
                                    }
                                }
                                // add new category
                                if(confirm == 0){
                                    punctuation[punctuation_cat] = ch;
                                    punctuation_num[punctuation_cat]++;
                                    punctuation_cat++;
                                    punctuation_total++;
                                }
                                confirm = 0;
                            }
                        }
                        else{
                            while( (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_' || ( ch >= '1' && ch <= '9')){
                                ch = getc(file);
                            }
                            if(ch == ',' || ch == ';' || ch == ':' || ch == '#' || ch == '"' || ch == '\''){
                                // check whether this token has been in the array
                                for( i = 0; i < punctuation_cat; i++ ){
                                    if(punctuation[i] == ch){
                                        punctuation_num[i]++;
                                        punctuation_total++;
                                        confirm = 1;
                                        break;
                                    }
                                }
                                // add new category
                                if(confirm == 0){
                                    punctuation[punctuation_cat] = ch;
                                    punctuation_num[punctuation_cat]++;
                                    punctuation_cat++;
                                    punctuation_total++;
                                }
                                confirm = 0;
                            }
                        }
                        
                        // pointer
                        if( ch == '*'){
                            pointer[pointer_cat][0] = ch;
                            ch = getc(file);
                            for( i = 1;  (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_' || ( ch >= '1' && ch <= '9'); i++ ){
                                pointer[pointer_cat][i] = ch;
                                ch = getc(file);
                            }
                            pointer_num[pointer_cat]++;
                            pointer_cat++;
                            pointer_total++;
                            
                            // Punctuation
                            if(ch == ','){
                                // check whether this token has been in the array
                                for( i = 0; i < punctuation_cat; i++ ){
                                    if(punctuation[i] == ch){
                                        punctuation_num[i]++;
                                        punctuation_total++;
                                        confirm = 1;
                                        break;
                                    }
                                }
                                // add new category
                                if(confirm == 0){
                                    punctuation[punctuation_cat] = ch;
                                    punctuation_num[punctuation_cat]++;
                                    punctuation_cat++;
                                    punctuation_total++;
                                }
                                confirm = 0;
                            }
                        }
                        
                        
                        // address
                        if( ch == '&'){
                            address[address_cat][0] = ch;
                            ch = getc(file);
                            for( i = 1;  (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_' || ( ch >= '1' && ch <= '9'); i++ ){
                                address[address_cat][i] = ch;
                                ch = getc(file);
                            }
                            address_num[address_cat]++;
                            address_cat++;
                            address_total++;
                            
                            // Punctuation
                            if(ch == ','){
                                // check whether this token has been in the array
                                for( i = 0; i < punctuation_cat; i++ ){
                                    if(punctuation[i] == ch){
                                        punctuation_num[i]++;
                                        punctuation_total++;
                                        confirm = 1;
                                        break;
                                    }
                                }
                                // add new category
                                if(confirm == 0){
                                    punctuation[punctuation_cat] = ch;
                                    punctuation_num[punctuation_cat]++;
                                    punctuation_cat++;
                                    punctuation_total++;
                                }
                                confirm = 0;
                            }
                            
                        }
                        
                        if( ch == ';' || ch == '\n' || ch == '/')break;
                        ch = getc(file);
                    }
                }
                
                
                // check whether this token has been in the array
                for( i = 0; i < reserved_word_cat; i++ ){
                    if( (strcmp(check_reserved_word, reserved_word[i] )) == 0 ){  // if == 0, means equal
                        reserved_word_num[i]++;
                        reserved_word_total++;
                        confirm = 1;
                        break;
                    }
                }
                // add new category
                if(confirm == 0){
                    strcpy( reserved_word[reserved_word_cat], check_reserved_word );
                    reserved_word_num[reserved_word_cat]++;
                    reserved_word_cat++;
                    reserved_word_total++;
                }
                confirm = 0;
            }
        }
        
        // Bracket
        if(ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}'){
            
            // check whether this token has been in the array
            for( i = 0; i < bracket_cat; i++ ){
                if(bracket[i] == ch){
                    bracket_num[i]++;
                    bracket_total++;
                    confirm = 1;
                    break;
                }
            }
            // add new category
            if(confirm == 0){
                bracket[bracket_cat] = ch;
                bracket_num[bracket_cat]++;
                bracket_cat++;
                bracket_total++;
            }
            confirm = 0;
            
            if( ch == '(' ){
                ch = getc(file);
                if( ch == '-'){
                    ch = getc(file);
                    if( ch >='1'&& ch <= '9'){
                        constant[constant_total][0] = '-';
                        constant[constant_total][1] = ch;
                        ch = getc(file);
                        for( i = 2; (ch >= '0' && ch <= '9') || ch == '.' ; i++ ){
                            constant[constant_total][i] = ch;
                            ch = getc(file);
                        }
                        constant_total++;
                    }
                    // ")" -> (-3)
                    // check whether this token has been in the array
                    for( i = 0; i < bracket_cat; i++ ){
                        if(bracket[i] == ch){
                            bracket_num[i]++;
                            bracket_total++;
                            confirm = 1;
                            break;
                        }
                    }
                    // add new category
                    if(confirm == 0){
                        bracket[bracket_cat] = ch;
                        bracket_num[bracket_cat]++;
                        bracket_cat++;
                        bracket_total++;
                    }
                    confirm = 0;
                }
            }
        }
        
        // Pointer & Address ( after declaring )
        if( ch == '*'){
            ch = getc(file);
            check_word[0] = '*';
            for( i = 1;  (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_'; i++ ){
                check_word[i] = ch;
                ch = getc(file);
            }
            
            for( i = 0; i < pointer_cat; i++ ){
                if(!strcmp(check_word, pointer[i])){
                    pointer_num[i]++;
                    pointer_total++;
                    confirm = 1;
                }
            }
            
            // This '*' is operator
            if( confirm == 0 ){
                
                ungetc(ch, file);
                check_operator[0] = '*';
                // check whether this token has been in the array
                for( i = 0; i < operator_cat; i++ ){
                    if( (strcmp(check_operator, operator[i] )) == 0 ){  // if == 0, means equal
                        operator_num[i]++;
                        operator_total++;
                        confirm = 1;
                        break;
                    }
                }
                // add new category
                if(confirm == 0){
                    strcpy( operator[operator_cat], check_operator );
                    operator_num[operator_cat]++;
                    operator_cat++;
                    operator_total++;
                }
                confirm = 0;
            }
            confirm = 0; // initialize confirm
        }
        else if( ch == '&'){
            ch = getc(file);
            check_word[0] = '&';
            for( i = 1;  (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_'; i++ ){
                check_word[i] = ch;
                ch = getc(file);
            }
            
            for( i = 0; i < address_cat; i++ ){
                if(!strcmp(check_word, address[i])){
                    address_num[i]++;
                    address_total++;
                    confirm = 1;
                }
            }
            
            // This '&' is operator
            if( confirm == 0 ){
                
                ungetc(ch, file);
                
                check_operator[0] = '&';
                // check whether this token has been in the array
                for( i = 0; i < operator_cat; i++ ){
                    if( (strcmp(check_operator, operator[i] )) == 0 ){  // if == 0, means equal
                        operator_num[i]++;
                        operator_total++;
                        confirm = 1;
                        break;
                    }
                }
                // add new category
                if(confirm == 0){
                    strcpy( operator[operator_cat], check_operator );
                    operator_num[operator_cat]++;
                    operator_cat++;
                    operator_total++;
                }
                confirm = 0;
            }
            
            confirm = 0;
        }
        
        // Address ( after declaring )
        
        
        // Comment
        if( ch == '/'){
            
            ch = getc(file);
            
            if( ch == '/'){
                comment[comment_total][0] = '/';
                comment[comment_total][1] = '/';
                for( i = 2; (ch = getc(file)) != '\n'; i++ ){
                    comment[comment_total][i] = ch;
                }
                comment_total++;
            }
            else if( ch == '*'){
                comment[comment_total][0] = '/';
                comment[comment_total][1] = '*';
                for( i = 2; (ch = getc(file)) != '/' || comment[comment_total][i-1] != '*'; i++ ){
                    comment[comment_total][i] = ch;
                }
                comment[comment_total][i] = '/';
                comment_total++;
            }
            else{
                check_operator[0] = '/';
                // check whether this token has been in the array
                for( i = 0; i < operator_cat; i++ ){
                    if( (strcmp(check_operator, operator[i] )) == 0 ){  // if == 0, means equal
                        operator_num[i]++;
                        operator_total++;
                        confirm = 1;
                        break;
                    }
                }
                // add new category
                if(confirm == 0){
                    strcpy( operator[operator_cat], check_operator );
                    operator_num[operator_cat]++;
                    operator_cat++;
                    operator_total++;
                }
                confirm = 0;
            }
        }
        
        // Format specifier
        if( ch == '%' || ch == '\\' ){
            if( ch == '%'){
                check_format_specifier[0] = ch;
                check_operator[0] = ch;
                ch = getc(file);
                if( ch == 'c' || ch == 'd' || ch == 'f'){
                    check_format_specifier[1] = ch;
                    // check whether this token has been in the array
                    for( i = 0; i < format_specifier_cat; i++ ){
                        if( (strcmp(check_format_specifier, format_specifier[i] )) == 0 ){  // if == 0, means equal
                            format_specifier_num[i]++;
                            format_specifier_total++;
                            confirm = 1;
                            break;
                        }
                    }
                    // add new category
                    if(confirm == 0){
                        strcpy( format_specifier[format_specifier_cat], check_format_specifier );
                        format_specifier_num[format_specifier_cat]++;
                        format_specifier_cat++;
                        format_specifier_total++;
                    }
                    confirm = 0;
                }
                else{ // it is operator
                    // check whether this token has been in the array
                    for( i = 0; i < operator_cat; i++ ){
                        if( (strcmp(check_operator, operator[i] )) == 0 ){  // if == 0, means equal
                            operator_num[i]++;
                            operator_total++;
                            confirm = 1;
                            break;
                        }
                    }
                    // add new category
                    if(confirm == 0){
                        strcpy( operator[operator_cat], check_operator );
                        operator_num[operator_cat]++;
                        operator_cat++;
                        operator_total++;
                    }
                    confirm = 0;
                }
            }
            else{
                check_format_specifier[0] = ch;
                ch = getc(file);
                check_format_specifier[1] = ch;
                // check whether this token has been in the array
                for( i = 0; i < format_specifier_cat; i++ ){
                    if( (strcmp(check_format_specifier, format_specifier[i] )) == 0 ){  // if == 0, means equal
                        format_specifier_num[i]++;
                        format_specifier_total++;
                        confirm = 1;
                        break;
                    }
                }
                // add new category
                if(confirm == 0){
                    strcpy( format_specifier[format_specifier_cat], check_format_specifier );
                    format_specifier_num[format_specifier_cat]++;
                    format_specifier_cat++;
                    format_specifier_total++;
                }
                confirm = 0;
            }
        }
        
        // Operator
        if(ch == '+' || ch == '-' || ch == '^' || ch == '|' ){
            
            check_operator[0] = ch;
            
            // ++, +
            if( ch == '+'){
                ch = getc(file);
                if( ch == '+' ){
                    check_operator[1] = ch;
                    // check whether this token has been in the array
                    for( i = 0; i < operator_cat; i++ ){
                        if( (strcmp(check_operator, operator[i] )) == 0 ){  // if == 0, means equal
                            operator_num[i]++;
                            operator_total++;
                            confirm = 1;
                            break;
                        }
                    }
                    // add new category
                    if(confirm == 0){
                        strcpy( operator[operator_cat], check_operator );
                        operator_num[operator_cat]++;
                        operator_cat++;
                        operator_total++;
                    }
                    confirm = 0;
                }
                else{
                    ungetc( ch, file );
                    // check whether this token has been in the array
                    for( i = 0; i < operator_cat; i++ ){
                        if( (strcmp(check_operator, operator[i] )) == 0 ){  // if == 0, means equal
                            operator_num[i]++;
                            operator_total++;
                            confirm = 1;
                            break;
                        }
                    }
                    // add new category
                    if(confirm == 0){
                        strcpy( operator[operator_cat], check_operator );
                        operator_num[operator_cat]++;
                        operator_cat++;
                        operator_total++;
                    }
                    confirm = 0;
                }
            }
            else if( ch == '-'){
                ch = getc(file);
                if( ch == '-' ){
                    check_operator[1] = ch;
                    // check whether this token has been in the array
                    for( i = 0; i < operator_cat; i++ ){
                        if( (strcmp(check_operator, operator[i] )) == 0 ){  // if == 0, means equal
                            operator_num[i]++;
                            operator_total++;
                            confirm = 1;
                            break;
                        }
                    }
                    // add new category
                    if(confirm == 0){
                        strcpy( operator[operator_cat], check_operator );
                        operator_num[operator_cat]++;
                        operator_cat++;
                        operator_total++;
                    }
                    confirm = 0;
                }
                else{
                    ungetc(ch, file);
                    // negative number & operator
                    if( ch >='1'&& ch <= '9'){
                        constant[constant_total][0] = '-';
                        constant[constant_total][1] = ch;
                        ch = getc(file);
                        for( i = 2; (ch >= '0' && ch <= '9') || ch == '.' ; i++ ){
                            constant[constant_total][i] = ch;
                            ch = getc(file);
                        }
                        constant_total++;
                    }
                    else{// check whether this token has been in the array
                        for( i = 0; i < operator_cat; i++ ){
                            if( (strcmp(check_operator, operator[i] )) == 0 ){  // if == 0, means equal
                                operator_num[i]++;
                                operator_total++;
                                confirm = 1;
                                break;
                            }
                        }
                        // add new category
                        if(confirm == 0){
                            strcpy( operator[operator_cat], check_operator );
                            operator_num[operator_cat]++;
                            operator_cat++;
                            operator_total++;
                        }
                        confirm = 0;
                    }
                }
            }
            else{
                // check whether this token has been in the array
                for( i = 0; i < operator_cat; i++ ){
                    if( (strcmp(check_operator, operator[i] )) == 0 ){  // if == 0, means equal
                        operator_num[i]++;
                        operator_total++;
                        confirm = 1;
                        break;
                    }
                }
                // add new category
                if(confirm == 0){
                    strcpy( operator[operator_cat], check_operator );
                    operator_num[operator_cat]++;
                    operator_cat++;
                    operator_total++;
                }
                confirm = 0;
            }
        }
        
        // Comparator
        if( ch == '=' || ch == '<' || ch == '>' || ch == '!' ){
            
            check_comparator[0] = ch;
            check_operator[0] = ch;
            
            if( ch == '='){
                ch = getc(file);
                
                if( ch == '='){
                    check_comparator[1] = ch;
                    // check whether this token has been in the array
                    for( i = 0; i < comparator_cat; i++ ){
                        if( (strcmp(check_comparator, comparator[i] )) == 0 ){  // if == 0, means equal
                            comparator_num[i]++;
                            comparator_total++;
                            confirm = 1;
                            break;
                        }
                    }
                    // add new category
                    if(confirm == 0){
                        strcpy( comparator[comparator_cat], check_comparator );
                        comparator_num[comparator_cat]++;
                        comparator_cat++;
                        comparator_total++;
                    }
                    confirm = 0;
                }
                else{
                    // check whether this token has been in the array
                    for( i = 0; i < operator_cat; i++ ){
                        if( (strcmp(check_operator, operator[i] )) == 0 ){  // if == 0, means equal
                            operator_num[i]++;
                            operator_total++;
                            confirm = 1;
                            break;
                        }
                    }
                    // add new category
                    if(confirm == 0){
                        strcpy( operator[operator_cat], check_operator );
                        operator_num[operator_cat]++;
                        operator_cat++;
                        operator_total++;
                    }
                    confirm = 0;
                }
            }
            else if( ch == '<' || ch == '>' || ch == '!'){
                ch = getc(file);
                if( ch == '='){
                    check_comparator[1] = ch;
                    // check whether this token has been in the array
                    for( i = 0; i < comparator_cat; i++ ){
                        if( (strcmp(check_comparator, comparator[i] )) == 0 ){  // if == 0, means equal
                            comparator_num[i]++;
                            comparator_total++;
                            confirm = 1;
                            break;
                        }
                    }
                    // add new category
                    if(confirm == 0){
                        strcpy( comparator[comparator_cat], check_comparator );
                        comparator_num[comparator_cat]++;
                        comparator_cat++;
                        comparator_total++;
                    }
                    confirm = 0;
                }
                else{
                    
                    if( check_comparator[0] == '!')break;
                    // check whether this token has been in the array
                    for( i = 0; i < comparator_cat; i++ ){
                        if( (strcmp(check_comparator, comparator[i] )) == 0 ){  // if == 0, means equal
                            comparator_num[i]++;
                            comparator_total++;
                            confirm = 1;
                            break;
                        }
                    }
                    // add new category
                    if(confirm == 0){
                        strcpy( comparator[comparator_cat], check_comparator );
                        comparator_num[comparator_cat]++;
                        comparator_cat++;
                        comparator_total++;
                    }
                    confirm = 0;
                }
            }
        }
        
        // Constant
        if( ch >= '0'&& ch <= '9'){
            constant[constant_total][0] = ch;
            ch = getc(file);
            for( i = 1; (ch >= '0' && ch <= '9') || ch == '.' ; i++ ){
                constant[constant_total][i] = ch;
                ch = getc(file);
            }
            constant_total++;
        }
        
        // Punctuation
        if(ch == ',' || ch == ';' || ch == ':' || ch == '#' || ch == '"' || ch == '\''){
            // check whether this token has been in the array
            for( i = 0; i < punctuation_cat; i++ ){
                if(punctuation[i] == ch){
                    punctuation_num[i]++;
                    punctuation_total++;
                    confirm = 1;
                    break;
                }
            }
            // add new category
            if(confirm == 0){
                punctuation[punctuation_cat] = ch;
                punctuation_num[punctuation_cat]++;
                punctuation_cat++;
                punctuation_total++;
            }
            confirm = 0;
        }
        
        if( (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ){
            
            for( i = 0;  (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '1' && ch <= '9') || ch == '_'; i++ ){ // 0
                check_word[i] = ch;
                check_reserved_word[i] = tolower(ch);
                ch = getc(file);
            }
            ungetc( ch, file );
            // Identifier ( after declaring )
            for( i = 0; i < identifier_cat; i++ ){
                if(!strcmp(check_word, identifier[i])){
                    identifier_num[i]++;
                    identifier_total++;
                }
            }
        }
        
        
        // initialize check reserved word
        for( i = 0; i < 10; i++ ){
            check_reserved_word[i] = '\0';
        }
        
        // initialize check operator word
        for( i = 0; i < 3; i++){
            check_operator[i] = '\0';
        }
        
        // initialize check comparator word
        for( i = 0; i < 3; i++){
            check_comparator[i] = '\0';
        }
        
        // initialize check format specifier word
        for( i = 0; i < 3; i++){
            check_format_specifier[i] = '\0';
        }
        
        // initialize check_word
        for( i = 0; i < NORMAL; i++ ){
            check_word[i] = '\0';
        }
    }
        /*
        // Constant
        if( ch >='1'&& ch <= '9'){
            constant[constant_total][0] = ch;
            ch = getc(file);
            for( i = 1; (ch >= '0' && ch <= '9') || ch == '.' ; i++ ){
                constant[constant_total][i] = ch;
                ch = getc(file);
            }
            constant_total++;
        }
        
        // Bracket
        if(ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}'){
            
            // check whether this token has been in the array
            for( i = 0; i < bracket_cat; i++ ){
                if(bracket[i] == ch){
                    bracket_num[i]++;
                    bracket_total++;
                    confirm = 1;
                    break;
                }
            }
            // add new category
            if(confirm == 0){
                bracket[bracket_cat] = ch;
                bracket_num[bracket_cat]++;
                bracket_cat++;
                bracket_total++;
            }
            confirm = 0;
            
            if( ch == '(' ){
                ch = getc(file);
                if( ch == '-'){
                    ch = getc(file);
                    if( ch >='1'&& ch <= '9'){
                        constant[constant_total][0] = '-';
                        constant[constant_total][1] = ch;
                        ch = getc(file);
                        for( i = 2; (ch >= '0' && ch <= '9') || ch == '.' ; i++ ){
                            constant[constant_total][i] = ch;
                            ch = getc(file);
                        }
                        constant_total++;
                    }
                    // ")" -> (-3)
                    // check whether this token has been in the array
                    for( i = 0; i < bracket_cat; i++ ){
                        if(bracket[i] == ch){
                            bracket_num[i]++;
                            bracket_total++;
                            confirm = 1;
                            break;
                        }
                    }
                    // add new category
                    if(confirm == 0){
                        bracket[bracket_cat] = ch;
                        bracket_num[bracket_cat]++;
                        bracket_cat++;
                        bracket_total++;
                    }
                    confirm = 0;
                }
            }
        }
        
        // Pointer ( after declaring )
        if( ch == '*'){
            ch = getc(file);
            check_word[0] = '*';
            for( i = 1;  (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_'; i++ ){
                check_word[i] = ch;
                ch = getc(file);
            }
            
            for( i = 0; i < pointer_cat; i++ ){
                if(!strcmp(check_word, pointer[i])){
                    pointer_num[i]++;
                    pointer_total++;
                }
            }
        }
        
        // Address ( after declaring )
        if( ch == '&'){
            ch = getc(file);
            check_word[0] = '&';
            for( i = 1;  (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_'; i++ ){
                check_word[i] = ch;
                ch = getc(file);
            }
            
            for( i = 0; i < address_cat; i++ ){
                if(!strcmp(check_word, address[i])){
                    address_num[i]++;
                    address_total++;
                }
            }
        }
        
        // Comment
        if( ch == '/'){
            
            ch = getc(file);
            
            if( ch == '/'){
                comment[comment_total][0] = '/';
                comment[comment_total][1] = '/';
                for( i = 2; (ch = getc(file)) != '\n'; i++ ){
                    comment[comment_total][i] = ch;
                }
                comment_total++;
            }
            else if( ch == '*'){
                comment[comment_total][0] = '/';
                comment[comment_total][1] = '*';
                for( i = 2; (ch = getc(file)) != '/' || comment[comment_total][i-1] != '*'; i++ ){
                    comment[comment_total][i] = ch;
                }
                comment[comment_total][i] = '/';
                comment_total++;
            }
            else{
                check_operator[0] = '/';
                // check whether this token has been in the array
                for( i = 0; i < operator_cat; i++ ){
                    if( (strcmp(check_operator, operator[i] )) == 0 ){  // if == 0, means equal
                        operator_num[i]++;
                        operator_total++;
                        confirm = 1;
                        break;
                    }
                }
                // add new category
                if(confirm == 0){
                    strcpy( operator[operator_cat], check_operator );
                    operator_num[operator_cat]++;
                    operator_cat++;
                    operator_total++;
                }
                confirm = 0;
            }
        }
        
        // Format specifier
        if( ch == '%' || ch == '\\' ){
            if( ch == '%'){
                check_format_specifier[0] = ch;
                check_operator[0] = ch;
                ch = getc(file);
                if( ch == 'c' || ch == 'd' || ch == 'f'){
                    check_format_specifier[1] = ch;
                    // check whether this token has been in the array
                    for( i = 0; i < format_specifier_cat; i++ ){
                        if( (strcmp(check_format_specifier, format_specifier[i] )) == 0 ){  // if == 0, means equal
                            format_specifier_num[i]++;
                            format_specifier_total++;
                            confirm = 1;
                            break;
                        }
                    }
                    // add new category
                    if(confirm == 0){
                        strcpy( format_specifier[format_specifier_cat], check_format_specifier );
                        format_specifier_num[format_specifier_cat]++;
                        format_specifier_cat++;
                        format_specifier_total++;
                    }
                    confirm = 0;
                }
                else{ // it is operator
                    // check whether this token has been in the array
                    for( i = 0; i < operator_cat; i++ ){
                        if( (strcmp(check_operator, operator[i] )) == 0 ){  // if == 0, means equal
                            operator_num[i]++;
                            operator_total++;
                            confirm = 1;
                            break;
                        }
                    }
                    // add new category
                    if(confirm == 0){
                        strcpy( operator[operator_cat], check_operator );
                        operator_num[operator_cat]++;
                        operator_cat++;
                        operator_total++;
                    }
                    confirm = 0;
                }
            }
            else{
                check_format_specifier[0] = ch;
                ch = getc(file);
                check_format_specifier[1] = ch;
                // check whether this token has been in the array
                for( i = 0; i < format_specifier_cat; i++ ){
                    if( (strcmp(check_format_specifier, format_specifier[i] )) == 0 ){  // if == 0, means equal
                        format_specifier_num[i]++;
                        format_specifier_total++;
                        confirm = 1;
                        break;
                    }
                }
                // add new category
                if(confirm == 0){
                    strcpy( format_specifier[format_specifier_cat], check_format_specifier );
                    format_specifier_num[format_specifier_cat]++;
                    format_specifier_cat++;
                    format_specifier_total++;
                }
                confirm = 0;
            }
        }
        
        // Operator
        if(ch == '+' || ch == '-' || ch == '*' || ch == '^' || ch == '&' || ch == '|' ){
            
            check_operator[0] = ch;
            
            // ++, +
            if( ch == '+'){
                ch = getc(file);
                if( ch == '+' ){
                    check_operator[1] = ch;
                    // check whether this token has been in the array
                    for( i = 0; i < operator_cat; i++ ){
                        if( (strcmp(check_operator, operator[i] )) == 0 ){  // if == 0, means equal
                            operator_num[i]++;
                            operator_total++;
                            confirm = 1;
                            break;
                        }
                    }
                    // add new category
                    if(confirm == 0){
                        strcpy( operator[operator_cat], check_operator );
                        operator_num[operator_cat]++;
                        operator_cat++;
                        operator_total++;
                    }
                    confirm = 0;
                }
                else{
                    check_operator[1] = ch;
                    // check whether this token has been in the array
                    for( i = 0; i < operator_cat; i++ ){
                        if( (strcmp(check_operator, operator[i] )) == 0 ){  // if == 0, means equal
                            operator_num[i]++;
                            operator_total++;
                            confirm = 1;
                            break;
                        }
                    }
                    // add new category
                    if(confirm == 0){
                        strcpy( operator[operator_cat], check_operator );
                        operator_num[operator_cat]++;
                        operator_cat++;
                        operator_total++;
                    }
                    confirm = 0;
                }
            }
            else if( ch == '-'){
                ch = getc(file);
                if( ch == '-' ){
                    check_operator[1] = ch;
                    // check whether this token has been in the array
                    for( i = 0; i < operator_cat; i++ ){
                        if( (strcmp(check_operator, operator[i] )) == 0 ){  // if == 0, means equal
                            operator_num[i]++;
                            operator_total++;
                            confirm = 1;
                            break;
                        }
                    }
                    // add new category
                    if(confirm == 0){
                        strcpy( operator[operator_cat], check_operator );
                        operator_num[operator_cat]++;
                        operator_cat++;
                        operator_total++;
                    }
                    confirm = 0;
                }
                else{
                    // negative number & operator
                    if( ch >='1'&& ch <= '9'){
                        constant[constant_total][0] = '-';
                        constant[constant_total][1] = ch;
                        ch = getc(file);
                        for( i = 2; (ch >= '0' && ch <= '9') || ch == '.' ; i++ ){
                            constant[constant_total][i] = ch;
                            ch = getc(file);
                        }
                        constant_total++;
                    }
                    else{// check whether this token has been in the array
                        for( i = 0; i < operator_cat; i++ ){
                            if( (strcmp(check_operator, operator[i] )) == 0 ){  // if == 0, means equal
                                operator_num[i]++;
                                operator_total++;
                                confirm = 1;
                                break;
                            }
                        }
                        // add new category
                        if(confirm == 0){
                            strcpy( operator[operator_cat], check_operator );
                            operator_num[operator_cat]++;
                            operator_cat++;
                            operator_total++;
                        }
                        confirm = 0;
                    }
                }
            }
            else{
                // check whether this token has been in the array
                for( i = 0; i < operator_cat; i++ ){
                    if( (strcmp(check_operator, operator[i] )) == 0 ){  // if == 0, means equal
                        operator_num[i]++;
                        operator_total++;
                        confirm = 1;
                        break;
                    }
                }
                // add new category
                if(confirm == 0){
                    strcpy( operator[operator_cat], check_operator );
                    operator_num[operator_cat]++;
                    operator_cat++;
                    operator_total++;
                }
                confirm = 0;
            }
        }
        
        // Comparator
        if( ch == '=' || ch == '<' || ch == '>' || ch == '!' ){
            
            check_comparator[0] = ch;
            check_operator[0] = ch;
            
            if( ch == '='){
                ch = getc(file);
                
                if( ch == '='){
                    check_operator[1] = ch;
                    // check whether this token has been in the array
                    for( i = 0; i < comparator_cat; i++ ){
                        if( (strcmp(check_comparator, comparator[i] )) == 0 ){  // if == 0, means equal
                            comparator_num[i]++;
                            comparator_total++;
                            confirm = 1;
                            break;
                        }
                    }
                    // add new category
                    if(confirm == 0){
                        strcpy( comparator[comparator_cat], check_comparator );
                        comparator_num[comparator_cat]++;
                        comparator_cat++;
                        comparator_total++;
                    }
                    confirm = 0;
                }
                else{
                    // check whether this token has been in the array
                    for( i = 0; i < operator_cat; i++ ){
                        if( (strcmp(check_operator, operator[i] )) == 0 ){  // if == 0, means equal
                            operator_num[i]++;
                            operator_total++;
                            confirm = 1;
                            break;
                        }
                    }
                    // add new category
                    if(confirm == 0){
                        strcpy( operator[operator_cat], check_operator );
                        operator_num[operator_cat]++;
                        operator_cat++;
                        operator_total++;
                    }
                    confirm = 0;
                }
            }
            else if( ch == '<' || ch == '>' || ch == '!'){
                ch = getc(file);
                if( ch == '='){
                    check_comparator[1] = ch;
                    // check whether this token has been in the array
                    for( i = 0; i < comparator_cat; i++ ){
                        if( (strcmp(check_comparator, comparator[i] )) == 0 ){  // if == 0, means equal
                            comparator_num[i]++;
                            comparator_total++;
                            confirm = 1;
                            break;
                        }
                    }
                    // add new category
                    if(confirm == 0){
                        strcpy( comparator[comparator_cat], check_comparator );
                        comparator_num[comparator_cat]++;
                        comparator_cat++;
                        comparator_total++;
                    }
                    confirm = 0;
                }
                else{
                    
                    if( check_comparator[0] == '!')break;
                    // check whether this token has been in the array
                    for( i = 0; i < comparator_cat; i++ ){
                        if( (strcmp(check_comparator, comparator[i] )) == 0 ){  // if == 0, means equal
                            comparator_num[i]++;
                            comparator_total++;
                            confirm = 1;
                            break;
                        }
                    }
                    // add new category
                    if(confirm == 0){
                        strcpy( comparator[comparator_cat], check_comparator );
                        comparator_num[comparator_cat]++;
                        comparator_cat++;
                        comparator_total++;
                    }
                    confirm = 0;
                }
            }
        }
        
        
        // Punctuation
        if(ch == ',' || ch == ';' || ch == ':' || ch == '#' || ch == '"' || ch == '\''){
            // check whether this token has been in the array
            for( i = 0; i < punctuation_cat; i++ ){
                if(punctuation[i] == ch){
                    punctuation_num[i]++;
                    punctuation_total++;
                    confirm = 1;
                    break;
                }
            }
            // add new category
            if(confirm == 0){
                punctuation[punctuation_cat] = ch;
                punctuation_num[punctuation_cat]++;
                punctuation_cat++;
                punctuation_total++;
            }
            confirm = 0;
        }
        
        
        // initialize check reserved word
        for( i = 0; i < 10; i++ ){
            check_reserved_word[i] = '\0';
        }
        
        // initialize check operator word
        for( i = 0; i < 3; i++){
            check_operator[i] = '\0';
        }
        
        // initialize check comparator word
        for( i = 0; i < 3; i++){
            check_comparator[i] = '\0';
        }
        
        // initialize check format specifier word
        for( i = 0; i < 3; i++){
            check_format_specifier[i] = '\0';
        }

        // initialize check_word
        for( i = 0; i < NORMAL; i++ ){
            check_word[i] = '\0';
        } 
    }
    */
    /*
     
     ==============================================================================================
     
     */
    
    
    file = fopen("answer.txt", "wb" );
    
    // write into scanner_test.txt
    fprintf( file, "\nTotal: %d tokens\n", punctuation_total + reserved_word_total + library_name_total
            + comment_total + identifier_total + pointer_total + constant_total + operator_total + comparator_total
            + bracket_total + format_specifier_total + address_total + printed_token_total);
    
    // Reserved word
    fprintf( file, "\nReserved word: %d\n", reserved_word_total );
    
    for( i = 0; i < reserved_word_cat; i++ ){
        fprintf( file, "%s ", reserved_word[i] );
        if(reserved_word_num[i]>1){
            fprintf( file, "(x%d)", reserved_word_num[i]);
        }
        fprintf( file, "\n" );
    }
    
    // Library name
    fprintf( file, "\nLibrary name: %d\n", library_name_total );
    
    for( i = 0; i < library_name_total; i++ ){
        fprintf( file, "<%s>\n", library_name[i]);
    }
    
    // Comment
    fprintf( file, "\nComment: %d\n", comment_total );
    
    for( i = 0; i < comment_total; i++ ){
        fprintf( file, "%s\n", comment[i] );
    }
    
    // Identifier
    fprintf( file, "\nIdentifier: %d\n", identifier_total );
    
    for( i = 0; i < identifier_cat; i++ ){
        fprintf( file, "%s ", identifier[i]);
        if(identifier_num[i]>1){
            fprintf( file, "(x%d)", identifier_num[i]);
        }
        fprintf( file, "\n" );
    }
    
    // Constant
    fprintf( file, "\nConstant: %d\n", constant_total );
    
    for( i = 0; i < constant_total; i++ ){
        fprintf( file, "%s\n", constant[i] );
    }
    
    // Operator
    fprintf( file, "\nOperator: %d\n", operator_total );
    
    for( i = 0; i < operator_cat; i++ ){
        fprintf( file, "%s ", operator[i] );
        if(operator_num[i]>1){
            fprintf( file, "(x%d)", operator_num[i]);
        }
        fprintf( file, "\n" );
    }
    
    // Comperator
    fprintf( file, "\nComparator: %d\n", comparator_total );
    
    for( i = 0; i < comparator_cat; i++ ){
        fprintf( file, "%s ", comparator[i] );
        if(comparator_num[i]>1){
            fprintf( file, "(x%d)",comparator_num[i]);
        }
        fprintf( file, "\n" );
    }
    
    // Bracket
    fprintf( file, "\nBracket: %d\n", bracket_total );
    
    for( i = 0; i < bracket_cat; i++ ){
        fprintf( file, "%c ", bracket[i]);
        if(bracket_num[i]>1){
            fprintf( file, "(x%d)", bracket_num[i]);
        }
        fprintf( file, "\n" );
    }
    
    // Format specifier
    fprintf( file, "\nFormat specifier: %d\n", format_specifier_total );
    
    for( i = 0; i < format_specifier_cat; i++ ){
        fprintf( file, "%s ", format_specifier[i] );
        if(format_specifier_num[i]>1){
            fprintf( file, "(x%d)",format_specifier_num[i]);
        }
        fprintf( file, "\n" );
    }
    
    // Pointer
    fprintf( file, "\nPointer: %d\n", pointer_total );
    
    for( i = 0; i < pointer_cat; i++ ){
        fprintf( file, "%s ", pointer[i]);
        if(pointer_num[i]>1){
            fprintf( file, "(x%d)", pointer_num[i]);
        }
        fprintf( file, "\n" );
    }
    
    // Address
    fprintf( file, "\nAddress: %d\n", address_total );
    
    for( i = 0; i < address_cat; i++ ){
        fprintf( file, "%s ", address[i]);
        if(address_num[i]>1){
            fprintf( file, "(x%d)", address_num[i]);
        }
        fprintf( file, "\n" );
    }
    
    // Punctuation
    fprintf( file, "\nPunctuation: %d\n", punctuation_total );
    
    for( i = 0; i < punctuation_cat; i++ ){
        fprintf( file, "%c ", punctuation[i]);
        if(punctuation_num[i]>1){
            fprintf( file, "(x%d)", punctuation_num[i]);
        }
        fprintf( file, "\n" );
    }
    
    // Printed token
    fprintf( file, "\nPrinted token: %d\n", printed_token_total );
    
    for( i = 0; i < printed_token_total; i++ ){
        fprintf( file, "%s\n", printed_token[i] );
    }
    
    fclose(file);
}

