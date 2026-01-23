#include <gpiod.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(){
    struct gpiod_chip *chip= gpiod_chip_open("/dev/gpiochip0");
    struct gpiod_line *line;
    if (chip==NULL){
        printf("cant open gpio chip");
        return 1;
    }
    printf("opened gpio chip\n");
    struct gpiod_chip_info *chip_info = gpiod_chip_get_info(chip);
    if (!chip_info){
        printf("chip info is null");
        return 1;
    }
    const char *label = gpiod_chip_info_get_label(chip_info);
    if (!label){
        printf("label is null");
        return 1;
    }
    printf("%s\n",label);
    gpiod_chip_info_free(chip_info);
    gpiod_chip_close(chip);
}