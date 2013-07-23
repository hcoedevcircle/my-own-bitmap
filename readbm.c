/*****************************************************
 * @autor Nootan Ghimire <nootan.ghimire@gmail.com>
 * @version 1.0.0
 ****************************************************/

#include<stdio.h>
#include<conio.h>
//remove the comment if you want a working test :D
//#include<graphics.h>
#define MAX_BMP_SZ 100

//Structure  Defination

typedef struct {
  int char_id;            // Char_id
  int char_bmap[16];     // The real character bitmap
  } xbmp ;

/*****************************************************************
 * main()
 * @params none
 * @return none
 * 
 * You can add functionality to get file as command line arguments
 *****************************************************************/ 
void main() {

    FILE *fp;
    int i, j, k ;                               //legacy counters
    int len;                                   //No. of characters loaded.
    xbmp char_coll[MAX_BMP_SZ], temp;
    i = j = k= 0;                             //not really needed. Just for fun :D
    fp = fopen("test.xbmp","rb");
    while(!feof(fp)) {
        fread(&temp, sizeof(temp),1, fp);
        char_coll[i] = temp ;               //copying Structure
        i++;                  
    }
    fclose(fp);
    len = i - 2 ;                         //Since we-are zero indexing, i think

    //Now display the contents : TEST CASE
    //This is for debug. Replace it with display_all_pixels(char_coll, len)
    for(j=0;  j<=i-2 ; j++ ) {
        printf("\n----------------------------\n\nChar ID: %d", char_coll[j].char_id);
        printf("\n\nShowing Character Bitmap Now: ");
        for(k=0; k<=15; k++) {
            printf("\nHex For Line %d :::  %x", char_coll[j], char_coll[j].char_bmap[k]);
        }
    }

}


/****************************************************************
 * dispaly_all_pixels
 * @param type:xbmp structure array
 * @param type:int
 * @return none
 ****************************************************************/ 

void display_all_pixels(xbmp coll[], int len) {

    //This is the Turbo C Version of the function.
    //This requires #include <graphics.h> preprocessor directive.
    //You are welcome to make your own function for a different Platform
    //Showcasing the Font Contents

    //Check Screen Size rather than total entries
   int y_max = 199, x_max = 319;
   int curr_x, curr_y, hold_x, hold_y ;
   int i,j; //legacy counters
   int iterator=0; //for_number of entries
   typedef int element2d[8][16];
   element2d *output_array;
   output_array = (element2d*) (malloc(len*sizeof(element2d)));

   //Convert bitmap to readable, i.e, seperate hex to bin
   convert_bmp_for_showcase(coll, len, output_array);

   curr_x = curr_y = hold_x = hold_y = 0;

   do{
        curr_x = hold_x;
        curr_y = hold_y;
        for(i=curr_x ; i<=curr_x+7; i++) {
            for(j=curr_y; j<=curr_y+15; j++){
                    if (output_array[iterator][i][j]) putpixel(i,j, 1);
                        hold_y++;
            } //end inner for loop
            hold_x++;
        } //end outer for loop
        iterator++;
    }while(hold_x<=x_max && hold_y<=y_max);

}
/***************************************************************
 * convert_bmp_for_showcase
 * @param type:xbmp structue array (not-mutated)
 * @param type:int
 * @param type:int array (mutated)
 * @return none
 ***************************************************************/ 

void convert_bmp_for_showcase(xbmp char_coll[], int len, int output_array[][8][16]) {

    //Converts Compelex Structure coll, to simpler array
    //The array will be 2-dimensional,  bmp_array[8][16],
    //which is again arrayed!!
    //So the final array: bmp_array[no_of_entries][8][16]

    //Logic: Use For loops

    //Counters:
    int i, j,k;
    for(i=0; i<=len; i++){
        //This is for first dimension
        for(j=0; j<=15;j++){
            //Now mask 'em
            //Use loops, instead, eh?
            output_array[i][0][j] = char_coll[j].char_bmap[k] & 0x80 ;
            output_array[i][1][j] = char_coll[j].char_bmap[k] & 0x40 ;
            output_array[i][2][j] = char_coll[j].char_bmap[k] & 0x20 ;
            output_array[i][3][j] = char_coll[j].char_bmap[k] & 0x10 ;
            output_array[i][4][j] = char_coll[j].char_bmap[k] & 0x8 ;
            output_array[i][5][j] = char_coll[j].char_bmap[k] & 0x4;
            output_array[i][6][j] = char_coll[j].char_bmap[k] & 0x2 ;
            output_array[i][7][j] = char_coll[j].char_bmap[k] & 0x1 ;
            //End Masking...
        } //End j loop
    }  //End i loop

   // This should probably work. Now you are presented with a array
   // which is 3-d and contains: [no_of_iterations][columns][columns]
} //End function

/**********************************************************************
 * plot_hex_horizontal
 * @param int hex_value
 * @param int start_x
 * @param int in_y
 * @param int color
 * @return void
 *********************************************************************/ 

void plot_hex_horizontal(int hex_value, int start_x, int in_y, int color){
    //Plots hex value directly using plot pixel
    if(hex_value & 0x80 ) putpixel(start_x, in_y, color); start_x++;
    if(hex_value & 0x40 ) putpixel(start_x, in_y, color); start_x++;
    if(hex_value & 0x20 ) putpixel(start_x, in_y, color); start_x++;
    if(hex_value & 0x10 ) putpixel(start_x, in_y, color); start_x++;
    if(hex_value & 0x8 ) putpixel(start_x, in_y, color); start_x++;
    if(hex_value & 0x4 ) putpixel(start_x, in_y, color); start_x++;
    if(hex_value & 0x2 ) putpixel(start_x, in_y, color); start_x++;
    if(hex_value & 0x1 ) putpixel(start_x, in_y, color); start_x++;
    //End function
}

/* Most probably unused! */ /* used it to increase size ;) (kidding) */
int* create_3d_array(int x, int y, int z){
int* a;
a = (int *) (malloc(x*y*z*sizeof(int)));
return a; //Hope it works!
}
