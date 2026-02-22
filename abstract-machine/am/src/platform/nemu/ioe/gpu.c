#include <am.h>
#include <nemu.h>

#define SYNC_ADDR (VGACTL_ADDR + 4)

#define HEIGHT_MASK 0x0000ffff
#define WIDTH_MASK 0xffff0000

static uint32_t screen_width = 0;
static uint32_t screen_height = 0;

void __am_gpu_init() {
  uint32_t vgactl = inl(VGACTL_ADDR);
  screen_width  = vgactl >> 16;
  screen_height = vgactl & HEIGHT_MASK;
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  *cfg = (AM_GPU_CONFIG_T){
    .present   = true,
    .has_accel = false,
    .width     = screen_width,
    .height    = screen_height,
    .vmemsz    = screen_width * screen_height * sizeof(uint32_t)
  };
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
  int x = ctl->x, y = ctl->y;
  int w = ctl->w, h = ctl->h;

  if (w == 0 || h == 0) {
    if (ctl->sync) outl(SYNC_ADDR, 1);
    return;
  }

  uint32_t *pixels = (uint32_t *)ctl->pixels;
  uint32_t base_offset = (y * screen_width + x) * sizeof(uint32_t);
  uint32_t row_stride = screen_width * sizeof(uint32_t);

  for (int i = 0; i < h; i++) {
    uint32_t ptr_offset = base_offset;
    for (int j = 0; j < w; j++) {
      outl(FB_ADDR + ptr_offset, pixels[i * w + j]);
      ptr_offset += sizeof(uint32_t);
    }
    base_offset += row_stride;
  }

  if (ctl->sync) {
    outl(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}

void __am_gpu_memcpy(AM_GPU_MEMCPY_T *ctl) {}
void __am_gpu_render(AM_GPU_RENDER_T *ctl) {}