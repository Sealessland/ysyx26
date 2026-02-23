#include <am.h>
#include <nemu.h>
#include <stdint.h> // 需要引入此头文件使用 uint32_t 和 uintptr_t

#define SYNC_ADDR (VGACTL_ADDR + 4)
#define HEIGHT_MASK 0x0000ffff

// 全局缓存屏幕宽度，消除每帧读取 MMIO 的总线开销
static int screen_w = 0;

void __am_gpu_init() {
  screen_w = inl(VGACTL_ADDR) >> 16;
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  uint32_t info = inl(VGACTL_ADDR);
  cfg->present = true;
  cfg->has_accel = false;
  cfg->width = info >> 16;
  cfg->height = info & HEIGHT_MASK;
  cfg->vmemsz = cfg->width * cfg->height * sizeof(uint32_t);
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
  int x = ctl->x, y = ctl->y, w = ctl->w, h = ctl->h;
  if (w == 0 || h == 0) goto sync_check;

  uint32_t *pixels = (uint32_t *)ctl->pixels;
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;

  // 核心优化1：外层按行遍历，内层全指针操作，彻底消灭乘法 ALU 运算
  for (int i = 0; i < h; i++) {
    // 预计算当前行的源和目的首地址
    uint32_t *dst = fb + ((y + i) * screen_w + x);
    uint32_t *src = pixels + (i * w);
    int n = w;

    // 核心优化2：8路循环展开 (8-way Loop Unrolling)
    // 打破内层循环导致的分支预测失败，极大提升处理器流水线吞吐量
    // n >> 3 等价于 n / 8，位运算更快
    int blocks = n >> 3; 
    while (blocks > 0) {
      dst[0] = src[0];
      dst[1] = src[1];
      dst[2] = src[2];
      dst[3] = src[3];
      dst[4] = src[4];
      dst[5] = src[5];
      dst[6] = src[6];
      dst[7] = src[7];
      
      dst += 8;
      src += 8;
      blocks--;
    }

    // 核心优化3：尾部收尾，处理宽度不是 8 的倍数时剩下的零碎像素
    // n & 7 等价于 n % 8
    int rem = n & 7; 
    while (rem > 0) {
      *dst++ = *src++;
      rem--;
    }
  }

sync_check:
  // 核心优化4（Bug修正）：必须在所有像素数据写入总线完成后，再发送屏幕刷新同步信号
  if (ctl->sync) {
    outl(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}