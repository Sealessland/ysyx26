package sCore.utils

import chisel3._

// -----------------------------------------------------------------------------
// 1. 定义细粒度的子配置 (按模块划分，避免一个类里有上百个参数)
// -----------------------------------------------------------------------------
case class FrontendConfig(
  fetchWidth: Int = 1,
  btbEntries: Int = 32,
  bpdType: String = "NONE",
  fetchMode: String = "dpi" // "dpi", "sramLite", "sram", "cache", "axiLite"
)

case class LsuConfig(
  lsuMode: String = "dpi" // "dpi", "axiLite", "axi4"(single-beat via AXI-Lite), "cache"
)


case class CoreConfig(
  xlen: Int = 32,             // 体系结构位宽
  vaddrBits: Int = 32,        // 虚拟地址位宽
  paddrBits: Int = 32,        // 物理地址位宽
  hasFPU: Boolean = false,     // 是否包含浮点单元 (F extension)
  hasRVC: Boolean = false,     // 是否支持压缩指令 (C extension)
  hasM: Boolean = false,       // 是否支持乘除法扩展 (M extension)
  hasA: Boolean = false,       // 是否支持原子指令扩展 (A extension)
  hasZicsr: Boolean = true,    // 是否支持 CSR 指令
  fastMdu: Boolean = true,     // 是否使用单周期组合逻辑乘除法单元
  isSingleCycle: Boolean = false, // 是否为单周期设计 (验证用)
  isMultiCycle: Boolean = true,   // 是否为严格握手的多周期设计 (只有一条指令流动)
  frontend: FrontendConfig = FrontendConfig(),
  lsu: LsuConfig = LsuConfig()
) {
  // 可以利用 require 做参数的编译期合法性检查
  require(xlen == 32 || xlen == 64, "XLEN must be 32 or 64")
  require(frontend.fetchWidth >= 1 && frontend.fetchWidth <= 8, "Fetch width must be bounded")
}

// -----------------------------------------------------------------------------
// 3. 特征混入 (Trait)，用于解包参数
// -----------------------------------------------------------------------------
trait HasCoreParams {
  // 要求混入此特质的类必须得有隐式参数 p
  implicit val p: CoreConfig

  // 将常用参数提取出来，子类直接用 `xlen` 即可，不用写 `p.xlen`
  val xlen          = p.xlen
  val vaddrBits     = p.vaddrBits
  val paddrBits     = p.paddrBits
  val hasFPU        = p.hasFPU
  val hasRVC        = p.hasRVC
  val hasM          = p.hasM
  val hasA          = p.hasA
  val hasZicsr      = p.hasZicsr
  val fastMdu       = p.fastMdu
  val isSingleCycle = p.isSingleCycle
  val isMultiCycle  = p.isMultiCycle
  
  // 衍生参数计算，一处定义，到处使用
  val instBytes = if (p.hasRVC) 2 else 4
  val xLenBytes = xlen / 8
}

// -----------------------------------------------------------------------------
// 4. 定义统一的基础 Module 和 Bundle
// -----------------------------------------------------------------------------
/** 所有 CPU 内部模块的基类，自动带有配置项 */
abstract class CoreModule(implicit val p: CoreConfig) extends Module with HasCoreParams

/** 所有 CPU 内部 Bundle 的基类，例如 IO 接口 */
abstract class CoreBundle(implicit val p: CoreConfig) extends Bundle with HasCoreParams
