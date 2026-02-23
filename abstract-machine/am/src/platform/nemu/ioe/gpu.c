#include <am.h>
#include <nemu.h>
#include <string.h> // 引入 memcpy

#define SYNC_ADDR (VGACTL_ADDR + 4)
static int screen_w = 0;

void __am_gpu_init() {
  screen_w = inl(VGACTL_ADDR) >> 16;
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  uint32_t info = inl(VGACTL_ADDR);
  cfg->present = true;
  cfg->has_accel = false;
  cfg->width  = info >> 16;
  cfg->height = info & 0xffff;
  cfg->vmemsz = cfg->width * cfg->height * sizeof(uint32_t);
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
  int x = ctl->x, y = ctl->y, w = ctl->w, h = ctl->h;
  if (w == 0 || h == 0) goto sync_check;

  uint32_t *pixels = (uint32_t *)ctl->pixels;
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;

  // 按行进行整块内存拷贝
  for (int i = 0; i < h; i++) {
    uint32_t *dst = fb + ((y + i) * screen_w + x);
    uint32_t *src = pixels + (i * w);
    // 核心：直接交由 memcpy 处理单行的像素搬运
    memcpy(dst, src, w * sizeof(uint32_t));
  }

sync_check:
  // 保持修复后的时序：画完再同步
  if (ctl->sync) {
    outl(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}