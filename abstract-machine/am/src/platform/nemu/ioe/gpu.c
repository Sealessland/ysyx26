#include <am.h>
#include <nemu.h>
#include<string.h>
#define SYNC_ADDR (VGACTL_ADDR + 4)

void __am_gpu_init() {
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width = 0, .height = 0,
    .vmemsz = 0
  };
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
  int x = ctl->x, y = ctl->y, w = ctl->w, h = ctl->h;
  uint32_t *pixels = ctl->pixels;
  uint32_t *fb = (uint32_t *)FB_ADDR;
  for (int i = 0; i < h; i++) {
    uint32_t *dst = fb + (y + i) * 400 + x;
    uint32_t *src = pixels + i * w;
    memcpy(dst, src, w * sizeof(uint32_t));
  } 
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
