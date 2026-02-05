#include <gpiod.h>
#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>



int main() {
    std::cout <<"Initializing chip program\n";
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
    unsigned int offset = 17;

    std::cout << label << std::endl;
    gpiod_line_settings *settings = gpiod_line_settings_new();
    gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_INPUT);
    gpiod_line_settings_set_bias(settings, GPIOD_LINE_BIAS_PULL_DOWN);

    gpiod_line_config *config = gpiod_line_config_new();
    gpiod_line_config_add_line_settings(config, &offset, 1, settings);

    gpiod_request_config *req_cfg = gpiod_request_config_new();
    gpiod_request_config_set_consumer(req_cfg, "poll-reader");

    gpiod_line_request *request =gpiod_chip_request_lines(chip, req_cfg, config);

    int value = gpiod_line_request_get_value(request, offset);

    gpiod_line_info* line = gpiod_chip_get_line_info(chip,17);
    while (true){
        value =gpiod_line_request_get_value(request, offset);
        std::cout<< value <<"\n";
        if (value<0){
            std::cout<<"Error reading the line\n";
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

    }
    std::cout<<"line info value: \n" << line;
    if (!line){
        return EXIT_FAILURE;
    }
    gpiod_line_request_release(request);
    gpiod_request_config_free(req_cfg);
    gpiod_line_config_free(config);
    gpiod_line_settings_free(settings);

    gpiod_line_info_free(line);
    gpiod_chip_info_free(chip_info);
    gpiod_chip_close(chip);

    return EXIT_SUCCESS;
}
