/*
Creed Jones

Summary:
Take in a picture and edit the picture
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* importColors() {
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

}

int* negate_green(int colors[]) {

}

int* negate_blue(int colors[]) {

}

int* flip_horizontal(int colors[]) {

}

int* grey_scale(int colors[]) {

}

int* flatten_red(int colors[]) {

}

int* flatten_green(int colors[]) {

}

int* flatten_blue(int colors[]) {

}

int* random_noise(int colors[]) {

}

int* extreme_contrast(int colors[]) {

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

void progam() {
    int* picture = importColors();
    int run = 1;
    do {
        int choice;
        printf("\n\nHere are your choices:\n[0] exit\n[1] convert to greyscale\n[2] flip horizontally\n[3] negative of red\n[4] negative of green\n[5] negative of blue\n[6] just the reds\n[7] just the greens\n[8] just the blues\n[9] extreme contrast\n[10] add random noise\n\nEnter choice: ");
        scanf("%i", &choice);
        switch(choice) {
            case 0:
                run = 0; 
                exitProgram(picture);
                break;
            case 1:
                picture = negate_red(picture);
                break;
            case 2:
                picture = negate_green(picture);
                break;
            case 3:
                picture = negate_blue(picture);
                break;
            case 4:
                picture = flip_horizontal(picture);
                break;
            case 5:
                picture = grey_scale(picture);
                break;
            case 6:
                picture = flatten_red(picture);
                break;
            case 7:
                picture = flatten_green(picture);
                break;
            case 8:
                picture = flatten_blue(picture);
                break;
            case 9:
                picture = extreme_contrast(picture);
                break;
            case 10:
                picture = random_noise(picture);
                break;
            default:
                printf("Invalid input\n");
        } 
    } while(run == 1);
}

void main() {
    progam();
} 