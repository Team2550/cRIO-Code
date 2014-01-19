#include "libfreenect.h"

freenect_context *f_ctx;
freenect_device *f_dev;

uint8_t *rgb_back;

int main()
{
	rgb_back = (uint8_t*)malloc(640*488*3);
	freenect_init(&f_ctx, NULL);
	freenect_set_log_level(f_ctx, FREENECT_LOG_DEBUG);
	Int nr_devices = freenect_num_devices (f_ctx);
	int user_device_number = 0;
	freenect_open_device(f_ctx, &f_dev, user_device_number);
	freenect_set_led(f_dev, LED_RED);
	return 0;
}
