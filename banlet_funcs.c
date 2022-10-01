// banlet_funcs.c: support functions for the banlet_main program.

#include "banlet.h"

// PROBLEM 1: Replace instances of character 'old' with 'new' in the
// string 'str'.  May use the strlen() library function to determine
// string length or directly look for a '\0' null termination
// character to end the string.
// 
// EXAMPLES:
// char s1[]="A A B B A"; string_replace_char(s1, 'A', 'X'); // s1 is "X X B B X"
// char s2[]="A A B B A"; string_replace_char(s2, 'B', 'Y'); // s2 is "A A Y Y A"
// char s3[]="A A B B A"; string_replace_char(s3, ' ', '-'); // s3 is "A-A-B-B-A"
void string_replace_char(char *str, char old, char new){

//check for old chars and replace with new
   for(int i=0; i< strlen(str);i++){
   if (str[i]==old){
   	 str[i] =new;
   }
  
  
  }
}

// PROBLEM 1: Counts the number of newline characters '\n' in the
// string 'msg'; return this number +1 as the end of lines will always
// be a line break. May use the strlen() library function to determine
// string length or directly look for a '\0' null termination
// character to end the string.
// 
// EXAMPLES:
// count_linebreaks("Hi")        ->  1
// count_linebreaks("Hi There")  ->  1
// count_linebreaks("Hi\nThere") ->  2
// count_linebreaks("O\nM\nG")   ->  3
int count_linebreaks(char *msg){
    
  int count=1;
  for(int i=0; i<strlen(msg);i++){   
      if (msg[i]=='\n'){
          count++;
      }
  }
  return count;
}

// PROBLEM 1: Counts the linebreaks (newline '\n' chars and end of
// string) and returns an array of integers with the position for each
// linebreak in string 'msg'.  Uses the count_linebreaks()
// function. The 'nbreaks' parameter is an OUTPUT integer that should
// be set to the number of breaks in 'msg' using the C dereference
// operator (*).
//
// EXAMPLES:
// int nbreaks = -1;
// int *breaks = find_linebreaks("Hello\nWorld", &nbreaks);
// //            index in string: 012345 67890
// // nbreaks is now 2
// // breask is now [5, 11]
int *find_linebreaks(char *msg, int *nbreaks){
    
  *nbreaks= count_linebreaks(msg); //the count of breaks
  
  int *breaks;
  
  breaks= malloc(*nbreaks*sizeof(int));  //dynamically allocate integer array for break positions
  
  int curr=0;
  int index= 0;
 
  while(index<strlen(msg)){     // find the location of '\n' and placed into the array-break
        if (msg[index]=='\n'){
          breaks[curr]=index;
          curr++;
      }
      index++;
  }

  breaks[curr]= index;  // adding the last index of '\n' into array
  
  return breaks; 
  }
 

// PROBLEM 1: Prints string 'msg' using 'font'. Only prints characters
// 0 to 'length-1'.  Iterates over each row in font->height and then
// scans across the charactes in 'msg' printing each "row" of the
// character. On reaching index 'length', prints a newline and then
// scans across 'msg' again printing characters from the next row.
// Each msg[i] character is used to as the index into fonts->glyphs[]
// to access the "glyph" that will be printed.
//
// NOTE: This function does NOT handle embedded newline '\n'
// characters. It is intended to be called repeatedly on each line in
// multiline text with '\n' characters found using the
// 'find_linebreaks()' function.
//
// EXAMPLE:
//
// print_fontified_oneline("Hello!", &font_standard, 6);
// // Prints the following on standard output:
// ._. ._.      ,-,,-,       ._.
// | | | |  ___ | || |  ___  | |
// | |_| | /'_`\| || | / _ \ | |
// |  _  ||  __/| || || (_) ||_|
// |_| |_| \___||_||_| \___/ (_)
void print_fontified_oneline (char *msg, font_t * font, int length)
{

  int row= font-> height;
  
  
   //doubly-nested loop to iterate over font rows and characters in the message
   for(int i=0;i<row;i++){
      for(int j=0;j<length;j++) {
           
        printf ("%s", font->glyphs[(int)msg[j]].data[i]);
    }
 
        printf("\n");

  }
  
  
}

// PROBLEM 2: Uses print_fontified_oneline() with find_linebreaks() to
// correctly print 'msg' with 'font' even if there are linebreaks in
// 'msg'.  Uses find_linebreaks() to find the end of each line in
// 'msg' and then iterates over lines printing each.  Uses pointer
// arithmetic to pass the starting position of each line into calls of
// print_fontified(). Frees memory allocated (such as through use of
// count_linebreaks()) before returning.
//
// EXAMPLE:
//   print_fontified("apple\nB@N@N@\nCarr0^", &font_standard);
// Shows the following on standard output:
//                      ,-,      
//   __ _ ,_ __. ,_ __. | |  ___ 
//  / _` || '_ \ | '_ \ | | /'_`\
// | (_| || |_) || |_) || ||  __/
//  \__,_|| .__/ | .__/ |_| \___|
//        |_|    |_|             
// ,____    ____  ._  ._.   ____  ._  ._.   ____  
// | == )  / __ \ | \ | |  / __ \ | \ | |  / __ \ 
// |  _ \ / / _` ||  \| | / / _` ||  \| | / / _` |
// | |_)|| | (_| || |\  || | (_| || |\  || | (_| |
// |____/ \ \__,.||_| \_| \ \__,.||_| \_| \ \__,.|
//         \____/          \____/          \____/ 
//   ____.                     ___   /\ 
//  / ___|  __ _ ._ __.._ __. / _ \ |/\|
// | |     / _` || `__|| `__|| | | |    
// | |___.| (_| || |   | |   | |_| |    
//  \____| \__,_||_|   |_|    \___/     
void print_fontified(char *msg, font_t *font){
    int nlines=-1;
    int *breaks= find_linebreaks(msg,&nlines);
    
    int curr=0;
    int temp=0;
     
    for(int i=0;i<nlines;i++){
        
        temp=breaks[i];
        print_fontified_oneline(&msg[curr], font, temp-curr);
        curr=breaks[i]+1;
    }
    
    free(breaks);

}


