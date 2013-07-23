/*********************************************************
 * writebm.c 
 * writes bitmap in files (not standard bitmap) 
 * 
 * @version 1.0.0
 * @author Nootan Ghimire <nootan.ghimire@gmail.com>
 * 
 ********************************************************/ 


//Includes
#include<stdio.h>
#include<conio.h> //used for getch()

//Structure defination
typedef struct {
  int char_id;            // Char_id
  int char_bmap[16];  // The real character bitmap
  } xbmp;

/*****************************************
 * main
 * @params none
 * @return void
 *****************************************/ 
 
void main() {
  FILE *fp;
  int maxlen, i, j;   //MaxLength and legacy counters :)
  xbmp myBitmap;

  printf("\n\t\t\tBitmap Writer\n\t\t\t=============\n\n");

  printf(" Enter No. Of Characters you want to write ");

  scanf("%d",&maxlen);

  fp = fopen("test.xbmp","ab");

    for(i = 0; i<maxlen; i++) {
        printf("\n |||Entering For Character %d|||\n\n", i+1);
        myBitmap.char_id = i; //Assigning Our Own Char id :D
        printf("Enter Character Bitmap Now::::");
        for(j=0; j<=15; j++) { //This is understandable, aye?
        printf("\nEnter Hex (in 0x00 format) For Row %d: ", j+1);
        scanf("%x",&myBitmap.char_bmap[j]);
        } //End j loop

   fwrite(&myBitmap, sizeof(myBitmap), 1, fp);

   printf("\n----------File Append Complete-------\n");

   } //End i loop

  fclose(fp); //close a file
  getch();
}
