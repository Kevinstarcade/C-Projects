#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pixel {
    int r, g, b;
};

struct pixel *readPixel() {
    struct pixel *p = malloc(sizeof(struct pixel));
    scanf("%d %d %d", &(p->r), &(p->g), &(p->b));
    // printf("r:%d, b:%d, g:%d", p->r, p->g, p->b);
    return p;
}

void flipPic(struct pixel **pic, int width, int height) {
    struct pixel tempP;
    for (int h = 0; h < height; ++h) {
        for (int w = 0; w < width/2; ++w) {
            tempP = *pic[h*width+w];
            *pic[h*width+w] = *pic[h*width+(width-1-w)];
            *pic[h*width+(width-1-w)] = tempP;  
        }
    }
}

// int roundNum(float num) {
//     if (num - (int) num >= 0.5) return (int) num + 1;
//     return (int) num;
// }

void applySepia(struct pixel **pic, int width, int height) {
    for (int i = 0; i < width*height; ++i) {
        int newRed = (pic[i]->r*0.393 + pic[i]->g*0.769 + pic[i]->b*0.189)/1;
        if (newRed > 255) newRed = 255;

        int newGreen = (pic[i]->r*0.349 + pic[i]->g*0.686 + pic[i]->b*0.168)/1;
        if (newGreen > 255) newGreen = 255;

        int newBlue = (pic[i]->r*0.272 + pic[i]->g*0.534 + pic[i]->b*0.131)/1;
        if (newBlue > 255) newBlue = 255;

        pic[i]->r = newRed;
        pic[i]->g = newGreen;
        pic[i]->b = newBlue;
    }
}

void printPicture(struct pixel **pic, int width, int height) {
    for (int h = 0; h < height; ++h) {
        for (int w = 0; w < width; ++w) {
            printf("%d %d %d ", pic[h*width + w]->r, pic[h*width + w]->g, pic[h*width + w]->b);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    char format[2];
    int width;
    int height;
    int maxVal;
    scanf("%s %d %d %d", format, &width, &height, &maxVal);

    struct pixel **pic = malloc(sizeof(struct pixel)*width*height);
    for (int i = 0; i < width*height; ++i) {
        struct pixel *p = readPixel();
        pic[i] = p;
    }

    char flip[] = "-f";
    char sepia[] = "-s";

    for (int c = 0; c < argc; ++c) if (strcmp(argv[c], flip) == 0) flipPic(pic, width, height);
    for (int c = 0; c < argc; ++c) if (strcmp(argv[c], sepia) == 0) applySepia(pic, width, height);

    // print header then pixels
    printf("%c%c\n%d %d\n%d\n", format[0], format[1], width, height, maxVal);
    printPicture(pic, width, height);

    for (int i = 0; i < width*height; ++i) {
        free(pic[i]);
    }
    free(pic);
}