// PROVIDED: Initializes a glyph to mostly X's except for its
// codepoint on the first line.
void glyph_init(glyph_t *glyph, int codepoint){
  glyph->codepoint = codepoint;
  glyph->width = 6;
  for(int i=0; i<MAX_HEIGHT; i++){
    for(int j=0; j<MAX_WIDTH; j++){
      if(j == glyph->width){
        glyph->data[i][j] = '\0'; // null terminate
      }
      else{
        glyph->data[i][j] = 'X';
      }
    }
  }
  int len = sprintf((char *)glyph->data, "%d",codepoint); // add codepoint # to glyph
  glyph->data[0][len] = 'X';                              // remove null termination char
}        

// PROBLEM 2: Loads a banner font from 'filename'.  The format of font
// files is documented more thoroughly in the project specification
// but is generally comprised of a first line that indicate the height
// of each glyph in the font followed by a sequence of each glyph
// starting with its codepoint (ASCII index) and a grid of characters
// in it. To make parsing easier, the ? character is used to represent
// blank spaces in glyph shapes.
//
// EXAMPLE:
// height: 4
// 42
// ???
// \|/
// /|\
// ???
// 43
// ???
// _|_
// ?|?
// ???
//
// The two characters above are the codepoint 42 '*' and codepoint 43
// '+' with the ? symbols eventually being replaced by spaces during
// loading.
// 
// If 'filename' cannot be opened for reading, returns NULL.
//
// Memory allocation happens in two steps: (1) allocates memory for a
// font_t struct then (2) allocates memory for an array of glyph_t
// structs of length NUM_ASCII_GLYPHS (a constant defined in
// banlet.h). Sets the font->glyphs field to be the allocated array of
// glyphs.  Reads the font->height field from teh first line of the
// file.  Iterates over each element of the glyphs array and calls the
// glyph_init() function on it to populate it with default data.  Then
// proceeds to read glyphs from the file. Glyphs are read by reading
// the integer codepoint first which determins which element of the
// glyph array to read into.  Then a loop over the height of the font
// is used to read each row of the glyph into the
// glyph[codepoint]->data[row]; fscanf() with '%s' specifier is used
// for this.  Finally, the string_replace_char() function is used to
// replace all '?' characters with ' ' (space) characters in the glyph
// data. Sets the width of each glyph using the strlen() function on
// any balid row of the glyph data.
//
// Glyphs are read from 'filename' until an attempt to read a glyph's
// codepoint with fscanf() returns EOF (end of file). This causes the
// routine to return the allocated font_t data for use elsewhere.
font_t *font_load(char *filename){
  FILE *fl= fopen(filename, "r");
  
  //check if the file fails to open, if failed return NULL
  if (fl== NULL){

      return NULL;
      
  }

  //malloc() for the font_t struct
  font_t *ft = malloc(sizeof(font_t));

  //allocate Glyph array
  ft-> glyphs = malloc(sizeof(glyph_t)*NUM_ASCII_GLYPHS);

  //Reads the font->height field from the first line of the file:
  fscanf(fl,"height: %d",&ft->height);

  for(int i=0;i<128;i++){ //on each glyph in the array to give it default data
     
     glyph_init(&(ft->glyphs[i]), i);
 }


  while(fscanf(fl,"%d",&ft->glyphs->codepoint)!=EOF){   //Iterates each codepoint
  
      
      //printf("%d\n",ft->glyphs->codepoint); 

      for(int i=0;i<ft->height;i++){     //with the height
      

          fscanf(fl,"%s",ft->glyphs[ft->glyphs->codepoint].data[i]);
          
          string_replace_char(ft->glyphs[ft->glyphs->codepoint].data[i],'?',' ');  //change '?' to space
          //printf("%s\n",ft->glyphs[ft->glyphs->codepoint].data[i]);

      }
      
      
  }
  
  fclose(fl);
  
//   test part: 
//   printf("% is : %s\n",ft->glyphs[(int)'%'].data[0]);
//   printf("% is : %s\n",ft->glyphs[(int)'%'].data[1]);
//   printf("% is : %s\n",ft->glyphs[(int)'%'].data[2]);
//   printf("% is : %s\n",ft->glyphs[(int)'%'].data[3]);
//   printf("% is : %s\n",ft->glyphs[(int)'%'].data[4]);
//   printf("% is : %s\n",ft->glyphs[(int)'%'].data[5]);
  
  return ft;
  
  
}

// PROBLEM 2: Frees the memory associated with 'font'.  First frees
// the glyph array, then frees the font itself. Hint: this funciton
// should be 2 lines long.
void font_free(font_t *font){
  free(font->glyphs);
  free(font);
}
