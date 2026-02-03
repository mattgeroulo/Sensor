#include <gpiod.h>
#include <iostream>
#include <cstdlib>

int main() {
    gpiod_chip* chip = gpiod_chip_open("/dev/gpiochip0");
    if (!chip) {
        std::cerr << "can't open gpio chip\n";
        return EXIT_FAILURE;
    }

    std::cout << "opened gpio chip\n";

    gpiod_chip_info* chip_info = gpiod_chip_get_info(chip);
    if (!chip_info) {
        std::cerr << "chip info is null\n";
        gpiod_chip_close(chip);
        return EXIT_FAILURE;
    }

    const char* label = gpiod_chip_info_get_label(chip_info);
    if (!label) {
        std::cerr << "label is null\n";
        gpiod_chip_info_free(chip_info);
        gpiod_chip_close(chip);
        return EXIT_FAILURE;
    }

    std::cout << label << std::endl;

    gpiod_chip_info_free(chip_info);
    gpiod_chip_close(chip);

    return EXIT_SUCCESS;
}
