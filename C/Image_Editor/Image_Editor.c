/*
Creed Jones

Summary:
Take in a picture and edit the picture
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Image_Editor.h"

int* importColors(void) {
    char filename[FILENAME_MAX]; 
    printf("Enter name of image file: ");
    scanf("%s", filename);
    FILE *file = fopen(filename, "r");

    char line[1000];

    //Since for the given images we do not need to track this line
    fgets(line, 1000, file); 

    //Get the picture size
    char *r, *c; 
    int row, col;
    fgets(line, 1000, file); 
    r = strtok(line, " ");
    c = strtok(NULL, " ");
    row = atoi(r);
    col = atoi(c);

    //Skip this line becuase the numbers are always the same for this project
    fgets(line, 1000, file); 

    //put each color number into the colors list
    int *colors = (int *) calloc((row * col * 3) + 2, sizeof(int));
    colors[0] = row;
    colors[1] = col;
    int count = 2;
    while (fgets(line, 1000, file) != NULL) {
        char *num = strtok(line, " ");
        while (num != NULL) {
            colors[count] = atoi(num);
            num = strtok(NULL, " ");
            count++; 
        }
    }
    fclose(file);
    return colors; 
}

int* negate_red(int colors[]) {
    for(int i = 2; i < (colors[0] * colors[1] * 3) + 2; i += 3) {
        colors[i] = 255 - colors[i];
    }
    return colors;
}

int* negate_green(int colors[]) {
    for(int i = 3; i < (colors[0] * colors[1] * 3) + 2; i += 3) {
        colors[i] = 255 - colors[i];
    }
    return colors;
}

int* negate_blue(int colors[]) {
    for(int i = 4; i < (colors[0] * colors[1] * 3) + 2; i += 3) {
        colors[i] = 255 - colors[i];
    }
    return colors;
}

int* flip_horizontal(int colors[]) {
    for(int r = 0; r < colors[1]; r++) { //For each row
        for(int c = 0; c < colors[0] / 2; c++) { //Split the row in 2 
            //get each pixel and the oppsite pixel starting locations
            int pixel1Start = ((colors[0]) * r * 3) + 2 + (c * 3);
            int pixel2Start = ((colors[0]) * (r + 1) * 3) - 1 - (c * 3);
            printf("%d %d\n", pixel1Start, pixel2Start);
            for(int i = 0; i < 3; i++) { //for each pixel flip all the values to the oppsite pixel
                int hold = colors[pixel1Start + i];
                colors[pixel1Start + i] = colors[pixel2Start + i];
                colors[pixel2Start + i] = hold;
            }
        }
    }
    return colors;
}

int* grey_scale(int colors[]) {
    for(int i = 2; i < (colors[0] * colors[1] * 3) + 2; i += 3) {
        int sum = 0;
        sum += colors[i];
        sum += colors[i + 1];
        sum += colors[i + 2];
        sum = sum / 3;
        colors[i] = sum;
        colors[i + 1] = sum;
        colors[i + 2] = sum; 
    }
    return colors;
}

int* flatten_red(int colors[]) {
    for(int i = 2; i < (colors[0] * colors[1] * 3) + 2; i += 3) {
        colors[i] = 0;
    }
    return colors;
}

int* flatten_green(int colors[]) {
    for(int i = 3; i < (colors[0] * colors[1] * 3) + 2; i += 3) {
        colors[i] = 0;
    }
    return colors;
}

int* flatten_blue(int colors[]) {
    for(int i = 4; i < (colors[0] * colors[1] * 3) + 2; i += 3) {
        colors[i] = 0;
    }
    return colors;
}

int* random_noise(int colors[]) {
    //Get range value
    int random_range;
    printf("Please enter a number between 0-255 for range of added num: ");
    scanf("%d", &random_range);
    for(int i = 2; i < (colors[0] * colors[1] * 3) + 2; i++) {
        //Here we are doubling the range so we can get the negative numbers
        int random_num = (rand() % (random_range * 2)) - random_num;
        if(colors[i] + random_num > 255) {
            colors[i] = 255;
        } else if (colors[i] + random_num < 0) {
            colors[i] = 0;
        } else {
            colors[i] += random_num; 
        }
    }
    return colors;
}

int* extreme_contrast(int colors[]) {
    for(int i = 2; i < (colors[0] * colors[1] * 3) + 2; i++) {
        if(colors[i] > 128) {
            colors[i] = 255;
        } else {
            colors[i] = 0; 
        }
    }
    return colors; 
}

void exitProgram(int colors[]) {
    char filename[FILENAME_MAX]; 
    printf("\nEnter name of output file: ");
    scanf("%s",  filename);
    FILE *file = fopen(filename, "w");
    fprintf(file, "P3\n%d %d\n255", colors[0], colors[1]);
    for(int i = 2; i < (colors[0] * colors[1] * 3) + 2; i++) {
        if((i - 2) % (colors[0] * 3) == 0) {
            fprintf(file, "\n%d ", colors[i]);
        } else {
            fprintf(file, "%d ", colors[i]);
        }
    }
    fclose(file);
    printf("\nFile created\nHave a good day!\n");
}