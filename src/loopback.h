#ifndef LOOPBACK_H
#define LOOPBACK_H

#ifdef __cplusplus
extern "C" {
#endif

#if(0)
	// for kit's video cam
	// #ifndef CAP_WIDTH
	// 		#define CAP_WIDTH 800
	// #endif
	// #ifndef CAP_HEIGHT
	// 		#define CAP_HEIGHT 600
	// #endif
#else
	// for brd or bkoi
	#ifndef CAP_WIDTH
		#define CAP_WIDTH 704
	#endif
	#ifndef CAP_HEIGHT
		#define CAP_HEIGHT 280
	#endif
#endif
#ifndef PIP_POS_X
	#define PIP_POS_X  25
#endif
#ifndef PIP_POS_Y
	#define PIP_POS_Y  25
#endif

#define NUM_OF_CAMS 			(4)

struct control
{
    unsigned int main_cam;
    unsigned int num_cams;
    unsigned int num_jpeg;
    unsigned int display_xres, display_yres;
    bool pip;
    bool jpeg;
    bool exit;
    bool use_cmem;
};

extern struct control status;

int init_loopback(void);
void process_frame(void);
void end_streaming(void);
void exit_devices(void);
void drm_disable_pip(void);
void drm_enable_pip(void);
void set_plane_properties(void);

#ifdef __cplusplus
}
#endif

#endif // LOOPBACK_H
