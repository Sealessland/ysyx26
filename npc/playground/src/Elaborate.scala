import sCore.CoreTop
import sCore.utils.CoreConfig

object Elaborate extends App {
  val firtoolOptions = Array(
    "--lowering-options=" + List(
      // make yosys happy
      // see https://github.com/llvm/circt/blob/main/docs/VerilogGeneration.md
      "disallowLocalVariables",
      "disallowPackedArrays",
      "locationInfoStyle=wrapInAtSquareBracket"
    ).reduce(_ + "," + _)
  )

  implicit val config: CoreConfig = CoreConfig(
    hasM = true,
    fastMdu = true,
    hasZicsr = true
  )

  // 2. 生成主要模块的Verilog代码
  circt.stage.ChiselStage.emitSystemVerilogFile(new CoreTop(), args, firtoolOptions)
}
